#ifndef SENDER_H
#define SENDER_H
//////////////////////////////////////////////////////////////////////////
// Sender.h -	Provides Sender functionalities  for client and server  // 
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
* This package provides core functionalities for sender, it will be used as sender in both Server and Client
*
* Public Interface:
* ==============================
*
* std::string extractPackageName(std::string const& fileName); //This function will extract package name out of the file name 
* std::string getRepoPath(std::string filePath); //This function will find the most latest version for the requested file and return the path to the calling function
* void ExtractFilesWoDep(Socket& si, HttpMessage msg); // This function will provide sending functionalities for the sende, and send string message using sockets
* void extractWithDep(Socket& si, HttpMessage msg);//This function will send message to extract a file from the server.
* void checkInFile(Socket &si, HttpMessage requestMessage, bool isUpload); // This function will help in checking in the file as well as download file
* void getPackagesInRepository(Socket &si, HttpMessage requestMessage); //This message will request all the packages available in the repository.
* void shutdownServer(Socket &si, HttpMessage requestMessage); // This function will send command to shutdown the server sender.
*
* Required Files:
* ============================
* FileMgr.h, FileMgr.cpp, FileSysytem.h, FileSystem.cpp, HttpMessage.h, HttpMessage.cpp,  Logger.h, Logger.cpp,
* Sender.cpp, Sender.h, Utilities.h, Utilities.cpp
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

#include<iostream>
#include<fstream>
#include <cstddef>
#include"../Sockets/Sockets.h"
#include"../HttpMessage/HttpMessage.h"
#include"../Utilities/Utilities.h"
#include"../FileMgr/FileMgr.h"
#include"../FileMgr/FileSystem.h"
class Sender
{
public:
	std::string extractPackageName(std::string const& fileName);
	std::string getRepoPath(std::string filePath);
	void ExtractFilesWoDep(Socket& si, HttpMessage msg);
	void extractWithDep(Socket& si, HttpMessage msg);
	void checkInFile(Socket &si, HttpMessage requestMessage, bool isUpload);
	void getPackagesInRepository(Socket &si, HttpMessage requestMessage);
	void shutdownServer(Socket &si, HttpMessage requestMessage);
};


#endif
