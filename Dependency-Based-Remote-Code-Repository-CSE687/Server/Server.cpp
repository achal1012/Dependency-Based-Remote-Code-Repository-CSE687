//////////////////////////////////////////////////////////////////////////
// Server.cpp -	Provides server functionalities for this project        // 
// Ver 1.0																//
// Application: Project #4 Dependency-Based Remote Code Repository      //
// Language:    C++, Visual Studio 2015									//
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10					//
// Author:      Achal Velani, SUID:292190387							//
// Reference:   Jim Fawcett, CST 4-187, Syracuse University				//
//              (315) 443-3948, jfawcett@twcny.rr.com					//
//////////////////////////////////////////////////////////////////////////
#include "./Server.h"

// This will start the receiver thread for the server by calling start sender.
void Server::startReceiverThread(){
	std::thread receiverThread(&Server::startReceiver, this);
	receiverThread.detach();
	std::cout << "\n Sender rec thread detached\n";
}

// This function will make connection to the socket and keep loop running which will deQ the send messages
// from sender queue.
void Server::startSender(){
	try{
		SocketSystem ss;
		SocketConnecter si;
		while (true){
			std::string request = serverQueue.deQ();
			HttpMessage rcvMessage;
			rcvMessage = rcvMessage.parseMessage(request);
			if (rcvMessage.command == SHUTDOWN_SERVER)
				break;
			processRequest(si, request);
		}
	}
	catch (std::exception& ex){
		std::cout<<"  Exception caught:";
		std::cout<<ex.what()<< "\n\n";
	}
}

//This function will start the sender thread by calling the startSender for the Server.
void Server::startSenderThread(){
	std::thread sendToClient(&Server::startSender,this);
	sendToClient.join();
	std::cout << "\n --- Server sender is shut down!\n";
}

//This function will start the receiver thread and make socket connections.
void Server::startReceiver(){
	try{
		std::cout << "\n--- Starting server receiver:\n";
		SocketSystem ss;
		SocketListener sl(port_, Socket::IP6);
		sl.start(serverReceiver);
		std::cout << "\n--- Press enter to exit.... ";
		std::cout.flush();
		std::cin.get();
	}
	catch (std::exception& ex){
		std::cout<<"\n ---Exception caught:";
		std::cout<< ex.what()<<"\n\n";
	}
}

// This function will be called while deQing the server queue
void Server::processRequest(SocketConnecter & si, std::string request)
{
	Sender sender;
	HttpMessage rcvMessage;
	rcvMessage = rcvMessage.parseMessage(request);
	if (rcvMessage.command == UPLOAD_ACK){
		if (connectToSocket(si, rcvMessage.destAdd, rcvMessage.destPort)){
			std::cout << "\n--- File: " << rcvMessage.fileName << "'s upload acknowledgement is sent to : " << rcvMessage.destAdd << ":" << std::to_string(rcvMessage.destPort)<<std::endl;
			si.sendString(request);
		}
	}
	else if ((rcvMessage.command == GETPACKAGES_RESPONSE)){
		if (connectToSocket(si, rcvMessage.destAdd, rcvMessage.destPort)){
			si.sendString(request);
		}
	}
	else if (rcvMessage.command == DOWNLOAD_REQUEST){
		if (connectToSocket(si, rcvMessage.destAdd, rcvMessage.destPort)){
			sender.checkInFile(si, rcvMessage, false);
		}
	}
	else if (rcvMessage.command == DOWNLOAD_WITH_DEP_REQ){
		if (connectToSocket(si, rcvMessage.destAdd, rcvMessage.destPort)){
			sender.extractWithDep(si, rcvMessage);
		}
	}
}

// This function will help connect the server with the sockets.
bool Server::connectToSocket(SocketConnecter & si, std::string ipAddress, int port){
	while (!si.connect(ipAddress, port)){
		std::cout<<"\nServer1's sender waiting to connect....\n";
		::Sleep(100);
	}
	std::cout<<" Server1's sender connected : "<<ipAddress << ": " << std::to_string(port);
	return true;
}

//This is a wrapper function for enQing to the server queue
void Server::enQ(std::string data){
	serverQueue.enQ(data);
}

//This is a wrapper function for enQing to the server queue
std::string Server::deQ()
{
	return serverQueue.deQ();
}

//This will process the command line arguments.
bool Server::processCommandArgs(int argc, char ** argv)
{
	HttpMessage msg;
	if (argc > 1 && argv[1]){
		std::string sourceDetails = argv[1];
		std::vector<std::string> source = msg.split(sourceDetails, ':');
		if (source.size() == 2){
			address_ = source[0];
			port_ = stoi(source[1]);
			std::cout<<"  Address :  "<< address_;
			std::cout<<"  Port    :  "<< std::to_string(port_);
			return true;
		}
		else{
			std::cout << "\n Thiere is some problem in the cmd arguments \n";
			return false;
		}
	
	}
	else {
		std::cout << "\n Please check command line arguments and try setting server again!\n";
		return false;
	}
}

#ifdef TEST_SERVER
int main(int argc, char* argv[])
{
	std::cout << "\n  ***  Server1  ***  \n";
	Server server;
	server.processCommandArgs(argc, argv);
	server.startReceiverThread();

	server.startSenderThread();
	std::cout << "HERE";
}
#endif // TEST_SERVER
