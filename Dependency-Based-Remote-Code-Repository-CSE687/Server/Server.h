#ifndef SERVER_H
#define SERVER_H
//////////////////////////////////////////////////////////////////////////
// Server.h -	Provides server functionalities for this project        // 
// Ver 1.0																//
// Application: Project #4 Dependency-Based Remote Code Repository      //
// Language:    C++, Visual Studio 2015									//
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10					//
// Author:      Achal Velani, SUID:292190387							//
// Reference:   Jim Fawcett, CST 4-187, Syracuse University				//
//              (315) 443-3948, jfawcett@twcny.rr.com					//
//////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* ===============================
* This package provides core functionalities for the server. Its constructor will set server port and address.
* This package will give functionality to start sending and receiver threads for the server.
*
* Public Interface:
* ============================== 
* void startReceiverThread(); // This will start the receiver thread for the server by calling start sender.
* void startSender();// This function will make connection to the socket and keep loop running which will deQ the send messages from sender queue.
* void startSenderThread(); //This function will start the sender thread by calling the startSender for the Server.
* void startReceiver(); //This function will start the receiver thread and make socket connections.
* void processRequest(SocketConnecter& si, std::string request); // This function will be called while deQing the server queue
* bool connectToSocket(SocketConnecter& si, std::string ipAddress, int port); // This function will help connect the server with the sockets.
* void enQ(std::string data); //This is a wrapper function for enQing to the server queue
* std::string deQ(); //This is a wrapper function for enQing to the server queue
* bool processCommandArgs(int argc, char** argv); //This will process the command line arguments.
*
* Required Files:
* ============================
* Cpp11-BlockingQueue.h, Cpp11-BlockingQueue.cpp, FileMgr.h, FileMgr.cpp, FileSysytem.h, FileSystem.cpp, HttpMessage.h, 
* HttpMessage.cpp, itokcollection.h, Logger.h, Logger.cpp, Sockets.h, Sockets.cpp
* MetadataFactory.h, MetadataFactory.cpp, Reciever.cpp, Reciever.h, Sender.cpp, Sender.h, Tokenizer.h, Tokenizer.cpp
* Utilities.h, Utilities.cpp, XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp, XmlElementParts.h,
* XmlElementsParts.cpp, XmlParser.h, XmlParser.cpp
*
* Build Command:
* ============================
* devenv Project4.sln /rebuild debug
*
* Maintenance History:
* ============================
* ver 1.0 : 3 May 16
* - first release
*/
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include "../Receiver/Receiver.h"
#include "../Sender/Sender.h"
class Server
{
public:
	Server(std::string address = "localhost", int port = 9085) : address_(address), port_(port), serverReceiver(serverQueue, "../Repository/") {}
	void startReceiverThread();
	void startSender();
	void startSenderThread();
	void startReceiver();
	void processRequest(SocketConnecter& si, std::string request);
	bool connectToSocket(SocketConnecter& si, std::string ipAddress, int port);
	void enQ(std::string data);
	std::string deQ();
	bool processCommandArgs(int argc, char** argv);

private:
	BlockingQueue<std::string> serverQueue;

	std::string address_;
	int port_;
	Receiver serverReceiver;
};
#endif