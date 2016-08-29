///////////////////////////////////////////////////////////////////////////
// Receiver.cpp -Provides receiver functionalities  for client and server// 
// Ver 1.0																 //
// Application: Project #4 Dependency-Based Remote Code Repository       //
// Language:    C++, Visual Studio 2015									 //
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10					 //
// Author:      Achal Velani, SUID:292190387							 //
// Reference:   Jim Fawcett, CST 4-187, Syracuse University				 //
//              (315) 443-3948, jfawcett@twcny.rr.com					 //
///////////////////////////////////////////////////////////////////////////

#include "Receiver.h"

// This function will help in creating reply message by swapping the sender and receiver ports
void swapAddressPort(HttpMessage &msg){
	std::string temp = msg.sourceAddress;
	msg.sourceAddress = msg.destAdd;
	msg.destAdd = temp;
	int tempPort = msg.senderPort;
	msg.senderPort = msg.destPort;
	msg.destPort = tempPort;
}

// This function helps in reading data from buffer of socket
bool Receiver::bufferReading(Socket& socket_, int size, Socket::byte* buffer){
	bool ok;
	if (socket_.bytesWaiting() == 0)
		return true;
	ok = socket_.recv(size, buffer);
	if (socket_ == INVALID_SOCKET || !ok)
		return false;
	return true;
}

//This will return all the packages in the repository
std::vector<std::string> Receiver::repositoryPackages()
{
	std::vector<std::string> packages= FileSystem::Directory::getDirectories(REPOPATH, "*");
	return packages;
}

//This function will be used to handel writes of checkins and extracts 
bool Receiver::fileWrite(Socket& socket, HttpMessage& rcvmessage, std::string filePath)
{
	bool flag = false;
	Socket::byte buffer[BUFFER_SIZE];
	std::ofstream* outFile = new std::ofstream;
	outFile->open(filePath, std::ios::out | std::ios::binary);
	if (outFile->is_open()){
		int size = rcvmessage.contentLength;
		bufferReading(socket, size, buffer);
		outFile->write(buffer, size);
		if (rcvmessage.command == UPLOAD_COMPLETED || rcvmessage.command == DOWNLOAD_COMPLETED){
			flag = true;
			if (outFile){
				outFile->close();
				outFile = nullptr;
			}
		}
		while (!flag){
			std::string command = socket.recvString();
			if (command.size() == 0)
				break;
			rcvmessage = rcvmessage.parseMessage(command);
			size = rcvmessage.contentLength;
			bufferReading(socket, size, buffer);
			outFile->write(buffer, size);
			if (rcvmessage.command == UPLOAD_COMPLETED || rcvmessage.command == DOWNLOAD_COMPLETED){
				flag = true;
				if (outFile){
					outFile->close();
					outFile = nullptr;
				}
			}
		}
	}
	else
		std::cout<<"\n---- File cannot be opened, could be an issue of file path. ----\n";
	return flag;
}

//This function wil help in getting the file name out of the whole path
std::string getFileName(std::string path){
	std::string filename;
	size_t pos = path.find_last_of("//");
	if (pos != std::string::npos)
		filename.assign(path.begin() + pos + 1, path.end());
	else{
		pos = path.find_last_of("\\");
		if (pos != std::string::npos)
			filename.assign(path.begin() + pos + 1, path.end());
		else
			filename = path;
	}
	return filename;
}

//This function will help in uploading more than one files simultaneously.
//This function is not in working condition, might be fixed in coming versions.
bool Receiver::multipleFileUpload(Socket & socket_, HttpMessage & rcvmessage){
	std::string temp = rcvmessage.fileName;
	std::string onlyFileName = getFileName(temp);
	std::string packageName = onlyFileName.substr(0, onlyFileName.find(".", 0));
	std::string path = "../Repository/";
	path.append(packageName);
	path.append("/");

	std::vector<std::string> versions = FileSystem::Directory::getDirectories(path);
	std::sort(versions.begin(), versions.end());
	path.append(versions.back());
	path.append("/");
	metadataFactory mf1;
	std::string xmlfilename = mf1.extractPackageName(onlyFileName);
	xmlfilename.append(".xml");
	path.append(xmlfilename);
	XmlDocument test = mf1.readXmlFile(path);
	std::vector <std::string> dependsOn = mf1.readDependecies(&test);
	std::cout << "\n-----------=====================--------------------\n";
	if (rcvmessage.command == DOWNLOAD_WITH_DEP_COMPLETED || rcvmessage.command == DOWNLOAD_WITH_DEP_STARTED)
	{
		std::cout << "\nDOWNLOAD MULTIPLE FILE FROM REPO:\n";
		temp = "../ClientDownload/";
		if (FileSystem::Directory::exists(temp) == false)
		{
			FileSystem::Directory::create(temp);
		}
		temp.append(onlyFileName);
	}
	return false;
}


