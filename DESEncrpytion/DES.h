#pragma once
#include <string>
#include <vector>
#include "SideFunctions.h"
#include <math.h>

class DES {
private:
	std::string cipherText;
public:
	 DES(std::string nPlainText, std::string nKey, int decrypt);
	 std::vector<int> convertKey(std::string nKeyText);
	 std::vector<std::vector<int>> convertPT(std::string nPlainText, int decrypt);
	 std::vector<int> roundPerm(std::vector<int> left, std::vector<int> right, std::vector<std::vector<int>> keySchedule, int round, int keyRound, int decrypt);
	 std::vector<int> feistelFun(std::vector<int> halfBlack, std::vector<int> key);
	 std::vector<int> expand(std::vector<int> halfBlock);
	 std::vector<int> SBoxExpansion(std::vector<int> block);
	 std::vector<int> P(std::vector<int> block);
	 std::vector<int> IP(std::vector<int> block);
	 std::vector<int> IPINV(std::vector<int> block);
	 std::vector<int> PC1(std::vector<int> block);
	 std::vector<int> PC2(std::vector<int> block);
	 void createCipherText(std::vector<std::vector<int>> blocks, int decrypt);
	 std::vector<int> keyShift(std::vector<int>, int round);
	 std::vector<std::vector<int>> createKeySchedule(std::vector<int> key);

	 std::string DES::getCipherText() { return cipherText; };
};
 std::vector<int> DES::PC1(std::vector<int> block) {
	int PC1Table[56] = {
		57,	49,	41,	33,	25,	17,	9,
		1,	58,	50,	42,	34,	26,	18,
		10,	2,	59,	51,	43,	35,	27,
		19,	11,	3,	60,	52,	44,	36,
		63,	55,	47,	39,	31,	23,	15,
		7,	62,	54,	46,	38,	30,	22,
		14,	6,	61,	53,	45,	37,	29,
		21,	13,	5,	28,	20,	12,	4
	};
	std::vector<int> blockOut;
	int i = 0;
	for (i = 0; i < 56; i++) {
		blockOut.push_back(block[PC1Table[i] - 1]);
	}
	return blockOut;
}

 std::vector<int> DES::PC2(std::vector<int> block) {
	int PC2Table[48] = {
		14,	17,	11,	24,	1,	5,
		3,	28,	15,	6,	21,	10,
		23,	19,	12,	4,	26,	8,
		16,	7,	27,	20,	13,	2,
		41,	52,	31,	37,	47,	55,
		30,	40,	51,	45,	33,	48,
		44,	49,	39,	56,	34,	53,
		46,	42,	50,	36,	29,	32
	};
	std::vector<int> blockOut;
	int i = 0;
	for (i = 0; i < 48; i++) {
		blockOut.push_back(block[PC2Table[i] - 1]);
	}
	return blockOut;
}

 std::vector<int> DES::IP(std::vector<int> block) {
	int IPTable[64] = {
		58,	50,	42,	34,	26,	18,	10,	2,
		60,	52,	44,	36,	28,	20,	12,	4,
		62,	54,	46,	38,	30,	22,	14,	6,
		64,	56,	48,	40,	32,	24,	16,	8,
		57,	49,	41,	33,	25,	17,	9,	1,
		59,	51,	43,	35,	27,	19,	11,	3,
		61,	53,	45,	37,	29,	21,	13,	5,
		63,	55,	47,	39,	31,	23,	15,	7
	};
	std::vector<int> blockOut;
	int i = 0;
	for (i = 0; i < 64; i++) {
		blockOut.push_back(block[IPTable[i] - 1]);
	}
	return blockOut;
}

 std::vector<int> DES::IPINV(std::vector<int> block) {
	int IPINVTable[64] = {
		40,	8,	48,	16,	56,	24,	64,	32,
		39,	7,	47,	15,	55,	23,	63,	31,
		38,	6,	46,	14,	54,	22,	62,	30,
		37,	5,	45,	13,	53,	21,	61,	29,
		36,	4,	44,	12,	52,	20,	60,	28,
		35,	3,	43,	11,	51,	19,	59,	27,
		34,	2,	42,	10,	50,	18,	58,	26,
		33,	1,	41,	9,	49,	17,	57,	25
	};
	std::vector<int> blockOut;
	int i = 0;
	for (i = 0; i < 64; i++) {
		blockOut.push_back(block[IPINVTable[i] - 1]);
	}
	return blockOut;
}

