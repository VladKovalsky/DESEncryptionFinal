#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Output {
public:
	Output(std::string cipherText, std::string filePath);
};

Output::Output(std::string cipherText, std::string filePath) {
	std::ofstream outputFile(filePath);
	outputFile << cipherText;
}
