#include "HttpMessage.h"
//////////////////////////////////////////////////////////////////////////
// HttpMessage.cpp - Provides Structure for HttpMessage					// 
// Ver 1.0																//
// Application: Project #4 Dependency-Based Remote Code Repository      //
// Language:    C++, Visual Studio 2015									//
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10					//
// Author:      Achal Velani, SUID:292190387							//
// Reference:   Jim Fawcett, CST 4-187, Syracuse University				//
//              (315) 443-3948, jfawcett@twcny.rr.com					//
//////////////////////////////////////////////////////////////////////////

//This funcion will convert HttpMessage object to string type.
std::string HttpMessage::createHeaderMessage(HttpMessage msg){
	std::string message = COMMAND;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += msg.command;
	message.append(1, ETX);
	message += SOURCE_ADD;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += msg.sourceAddress;
	message.append(1, ETX);
	message += SOURCE_PORT;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += std::to_string(msg.senderPort);;
	message.append(1, ETX);
	message += DESTINATION_ADD;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += msg.destAdd;
	message.append(1, ETX);
	message += DESTINATION_PORT;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += std::to_string(msg.destPort);
	message.append(1, ETX);
	message += FILE_NAME;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += msg.fileName;
	message.append(1, ETX);
	message += STATUS;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += msg.status;
	message.append(1, ETX);
	message += DEPENDANCIES;
	message.append(1, KEY_VALUE_PAIR_SEP);
	for (std::string d : msg.dependancies){
		message += d;
		message.append("<");
	}
	message.append(1, ETX);
	message += CONTENT;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += msg.content;
	message.append(1, ETX);
	message += CONTENT_LENGTH;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += std::to_string(msg.contentLength);
	message.append(1, ETX);
	message += msg.body;
	return message;
}

//This function will help in creating the Http stype operation message.
std::string HttpMessage::createOperation(std::string command, std::string fileName, std::string destAdd, int destPort, std::string body){
	std::string message = COMMAND;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += command;
	message.append(1, ETX);

	message += FILE_NAME;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += fileName;
	message.append(1, ETX);

	message += DESTINATION_ADD;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += destAdd;
	message.append(1, ETX);

	message += DESTINATION_PORT;
	message.append(1, KEY_VALUE_PAIR_SEP);
	message += std::to_string(destPort);

	if (body.size() > 0){
		message.append(1, ETX);
		message += OPERATION_BODY;
		message.append(1, KEY_VALUE_PAIR_SEP);
		message += body;
	}
	return message;
}

//This function is used to split a string with specific sperarator, this will return vector of string.
std::vector<std::string> HttpMessage::split(std::string message, char seperator){
	std::vector<std::string> elements;
	std::stringstream ss(message);
	std::string item;
	while (std::getline(ss, item, seperator)){
		elements.push_back(item);
	}
	return elements;
}

// This function will create map out of the attributes.
std::map<std::string, std::string> HttpMessage::createMap(std::vector<std::string> headerAttributes){
	std::map<std::string, std::string> attributeMap;

	for (auto item : headerAttributes){
		auto vectorKeyValue = split(item, KEY_VALUE_PAIR_SEP);
		if (vectorKeyValue.size() >= 2){
			attributeMap[vectorKeyValue[0]] = vectorKeyValue[1];
		}
	}
	return attributeMap;
}

//This function will help in parshing the string message to Httpstyle message.
HttpMessage HttpMessage::parseMessage(std::string message){
	HttpMessage parsedMessage;
	if (message.size() > 0){
		std::vector<std::string> elements = split(message, ETX);
		if (elements.size() == 0)
			return parsedMessage;
		std::map<std::string, std::string>  headerData = createMap(elements);
		if (headerData.size() > 0){
			parsedMessage.command = headerData[COMMAND];
			parsedMessage.sourceAddress = headerData[SOURCE_ADD];
			parsedMessage.senderPort = stoi(headerData[SOURCE_PORT]);
			parsedMessage.destAdd = headerData[DESTINATION_ADD];
			parsedMessage.destPort = stoi(headerData[DESTINATION_PORT]);
			parsedMessage.fileName = headerData[FILE_NAME];
			parsedMessage.content = headerData[CONTENT];
			parsedMessage.contentLength = stoi(headerData[CONTENT_LENGTH]);
			parsedMessage.status = headerData[STATUS];
			parsedMessage.dependancies = parsedMessage.depSplit(headerData[DEPENDANCIES]);
			std::string temp;
			temp.append(1, ETX);
			unsigned found = message.find_last_of(temp);
			parsedMessage.body = message.substr(found + 1);
		}
		return parsedMessage;
	}
	return parsedMessage;
}

// This function will seprate packages in the body of the message.
std::vector<std::string> HttpMessage::depSplit(std::string dep){
	std::string input = dep;
	std::istringstream ss(input);
	std::string token;
	std::vector<std::string> ret;
	while (std::getline(ss, token, '<')){
		ret.push_back(token);
	}
	return ret;
}

//This function will extractPackageName from the responce
std::vector<std::string> HttpMessage::extractPackageName_Responce(std::string rcvString){
	std::vector<std::string> returnVector;
	std::string input = rcvString;
	std::istringstream ss(input);
	std::string token;
	while (std::getline(ss, token, ':')) {
		returnVector.push_back(token);
	}
	return returnVector;
}

#ifdef TEST_HTTPMESSAGE
int main()
{
	std::cout << " Demonstrate Http Message class " << std::endl;
	std::cout << "================================" << std::endl;
	std::cout << std::endl;
	HttpMessage msg;
	msg.command = CHECK_IN;
	msg.sourceAddress = "localhost";
	msg.destAdd = "localhost";
	msg.destPort = 9090;
	msg.senderPort = 9091;
	msg.fileName = "test.txt";
	msg.content = "file";
	msg.contentLength = 0;
	std::string temp = msg.createHeaderMessage(msg);
	std::cout << " Created message without body is : " << temp << std::endl;
	std::cout << std::endl;
	msg.body = "hello how are you.";
	msg.contentLength = msg.body.length();

	temp = msg.createHeaderMessage(msg);
	std::cout << " Created message with body is : " << temp << std::endl;
	std::cout << std::endl;
	std::vector<std::string> vectorOfAttributes = msg.split(temp, ETX);
	std::cout << "Http Message attributes list : " << std::endl;
	std::cout << std::endl;
	for (auto attribute : vectorOfAttributes)
	{
		std::cout << "     " << attribute << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Http Message attribute key-value pairs : " << std::endl;
	std::cout << std::endl;
	std::map<std::string, std::string> mapOfKeyValuePair = msg.createMap(vectorOfAttributes);
	for (auto keyvaluePair : mapOfKeyValuePair){
		std::cout << "     " << keyvaluePair.first << " : " << keyvaluePair.second << std::endl;
	}

	return 0;
}
#endif