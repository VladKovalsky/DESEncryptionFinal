#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>

class Key {
private:
	std::vector<int> KeyBlock;
	void generateKey();
	void loadKey();
	void createBlockKey(std::string textKey);
	void saveKey(std::string textKey);
public:
	Key(int genKey);
	std::vector<int> getKeyBlock() { return KeyBlock; };
};

Key::Key(int genKey) {
	if (genKey) {
		generateKey();
	}
	else {
		loadKey();
	}
}

void Key::generateKey() {
	int i = 0;
	std::string textKey;
	for (i = 0; i < 8; i++)
		textKey.push_back(rand() % 256);

	createBlockKey(textKey);
	saveKey(textKey);
}

void Key::loadKey() {
	std::ifstream inputFile("key.txt", std::ifstream::binary);

	if (!inputFile) {
		std::cout << "Key file does not exist (key.txt not in root): making new Key file to continue execution (will not decrypt properly)" << std::endl;
		generateKey();
		return;
	}

	std::istreambuf_iterator<char> begin(inputFile), end;

	createBlockKey(std::string(begin, end));
}

void Key::createBlockKey(std::string textKey) {
	int i = 0;
	for (i = 0; i < 64; i++) {
		if (i < textKey.size() * 8) {
			KeyBlock.push_back(textKey.at(i / 8) >> (7 - (i % 8)) & 1);
		}
		else
			KeyBlock.push_back(0);
	}
}

void Key::saveKey(std::string textKey) {
	std::ofstream outputFile("key.txt", std::ofstream::binary);
	outputFile << textKey;
}