//
//  SparseMatrix.cpp
//
//
//  Created by Greyson Wright on 2/27/16.
//
//

#include "SparseMatrix.h"
//Element Functions
Element::Element() {
	this->row = 0;
	this->col = 0;
	this->value = 0;
	this->next = NULL;
}

Element::Element(int row, int col, double value, Element *next) {
	this->row = row;
	this->col = col;
	this->value = value;
	this->next = next;
}

// Private Functions
Element *add(int row, int col, double value, Element *list) {
	Element *back = list;
	Element *currElement = back;
	Element *newElement = new Element(row, col, value, NULL);
	
	if (list) {
		if (row < list->row) {
			newElement->next = list;
			return newElement;
		}
		
		while (currElement && row >= currElement->row) {
			back = currElement;
			currElement = currElement->next;
		}
		newElement->next = currElement;
		back->next = newElement;
		
		return list;
	}
	
	return newElement;
}

Element *add(Element *element, Element *list) {
	Element *back = list;
	Element *currElement = back;
	Element *newElement = new Element(element->row, element->col, element->value, NULL);
	
	if (list) {
		if (element->row < list->row) {
			newElement->next = list;
			return newElement;
		}
		
		while (currElement && element->row >= currElement->row) {
			back = currElement;
			currElement = currElement->next;
		}
		newElement->next = currElement;
		back->next = newElement;
		
		return list;
	}
	
	return newElement;
}

// SparseMatrix Public Methods
SparseMatrix operator+(const SparseMatrix &left, const SparseMatrix &right){
	SparseMatrix resultMatrix;
	//	resultMatrix.elements = new Element();
	
	//	Element *resultElement = resultMatrix.elements;
	Element *rightElement = left.elements;
	Element *leftElement = right.elements;
	
	while(rightElement && leftElement) {
		if (rightElement->row == leftElement->row && rightElement->col == leftElement-> col) {
			resultMatrix.elements = add(rightElement->row, rightElement->col, leftElement->value + rightElement->value, resultMatrix.elements);
		} else if (rightElement->col < leftElement->col) {
			resultMatrix.elements = add(rightElement, resultMatrix.elements);
			resultMatrix.elements = add(leftElement, resultMatrix.elements);
		} else {
			resultMatrix.elements = add(leftElement, resultMatrix.elements);
			resultMatrix.elements = add(rightElement, resultMatrix.elements);
		}
		rightElement = rightElement->next;
		leftElement = leftElement->next;
	}
	
	return resultMatrix;
}

SparseMatrix operator-(const SparseMatrix &left, const SparseMatrix &right) {
	SparseMatrix resultMatrix;
	Element *rightElement = right.elements;
	Element *leftElement = left.elements;
	double difference = 0.0;
	
	while(rightElement && leftElement) {
		difference = leftElement->value - rightElement->value;
		if (rightElement->row == leftElement->row && rightElement->col == leftElement-> col) {
			if (difference != 0) {
				resultMatrix.elements = add(rightElement->row, rightElement->col, difference, resultMatrix.elements);
			}
		} else if (rightElement->col > leftElement->col) {
			resultMatrix.elements = add(leftElement, resultMatrix.elements);
			rightElement->value *= -1;
			resultMatrix.elements = add(rightElement, resultMatrix.elements);
		} else {
			
			leftElement->value *= -1;
			resultMatrix.elements = add(leftElement, resultMatrix.elements);
			resultMatrix.elements = add(rightElement, resultMatrix.elements);
		}
		rightElement = rightElement->next;
		leftElement = leftElement->next;
	}
	
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
				//				resultElement->next->prev = resultElement;
				resultElement = resultElement->next;
				dotProduct = 0.0;
			}
		}
		
		leftElement = leftElement->next;
		rightElement = right.elements;
	}
	
	return resultMatrix;
}

SparseMatrix::SparseMatrix() {
	elements = NULL;
}

//fstream operators
std::ostream &operator<<(std::ostream &os, SparseMatrix &matrix) {
	Element *currElement = matrix.elements;
	
	while(currElement) {
		os << currElement->row << " " << currElement->col << " " << currElement->value << std::endl;
		currElement = currElement->next;
	}
	os << "0 0 0" << std::endl;
	
	return os;
}

std::istream &operator>>(std::istream &is, SparseMatrix &matrix) {
	
	int row = 0;
	int col = 0;
	double value = 0.0;
	
	while (is) {
		is >> row;
		is >> col;
		is >> value;
		if (value != 0 || row + col != 0) {
			matrix.elements = add(row, col, value, matrix.elements);
		}
	}
	
	return is;
}