DES::DES(std::string nPlainText, std::string nKey, int decrypt) {
	std::vector<std::vector<int>> blocks = convertPT(nPlainText, decrypt);
	std::vector<int> key = convertKey(nKey);
	std::vector<std::vector<int>> cipherBlocks;

	int i = 0;
	std::vector<int> * temp;
	std::vector<std::vector<int>> keySchedule = createKeySchedule(key);
	for (i = 0; i < blocks.size(); i++) {
		temp = new std::vector<int>;
		*temp = IP(blocks.at(i));
		*temp = roundPerm(std::vector<int>(temp->begin(), temp->begin() + 32), std::vector<int>(temp->begin() + 32, temp->end()), keySchedule, 0, decrypt*15, decrypt); //keyRound argument is 0 if decrypt is false, 15 if decrypt is true (easy way)
		*temp = IPINV(*temp);
		cipherBlocks.push_back(*temp);
	}

	createCipherText(cipherBlocks, decrypt);
}

void DES::createCipherText(std::vector<std::vector<int>> blocks, int decrypt) {
	int i = 0;
	int j = 0;
	int temp = 0;
	cipherText.clear();
	if (!decrypt) {
		for (i = 0; i < blocks.size(); i++) {
			temp = 0;
			for (j = 0; j < blocks[i].size(); j++) {
				cipherText.push_back(std::to_string(blocks[i][j])[0]);
			}
		}
	}
	else {
		for (i = 0; i < blocks.size(); i++) {
			temp = 0;
			for (j = 0; j < blocks[i].size(); j++) {
				temp |= blocks[i][j] * (int)pow(2, 7 - (j % 8));

				if ((j + 1) % 8 == 0) {
					cipherText.push_back(temp);
					temp = 0;
				}
			}
		}
	}
}

std::vector<std::vector<int>> DES::createKeySchedule(std::vector<int> key) {
	key = PC1(key);
	std::vector<std::vector<int>> keySchedule;
	int i = 0;
	for (i = 0; i < 16; i++) {
		key = keyShift(key, i + 1);
		keySchedule.push_back(PC2(key));
	}

	return keySchedule;
}

 std::vector<int> DES::roundPerm(std::vector<int> left,  std::vector<int> right,  std::vector<std::vector<int>> keySchedule, int round, int keyRound, int decrypt) {
	std::vector<int> temp;
	if (round < 16) {
		left = xorVector(left, feistelFun(right, keySchedule[keyRound]));
		if (!decrypt) keyRound++;
		else keyRound--;

		if (round == 15) {//16th round
			left.insert(left.end(), right.begin(), right.end());
			return left;
		}

		temp = roundPerm(right, left, keySchedule, round + 1, keyRound, decrypt);
	}
	
	return temp;
}

 std::vector<int> DES::keyShift( std::vector<int> key, int round) {
	int shiftAmount = 0;
	switch (round) {
	case 16:
	case 15:
	case 8:
	case 1:
		shiftAmount = 1;
		break;
	default:
		shiftAmount = 2;
		break;
	}

	std::vector<int> leftKey = rotateLeft(std::vector<int>(key.begin(), key.begin() + 28), shiftAmount);
	std::vector<int> rightKey = rotateLeft(std::vector<int>(key.begin() + 28, key.end()), shiftAmount);

	key = leftKey;
	key.insert(key.end(), rightKey.begin(), rightKey.end());

	return key;
}

 std::vector<int> DES::convertKey(std::string nKeyText) {
	int i = 0;
	std::vector<int> key;
	for (i = 0; i < 64; i++) {

		if (i < nKeyText.size() * 8) {
			key.push_back(nKeyText.at(i / 8) >> (7 - (i % 8)) & 1);
		}
		else
			key.push_back(0);
	}
	return key;
}

