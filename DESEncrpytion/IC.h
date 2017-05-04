#pragma once
#include <string>

double calcIC(std::string text) {
	double out = 0;
	int i = 0;
	int letterFreq[26];
	int size = 0;
	for (i = 0; i < 26; i++) {
		letterFreq[i] = 0;
	}
	for (i = 0; i < text.size(); i++) {
		if (text[i] >= 'a' && text[i] <= 'z') {
			letterFreq[text[i] - 'a']++;
			size++;
		}
		if (text[i] >= 'A' && text[i] <= 'Z') {
			letterFreq[text[i] - 'A']++;
			size++;
		}
	}

	for (i = 0; i < 26; i++) {
		out += letterFreq[i] * (letterFreq[i] - 1);
	}
	out = out / (size * (size - 1));
	out = out * 26;

	return out;
}