#include "Input.h"
#include <iostream>
#include <string>
#include "DES.h"
#include "Output.h"
#include "Modes.h"
#include <Windows.h>
#include <time.h>
int main(int argc, char* argv[]) {
	clock_t t;
	std::string filePath = "";
	std::string key = "";
	std::string outFilePath = "";
	int decrypt = 0;
	float sec;
	
	if (argc != 6) {
		std::cout << "Correct usage: DESEncryption plainTextFile/cipherTextFile cipherTextFile/plainTextFile key mode(ECB,CBC,etc..) encrypt/decrypt(e/d)" << std::endl;
		return -1;
	}

	filePath = argv[1];
	outFilePath = argv[2];
	key = argv[3];
	if (argv[5][0] == 'd') decrypt = 1;

	//NOTE: IF DECRYPTING, IF THE INPUT FILE (CIPHERTEXTFILE) IS NOT PURE BINARY, THE OUTPUT WILL BE BLANK (as it should be)
	Input newInput(filePath);
	t = clock();
	Modes stardModeCipher(argv[4], newInput.getInputBlocks(), key, decrypt);
	sec = (clock() - t)/CLOCKS_PER_SEC;
	Output newOutput(stardModeCipher.getEncrypteBlocks(), outFilePath, decrypt);
	return 0;
}