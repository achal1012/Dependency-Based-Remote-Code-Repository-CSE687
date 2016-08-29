//////////////////////////////////////////////////////////////////////////
// Client1.cpp - Provides client functionalities for this project       // 
// Ver 1.0																//
// Application: Project #4 Dependency-Based Remote Code Repository      //
// Language:    C++, Visual Studio 2015									//
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10					//
// Author:      Achal Velani, SUID:292190387							//
// Reference:   Jim Fawcett, CST 4-187, Syracuse University				//
//              (315) 443-3948, jfawcett@twcny.rr.com					//
//////////////////////////////////////////////////////////////////////////

#include "./Client1.h"

//This function will start the receieve thread by calling startReceiver function.
void Client1::startRcvThread(){
	std::thread serverThread(&Client1::startReceiver, this);
	serverThread.detach();
	std::cout << "\n--- Client receive thread started\n";
}

//This function will start the server receiver and keep it in the listning mode.
void Client1::startReceiver(){
	try {
		SocketSystem ss;
		SocketListener sl(c1Port, Socket::IP6);
		sl.start(c1receiver);
		std::cout<<"\n----------press key to exit:---------\n";
		std::cout.flush();
		std::cin.get();
	}
	catch(std::exception& e){
		std::cout << "\n Exception Caught:";
		std::cout << e.what() << std::endl;
	}
}

//This function will start the sender thread by calling startSender of the client.
void Client1::startSndThread(){
	std::thread clientThread(&Client1::startSender, this);
	clientThread.detach();
	std::cout << "\n--- Client send detached!\n";
}

//This function will start sender thread and keep it on until it receives termination message.
void Client1::startSender(){
	try{
		SocketSystem ss;
		SocketConnecter si;
		while (true){
			HttpMessage request = senderQueue.deQ();
			if (request.command == "end of send queue")
				break;
			actionOnRequest(si, request);
		}
	}
	catch (std::exception& e){
		std::cout<<" \n--- Exception caught:";
		std::cout<< e.what()<<"\n\n";
	}
}

//This function will help the client to make socket connection.
bool Client1::connectToSocket(SocketConnecter & si, std::string ipAddress, int port)
{
	while (!si.connect(ipAddress, port)){
		std::cout<<"\n--- Client1 waiting to connect.....\n";
		std::cout << ipAddress;
		std::cout << port;
		::Sleep(100);
	}
	std::cout<<"\n--- Client1 connected on port number : "<< std::to_string(port)<<std::endl;
	return true;
}

// This function will be used by GUI client and it will deQ messages form the client receiver queue.
HttpMessage Client1::getMessage(){
	HttpMessage message;
	std::string result = receiverQueue.deQ();
	message = message.parseMessage(result);
	return message;
}

// This is a simple task starting function which has some demo messages to test the functionalities of the client.
void Client1::startTask(){
	HttpMessage msg;
	startRcvThread();
	msg.command = CHECK_IN;				// CheckIn message
	msg.senderPort = 9080;
	msg.destAdd = "localhost";
	msg.destPort = 9085;
	msg.fileName = "Parser.cpp";
	msg.dependancies.push_back("A");
	msg.dependancies.push_back("B");
	msg.status = CLOSED;
	senderQueue.enQ(msg);
	HttpMessage msg1;					// CheckIn message
	msg1.command = CHECK_IN;
	msg1.senderPort = 9080;
	msg1.destAdd = "localhost";
	msg1.destPort = 9085;
	msg1.fileName = "A.txt";
	msg1.dependancies.push_back("B");
	msg1.status = CLOSED;
	senderQueue.enQ(msg1);
	HttpMessage dl;						// Extract Message
	dl.command = EXTRACT_WO_DEP;
	dl.senderPort = 9080;
	dl.destAdd = "localhost";
	dl.destPort = 9085;
	dl.fileName = "bigtext.txt";
	senderQueue.enQ(dl);
	HttpMessage pr;						//Repository Package request
	pr.command = REPOSITORYCHECK;
	pr.senderPort = 9080;
	pr.destAdd = "localhost";
	pr.destPort = 9085;
	senderQueue.enQ(pr);

	startSndThread(); // strat sender is called.
}

//This will be called dequeue of sender queue and in turn it will call other functions to make http messages.
void Client1::actionOnRequest(SocketConnecter & si, HttpMessage request){
	Sender sender;
	connectToSocket(si, request.destAdd, request.destPort);
	request.senderPort = c1Port;
	request.sourceAddress = c1Address;
	if (request.command == CHECK_IN)
		sender.checkInFile(si, request, true);
	else if (request.command == REPOSITORYCHECK)
		sender.getPackagesInRepository(si, request);
	else if (request.command == EXTRACT_WO_DEP)
		sender.ExtractFilesWoDep(si, request);
	else if (request.command == SHUTDOWN_SERVER)
		sender.shutdownServer(si, request);
	else if (request.command == DOWNLOAD_WITH_DEP_REQ)
		sender.extractWithDep(si, request);
	si.shutDown();
	std::cout << "sender socket shut down";
}

// This function will parse commandline arguments.
bool Client1::processCommandArgs(int argc, char ** argv)
{
	HttpMessage msg;
	if (argc > 1 && argv[1]){
		std::string sourceDetails = argv[1];
		std::vector<std::string> source = msg.split(sourceDetails, ':');
		if (source.size() == 2)
		{
			c1Address = source[0];
			c1Port = stoi(source[1]);
		}
	}
	if (argc > 2 && (std::string(argv[2]) == "/s" || std::string(argv[2]) == "/f")){
		if (std::string(argv[2]) == "/s")
			isFileTest_ = false;
		else if (std::string(argv[2]) == "/f")
			isFileTest_ = true;
		for (int i = 3; i < argc; i++)
			commandInfo.push_back(argv[i]);
	}
	else
		return false;
	return true;
}

//This function will be called by the client and it provides wrapper for enquing the messages in sender.
void Client1::postMessage(const HttpMessage & msg)
{
	senderQueue.enQ(msg);
}

#ifdef CLIENT1_TEST
int main(int argc, char* argv[])
{
	std::cout<<"\n *** Client1 ***  \n";
	Client1 client1;
	if (client1.processCommandArgs(argc, argv))
	{
		client1.startTask();
	}
	else
	{
		std::cout<<"\n\n Please provide correct command line arguments, Please check README file for more details.\n\n";
	}

	return 0;
}
#endif // CLIENT1_TEST


