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
	Element *rightElement = right.elements;
	Element *leftElement = left.elements;
	double difference = 0.0;

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
				resultElement->value = leftElement->value;
				resultElement->next = new Element();
				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;

				resultElement->row = rightElement->row;
				resultElement->col = rightElement->col;
				resultElement->value = rightElement->value * -1;
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
	SparseMatrix resultMatrix;
	resultMatrix.elements = new Element();

	Element *resultElement = resultMatrix.elements;
	Element *rightElement = right.elements;
	Element *leftElement = left.elements;
	double dotProduct = 0.0;
	int col = 0;
	// Element *currRightElement = rightElement;
	Element *currLeftElement = leftElement;

	while(leftElement) {
		if (leftElement->next) {
			while(rightElement) {
				if (rightElement->next) {
					if (leftElement->col == rightElement->row) {
						dotProduct += leftElement->value * rightElement->value;
						col = rightElement->col;
					}
				}
				rightElement = rightElement->next;
				currLeftElement = left.elements;
			}
		}

		if (leftElement && dotProduct != 0) {
			if (leftElement->row != 0 && leftElement->col != 0) {
				resultElement->row = leftElement->col;
				resultElement->col = col;
				resultElement->value = dotProduct;
				resultElement->next = new Element();
				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;
				dotProduct = 0.0;
			}
		}

		leftElement = leftElement->next;
		rightElement = right.elements;
	}

	resultElement->row = 0;
	resultElement->col = 0;
	resultElement->value = 0;
	resultElement->next = NULL;

	return resultMatrix;
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
