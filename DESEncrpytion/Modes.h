#pragma once
#include "DES.h"
#include "IV.h"
#include "Key.h"
#include "SideFunctions.h"

class Modes {
private:
	std::vector<int> key;
	std::vector<std::vector<int>> modeBlocks;
	void ECB(std::vector<std::vector<int>> blocks, int decrypt);
	void CBC(std::vector<std::vector<int>> blocks, int decrypt);
	void CFB(std::vector<std::vector<int>> blocks, int decrypt);
	void OFB(std::vector<std::vector<int>> blocks, int decrypt);
	void CTR(std::vector<std::vector<int>> blocks, int decrypt);

public:
	Modes(char* type, std::vector<std::vector<int>> blocks, int genKey, int decrypt);
	std::vector<std::vector<int>> getEncrypteBlocks() { return modeBlocks; };
};

Modes::Modes(char* type, std::vector<std::vector<int>> blocks, int genKey, int decrypt) {
	key = Key(genKey).getKeyBlock();
	if (strcmp(type, "ECB") == 0 || strcmp(type, "ecb") == 0) {
		ECB(blocks, decrypt);
	}
	else if (strcmp(type, "CBC") == 0 || strcmp(type, "cbc") == 0) {
		CBC(blocks, decrypt);
	}
	else if (strcmp(type, "CFB") == 0 || strcmp(type, "cfb") == 0) {
		CFB(blocks, decrypt);
	}
	else if (strcmp(type, "OFB") == 0 || strcmp(type, "ofb") == 0) {
		OFB(blocks, decrypt);
	}
	else if (strcmp(type, "CTR") == 0 || strcmp(type, "ctr") == 0) {
		CTR(blocks, decrypt);
	}
}
void Modes::ECB(std::vector<std::vector<int>> blocks, int decrypt) {
	int i = 0;
	for (i = 0; i < blocks.size(); i++) {
		modeBlocks.push_back(DES(blocks[i], key, decrypt).getEncryptedBlock());
	}
}

void Modes::CBC(std::vector<std::vector<int>> blocks, int decrypt) {
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

void Modes::CFB(std::vector<std::vector<int>> blocks, int decrypt) {
	int i = 0;
	std::vector<int> temp;
	
	if (!decrypt) {
		temp = IV(decrypt).getIVBlock();
		for (i = 0; i < blocks.size(); i++) {
			temp = DES(temp, key, decrypt).getEncryptedBlock();
			temp = xorVector(temp, blocks[i]);
			modeBlocks.push_back(temp);
		}
	}
	else {
		temp = IV(decrypt).getIVBlock();
		for (i = 0; i < blocks.size(); i++) {
			temp = DES(temp, key, !decrypt).getEncryptedBlock();
			temp = xorVector(temp, blocks[i]);
			modeBlocks.push_back(temp);
			temp = blocks[i];
		}
	}
}


void Modes::OFB(std::vector<std::vector<int>> blocks, int decrypt) {
	int i = 0;
	std::vector<int> temp;
	temp = IV(decrypt).getIVBlock();
	for (i = 0; i < blocks.size(); i++) {
		temp = DES(temp, key, 0).getEncryptedBlock();
		modeBlocks.push_back(xorVector(temp, blocks[i]));
	}
}

void Modes::CTR(std::vector<std::vector<int>> blocks, int decrypt) {
	int i = 0;
	std::vector<int> temp;
	temp = IV(decrypt).getIVBlock();
	for (i = 0; i < blocks.size(); i++) {
		modeBlocks.push_back(xorVector(DES(temp, key, 0).getEncryptedBlock(), blocks[i]));
		temp = incrBin(temp);
	}
}