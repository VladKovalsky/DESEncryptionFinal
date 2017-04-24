#pragma once
#include <vector>

std::vector<int> xorVector(std::vector<int> in1, std::vector<int> in2) {
	std::vector<int> out;
	if (in1.size() != in2.size())	
		return out;

	int i = 0;
	for (i = 0; i < in1.size(); i++) {
		out.push_back(in1.at(i) ^ in2.at(i));
	}
	return out;
}

long long int convertToLarge(std::vector<int> in, int bitSize) {
	int i = 0;
	long long int out = 0;
	for (i = in.size() - 1; i >= 0; i--) {
		out += ((2 ^ bitSize - 1) & in.at(i)) << i * bitSize;
	}

	return out;
}

std::vector<int> rotateLeft(std::vector<int> in, int num) {
	std::vector<int> out(in.begin() + num, in.end());
	out.insert(out.end(), in.begin(), in.begin() + num);
	return out;
}