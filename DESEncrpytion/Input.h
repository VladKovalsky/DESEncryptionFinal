#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Input {
private:
	std::string inputFileStr;
	std::string plainText;
public:
	Input(std::string nInputFileStr);
	std::string getPlainText() { return plainText; };
	void createPlainText();
};

Input::Input(std::string nInputFileStr) {
	inputFileStr = nInputFileStr;
	createPlainText();
}

void Input::createPlainText() {
	std::ifstream inputFile(inputFileStr);
	if (!inputFile) {
		std::cout << "Unable to open input file!" << std::endl;
		plainText = "";
		return;
	}
	
	std::stringstream tempStream;
	tempStream << inputFile.rdbuf();
	plainText = tempStream.str();
}