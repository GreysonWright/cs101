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

Element::Element(int row, int col, double value, Element *next, Element *prev) {
	this->row = row;
	this->col = col;
	this->value = value;
	this->next = next;
	this->prev = prev;
}

// Private Functions
Element *add(int row, int col, double value, Element *list) {
	Element *prev = list;
	Element *currElement = prev;
	Element *newElement = new Element(row, col, value, NULL, NULL);
	
	if (list) {
		if (row < list->row) {
			newElement->next = list;
			return newElement;
		}
		
		while (currElement && row >= currElement->row) {
			prev = currElement;
			currElement = currElement->next;
		}
		newElement->next = currElement;
		prev->next = newElement;
		newElement->prev = prev;
		
		return list;
	}
	
	return newElement;
}

Element *add(Element *element, Element *list) {
	Element *newElement = add(element->row, element->col, element->value, list);
	
	return newElement;
}

// SparseMatrix Public Methods
SparseMatrix operator+(const SparseMatrix &left, const SparseMatrix &right){
	SparseMatrix resultMatrix;
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
		
		if (rightElement) {
			rightElement = rightElement->next;
		}
		if (leftElement) {
			leftElement = leftElement->next;
		}
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
		
		if (rightElement) {
			rightElement = rightElement->next;
		}
		if (leftElement) {
			leftElement = leftElement->next;
		}
	}
	
	return resultMatrix;
}

struct Key {
	int col;
	int row;
};

SparseMatrix operator*(const SparseMatrix &left, const SparseMatrix &right) {
	SparseMatrix resultMatrix;
	Element *leftElement = left.elements;
	Element *rightElement = right.elements;
	std::vector<Element> products;
	double product = 0.0;
	
	while (leftElement) {
		while (rightElement) {
			if (leftElement->col == rightElement->row) {
				product = leftElement->value * rightElement->value;
				if (product != 0) {
					Element newElement = Element(leftElement->row, rightElement->col, product, NULL, NULL);
					products.push_back(newElement);
					product = 0.0;
				}
			}
			
			rightElement = rightElement->next;
		}
		rightElement = right.elements;
		leftElement = leftElement->next;
		
	}
	
	for (int i = 0; i < products.size(); ++i) {
		for (int p = 0; p < products.size(); ++p) {
			if (products[p].row == products[i].row && products[p].col == products[i].col) {
				products[i].value += products[p].value;
//				products.erase(products.begin() + p);
			}
		}
	}
	
	for (Element element : products) {
		resultMatrix.elements = add(element.row, element.col, element.value, resultMatrix.elements);
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
