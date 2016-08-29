//////////////////////////////////////////////////////////////////////////
// MetadataFactory.cpp - Provides functionalities for xml metadata      // 
// Ver 1.0																//
// Application: Project #4 Dependency-Based Remote Code Repository      //
// Language:    C++, Visual Studio 2015									//
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10					//
// Author:      Achal Velani, SUID:292190387							//
// Reference:   Jim Fawcett, CST 4-187, Syracuse University				//
//              (315) 443-3948, jfawcett@twcny.rr.com					//
//////////////////////////////////////////////////////////////////////////

#include "./MetadataFactory.h"


// This function will help in creating the metadata files for the application of this project.
XmlDocument metadataFactory::createMetadata(HttpMessage msg, std::vector<std::string> listOffiles){
	std::string fileName = msg.fileName;
	std::string packageName = metadataFactory::extractPackageName(fileName);
	std::string status = msg.status;

	sPtr pRoot = makeTaggedElement("Metadata");
	XmlDocument metadata(XmlProcessing::makeDocElement(pRoot));

	sPtr pkgName = makeTaggedElement("PackageName");
	pkgName->addChild(makeTextElement(packageName));
	pRoot->addChild(pkgName);

	sPtr ckStatus = makeTaggedElement("checkInStatus");
	ckStatus->addChild(makeTextElement(status));
	pRoot->addChild(ckStatus);

	sPtr dependencies = makeTaggedElement("Dependencies");
	for (std::string file : listOffiles){
		sPtr dependency = makeTaggedElement("Dependency"); 
		dependency->addChild(makeTextElement(file));
		dependencies->addChild(dependency);
	}
	pRoot->addChild(dependencies);
	return metadata;
}

//This function will help in extracting the packagenames out of the filenames.
std::string metadataFactory::extractPackageName(std::string const& fileName){
	std::string::size_type pos = fileName.find_last_of('.');
	if (pos != std::string::npos){
		std::string a = fileName.substr(0, pos);
		std::string ret = fileName.substr(0,pos);
		std::string::size_type pos1 = ret.find_last_of('\\');
		if (pos1 != std::string::npos){
			std::string b = ret.substr(pos1 + 1, pos);
			return b;
		}
		else
			return a;
	}
	else{
		return fileName;
	}
}

// This function will check whether a file exsists of not for the given directory. 
bool metadataFactory::fileExists(const std::string& filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1){
		return true;
	}
	return false;
}

// This function will create xml file at the specific file path using already created Xdocument
void metadataFactory::createXmlFile(XmlDocument *xdoc, std::string filename){
	std::string xmlName= metadataFactory::extractPackageName(filename);
	xmlName.append(".xml");
	if (metadataFactory::fileExists(xmlName)==true){
		std::cout << "\n--- XML already exsists and it will is overwritten!";
		std::ofstream xmlfile(xmlName);
		xmlfile << xdoc->toString();
		xmlfile.close();
		std::cout << "\n--- XML Created\n";
	}
	else{
		std::ofstream xmlfile(xmlName);
		xmlfile << xdoc->toString();
		xmlfile.close();
		std::cout << "\nXML Created\n";
	}
}

// This function will help in reading the XML document and will return an object of XmlDocument
XmlDocument metadataFactory::readXmlFile(std::string filepath){
	XmlDocument doc2(filepath, XmlDocument::file);
	return doc2;
}

// This function will be used to check the status tag for the xml file
std::string metadataFactory::readStatus(XmlDocument *xdoc)
{
	std::string checkInStatus;
	std::string testStatus = "checkInStatus";

	std::vector<sPtr> found = xdoc->elements(testStatus).select();
	if (found.size() > 0){
		for (auto pElem : found){
			if (pElem->tag() != "")
				std::cout << "\n  found: " << pElem->tag();
			else{
				checkInStatus = pElem->value();
				checkInStatus.erase(remove_if(checkInStatus.begin(), checkInStatus.end(), isspace), checkInStatus.end());
				checkInStatus.erase(std::remove(checkInStatus.begin(), checkInStatus.end(), '\n'), checkInStatus.end());
			}
		}
	}
	else{
		std::cout << "\n  couldn't find child elements";
	}
	return checkInStatus;
}

// This function will check all the dependencies recorded in the XML and return the vector.
std::vector<std::string> metadataFactory::readDependecies(XmlDocument * xdoc)
{
	std::vector<std::string> a;
	std::string testTag = "Dependencies";
	std::vector<sPtr> found = xdoc->element(testTag).descendents().select();
	if (found.size() > 0){
		for (auto pElem : found){
			if (pElem->tag() != "")
				std::cout << ""; 
			else{
				std::string dep = pElem->value();
				dep.erase(remove_if(dep.begin(), dep.end(), isspace), dep.end());
				dep.erase(std::remove(dep.begin(), dep.end(), '\n'), dep.end());
				a.push_back(dep);
			}
		}
	}
	else{
		std::cout << "\n  couldn't find descendent elements\n";
		a.clear();
	}
	return a;
}



#ifdef TEST_METADATAFACTORY
int main(){
	HttpMessage testMEssage;
	testMEssage.fileName = "testPackage";
	testMEssage.status = "closed";
	std::vector<std::string> lsfiles;
	lsfiles.push_back("a");
	lsfiles.push_back("b");
	metadataFactory mf;
	XmlDocument met = mf.createMetadata(testMEssage, lsfiles);
	//std::cout<<met.toString();
	std::cout<<"\n ------ Create XML ------\n";
	mf.createXmlFile(&met,"test");
	std::cout << "\n ------ Reading XML ------\n";
	XmlDocument test= mf.readXmlFile("./test.xml");
	std::cout << test.toString();
	std::cout << "\n";
	std::string status = mf.readStatus(&test);
	std::cout << "\n ------ Status ------\n";
	std::cout << status;
	std::vector<std::string> dependancies = mf.readDependecies(&test);
	std::cout << "\n ------ Dependancies ------\n";
	for (std::string d : dependancies)
			std::cout << d << std::endl;
	return 0;
}

#endif //TEST_METADATAFACTORY


