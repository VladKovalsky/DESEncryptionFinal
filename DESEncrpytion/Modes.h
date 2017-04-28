#pragma once
#include "DES.h"
#include "IV.h"
#include "SideFunctions.h"

class Modes {
private:
	std::vector<std::vector<int>> modeBlocks;
	void ECB(std::vector<std::vector<int>> blocks, std::string key, int decrypt);
	void CBC(std::vector<std::vector<int>> blocks, std::string key, int decrypt);
public:
	Modes(char* type, std::vector<std::vector<int>> blocks, std::string key, int decrypt);
	std::vector<std::vector<int>> getEncrypteBlocks() { return modeBlocks; };
};

Modes::Modes(char* type, std::vector<std::vector<int>> blocks, std::string key, int decrypt) {
	if (strcmp(type, "ECB") == 0 || strcmp(type, "ecb") == 0) {
		ECB(blocks, key, decrypt);
	}
	else if (strcmp(type, "CBC") == 0 || strcmp(type, "cbc") == 0) {
		CBC(blocks, key, decrypt);
	}
}
void Modes::ECB(std::vector<std::vector<int>> blocks, std::string key, int decrypt) {
	int i = 0;
	for (i = 0; i < blocks.size(); i++) {
		modeBlocks.push_back(DES(blocks[i], key, decrypt).getEncryptedBlock());
	}
}

void Modes::CBC(std::vector<std::vector<int>> blocks, std::string key, int decrypt) {
	int i = 0;
	std::vector<int> temp;
	if (!decrypt) {
		temp = IV(decrypt).getIVBlock();
		for (i = 0; i < blocks.size(); i++) {
			temp = xorVector(temp, blocks[i]);
			temp = DES(temp, key, decrypt).getEncryptedBlock();
			modeBlocks.push_back(temp);
		}
	}
	else {
		temp = IV(decrypt).getIVBlock();
		for (i = 0; i < blocks.size(); i++) {
			modeBlocks.push_back(xorVector(DES(blocks[i], key, decrypt).getEncryptedBlock(), temp));
			temp = blocks[i];
		}
	}
}