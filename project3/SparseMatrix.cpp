//
//  SparseMatrix.cpp
//  
//
//  Created by Greyson Wright on 2/27/16.
//
//

#include "SparseMatrix.h"

//SparseMatrix Publix Methods
SparseMatrix operator+(const SparseMatrix &left, const SparseMatrix &right){
	SparseMatrix resultMatrix;
	resultMatrix.elements = new Element();

	Element *resultElement = resultMatrix.elements;
	Element *rightElement = left.elements;
	Element *leftElement = right.elements;

	while(rightElement && leftElement) {
		if (rightElement->next && leftElement->next) {
			if (rightElement->row == leftElement->row && rightElement->col == leftElement-> col) {
				resultElement->row = rightElement->row;
				resultElement->col = rightElement->col;
				resultElement->value = leftElement->value + rightElement->value;
				resultElement->next = new Element();
				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;
			} else if (rightElement->value > leftElement->value) {
				resultElement->row = rightElement->row;
				resultElement->col = rightElement->col;
				resultElement->value = rightElement->value;
				resultElement->next = new Element();
				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;

				resultElement->row = leftElement->row;
				resultElement->col = leftElement->col;
				resultElement->value = leftElement->value;
				resultElement->next = new Element();
				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;
			} else {
				resultElement->row = leftElement->row;
				resultElement->col = leftElement->col;
				resultElement->value = leftElement->value;
				resultElement->next = new Element();
				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;

				resultElement->row = rightElement->row;
				resultElement->col = rightElement->col;
				resultElement->value = rightElement->value;
				resultElement->next = new Element();
				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;
			}
		}
		rightElement = rightElement->next;
		leftElement = leftElement->next;
	}
	resultElement = resultElement->prev;
	delete resultElement->next;
	resultElement->next = NULL; 

	return resultMatrix;
}

SparseMatrix operator-(const SparseMatrix &left, const SparseMatrix &right) {
	SparseMatrix resultMatrix;
	resultMatrix.elements = new Element();

	Element *resultElement = resultMatrix.elements;
	Element *rightElement = left.elements;
	Element *leftElement = right.elements;
	double difference = 0;

	while(rightElement && leftElement) {
		difference = leftElement->value - rightElement->value;
		if (rightElement->next && leftElement->next) {
			if (rightElement->row == leftElement->row && rightElement->col == leftElement-> col) {
				if (difference != 0) {
					resultElement->row = rightElement->row;
					resultElement->col = rightElement->col;
					resultElement->value = difference;
					resultElement->next = new Element();
					resultElement->next->prev = resultElement;
					resultElement = resultElement->next;
				}
			} else if (rightElement->value > leftElement->value) {
				resultElement->row = rightElement->row;
				resultElement->col = rightElement->col;
				resultElement->value = rightElement->value;
				resultElement->next = new Element();
				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;

				resultElement->row = leftElement->row;
				resultElement->col = leftElement->col;
				resultElement->value = leftElement->value * -1;
				resultElement->next = new Element();
				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;
			} else {
				resultElement->row = leftElement->row;
				resultElement->col = leftElement->col;
				resultElement->value = leftElement->value * -1;
				resultElement->next = new Element();
				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;

				resultElement->row = rightElement->row;
				resultElement->col = rightElement->col;
				resultElement->value = rightElement->value;
				resultElement->next = new Element();
				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;
			}
		}
		rightElement = rightElement->next;
		leftElement = leftElement->next;
	} 

	resultElement->row = 0;
	resultElement->col = 0;
	resultElement->value = 0;
	resultElement->next = NULL;

	return resultMatrix;
}

SparseMatrix operator*(const SparseMatrix &left, const SparseMatrix &right) {
	
}

SparseMatrix::SparseMatrix() {
	elements = NULL;
}

//fstream operators
std::ostream &operator<<(std::ostream &os, SparseMatrix &matrix) {
	Element *currElement = matrix.elements;

	while(currElement) {
		os << currElement->row << " ";
		os << currElement->col << " ";
		os << currElement->value;
		os << std::endl;		
		currElement = currElement->next;
	}

	return os;
}

std::istream &operator>>(std::istream &is, SparseMatrix &matrix) {
	Element *currElement = new Element();
	matrix.elements = currElement;

	while(is) {
		is >> currElement->row;
		is >> currElement->col;
		is >> currElement->value;
		currElement->next = new Element();
		currElement->next->prev = currElement;
		currElement = currElement->next;
	}
	currElement = currElement->prev;
	delete currElement->next;
	currElement->next = NULL;

	return is;
}
