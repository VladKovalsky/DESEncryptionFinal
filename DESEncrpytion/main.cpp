#include "Input.h"
#include <iostream>
#include <string>
#include "DES.h"
#include "Output.h"

int main(int argc, char* argv[]) {
	std::string filePath = "";
	std::string key = "";
	std::string outFilePath = "";
	int decrypt = 0;

	if (argc != 5) {
		std::cout << "Correct usage: DESEncryption plainTextFile/cipherTextFile cipherTextFile/plainTextFile key encrypt/decrypt(e/d)" << std::endl;
		return -1;
	}

	filePath = argv[1];
	outFilePath = argv[2];
	key = argv[3];
	if (argv[4][0] == 'd') decrypt = 1;

	//NOTE: IF DECRYPTING, IF THE INPUT FILE (CIPHERTEXTFILE) IS NOT PURE BINARY, THE OUTPUT WILL BE BLANK (as it should be)
	Input newInput(filePath);
	DES newDES(newInput.getPlainText(), key, decrypt);
	Output newOutput(newDES.getCipherText(), outFilePath);
	return 0;
}