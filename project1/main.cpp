//
//  main.cpp
//  Project1
//
//  Created by greyson on 1/24/16.
//  Copyright © 2016 Greyson Wright. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int findWord(std::string word, std::vector<std::string> words) {
	
	int count = 0;
	std::vector<std::string>::iterator element = words.begin();
	
	if (words[0] == word) {
		++count;
	}
	while (element != words.end()) {
		
		element = std::find(element + 1, words.end(), word);
		++count;
		
	}
	
	return count - 1;
	
}

std::map<std::string, int> complexFindWord(std::string word, std::vector<std::string> words) {
	
	int count = 0;
	std::map<std::string, int> wordCounts;
	
	for (unsigned int i = 0; i < words.size(); ++i) {
		
		for (unsigned int p = 0; p < word.length(); ++p) {
			
			if (word[p] != '?' && word[p] != words[i][p]) {
				
				break;
				
			}
			
			if (p == word.length() - 1 && word.length() >= words[i].length()) {
				
				++count;
				++wordCounts[words[i]];
				
			}
			
		}
		
	}
	
	if (word.rfind('?') == 1) {
		
		word.erase(word.rfind('?'), 1);
		complexFindWord(word, words);
		
	}
	
	if (count == 0) {
		
		wordCounts[word] = 0;
		
	}
	
	return wordCounts;
	
}

int main(int argc, char **argv) {
	
	if (argc < 2) {
		
		std::cerr << "Please include a text file." << std::endl;
		exit(0);
		
	}
	
	char character;
	int uniqueCount = 0;
	std::string input;
	std::string word;
	std::vector<std::string> words;
	std::ifstream file(argv[1]);
	
	while (!file.eof()) {
		
		file.get(character);
		
		if (!isalpha(character) || file.eof()) {
			
			if (word.length() > 0) {
				
				if(std::find(words.begin(), words.end(), word) == words.end()) {
					
					++uniqueCount;
					
				}
				
				words.push_back(word);
				word = "";
				
			}
			
		} else {
			
			character = tolower(character);
			word += character;
			
		}
		
	}
	
	file.close();
	
	std::cout << "The number of unique words found in the file was " << uniqueCount << std::endl;
	std::cout << "The number of words found in the file was " << words.size() << std::endl << std::endl;
	
	while (true) {
		
		std::cout << "Please enter a word: ";
		std::cin >> input;
		
		if (input.find("?") == std::string::npos) {
			
			std::cout << "The word " << input << " appears " << findWord(input, words) << " times in the document " << std::endl << std::endl;
			
		} else {
			
			std::map<std::string, int> wordCounts = complexFindWord(input, words);
			
			for (auto i = wordCounts.begin(); i != wordCounts.end(); i++) {
				
				std::cout << "The word " << i->first << " appears " << i->second << " times in the document "<< std::endl;
				
			}
			
			std::cout << std::endl;
			
		}
		
	}
	
	return 0;
	
}
