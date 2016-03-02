#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
	
	std::string line;
	std::vector<std::string> file0;
	std::vector<std::string> file1;
	int count = 0;
	bool lineErr = false;

	std::ifstream inFile0(argv[1]);
	if (inFile0) {
		while(getline(inFile0, line)) {
			file0.push_back(line);
		}
		inFile0.close();
	} else {
		std::cout << "Could not open " << argv[1] << std::endl;
		exit(-1);
	}

	std::ifstream inFile1(argv[2]);
	if (inFile1) {
		while(getline(inFile1, line)) {
			file1.push_back(line);
		}
		inFile1.close();
	} else {
		std::cout << "Could not open " << argv[2] << std::endl;
		exit(-1);
	}
	std::cout << "Checking output..." << std::endl;
	for (int p = 0; p < file0.size(); ++p) {
		for (int i = 0; i < file0[p].size(); ++i) {
			if (file0[p][i] != file1[p][i]) {
				lineErr = true;
				break;
			}
		}
		if (lineErr) {
			++count;
			std::cout << "-------" << std::endl << "Line " << p << std::endl << std::endl;
			std::cout << "<" << file0[p] << ">" << " != " << "<" << file1[p] << ">" << std::endl << std::endl;
			lineErr = false;
		}
	}

	std::cout << "Found " << count <<" errors." << std::endl;

	if (count == 0) {
		std::cout << "Reverse Checking..." << std::endl;

		for (int p = 0; p < file0.size(); ++p) {
			for (int i = 0; i < file0[p].size(); ++i) {
				if (file0[p][i] != file1[p][i]) {
					lineErr = true;
					break;
				}
			}
			if (lineErr) {
				++count;
				std::cout << "-------" << std::endl << "Line " << p << std::endl << std::endl;
				std::cout << "<" << file0[p] << ">" << " != " << "<" << file1[p] << ">" << std::endl << std::endl;
				lineErr = false;
			}
		}
	}

	std::cout << "Found " << count <<" errors." << std::endl;

	return 0;
}