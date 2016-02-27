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

}

SparseMatrix operator-(const SparseMatrix &left, const SparseMatrix &right) {

}

SparseMatrix operator*(const SparseMatrix &left, const SparseMatrix &right) {

}

SparseMatrix::SparseMatrix() {

}

SparseMatrix::~SparseMatrix() {

}

//fstream operators
std::ostream &operator<<(std::ostream &os, const SparseMatrix &matrix) {
	Element *head = matrix.elements;
	Element *currElement = head;

	while(currElement) {
		if (currElement->next) {
			os << currElement->value << " ";		
		}

		currElement = currElement->next;
	}

	return os;
}

std::istream &operator>>(std::istream &is, const SparseMatrix &matrix) {
	Element *head = new Element();
	Element *currElement = head;

	while(is) {
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