// This function will help in creating xml for uploaded files as well as generating required httpMessages it will
// call the file writer function.
bool Receiver::fileUpload(Socket& socket, HttpMessage& rcvmessage, bool upload)
{
	bool flag = false;
	std::string temp = rcvmessage.fileName;
	std::string onlyFileName = getFileName(temp);
	if (rcvmessage.command == UPLOAD_COMPLETED || rcvmessage.command == UPLOAD_STARTED)
	{
		temp = whichDiectory(onlyFileName);
		metadataFactory mf;
		XmlDocument xd = mf.createMetadata(rcvmessage, rcvmessage.dependancies);
		mf.createXmlFile(&xd, temp);
		
	}
	else if (rcvmessage.command == DOWNLOAD_COMPLETED || rcvmessage.command == DOWNLOAD_STARTED)
	{
		std::cout << std::endl << "\n--- DOWNLOAD FROM REPOSITORY ---\n" << std::endl;
		std::cout << "\nCLIENT ADDRESS:";
		std::cout << rcvmessage.sourceAddress << ":" << rcvmessage.senderPort << std::endl;
		temp = "../ClientDownload/";
		if (FileSystem::Directory::exists(temp) == false)
		{
			FileSystem::Directory::create(temp);
		}
		temp.append(onlyFileName);
	}
	flag = fileWrite(socket, rcvmessage, temp);
	return flag;
}

// This function will provide functionalities for getting current datetime stamp to generate versions.
std::string Receiver::getCurrentDateTime(){
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%F_%H_%M_%S", &timeinfo);
	return buffer;
}

//This function will return all the packages in a vector, this will be used in decoding the received repo package 
//request, whicg wil have all the packages in message's body with ":" seperator.
std::vector<std::string> Receiver::setPackages(std::string rcvString )
{
	std::vector<std::string> returnVector;
	std::string input = rcvString;
	std::istringstream ss(input);
	std::string token;
	while (std::getline(ss, token, ':')) {
		returnVector.push_back(token);
	}
	return returnVector;
}

// This function will be called by directory determining function when no repository exsists.
std::string Receiver::directoryHelper1(std::string temp, std::string filename, std::string onlyFileName){
	FileSystem::Directory::create(temp);
	temp.append(filename);
	temp.append("/");
	FileSystem::Directory::create(temp);
	temp.append(getCurrentDateTime());
	FileSystem::Directory::create(temp);
	temp.append("/");
	std::cout << "\n" << temp << std::endl;
	temp.append(onlyFileName);
	return temp;
}

// This function will help in deciding the directory for the file being checked in
std::string Receiver::whichDiectory(std::string onlyFileName){
	std::string filename = onlyFileName.substr(0, onlyFileName.find(".", 0));
	std::string temp = "../Repository/";
	std::string temp1 = temp;
	temp1.append(filename); temp1.append("/");
	if (FileSystem::Directory::exists(temp) == false){ 			//CASE 1: if no repo exisists
		return directoryHelper1(temp, filename, onlyFileName);
	}
	else if (FileSystem::Directory::exists(temp1) == false){	//CASE 2: if no package for specified file name exsists
		FileSystem::Directory::create(temp1);
		temp1.append(getCurrentDateTime()); temp1.append("/");
		FileSystem::Directory::create(temp1);
		temp1.append(onlyFileName);
		return temp1;
	}
	else{														//CASE 3: package folder exsists but no directories
		std::vector<std::string> versionsInPackage = FileSystem::Directory::getDirectories(temp1);
		std::sort(versionsInPackage.begin(), versionsInPackage.end());
		if (versionsInPackage.size() == 0){						//SUBCASE: If no previous versions exsists.
			std::cout << "\n No Versions Exists";
			temp1.append(getCurrentDateTime()); temp1.append("/");
			FileSystem::Directory::create(temp1);
			temp1.append(onlyFileName);
			return temp1;
		}
		else{													//SUBCASE: Check if package is open or closed to 
			std::string check = temp1;							//         choose appropiate path
			check.append(versionsInPackage.back());	check.append("/");
			metadataFactory mf1;
			std::string xmlfilename = mf1.extractPackageName(onlyFileName);
			xmlfilename.append(".xml");
			std::string vercheck = check;
			vercheck.append(xmlfilename);
			XmlDocument test = mf1.readXmlFile(vercheck);
			std::string status = mf1.readStatus(&test);
			if (status == CLOSED){
				temp1.append(getCurrentDateTime());
				temp1.append("/");
				FileSystem::Directory::create(temp1);
				temp1.append(onlyFileName);
				return temp1;
			}
			check.append(onlyFileName);
			return check;
		}
	}
}

