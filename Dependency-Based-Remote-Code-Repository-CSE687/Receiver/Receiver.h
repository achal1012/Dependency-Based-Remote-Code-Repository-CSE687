#ifndef RECEIVER_H
#define RECEIVER_H
//////////////////////////////////////////////////////////////////////////
// Receiver.h -	Provides receiver functionalities  for client and server// 
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
* This package provides functionalities for the receiver side in the communication channel. It works as receiver for both client and
* server.
* Public Interface:
* ==============================
* void operator()(Socket& socket_); // This is the functor for the Reciver class and will be called by the socket in the listning mode.
* void fileUploadHandler(Socket& socket_, HttpMessage& rcvMessage);//This function will handel all the requests for file upload handelings.
* void fileDownloadHandler(Socket& socket_, HttpMessage& rcvmessage); // This function will help in creating proper http message as well as call fileupload function to handel download requests
* void multipleFileDownloadHandeler(Socket & socket_, HttpMessage& rcvMessage);// This function is written in intent with downloading more than one file.
* bool multipleFileUpload(Socket & socket_, HttpMessage& rcvmessage); //This function will help in uploading more than one files simultaneously.
* bool fileUpload(Socket& socket_, HttpMessage& rcvmessage, bool upload); //This function will handel all the requests for file upload handelings.
* bool fileWrite(Socket& socket, HttpMessage& rcvmessage, std::string filePath); //This function will be used to handel writes of checkins and extracts  
* bool bufferReading(Socket& socket_, int size, Socket::byte* buffer); // This function helps in reading data from buffer of socket
* std::vector<std::string> repositoryPackages(); //This will return all the packages in the repository
* void directoryRequestHandler(Socket& socket_, HttpMessage& rcvMessage); //This function will handel the request of repository package request.
* void serverShutDownHandler(Socket& socket_, HttpMessage& rcvMessage); //This function will handel the request for shutting down the server.
* std::string whichDiectory(std::string); // This function will help in deciding the directory for the file being checked in
* std::string directoryHelper1(std::string,std::string, std::string); // This function will be called by directory determining function when no repository exsists.
* std::string getCurrentDateTime(); // This function will provide functionalities for getting current datetime stamp to generate versions.
* std::vector<std::string> setPackages(std::string); //This function will return all the packages in a vector.
* void operatorHelper1(Socket & socket_, HttpMessage rcvMessage); // This is a helper function for the functor operator 
* void operatorHelper2(Socket & socket_, HttpMessage rcvMessage); // This is a helper function for the functor operator 
*
* Required Files:
* ============================
* Cpp11-BlockingQueue.h, Cpp11-BlockingQueue.cpp, FileSysytem.h, FileSystem.cpp, HttpMessage.h, HttpMessage.cpp, itokcollection.h, Logger.h, Logger.cpp,
* MetadataFactory.h, MetadataFactory.cpp, Reciever.cpp, Reciever.h,
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
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <ctime>
#include <chrono>
#include<vector>
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include "../HttpMessage/HttpMessage.h"
#include "../Sockets/Sockets.h"
#include "../FileMgr/FileSystem.h"
#include "../MetadataFactory/MetadataFactory.h"
#define REPOPATH "../Repository/"

class Receiver{
public:
	Receiver(BlockingQueue<std::string> &arg, std::string rcvPath = "") : serverqueue(arg), receiverPath(rcvPath){}
	void operator()(Socket& socket_);
	void fileUploadHandler(Socket& socket_, HttpMessage& rcvMessage);
	void fileDownloadHandler(Socket& socket_, HttpMessage& rcvmessage);
	void multipleFileDownloadHandeler(Socket & socket_, HttpMessage& rcvMessage);
	bool multipleFileUpload(Socket & socket_, HttpMessage& rcvmessage);
	bool fileUpload(Socket& socket_, HttpMessage& rcvmessage, bool upload);
	bool fileWrite(Socket& socket, HttpMessage& rcvmessage, std::string filePath);
	bool bufferReading(Socket& socket_, int size, Socket::byte* buffer);
	std::vector<std::string> repositoryPackages();
	void directoryRequestHandler(Socket& socket_, HttpMessage& rcvMessage);
	void serverShutDownHandler(Socket& socket_, HttpMessage& rcvMessage);
	std::string whichDiectory(std::string);
	std::string directoryHelper1(std::string,std::string, std::string);
	std::string getCurrentDateTime();
	std::vector<std::string> setPackages(std::string);
	void operatorHelper1(Socket & socket_, HttpMessage rcvMessage);
	void operatorHelper2(Socket & socket_, HttpMessage rcvMessage);
private:
	BlockingQueue<std::string> &serverqueue;
	std::string receiverPath;
	std::vector<std::string> _RepoPackages;
};

#endif