std::vector<std::vector<int>> DES::convertPT(std::string nPlainText, int decrypt) {
	int i = 0;
	std::vector<std::vector<int>> blocks;
	std::vector<int> * binary = new std::vector<int>;
	if (!decrypt) {
		for (i = 0; i <= (nPlainText.size() + 8 - nPlainText.size() % 8) * 8; i++) {
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
	}
	else {
		for (i = 0; i < nPlainText.size(); i++) {
			if (i != 0 && i % 64 == 0) {
				blocks.push_back(*binary);
				binary = new std::vector<int>;
			}

			if ((int)nPlainText[i] - 48 != 0 || (int)nPlainText[i] - 48 != 1) {
				blocks.clear();
				return blocks;
			}
			binary->push_back((int)nPlainText[i] - 48);
		}
	}

	return blocks;
}

std::vector<int> DES::feistelFun(std::vector<int> halfBlock, std::vector<int> key) {
	std::vector<int> step = expand(halfBlock);
	step = xorVector(step, key); //assumes key is 48 bits here
	step = SBoxExpansion(step);
	step = P(step);
	return step;
}

 std::vector<int> DES::expand(std::vector<int> halfBlock) {
	int expansionTable[48] = { 32, 	1, 	2,	3, 	4, 	5,
		4, 	5, 	6, 	7, 	8, 	9,
		8, 	9, 	10, 	11, 	12, 	13,
		12, 	13, 	14, 	15, 	16, 	17,
		16, 	17, 	18, 	19, 	20, 	21,
		20, 	21, 	22, 	23, 	24, 	25,
		24, 	25, 	26, 	27, 	28, 	29,
		28, 	29, 	30, 	31, 	32, 	1 };
	int i = 0;
	std::vector<int> expanded;
	for (i = 0; i < 48; i++) {
		expanded.push_back(halfBlock[expansionTable[i] - 1]);
	}

	return expanded;
}

 std::vector<int> DES::SBoxExpansion(std::vector<int> block) {
	int SBox[8][64] = { {14,	4,	13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7,
		0,	15,	7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8,
		4,	1,	14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0,
		15,	12,	8,	2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13},
		{15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5,	10,
		3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5,
		0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15,
		13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9},
		{10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8,
		13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1,
		13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7,
		1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12},
		{7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15,
		13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9,
		10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4,
		3,	15,	0,	6,	10,	1,	13,	8,	9,	4,	5,	11,	12,	7,	2,	14},
		{ 2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9,
		14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	6,
		4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14,
		11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3 },
		{ 12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11,
		10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8,
		9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6,
		4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13 },
		{ 4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1,
		13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6,
		1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2,
		6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12 },
		{ 13,	2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7,
		1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2,
		7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8,
		2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11 } };

	int i = 0;
	int row = 0;
	int col = 0;
	std::vector<int> blockOut;
	for (i = 0; i < 8; i++) {
		row = block[i * 6] * 2 + block[5 + i * 6];
		col = block[1 + i * 6] * 8 + block[2 + i * 6] * 4 + block[3 + i * 6] * 2 + block[4 + i * 6];
		blockOut.push_back(SBox[i][col + row * 16] >> 3 & 1);
		blockOut.push_back(SBox[i][col + row * 16] >> 2 & 1);
		blockOut.push_back(SBox[i][col + row * 16] >> 1 & 1);
		blockOut.push_back(SBox[i][col + row * 16] & 1);
	}

	return blockOut;
}

 std::vector<int> DES::P(std::vector<int> block) {
	int PTable[32] = { 16,	7,	20,	21,	29,	12,	28,	17,
		1,	15,	23,	26,	5,	18,	31,	10,
		2,	8,	24,	14,	32,	27,	3,	9,
		19,	13,	30,	6,	22,	11,	4,	25 };

	std::vector<int> blockOut;

	int i = 0;
	for (i = 0; i < 32; i++) {
		blockOut.push_back(block[PTable[i] - 1]);
	}

	return blockOut;
}