// This function will help in creating proper http message as well as call fileupload function to handel download requests.
void Receiver::fileDownloadHandler(Socket& socket_, HttpMessage& rcvmessage)
{
	if (rcvmessage.command == DOWNLOAD_REQUEST){
		rcvmessage.command = DOWNLOAD_REQUEST;
		Utilities::StringHelper::title("\n--- File download request has been received by " + rcvmessage.sourceAddress + ":" + std::to_string(rcvmessage.senderPort));
		swapAddressPort(rcvmessage);
		std::string message = rcvmessage.createHeaderMessage(rcvmessage);
		serverqueue.enQ(message);
	}
	else if (rcvmessage.command == DOWNLOAD_STARTED || rcvmessage.command == DOWNLOAD_COMPLETED && rcvmessage.fileName.size() > 0){
		std::string fileName = rcvmessage.fileName;
		if (fileUpload(socket_, rcvmessage,false)){
			std::string onlyFileName = getFileName(fileName);
			rcvmessage.command = DOWNLOAD_ACK;
			std::string message = rcvmessage.createHeaderMessage(rcvmessage);
			serverqueue.enQ(message);
			Utilities::StringHelper::title("\n--- File downloaded from " + rcvmessage.sourceAddress + ":" + std::to_string(rcvmessage.senderPort));
		}
		else
			Utilities::StringHelper::title("\n--- File download failed ");
	}
}

// This function is written in intent with downloading more than one file. It is not implemented properly
// but will be implemented in coming versions.
void Receiver::multipleFileDownloadHandeler(Socket & socket_, HttpMessage & rcvMessage)
{
	if (rcvMessage.command == DOWNLOAD_WITH_DEP_REQ)
	{
		Utilities::StringHelper::title(" File download request with dependencies has been received by " + rcvMessage.sourceAddress + ":" + std::to_string(rcvMessage.senderPort));
		swapAddressPort(rcvMessage);
		std::string message = rcvMessage.createHeaderMessage(rcvMessage);
		serverqueue.enQ(message);
	}
	else if (rcvMessage.command == DOWNLOAD_WITH_DEP_STARTED || rcvMessage.command == DOWNLOAD_WITH_DEP_COMPLETED && rcvMessage.fileName.size() > 0)
	{
		std::string fileName = rcvMessage.fileName;
		if (fileUpload(socket_, rcvMessage, false))
		{
			std::string onlyFileName = getFileName(fileName);
			rcvMessage.command = DOWNLOAD_ACK;
			std::string message = rcvMessage.createHeaderMessage(rcvMessage);
			serverqueue.enQ(message);
			Utilities::StringHelper::title(" File downloaded from " + rcvMessage.sourceAddress + ":" + std::to_string(rcvMessage.senderPort));
		}
		else
			Utilities::StringHelper::title(" File download failed ");
	}
}

//This function will handel the request of repository package request.
void Receiver::directoryRequestHandler(Socket & socket_, HttpMessage & rcvMessage){
	if (rcvMessage.command == GETPACKAGES_REQUEST){
		swapAddressPort(rcvMessage);
		rcvMessage.command = GETPACKAGES_RESPONSE;
		std::vector<std::string> packages = repositoryPackages();
		std::string package;
		bool  first = false;
		for (std::string p : packages){
			if(first == true){
				package.append(p);
				package.append(":");
			}
			first = true;
		}
		rcvMessage.body = package;
		std::string message = rcvMessage.createHeaderMessage(rcvMessage);
		serverqueue.enQ(message);
		std::cout << "\nRepository Packages are sent to" << rcvMessage.destAdd << std::to_string(rcvMessage.destPort) << "\n";
		std::cout << "\n And files in Rep are:\n" << rcvMessage.body;
	}
	else if(rcvMessage.command == GETPACKAGES_RESPONSE){
		std::string temp = "\n-- Files in repository are: " + rcvMessage.body +"\n--- From receiverPort:"+ rcvMessage.sourceAddress + ":" + std::to_string(rcvMessage.senderPort) + "\n";
		_RepoPackages = setPackages(rcvMessage.body);
		std::string message = rcvMessage.createHeaderMessage(rcvMessage);
		serverqueue.enQ(message);
	}
}

//This function will handel the request for shutting down the server.
void Receiver::serverShutDownHandler(Socket & socket_, HttpMessage & rcvMessage){
	swapAddressPort(rcvMessage);
	rcvMessage.command = SHUTDOWN_SERVER;
	std::string message = rcvMessage.createHeaderMessage(rcvMessage);
	serverqueue.enQ(message);
}

