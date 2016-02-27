#include <iostream>
#include <fstream>
#include "SparseMatrix.h"
using namespace std;

int main(int argc, char **argv) {
    SparseMatrix m1, m2, m;
    ifstream infile1(argv[2]), infile2(argv[3]);

    infile1 >> m1;
    infile2 >> m2;

    infile1.close(); infile2.close();

    string op(argv[1]);
    if (op=="add") m=m1+m2;
    else if (op=="sub") m=m1-m2;
    else if (op=="mul") m=m1*m2;
    else {
        cerr << "No such operation" << endl;
        return 1;
    }
    
    ofstream outfile(argv[4]);

    outfile << m;

    outfile.close();
    return 0;
}
