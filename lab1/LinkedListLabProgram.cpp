#include <iostream>
using namespace std;

struct Node {
	int data;
	Node *next;
	Node (int v, Node *n) {data=v; next=n;}
};

class LinkedList {
	Node *front;
public:  
	LinkedList( ) { front=NULL; }
	void add (int);
	void remove (int);
	friend ostream& operator<< (ostream&, LinkedList&);
};

void LinkedList::add (int v) {
	Node *list = this->front;
	Node *prev = list;
	Node *currNode = prev;
	Node *newNode = new Node(v, NULL);
	bool isDup = false;
	
	if (list) {
		if (v < list->data) {
			newNode->next = list;
			this->front = newNode;
			return;
		}
		
		while (currNode && v >= currNode->data) {
			if (v == currNode->data) {
				isDup = true;
			}
			prev = currNode;
			currNode = currNode->next;
		}
		if (!isDup) {
			newNode->next = currNode;
			prev->next = newNode;
		}
		this->front = list;
		return;
	}
	this->front = newNode;
}

void LinkedList::remove (int v) {
	Node *prev = this->front;
	Node *currNode = this->front;
	Node *head = currNode;

	while(currNode) {
		if (currNode->data == v) {
			if (currNode == this->front) {
				this->front = currNode->next;
				break;
			}
			prev->next = currNode->next;
			break;
		}
		prev = currNode;
		currNode = currNode->next;
	}
}

ostream & operator<< (ostream & os,LinkedList & L) {
	Node *p=L.front;
	os << '[';
	while (p!=NULL) {
		os << p->data;
		if (p->next!=NULL) os << ',';
		p=p->next;
	}
	os << ']';
	return os;
}

int main( ) {
	LinkedList L;
	char c;
	int x;
	cout << L << endl;
	while (cin >> c >> x) {
		if (c=='A') L.add(x);
		else if (c=='R') L.remove(x);
		cout << L << endl;
	}
	return 0;
}