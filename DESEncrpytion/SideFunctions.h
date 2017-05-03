#pragma once
#include <vector>
#include <math.h>

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

std::vector<int> incrBin(std::vector<int> in) {
	int i = 0;
	std::vector<int> out = in;
	for (i = 0; i < in.size(); i++) {
		if (out[63 - i] == 0) {
			out[63 - i] = 1;
			return out;
		}
		else {
			out[63 - i] = 0;
		}
	}
	return out;
}

std::vector<int> rotateLeft(std::vector<int> in, int num) {
	std::vector<int> out(in.begin() + num, in.end());
	out.insert(out.end(), in.begin(), in.begin() + num);
	return out;
}