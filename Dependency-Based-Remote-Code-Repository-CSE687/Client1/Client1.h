#ifndef CLIENT1_H
#define CLIENT1_H
//////////////////////////////////////////////////////////////////////////
// Client1.h -	Provides client functionalities for this project        // 
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
* This package provides core functionalities for the client. Its constructor will set client port and address.
* This package will give functionality to start sendin and receiver threads.
*
* Public Interface:
* ==============================
* void startRcvThread();		// start receiver thread.
* void startSender();           // start sender.
* void startSndThread();        // start sender thread.
* void startReceiver();         // start receiver.
* bool connectToSocket(SocketConnecter& si, std::string ipAddress, int port); // connect socket.
* void actionOnRequest(SocketConnecter& si, std::string request); // deq from queue and process requet
* bool processCommandArgs(int argc, char** argv); // process command line arguments and store in member variables
* void startTask();			    // start client1's task
* HttpMessage getMessage();     // This function will be called by client UI to deq incoming messages.
* void postMessage(const HttpMessage &msg) // This function will post messages from client Ui on the sender queue
* Required Files:
* ============================
* Client1.h, Client1.cpp, HttpMessage.cpp , HttpMessage.h , Cpp11-BlockingQueue.h, Cpp11-BlockingQueue.cpp, FileMgr.h, 
* FileMgr.cpp, FileSysytem.h, FileSystem.cpp, HttpMessage.h, HttpMessage.cpp, itokcollection.h, Logger.h, Logger.cpp,
* MetadataFactory.h, MetadataFactory.cpp, Reciever.cpp, Reciever.h, Sender.cpp, Sender.h, Tokenizer.h, Tokenizer.cpp
* Utilities.h, Utilities.cpp, XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp, XmlElementParts.h, 
* XmlElementsParts.cpp, XmlParser.h, XmlParser.cpp, Sockets.h, Sockets.cpp
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
#include"../HttpMessage/HttpMessage.h"
#include"../Sender/Sender.h"
#include"../Receiver/Receiver.h"
#include<string>

class Client1
{
public:
	Client1(std::string address = "localhost", int port = 9080) :c1Address(address), c1Port(port), c1receiver(receiverQueue)
	{}
	void startRcvThread();
	void startReceiver();
	void startSndThread();
	void startSender();
	bool connectToSocket(SocketConnecter& si, std::string ipAddress, int port);
	HttpMessage getMessage();
	void startTask();
	void actionOnRequest(SocketConnecter& si, HttpMessage request);
	bool processCommandArgs(int argc, char** argv);
	void postMessage(const HttpMessage &msg);

private:
	BlockingQueue<HttpMessage> senderQueue;
	BlockingQueue<std::string> receiverQueue;
	int c1Port;
	std::string c1Address;
	Receiver c1receiver;
	std::vector<std::string> commandInfo;
	bool isFileTest_;
};

#endif