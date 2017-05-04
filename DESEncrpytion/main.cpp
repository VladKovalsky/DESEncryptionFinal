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
	std::string outFilePath = "";
	int decrypt = 0;
	int keyGen = 0;
	float sec;
	
	srand(time(NULL));

	//Key will NOT be generated when decrypting (unless the key.txt file does exist in root)
	if (argc != 6) {
		std::cout << "Correct usage: DESEncryption plainTextFile/cipherTextFile cipherTextFile/plainTextFile keyMode(g for generate, l for load) mode(ECB,CBC,etc..) encrypt/decrypt(e/d)" << std::endl;
		return -1;
	}

	filePath = argv[1];
	outFilePath = argv[2];
	if (argv[5][0] == 'd') decrypt = 1;
	if (argv[3][0] == 'g' && !decrypt) keyGen = 1;

	Input newInput(filePath);
	t = clock();
	Modes stardModeCipher(argv[4], newInput.getInputBlocks(), keyGen, decrypt);
	sec = (clock() - t)/CLOCKS_PER_SEC;
	Output newOutput(stardModeCipher.getEncrypteBlocks(), outFilePath, decrypt);
	return 0;
}