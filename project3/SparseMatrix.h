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
	float value;
	Element *prev;
	Element *next;

	Element();
	~Element();
};

class SparseMatrix {
public:
	Element *elements;

	friend SparseMatrix operator+(const SparseMatrix &left, const SparseMatrix &right);
	friend SparseMatrix operator-(const SparseMatrix &left, const SparseMatrix &right);
	friend SparseMatrix operator*(const SparseMatrix &left, const SparseMatrix &right);

	SparseMatrix();
	~SparseMatrix();
};

std::ostream &operator<<(std::ostream &os, const SparseMatrix &matrix);
std::istream &operator>>(std::istream &is, const SparseMatrix &matrix);
