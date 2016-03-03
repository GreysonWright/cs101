//
//  SparseMatrix.cpp
//
//
//  Created by Greyson Wright on 2/27/16.
//
//

#include "SparseMatrix.h"

//Element Methods
Element::Element() {
	this->row = 0;
	this->col = 0;
	this->value = 0;
	this->next = NULL;
}

Element::Element(int row, int col, double value, Element *next, Element *prev) {
	this->row = row;
	this->col = col;
	this->value = value;
	this->next = next;
	this->prev = prev;
}

// SparseMatrix Public Methods
SparseMatrix operator+(const SparseMatrix &left, const SparseMatrix &right){
	SparseMatrix resultMatrix;
	Element *rightElement = left.elements;
	Element *leftElement = right.elements;
	
	while(true) {
		if (!rightElement && !leftElement) {
			break;
		}
		
		if (rightElement) {
			resultMatrix.addElement(rightElement);
			rightElement = rightElement->next;
		}
		if (leftElement) {
			resultMatrix.addElement(leftElement);
			leftElement = leftElement->next;
		}
	}
	resultMatrix.sumElements();
	
	return resultMatrix;
}

SparseMatrix operator-(const SparseMatrix &left, const SparseMatrix &right) {
	SparseMatrix resultMatrix;
	Element *rightElement = left.elements;
	Element *leftElement = right.elements;
	
	while(true) {
		if (!rightElement && !leftElement) {
			break;
		}
		
		if (rightElement) {
			resultMatrix.addElement(rightElement);
			rightElement = rightElement->next;
		}
		if (leftElement) {
			leftElement->value *= -1;
			resultMatrix.addElement(leftElement);
			leftElement = leftElement->next;
		}
	}
	resultMatrix.sumElements();
	
	return resultMatrix;
}

SparseMatrix operator*(const SparseMatrix &left, const SparseMatrix &right) {
	SparseMatrix resultMatrix;
	Element *leftElement = left.elements;
	Element *rightElement = right.elements;
	double product = 0.0;
	
	while (leftElement) {
		while (rightElement) {
			if (leftElement->col == rightElement->row) {
				product = leftElement->value * rightElement->value;
				if (product != 0) {
					resultMatrix.addElement(leftElement->row, rightElement->col, product);
					product = 0.0;
				}
			}
			
			rightElement = rightElement->next;
		}
		rightElement = right.elements;
		leftElement = leftElement->next;
		
	}
	resultMatrix.sumElements();
	
	return resultMatrix;
}

SparseMatrix::SparseMatrix() {
	elements = NULL;
}

void SparseMatrix::addElement(int row, int col, double value) {
	Element *list = this->elements;
	Element *prev = list;
	Element *currElement = prev;
	Element *newElement = new Element(row, col, value, NULL, NULL);
	bool isHead = true;
	
	if (list) {
		if (row < list->row) {
			newElement->next = list;
			this->elements = newElement;
			return;
		}
		
		while (currElement && (row > currElement->row || (row == currElement->row && col > currElement->col))) {
			isHead = false;
			prev = currElement;
			currElement = currElement->next;
		}
		if (isHead) {
			newElement->next = currElement;
			currElement->prev = newElement;
			this->elements = newElement;
			return;
		}
		
		newElement->next = currElement;
		prev->next = newElement;
		newElement->prev = prev;
		this->elements = list;
		return;
	}
	this->elements = newElement;
}

void SparseMatrix::addElement(Element *element) {
	this->addElement(element->row, element->col, element->value);
}

void SparseMatrix::sumElements() {
	Element *list = this->elements;
	Element *element = list;
	Element *head = element;
	
	while (element) {
		if (element->next && element->next->row == element->row && element->next->col == element->col) {
			element->value += element->next->value;
			if (element->next->next) {
				element->next->next->prev = element;
			}
			element->next = element->next->next;
		}
		element = element->next;
	}
	
	this->elements = head;
}

//fstream operators
std::ostream &operator<<(std::ostream &os, SparseMatrix &matrix) {
	Element *currElement = matrix.elements;
	
	while(currElement) {
		if (currElement->value != 0) {
			os << currElement->row << " " << currElement->col << " " << currElement->value << std::endl;
		}
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
			matrix.addElement(row, col, value);
		}
	}
	
	return is;
}
