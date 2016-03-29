//
//  Project4.cpp
//  Project4
//
//  Created by Greyson on 3/27/16.
//  Copyright © 2016 Greyson Wright. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>

class Hashable {
public:
	std::string key;
	std::vector<int> values;
	bool isEmpty;
	Hashable();
	void add(int value, std::string key);
};

class HashMap {
private:
	std::vector<Hashable> values;
	int size;
	int option;
	unsigned long hash(char *str);

public:
	int count;
	int collisions;
	HashMap(int size, int option);
	void removeKey(std::string key);
	void insert(int value, std::string key);
	std::vector<int> valueForKey(std::string key);
};

Hashable::Hashable() {
	key = "";
	isEmpty = true;
}

void Hashable::add(int value, std::string key) {
	this->values.push_back(value);
	this->key = key;
	isEmpty = false;
}

HashMap::HashMap(int size, int option) {
	this->size = size;
	this->option = option;
	collisions = 0;
	count = 0;
	values = std::vector<Hashable>(size);
}

unsigned long HashMap::hash(char *str) {
	unsigned long hash = 5381;
	char *stricd ng = (char *)malloc(sizeof(str));
	int c;

	strcpy(string, str);
	while ((c = *string++)) {
		hash = ((hash << 5) + hash) + c;
	}

	string = 0;
	free(string);
	return hash;
}

void HashMap::insert(int value, std::string key) {
	char *cKey = (char *)key.c_str();
	unsigned long hashVal = hash(cKey) % size;
	int i = 1;

	while (values[hashVal].key != key && !values[hashVal].isEmpty) {
		hashVal = (hashVal + (unsigned long)pow(i, option)) % size;
		++i;
		collisions++;
	}

	values[hashVal].add(value, key);
	++count;
}

std::vector<int> HashMap::valueForKey(std::string key) {
	char *cKey = (char *)key.c_str();
	unsigned long hashVal = hash(cKey) % size;
	int i = 1;

	while (values[hashVal].key != key && !values[hashVal].isEmpty) {
		hashVal = (hashVal + (unsigned long)pow(i, option)) % size;
		++i;
	}

	return values[hashVal].values;
}

std::vector<std::string> getFileContents(std::string fileName) {
	std::ifstream file(fileName);
	std::vector<std::string> contents;
	std::string line;

	while (getline(file, line)) {
		contents.push_back(line);
	}

	file.close();
	return contents;
}

HashMap getFileContents(std::string fileName, int size, int option, int &wordCount) {
	std::ifstream file(fileName);
	HashMap contents(size, option);
	std::string line;
	std::string word;
	int lineCount = 1;

	while (getline(file, line)) {
		for (char c : line) {
			if (!isalpha(c)) {
				if (word.length() > 0) {
					contents.insert(lineCount, word);
					word = "";
					++wordCount;
				}
			} else {
				c = tolower(c);
				word += c;
			}
		}
		if (word != "") {
			contents.insert(lineCount, word);
			word = "";
			++wordCount;
		}
		++lineCount;
	}

	file.close();
	return contents;
}

void printValues(std::vector<int> values) {
	std::cout << "[";
	for (int i = 0; i < values.size(); ++i) {
		std::cout << values[i];
		if (i != values.size() - 1) {
			std::cout << ",";
		}
	}
	std::cout << "]" << std::endl;
}

void printResults(int wordCount, HashMap contents, std::vector<std::string> queryContents) {
	std::cout << "The number of words found in the file was " << wordCount << std::endl;
	std::cout << "The number of unique words found in the file was " << contents.count << std::endl;
	std::cout << "The number of collisions was " << contents.collisions << std::endl;
	for (std::string word : queryContents) {
		std::cout << word;
		printValues(contents.valueForKey(word));
	}
}

int main(int argc, char **argv) {
	int option = !strcmp(argv[4], "lp") ? 1 : 2;
	int wordCount = 0;
	HashMap inputContents = getFileContents(argv[1], std::stoi(argv[3]), option, wordCount);
	std::vector<std::string> queryContents = getFileContents(argv[2]);

	printResults(wordCount, inputContents, queryContents);

	return 0;
}
