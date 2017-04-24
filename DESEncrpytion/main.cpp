#include "Input.h"
#include <iostream>
#include <string>
#include "DES.h"
#include "Output.h"

int main(int argc, char* argv[]) {
	std::string filePath;
	std::string key;

	if (argc != 3) {
		std::cout << "Correct usage: DESEncryption plainTextFile key" << std::endl;
		return -1;
	}

	filePath = argv[1];
	key = argv[2];

	Input newInput(filePath);
	DES newDES(newInput.getPlainText(), key);
	Output newOutput(newDES.getCipherText());
	return 0;
}