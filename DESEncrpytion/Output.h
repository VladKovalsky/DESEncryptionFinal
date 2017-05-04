#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "IC.h"

class Output {
private:
	std::string outputText;
	void blocksToString(std::vector<std::vector<int>> blocks, int decrypt);
public:
	Output(std::vector<std::vector<int>> outputBlocks, std::string filePath, int decrypt);
};

Output::Output(std::vector<std::vector<int>> outputBlocks, std::string filePath, int decrypt) {
	std::ofstream outputFile(filePath, std::ofstream::binary);
	blocksToString(outputBlocks, decrypt);
	std::cout << "IC of output text: " << calcIC(outputText) << std::endl;
	outputFile << outputText;
}

void Output::blocksToString(std::vector<std::vector<int>> blocks, int decrypt) {
	int i = 0;
	int j = 0;
	int temp = 0;
	outputText.clear();
	for (i = 0; i < blocks.size(); i++) {
		temp = 0;
		for (j = 0; j < blocks[i].size(); j++) {
			temp |= blocks[i][j] * (int)pow(2, 7 - (j % 8));

			if ((j + 1) % 8 == 0) {
				if (decrypt == 0 || (decrypt == 1 && temp != 0)) outputText.push_back(temp);
				temp = 0;
			}
		}
	}
}
