//
//  main.cpp
//  Project2
//
//  Created by greyson on 2/10/16.
//  Copyright © 2016 Greyson Wright. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

class DataRow {
	
public:
	
	std::vector<std::string> columns;
	
	DataRow(std::string line);
	void write(std::ofstream &file);
	
};

class DataTable {
	
	DataRow header = DataRow("");
	std::vector<std::vector<std::string>> fileOptions;
	
	void readInFile(std::ifstream &file);
	void readOptionsFile(std::ifstream &file);
	void merge(std::vector<DataRow> &vec, std::vector<DataRow> &vec1, std::vector<DataRow> &vec2, std::vector<std::string> &options);
	void sort(std::vector<DataRow> &vec, std::vector<std::string> &options);
	void writeHeader(std::ofstream &file);
	bool compareValues(std::string c1, std::string c2, std::vector<std::string> &options);
	bool compareValues(float c1, float c2, std::vector<std::string> &options);
	
public:
	
	std::vector<DataRow> rows;
	
	DataTable(std::ifstream &inFile, std::ifstream &optionsFile);
	void write(std::ofstream &file);
	void sort();
	
};

//DataRow Public

DataRow::DataRow(std::string line) {
	
	std::string currentWord;
	
	for (unsigned int i = 0; i <= line.length(); ++i) {
		
		if (line[i] == ',' || i == line.length() - 1) {
			
			if (line[i] != ',') {
				
				currentWord += line[i];
				
			}
			
			columns.push_back(currentWord);
			currentWord = "";
			
		} else {
			
			currentWord += line[i];
			
		}
		
	}
	
}

void DataRow::write(std::ofstream &file) {
	
	for (unsigned int i = 0; i < columns.size(); ++i) {

		file << columns[i];
		
		if (i < columns.size() - 1) {

			file << ',';

		}
		
	}
	
}

//DataTable Private
void DataTable::readInFile(std::ifstream &file) {
	
	int count = 0;
	std::string line;
	
	while (std::getline(file, line) && line != "") {
		
		if (count > 0) {
			
			DataRow *row = new DataRow(line);
			rows.push_back(*row);
			delete row;
			
		} else {
			
			header = DataRow(line);
			
		}
		
		++count;
		
	}
	
	file.close();
	
}

void DataTable::readOptionsFile(std::ifstream &file) {
	
	std::string line;
	std::string currentWord;
	int count = 0;
	
	while (std::getline(file, line) && line != "") {
		
		std::vector<std::string> options;
		
		for (unsigned int i = 0; i < line.length(); ++i) {

			if (line[i] == ',' || i == line.length() - 1) {

				if (count == 0) {
					
					for (unsigned int i = 0; i < header.columns.size(); ++i) {
						
						if (header.columns[i] == currentWord) {
							
							currentWord = std::to_string(i);
							options.push_back(currentWord);
							currentWord = "";
							++count;
							
						}
						
					}
					
				} else {
					
					if (line[i] != ',') {
						
						currentWord += line[i];
						
					}
					options.push_back(currentWord);
					currentWord = "";
					++count;
					
				}
				
			} else {
				
				currentWord += line[i];
				
			}
			
			
		}
		
		fileOptions.push_back(options);
		count = 0;
		
	}
	
	file.close();
	
}

void DataTable::merge(std::vector<DataRow> &vec, std::vector<DataRow> &vec1, std::vector<DataRow> &vec2, std::vector<std::string> &options) {
	
	unsigned int p1 = 0;
	unsigned int p2 = 0;
	
	while (p1 < vec1.size() && p2 < vec2.size()) {

		if (options[2] == "float" || options[2] == "int") {

			if (compareValues(std::stof(vec1[p1].columns[std::stoi(options[0])]), std::stof(vec2[p2].columns[std::stoi(options[0])]), options)) {
				
				vec.push_back(vec1[p1++]);
				
			} else {
				
				vec.push_back(vec2[p2++]);
				
			}
			
		} else {

			if (compareValues(vec1[p1].columns[std::stoi(options[0])], vec2[p2].columns[std::stoi(options[0])], options)) {
				
				vec.push_back(vec1[p1++]);
				
			} else {
				
				vec.push_back(vec2[p2++]);
				
			}
			
		}
		
		
	}
	
	while (p1 < vec1.size()) {
		
		vec.push_back(vec1[p1++]);
		
	}
	while (p2 < vec2.size()) {
		
		vec.push_back(vec2[p2++]);
		
	}
	
}

void DataTable::sort(std::vector<DataRow> &vec, std::vector<std::string> &options) {
	
	long n = vec.size();
	
	if (n <= 1) {
		
		return;
		
	}
	
	std::vector<DataRow> vec1;
	std::vector<DataRow> vec2;
	
	for (unsigned int i = 0; i < n; ++i) {
		
		if (i < n / 2) {
			
			vec1.push_back(vec[i]);
			
		} else {
			
			vec2.push_back(vec[i]);
			
		}
		
	}
	
	sort(vec1, options);
	sort(vec2, options);
	vec.clear();
	merge(vec, vec1, vec2, options);
	
}

void DataTable::writeHeader(std::ofstream &file) {
	
	for (unsigned int i = 0; i < header.columns.size(); ++i) {

		file << header.columns[i];
		
		if (i < header.columns.size() - 1) {

			file << ',';

		}
		
	}
	file << std::endl;
	
}

bool DataTable::compareValues(std::string c1, std::string c2, std::vector<std::string> &options) {
	
	unsigned int length = c1.length() > c2.length() ? c1.length() : c2.length();

	for (unsigned int i = 0; i < length; ++i) {

		if (options[1] == "ascend") {

			if (c1[i] < c2[i]) {

				return true;

			}

			if (c1[i] > c2[i]) {

				return false;

			}

		}

		if (options[1] == "descend") {

			if (c1[i] > c2[i]) {

				return true;

			}

			if (c1[i] < c2[i]) {

				return false;

			}

		}
		
	}
	
	return true;
	
}

bool DataTable::compareValues(float c1, float c2, std::vector<std::string> &options) {
	
	return options[1] == "ascend" ? c2 >= c1 : c1 >= c2;
	
}

//DataTable Public

DataTable::DataTable(std::ifstream &inFile, std::ifstream &optionsFile) {
	
	readInFile(inFile);
	readOptionsFile(optionsFile);
	
}

void DataTable::write(std::ofstream &file) {
	
	writeHeader(file);
	
	for (DataRow row : rows) {
		
		row.write(file);
		file << std::endl;
		
	}
	
}

void DataTable::sort() {
	
	for (long i = fileOptions.size() - 1; i >= 0; --i) {
		
		sort(rows, fileOptions[i]);
		
	}
	
}

int main(int argc, char **argv) {
	
	std::ifstream optionsFile(argv[2]);
	std::ifstream inFile(argv[1]);
	std::ofstream outFile(argv[3]);
	
	if (optionsFile && inFile) {
		
		DataTable *dataTable = new DataTable(inFile, optionsFile);
		dataTable->sort();
		dataTable->write(outFile);
		delete dataTable;
		
	}
	
	return 0;
	
}
