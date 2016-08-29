#ifndef MOCKCHANNEL_H
#define MOCKCHANNEL_H
//////////////////////////////////////////////////////////////////////////
// MockChannel.h - Channel connection between client and UI             //
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
* void postMessage(const HttpMessage& msg) // This will post message to client send queue
* void start() // This will start client sender and receiver threads.
* void stop()  // This is not implemented in this version 
* HttpMessage getMessage() // This will retrive messages from the client receiver thread.
*
* Required Files:
* ============================
* Client1.h, Client1.cpp,  Cpp11-BlockingQueue.h, Cpp11-BlockingQueue.cpp, FileMgr.h,
* FileMgr.cpp, FileSysytem.h, FileSystem.cpp, HttpMessage.h, HttpMessage.cpp, itokcollection.h, Logger.h, Logger.cpp,
* MetadataFactory.h, MetadataFactory.cpp, Reciever.cpp, Reciever.h, Sender.cpp, Sender.h, Tokenizer.h, Tokenizer.cpp
* Utilities.h, Utilities.cpp, XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp, XmlElementParts.h,
* XmlElementsParts.cpp, XmlParser.h, XmlParser.cpp, MockChannel.h, MockChannel.cpp
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



#ifdef IN_DLL
#define DLL_DECL __declspec(dllexport)
#else
#define DLL_DECL __declspec(dllimport)
#endif
#include"../HttpMessage/HttpMessage.h"
#include <string>

// Interface class for the UI channel
struct IMockChannel{
public:
  virtual void postMessage(const HttpMessage& msg) = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual HttpMessage getMessage() = 0;
};

extern "C" {
  struct ObjectFactory{
    DLL_DECL IMockChannel* createMockChannel(std::string ip, int port);
  };
}

#endif


