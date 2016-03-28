
#include "SparseMatrix.h"

using namespace std;

istream & operator>>(istream & input, SparseMatrix & m)
{
	int row = 0, col = 0;
	double value = 0.0;
	
	while (input) {
		input >> row;
		input >> col;
		input >> value;
		if (value!=0)
			m.insert(row, col, value);
	}
	
	return input;
}

ostream & operator<<(ostream & output, SparseMatrix & m)
{
	Node *p= m.head;
	
	while (p!=NULL){
		
		output << p->rowIndex<<" "<< p->colIndex<< " "<< p->value<< endl;
		p=p->nextRowIndex;
		
	}
	output<< "0 "<< "0 "<< "0"<< endl;
	
	return output;
}



SparseMatrix  operator+(SparseMatrix & left, SparseMatrix & right)
{
	SparseMatrix sum;
	Node *back=right.head;
	Node *lp=left.head;
	Node *rp=right.head;
	
	while(lp!=NULL){
		while(rp!=NULL){
			if (lp->rowIndex== rp->rowIndex && lp->colIndex== rp->colIndex){
				sum.insert(lp->rowIndex, lp->colIndex, rp->value+lp->value);
				back->nextRowIndex=rp->nextRowIndex;
				break;
			}
			if (rp->nextRowIndex==NULL){
				sum.insert(lp->rowIndex, lp->colIndex, lp->value);
			}
			back=rp;
			rp=rp->nextRowIndex;
		}
		
		rp=right.head;
		lp=lp->nextRowIndex;
		
	}
	
	while (rp!=NULL){
		sum.insert(rp->rowIndex, rp->colIndex, rp->value);
		rp=rp->nextRowIndex;
	}
	
	
	return sum;
}

SparseMatrix operator - (SparseMatrix & left, SparseMatrix & right){
	SparseMatrix diff;
	Node *back=right.head;
	Node *lp=left.head;
	Node *rp=right.head;
	
	while(lp!=NULL){
		while(rp!=NULL){
			if (lp->rowIndex== rp->rowIndex && lp->colIndex== rp->colIndex){
				diff.insert(lp->rowIndex, lp->colIndex, rp->value - lp->value);
				back->nextRowIndex=rp->nextRowIndex;
				delete rp;
				break;
			}
			if (rp->nextRowIndex==NULL){
				diff.insert(lp->rowIndex, lp->colIndex, lp->value);
				
			}
			back=rp;
			rp=rp->nextRowIndex;
		}
		
		rp=right.head;
		lp=lp->nextRowIndex;
		
	}
	
	while (rp!=NULL){
		diff.insert(rp->rowIndex, rp->colIndex, rp->value*-1);
		rp=rp->nextRowIndex;
	}
	
	
	return diff;
}

SparseMatrix::SparseMatrix()
{
	head = NULL;
}

void SparseMatrix::insert(int row, int col, double value)
{
	cout<< "debug"<<endl;
	Node *prev = head;
	Node *current = prev;
	Node *n = new Node(row, col, value);
	if (value==0){
		return;
	}
	if (head) {
		if (row < head->rowIndex) {
			n->nextRowIndex = head;
			head = n;
			
			return;
		}
		
		while (current && row >= current->rowIndex) {
			if (row==current->rowIndex)
				break;
			prev = current;
			current = current->nextRowIndex;
			
		}	while(current !=NULL && row==current->rowIndex && col>current->colIndex){
			prev = current;
			current = current->nextRowIndex;
		}
		
		n->nextRowIndex = current;
		prev->nextRowIndex = n;
		
		return;
	}
	head = n;
}

Node::Node(int r, int c, double v)
{
	rowIndex = r;
	colIndex = c;
	value = v;
	
	nextRowIndex = NULL;
	
}