//This function will handel all the requests for file upload handelings.
void Receiver::fileUploadHandler(Socket& socket_, HttpMessage& rcvMessage){
	if ((rcvMessage.command == UPLOAD_STARTED || rcvMessage.command == UPLOAD_COMPLETED) && rcvMessage.fileName.size() > 0){
		std::string fileName = rcvMessage.fileName;
		if (fileUpload(socket_, rcvMessage,true)){
			std::string onlyFileName = getFileName(fileName);
			std::string temp = "\n--- " + onlyFileName + " is uploaded Successfully at " + rcvMessage.sourceAddress + ":" + std::to_string(rcvMessage.senderPort) + "\n";
			std::cout << temp;
			swapAddressPort(rcvMessage);
			rcvMessage.command = UPLOAD_ACK;
			std::string message = rcvMessage.createHeaderMessage(rcvMessage);
			serverqueue.enQ(message);
		}
		else
			std::cout<<" File upload failed ";
	}
	else if ((rcvMessage.command == UPLOAD_ACK)) { // get files
		std::string temp = "\n--- " + rcvMessage.fileName + " is uploaded Successfully at " + rcvMessage.sourceAddress + ":" + std::to_string(rcvMessage.senderPort) + "\n";
		std::cout << temp;
		std::string message = rcvMessage.createHeaderMessage(rcvMessage);
		serverqueue.enQ(message);
	}
}

// This is a helper function for the functor operator 
void Receiver::operatorHelper1(Socket & socket_, HttpMessage rcvMessage)
{
	if (rcvMessage.command == UPLOAD_STARTED || rcvMessage.command == UPLOAD_COMPLETED || rcvMessage.command == UPLOAD_ACK) {
		fileUploadHandler(socket_, rcvMessage);
	}
	else 
		directoryRequestHandler(socket_, rcvMessage);
}

// This is a helper function for the functor operator 
void Receiver::operatorHelper2(Socket & socket_, HttpMessage rcvMessage)
{
	if (rcvMessage.command == DOWNLOAD_REQUEST || rcvMessage.command == DOWNLOAD_STARTED || rcvMessage.command == DOWNLOAD_COMPLETED || rcvMessage.command == EXTRACT_WO_DEP) {
		fileDownloadHandler(socket_, rcvMessage);
	}
	else
		serverShutDownHandler(socket_, rcvMessage);
}

// This is the functor for the Reciver class and will be called by the socket in the listning mode.
void Receiver::operator()(Socket & socket_){
	std::string command;
	while (true){
		command = socket_.recvString();
		if (command.size() == 0)
			break;
		HttpMessage rcvMessage;
		rcvMessage = rcvMessage.parseMessage(command);
		if (rcvMessage.command == UPLOAD_STARTED || rcvMessage.command == UPLOAD_COMPLETED || rcvMessage.command == UPLOAD_ACK|| rcvMessage.command == GETPACKAGES_REQUEST || rcvMessage.command == GETPACKAGES_RESPONSE){
			operatorHelper1(socket_, rcvMessage);
			continue;  // go back and get another command
		}
		else if (rcvMessage.command == DOWNLOAD_REQUEST || rcvMessage.command == DOWNLOAD_STARTED || rcvMessage.command == DOWNLOAD_COMPLETED||rcvMessage.command == EXTRACT_WO_DEP || rcvMessage.command == SHUTDOWN_SERVER){
			operatorHelper2(socket_, rcvMessage);
			continue;
		}
		else if(rcvMessage.command == DOWNLOAD_WITH_DEP_REQ|| rcvMessage.command == DOWNLOAD_WITH_DEP_COMPLETED||rcvMessage.command == DOWNLOAD_WITH_DEP_STARTED){
			multipleFileDownloadHandeler(socket_, rcvMessage);
			continue;
		}
	}
	std::cout<<"\n--- ClientHandler socket connection closing";
	socket_.shutDown();
	socket_.close();
	std::cout << "\n--- ClientHandler thread terminating";
}

#ifdef TEST_RECEIVER
int main(){
	std::cout<<"\n-------------Testing Receiver Package--------------------------\n";
	try{
		BlockingQueue<std::string> queue;
		SocketSystem ss;
		SocketListener sl(9085, Socket::IP6);
		Receiver cp(queue);
		sl.start(cp);
		std::cout.flush();
		std::cout << "\n--- press key to exit: ";
		std::cin.get();
	}
	catch (std::exception& ex){
		std::cout<<"\n --- Exception caught:";
		std::cout << "\n  ";
		std::cout<<ex.what() << "\n\n";
	}
}
#endif