#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H
//////////////////////////////////////////////////////////////////////////
// HttpMessage.h - Provides Structure for HttpMessage					// 
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
* This package provides core functionalities for Http-style message. It provides core structure as well as corrolary
* functionalities for the the HttpMessage.
*
* Public Interface:
* ==============================
* std::string HttpMessage::createHeaderMessage(HttpMessage msg); //This funcion will convert HttpMessage object to string type. 
* std::string createOperation(std::string commandType, std::string fileName, std::string destAdd, int destPort, std::string body = ""); //This function will help in creating the Http stype operation message.
* std::vector<std::string> split(std::string message, char seperator); //This function is used to split a string with specific sperarator, this will return vector of string.
* std::map<std::string, std::string> createMap(std::vector<std::string> headerAttributes); //This function will create map out of the attributes.
* HttpMessage parseMessage(std::string message); //This function will help in parshing the string message to Httpstyle message.
* std::vector<std::string> depSplit(std::string); // This function will seprate packages in the body of the message.
* std::vector<std::string> extractPackageName_Responce(std::string); //This function will extractPackageName from the responce
*
* Required Files:
* ============================
* HttpMessage.h , HttpMessage.cpp
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


#include<string>
#include<vector>
#include<iostream>
#include<map>
#include<algorithm>
#include<sstream>

enum action_byte
{
	ETX = 0x03, ///end of text = 0x03H
};
// Buffer Size
#define BUFFER_SIZE  1024
#define KEY_VALUE_PAIR_SEP '|'
#define FILES_SEP '$'
// command types
#define UPLOAD_STARTED "01"
#define UPLOAD_COMPLETED "02"
#define UPLOAD_ACK "03" 
#define GETPACKAGES_REQUEST "11"
#define GETPACKAGES_RESPONSE "12"
#define GETPACKAGES_REQUEST_ACK "13"
#define DOWNLOAD_REQUEST "20"
#define DOWNLOAD_STARTED "21"
#define DOWNLOAD_COMPLETED "22"
#define DOWNLOAD_ACK "23"
#define DOWNLOAD_WITH_DEP_REQ "30"
#define DOWNLOAD_WITH_DEP_STARTED "31"
#define DOWNLOAD_WITH_DEP_COMPLETED "32"
#define DOWNLOAD_WITH_DEP_ACK "33"
// Attributes keys
#define COMMAND "command"
#define SOURCE_ADD "sourceaddress"
#define SOURCE_PORT "sourceport"
#define DESTINATION_ADD "destinationaddress"
#define DESTINATION_PORT "destinationport"
#define CONTENT "content"
#define FILE_NAME "filename"
#define OPERATION_BODY "operation_body"
#define CONTENT_LENGTH "contentlength"
#define STATUS "status"
#define DEPENDANCIES "dependancies"
// Operation names,
#define TEST_MESSAGE "testMessage"
#define CHECK_IN "chekin"
#define REPOSITORYCHECK "repositorycheck"
#define EXTRACT "extract"
#define EXTRACT_WO_DEP "extract_without_dependencies"
#define SEND_STRING "sentstring"
#define SEND_BUFFER "sentbuffer"
#define SHUTDOWN_SERVER "shutdown server sender"
// Property 
#define CLOSED "closed"
#define OPEN "open"

class HttpMessage{
public:
	std::string HttpMessage::createHeaderMessage(HttpMessage msg);
	std::string createOperation(std::string commandType, std::string fileName, std::string destAdd, int destPort, std::string body = "");
	std::vector<std::string> split(std::string message, char seperator);
	std::map<std::string, std::string> createMap(std::vector<std::string> headerAttributes);
	HttpMessage parseMessage(std::string message);
	std::vector<std::string> depSplit(std::string);
	std::vector<std::string> extractPackageName_Responce(std::string);
	// No getter setter functions were needed for this Class and hence HttpMessage Attributes are under 
	// public data declaration.
	std::string command;
	std::string sourceAddress;
	int senderPort;
	std::string destAdd;
	int destPort;
	std::string content;
	std::string fileName;
	std::string status;
	int contentLength = 0;
	std::string body = "";
	std::vector<std::string> dependancies;
};

#endif