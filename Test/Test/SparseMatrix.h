
#ifndef _SparseMatrix_h
#include <iostream>
#include <fstream>
#define _SparseMatrix_h

class Node {
public:
	int rowIndex, colIndex;
	double value;
	
	Node *nextRowIndex;
	Node(int, int, double);
	// int getRowIndex();
	
	// int getColIndex();
	
	// double getValue();
	
	// Node *getNextRowIndex();
	
	// Node *getNextColIndex();
	
	// void setRowIndex(int);
	
	// void setColIndex(int);
	
	// void setValue(double);
	
	// void setNextRowIndex(Node *);
	
	// void setNextColIndex(Node *);
	
};

class SparseMatrix {
public:
	Node *head;
	
	SparseMatrix();
	
	void insert(int row, int col, double value);
	
	friend std::ostream &operator << (std::ostream &output, SparseMatrix &m);
	
	friend std::istream &operator >> (std::istream &input, SparseMatrix &m);
	
	friend SparseMatrix operator + ( SparseMatrix & left, SparseMatrix & right);
	
	friend SparseMatrix operator - (SparseMatrix & left, SparseMatrix & right);
};





#endif

