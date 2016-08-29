//////////////////////////////////////////////////////////////////////////
// Sender.cpp -	Provides Sender functionalities  for client and server  // 
// Ver 1.0																//
// Application: Project #4 Dependency-Based Remote Code Repository      //
// Language:    C++, Visual Studio 2015									//
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10					//
// Author:      Achal Velani, SUID:292190387							//
// Reference:   Jim Fawcett, CST 4-187, Syracuse University				//
//              (315) 443-3948, jfawcett@twcny.rr.com					//
//////////////////////////////////////////////////////////////////////////
#include "Sender.h"

//This function will extract package name out of the file name 
std::string Sender::extractPackageName(std::string const & fileName){
	std::string::size_type pos = fileName.find('.');
	if (pos != std::string::npos){
		return fileName.substr(0, pos);
	}
	else{
		return fileName;
	}
}

//This function will find the most latest version for the requested file and return the path to the calling function
std::string Sender::getRepoPath(std::string filePath){
	std::string path = "../Repository/";
	std::string pkgName = extractPackageName(filePath);
	std::vector<std::string> foldersInRepo = FileSystem::Directory::getDirectories(path);
	if (std::find(foldersInRepo.begin(), foldersInRepo.end(), pkgName) != foldersInRepo.end()){
		path.append(pkgName);
		path.append("/");
		std::vector<std::string> versionsInPackage = FileSystem::Directory::getDirectories(path);
		std::sort(versionsInPackage.begin(), versionsInPackage.end());
		path.append(versionsInPackage.back());
		path.append("/");
		std::cout << std::endl << path;
	}
	else{
		std::cout << "\nPackage folder not found \n";
	}
	return path;
}

// This function will provide sending functionalities for the sende, and send string message using sockets
void Sender::ExtractFilesWoDep(Socket & si, HttpMessage msg){
	msg.command = DOWNLOAD_REQUEST;
	std::string stringmessage = "";
	stringmessage = msg.createHeaderMessage(msg);
	si.sendString(stringmessage);
}

//This function will send message to extract a file from the server.
void Sender::extractWithDep(Socket & si, HttpMessage msg){
	msg.command = DOWNLOAD_WITH_DEP_REQ;
	std::string stringmessage = "";
	stringmessage = msg.createHeaderMessage(msg);
	si.sendString(stringmessage);
}

// This function will help in checking in the file as well as download file, this will be helpful as if request is sent by the client 
// server will upload the files and it is checkin from the server side, visa versa is evident.
void Sender::checkInFile(Socket & si, HttpMessage requestMessage, bool isUpload){
	std::ifstream infile;
	std::string filePath="";
	if (isUpload == true){
		filePath = requestMessage.fileName;
		//filePath = "../checkIn/"; enable this while using command prompt client as start up 
	}
	else{
		filePath = getRepoPath(requestMessage.fileName);
		filePath.append(requestMessage.fileName);
	}
	infile.open(filePath, std::ios::binary | std::ios::ate | std::ios::in);
	if (infile.is_open()) {
		int size;
		char buffer[BUFFER_SIZE];
		size = static_cast<int>(infile.tellg());
		infile.seekg(0, infile.beg);
		while (size > 0) {
			std::memset(buffer, 0, BUFFER_SIZE);
			int bSize = 1024;
			if (size < bSize)
				bSize = size;
			size = size - bSize;
			std::string stringmessage = "";
			requestMessage.contentLength = bSize;
			if (size == 0) {
				if (isUpload)
					requestMessage.command = UPLOAD_COMPLETED;
				else
					requestMessage.command = DOWNLOAD_COMPLETED;
			}
			else {
				if (isUpload)
					requestMessage.command = UPLOAD_STARTED;
				else
					requestMessage.command = DOWNLOAD_STARTED;
			}
			stringmessage = requestMessage.createHeaderMessage(requestMessage);
			si.sendString(stringmessage);
			infile.read(buffer, bSize);
			si.send(bSize, buffer);
			if (infile.eof())
				break;
		}
		infile.close();
	}
	else
		std::cout << "\n---- Cannot open : " << requestMessage.fileName << " for read! ----\n";
}

//This message will request all the packages available in the repository.
void Sender::getPackagesInRepository(Socket & si, HttpMessage requestMessage){
	requestMessage.command = GETPACKAGES_REQUEST;
	std::string stringmessage = "";
	stringmessage = requestMessage.createHeaderMessage(requestMessage);
	si.sendString(stringmessage);
}

// This function will send command to shutdown the server sender.
void Sender::shutdownServer(Socket & si, HttpMessage requestMessage){
	requestMessage.command = SHUTDOWN_SERVER;
	std::string stringmessage = "";
	stringmessage = requestMessage.createHeaderMessage(requestMessage);
	si.sendString(stringmessage);
}

#ifdef TEST_SENDER
int main()
{
	std::cout << "\n TESTING SENDER PACKAGE \n";
	try{
		
		Sender sender;
		SocketSystem ss;
		SocketConnecter si;
		HttpMessage msg;
		while (!si.connect("localhost", 9085))
		{
			std::cout<<"\n-----------client waiting to connect\n";
			::Sleep(100);
		}
		// To check in file
		msg.command = CHECK_IN;
		msg.senderPort = 9080;
		msg.destAdd = "localhost";
		msg.destPort = 9085;
		msg.fileName = "bigtext.txt";
		sender.checkInFile(si, msg, true);
		// To check packages in Repo
		HttpMessage chkrep;
		chkrep.command = REPOSITORYCHECK;
		chkrep.senderPort = 9080;
		chkrep.destAdd = "localhost";
		chkrep.destPort = 9085;
		sender.getPackagesInRepository(si, chkrep);
		//To extractfile from repo
		HttpMessage dlfile;
		dlfile.command = EXTRACT_WO_DEP;
		dlfile.senderPort = 9080;
		dlfile.destAdd = "localhost";
		dlfile.destPort = 9085;
		dlfile.fileName = "SemiExp.cpp";
		sender.checkInFile(si, dlfile,false);
		std::cout<<"\n---- client calling send shutdown ----\n";
		si.shutDownSend();
	}
	catch (std::exception& ex)
	{
		std::cout<<"\n///////////// Exception caught://////////n";
		std::cout << " ";
		std::cout << "\n";
		std::cout<<ex.what() << "\n\n";
	}
}
#endif