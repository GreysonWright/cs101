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

class Element
{
public:
	Element();
	~Element();
};

class SparseMatrix {
public:
	friend std::ostream& operator<<(std::ostream &os, const SparseMatrix &obj);
	friend std::istream& operator>>(std::istream &is, const SparseMatrix &obj);
	friend SparseMatrix operator+(const SparseMatrix &left, const SparseMatrix &right);
	friend SparseMatrix operator-(const SparseMatrix &left, const SparseMatrix &right);
	friend SparseMatrix operator*(const SparseMatrix &left, const SparseMatrix &right);
	SparseMatrix();
	~SparseMatrix();
};


