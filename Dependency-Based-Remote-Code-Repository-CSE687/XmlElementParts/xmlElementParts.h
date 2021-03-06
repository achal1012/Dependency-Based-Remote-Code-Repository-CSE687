#ifndef XMLELEMENTPARTS_H
#define XMLELEMENTPARTS_H
//////////////////////////////////////////////////////////////////////////
// XmlElementParts.h - Collects tokens for XML analysis                 //
// ver 1.3                                                              //
// Application: Project #4 Dependency-Based Remote Code Repository      //
// Language:    C++, Visual Studio 2015                                 //
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10                 //
// Author:	    Jim Fawcett, CST 4-187, Syracuse University             //
//              (315) 443-3948, jfawcett@twcny.rr.com                   //
//////////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module defines an XmlParts class.  Its instances build a sequence 
  of tokens obtained from the Tokenizer module for analysis of XML.
  XmlElementParts are lists of tokens that terminate on one of the tokens:
  < or >.

  This structure is designed to collect just the right amount of inform-
  ation from an XML file for analysis.  That is, it collects the smallest
  set of tokens that lead to the detection of grammatical constructs, 
  without having to save part of the sequence for later use or get more
  to complete the detection process.  This simplifies the design of code
  analysis tools.

  Note that assignment and copying of XmlParts instances is supported, using
  the default operations provided by the C++ language.  Copies and assignments
  result in both source and target XmlParts instances sharing the same toker.

  Public Interface:
  =================
  Toker t;                                  // create tokenizer instance
  XmlParts parts(&t);                       // create instance and attach
  if(xml.get())                             // collect an XmlElementParts
    std::cout << parts.showXmlParts().c_str();  // show it
  int n = parts.length();                   // number of tokens in parts
  std::string tok = parts[2] = "a change";  // indexed read and write
  if(parts.find("aTok") < parts.length())   // search for a token
    std::cout << "found aTok";  
  parts.clear();                            // remove all tokens

  Build Process:
  ==============
  devenv Project4.sln /rebuild debug

  Maintenance History:
  ====================
  ver 1.3 : 31 Jan 09
  - fixed bug identified by Phil Pratt-Szeliga where white space before
    an internal '<' character caused a parsing error.  The solution used
    here is Phil's suggested solution.
  ver 1.1 : 24 Jan 09
  - fixed parsing failure when encountering internal '<' character
  ver 1.0 : 17 Jan 09
  - first release

*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "ITokCollection.h"
#include "tokenizer.h"

class XmlParts : public ITokCollection
{
public:
  XmlParts(Toker* pTokr);
  XmlParts();
  ~XmlParts();
  bool get();
  int length();
  std::string& operator[](int n);
  int find(const std::string& tok);
  void push_back(const std::string& tok);
  bool remove(const std::string& tok);
  void toLower();
  void trimFront();
  void clear();
  std::string show();
  void verbose(bool v = true);

private:
  Toker* pToker;
  std::vector<std::string> toks;
  bool isTerminator(std::string tok);
  bool Verbose;
};

inline XmlParts::XmlParts() : pToker(nullptr) {}

inline int XmlParts::length() { return (int)toks.size(); }

inline void XmlParts::verbose(bool v) { Verbose = v; }

inline void XmlParts::clear() { toks.clear(); }

inline void XmlParts::push_back(const std::string& tok)
{
  toks.push_back(tok);
}


#endif
