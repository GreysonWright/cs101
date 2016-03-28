#include <iostream>
#include <fstream>
#include "SparseMatrix.h"
using namespace std;

int main(int argc, char **argv) {
	SparseMatrix m1, m2, m;
	ifstream infile1("/Users/gwright/cs101/Test/Test/a1.txt"), infile2("/Users/gwright/cs101/Test/Test/b1.txt");
	
	infile1 >> m1;
	infile2 >> m2;
	
	infile1.close(); infile2.close();
	
	string op("add");
	if (op=="add") m=m1+m2;
	else if (op=="sub") m=m1-m2;
//	else if (op=="mul") m=m1*m2;
	else {
		cerr << "No such operation" << endl;
		return 1;
	}
	
	ofstream outfile("/Users/gwright/cs101/Test/Test/c.txt");
	
	outfile << m;
	
	outfile.close();
	return 0;
}
