#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>

class IV {
private:
	std::vector<int> IVBlock;
	void generateIV();
	void loadIV();
	void createBlockIV(std::string textIV);
	void saveIV(std::string textIV);
public:
	IV(int decrypt);
	std::vector<int> getIVBlock() { return IVBlock; };
};

IV::IV(int decrypt) {
	if (!decrypt) {
		generateIV();
	}
	else {
		loadIV();
	}
}

void IV::generateIV() {
	int i = 0;
	std::string textIV;
	for(i = 0; i < 8; i++)
		textIV.push_back(rand() % 256);

	createBlockIV(textIV);
	saveIV(textIV);
}

void IV::loadIV() {
	std::ifstream inputFile("IV.txt", std::ifstream::binary);

	if (!inputFile) {
		std::cout << "IV file does not exist: making new IV file to continue execution (will encrypt again)" << std::endl;
		generateIV();
		return;
	}

	std::istreambuf_iterator<char> begin(inputFile), end;

	createBlockIV(std::string(begin, end));
}

void IV::createBlockIV(std::string textIV) {
	int i = 0;
	for (i = 0; i < 64; i++) {
		if (i < textIV.size() * 8) {
			IVBlock.push_back(textIV.at(i / 8) >> (7 - (i % 8)) & 1);
		}
		else
			IVBlock.push_back(0);
	}
}

void IV::saveIV(std::string textIV) {
	std::ofstream outputFile("IV.txt", std::ofstream::binary);
	outputFile << textIV;
}