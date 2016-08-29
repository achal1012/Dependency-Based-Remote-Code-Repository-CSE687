#ifndef METADATAFACTORY_H
#define METADATAFACTORY_H
//////////////////////////////////////////////////////////////////////////
// MetadataFactory.h - Provides functionalities for xml metadata        // 
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
* This package provides functionality to create and store metadata and also writing and reading metadata files.
*
* Public Interface:
* ==============================
* XmlDocument createMetadata(HttpMessage msg,std::vector<std::string> listOffiles); // This function will help in creating the metadata files for the application of this project.
* std::string extractPackageName(std::string const& fileName); //This function will help in extracting the packagenames out of the filenames.
* void createXmlFile(XmlDocument *xdoc, std::string filename);// This function will create xml file at the specific file path using already created Xdocument
* XmlDocument readXmlFile(std::string filepath); // This function will help in reading the XML document and will return an object of XmlDocument
* std::string readStatus(XmlDocument* xdoc); // This function will be used to check the status tag for the xml file
* std::vector<std::string> readDependecies(XmlDocument *xdoc);// This function will check all the dependencies recorded in the XML and return the vector.
* bool fileExists(const std::string& filename); // This function will check whether a file exsists of not for the given directory. 
*
* Required Files:
* ============================
* HttpMessage.cpp , HttpMessage.h , itokcollection.h, MetadataFactory.h, MetadataFactory.cpp, Tokenizer.h, Tokenizer.cpp
* XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp, XmlElementParts.h,
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


#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../HttpMessage/HttpMessage.h"
#include "../XmlDocument/XmlDocument.h"
#include "../XmlParser/XmlParser.h"
#include "../Sender/Sender.h"
using namespace XmlProcessing;
using sPtr = std::shared_ptr < AbstractXmlElement >;



class metadataFactory{
public:
	XmlDocument createMetadata(HttpMessage msg,std::vector<std::string> listOffiles);
	std::string extractPackageName(std::string const& fileName);
	void createXmlFile(XmlDocument *xdoc, std::string filename);
	XmlDocument readXmlFile(std::string filepath);
	std::string readStatus(XmlDocument* xdoc);
	std::vector<std::string> readDependecies(XmlDocument *xdoc);
	bool fileExists(const std::string& filename);
};


#endif // !METADATAFACTORY_H

