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
	int value;
	bool isEmpty;
	Hashable();
	Hashable(int value, std::string key);
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
 	int valueForKey(std::string key);
};

Hashable::Hashable() {
	key = "";
	value = 0;
	isEmpty = true;
}

Hashable::Hashable(int value, std::string key) {
	this->value = value;
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
	char *string = (char *)malloc(sizeof(str));
	int c;

	strcpy(string, str);
	while ((c = (*string)++)) {
		hash = ((hash << 5) + hash) + c;
	}

	string = 0;
	free(string);
	return hash;
}

void HashMap::insert(int value, std::string key) {
	Hashable hashable(value, key);
 	char *cKey = (char *)key.c_str();
	unsigned long hashVal = hash(cKey) % size;

	while (values[hashVal].key != key && !values[hashVal].isEmpty) {
		hashVal = (long)pow((hashVal + 1), option) % size;
		++collisions;
	}

	values[hashVal] = hashable;
	++count;
}

int HashMap::valueForKey(std::string key) {
	char *cKey = (char *)key.c_str();
	unsigned long hashVal = hash(cKey) % size;

	while (values[hashVal].key != key && !values[hashVal].isEmpty) {
		hashVal = (long)pow((hashVal + 1), option) % size;
	}

	return values[hashVal].value;
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
			if (!isalpha(c) || file.eof()) {
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
		++lineCount;
	}

	file.close();
	return contents;
}

void printResults(int wordCount, HashMap contents, std::vector<std::string> queryContents) {
	std::cout << "The number of words found in the file was " << wordCount << std::endl;
	std::cout << "The number of unique words found in the file was " << contents.count << std::endl;
	std::cout << "The number of collisions was " << contents.collisions << std::endl;
	for (std::string word : queryContents) {
		std::cout << contents.valueForKey(word) << std::endl;
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
