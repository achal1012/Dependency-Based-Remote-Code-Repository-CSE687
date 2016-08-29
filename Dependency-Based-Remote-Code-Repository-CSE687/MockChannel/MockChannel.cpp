//////////////////////////////////////////////////////////////////////////
// MockChannel.cpp - Channel connection between client and UI           //
// Ver 1.0																//
// Application: Project #4 Dependency-Based Remote Code Repository      //
// Language:    C++, Visual Studio 2015									//
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10					//
// Author:      Achal Velani, SUID:292190387							//
// Reference:   Jim Fawcett, CST 4-187, Syracuse University				//
//              (315) 443-3948, jfawcett@twcny.rr.com					//
//////////////////////////////////////////////////////////////////////////


#define IN_DLL
#include "MockChannel.h"
#include "Cpp11-BlockingQueue.h"
#include <string>
#include <thread>
#include <iostream>
#include "../HttpMessage/HttpMessage.h"
#include "../Client1/Client1.h"

using BQueue = BlockingQueue < HttpMessage >;

class MockChannel : public IMockChannel
{
public:
  MockChannel(std::string ip, int port);
  void start();
  void stop();
  void postMessage(const HttpMessage& msg) { client_.postMessage(msg); } // posts messages in client sender queue
  HttpMessage getMessage() {return  client_.getMessage(); } // This retrives message form client receiver.
private:
  std::thread thread_;
  bool stop_ = false;
  Client1 client_;
};

//----< pass pointers to Sender and Receiver >-------------------------------
MockChannel::MockChannel(std::string ip, int port) :client_(ip, port){}

//----< creates thread to read from sendQ and echo back to the recvQ >-------
void MockChannel::start()
{
  std::cout << "\n  UI channel starting up";
  client_.startRcvThread();
  client_.startSndThread();
  
}
//----< signal server thread to stop >---------------------------------------

void MockChannel::stop() { stop_ = true; }

// This returns the mockchannel instance 
IMockChannel* ObjectFactory::createMockChannel(std::string ip, int port)
{ 
  return new MockChannel(ip, port); 
}

#ifdef TEST_MOCKCHANNEL

//----< test stub >----------------------------------------------------------

int main()
{
  ObjectFactory objFact;
  ISendr* pSendr = objFact.createSendr();
  IRecvr* pRecvr = objFact.createRecvr();
  IMockChannel* pMockChannel = objFact.createMockChannel(pSendr, pRecvr);
  pMockChannel->start();
  pSendr->postMessage("Hello World");
  pSendr->postMessage("CSE687 - Object Oriented Design");
  Message msg = pRecvr->getMessage();
  std::cout << "\n  received message = \"" << msg << "\"";
  msg = pRecvr->getMessage();
  std::cout << "\n  received message = \"" << msg << "\"";
  pSendr->postMessage("stopping");
  msg = pRecvr->getMessage();
  std::cout << "\n  received message = \"" << msg << "\"";
  pMockChannel->stop();
  pSendr->postMessage("quit");
  std::cin.get();
}
#endif
