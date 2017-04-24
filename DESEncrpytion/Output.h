#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Output {
public:
	Output(std::string cipherText);
};

Output::Output(std::string cipherText) {
	std::ofstream outputFile("cipher.txt");
	outputFile << cipherText;
}
