#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

class Input {
private:
	std::string inputFileStr;
	std::vector<std::vector<int>> inputBlocks;

	void convertPT(std::string nPlainText);
	std::string createPlainText();
public:
	Input(std::string nInputFileStr);
	std::vector<std::vector<int>> getInputBlocks() { return inputBlocks; };
};

Input::Input(std::string nInputFileStr) {
	inputFileStr = nInputFileStr;
	std::string plainText = createPlainText();
	convertPT(plainText);
}

std::string Input::createPlainText() {
	std::ifstream inputFile(inputFileStr, std::ifstream::binary);

	if (!inputFile) {
		std::cout << "Unable to open input file!" << std::endl;
		return "";
	}
	
	std::istreambuf_iterator<char> begin(inputFile), end;
	return std::string(begin, end);
}

void Input::convertPT(std::string nPlainText) {
	int i = 0;
	std::vector<std::vector<int>> blocks;
	std::vector<int> * binary = new std::vector<int>;
	for (i = 0; i < (nPlainText.size() + 8 - nPlainText.size() % 8) * 8; i++) {
		if (i != 0 && i % 64 == 0) {
			blocks.push_back(*binary);
			binary = new std::vector<int>;
		}

		if (i < nPlainText.size() * 8) {
			binary->push_back(nPlainText.at(i / 8) >> (7 - (i % 8)) & 1);
		}
		else
			binary->push_back(0);
	}
	if (i - nPlainText.size() * 8 != 64) blocks.push_back(*binary);

	inputBlocks = blocks;
}