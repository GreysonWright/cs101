//
//  SparseMatrix.hpp
//  
//
//  Created by Greyson Wright on 2/27/16.
//
//

#ifndef SparseMatrix_h
#define SparseMatrix_h

#include <iostream>
#include <fstream>

#endif

class Element {
public:
	int row;
	int col;
	double value;
	Element *prev;
	Element *next;

	Element();
	Element(int row, int col, double value, Element *next, Element *prev);
	
};

class SparseMatrix {
public:
	Element *elements;

	friend SparseMatrix operator+(const SparseMatrix &left, const SparseMatrix &right);
	friend SparseMatrix operator-(const SparseMatrix &left, const SparseMatrix &right);
	friend SparseMatrix operator*(const SparseMatrix &left, const SparseMatrix &right);

	SparseMatrix();
};

std::ostream &operator<<(std::ostream &os, SparseMatrix &matrix);
std::istream &operator>>(std::istream &is, SparseMatrix &matrix);
