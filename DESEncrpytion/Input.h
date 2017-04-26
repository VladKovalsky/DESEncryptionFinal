#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

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
	std::ifstream inputFile(inputFileStr, std::ifstream::binary);
	//if(decrypt) inputFile.open(inputFileStr, std::ifstream::binary);
	//else inputFile.open(inputFileStr);
	if (!inputFile) {
		std::cout << "Unable to open input file!" << std::endl;
		plainText = "";
		return;
	}
	
	std::istreambuf_iterator<char> begin(inputFile), end;
	plainText = std::string(begin, end);
}