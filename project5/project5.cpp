#include <iostream>
#include <fstream>
#include <string>

class Node {
public:
	char letter;
	Node *left;
	Node *right;
	Node();
	Node(char letter);
};

Node::Node() {
	letter = 0;
	left = NULL;
	right = NULL;
}

Node::Node(char letter) {
	this->letter = letter;
	left = NULL;
	right = NULL;
}

std::string getFileContents(std::string fileName) {
	std::ifstream file(fileName);
	std::string line;

	getline(file, line);
	file.close();

	return line;
}

int search(std::string arr, int strt, int end, char value) {
	for (int i = strt; i <= end; i++)
		if (arr[i] == value)
			return i;
	return -1;
}

std::string extrackKeys(std::string in, std::string level, int m, int n) {
	std::string newLevel = "";
	int j = 0;
	for (int i = 0; i < n; i++){
		if (search(in, 0, m-1, level[i]) != -1) {
			newLevel += level[i];
			j++;
			return newLevel;
		}
	}
	return newLevel;
}

Node* generateTreeInLevel(std::string in, std::string level, int inStrt, int inEnd, int n) {
	if (inStrt > inEnd) {
		return NULL;
	}

	Node *root = new Node(level[0]);

	if (inStrt == inEnd){
		return root;
	}
	int inIndex = search(in, inStrt, inEnd, root->letter);
	std::string llevel  = extrackKeys(in, level, inIndex, n);
	std::string rlevel  = extrackKeys(in.substr(inIndex + 1, in.size()), level, n-inIndex-1, n);

	root->left = generateTreeInLevel(in, llevel, inStrt, inIndex-1, n);
	root->right = generateTreeInLevel(in, rlevel, inIndex+1, inEnd, n);

	return root;
}

Node *generateTreePrePost(std::string pre, std::string post, int* index, int l, int h, int size) {
	if ((*index) >= size || l > h) {
		return NULL;
	}

	Node *root = new Node(pre[*index]);
	++(*index);

	if (l == h) {
		return root;
	}

	unsigned int i = 0;
	for (i = l; i <= h; ++i) {
		if (pre[*index] == post[i]) {
			break;
		}
	}

	if (i <= h) {
		root->left = generateTreePrePost(pre, post, index, l, i, size);
		root->right = generateTreePrePost(pre, post, index, i + 1, h, size);
	}

	return root;
}

void printLevel(std::ofstream *file, Node* node, int level) {
	if (node == NULL) {
		return;
	}

	if (level == 1) {
		*file << node->letter;
	}

	else if (level > 1) {
		printLevel(file, node->left, level-1);
		printLevel(file, node->right, level-1);
	}
}

int height(Node *node) {
	if (node == NULL) {
		return 0;
	}
	int left = height(node->left);
	int right = height(node->right);
	if (left > right) {
		return left + 1;
	}
	return right + 1;
}

void writeTree(std::ofstream *file, Node* node, int &option) {
	if (option == 3) {
		int h = height(node);
		for (unsigned int i = 1; i <= h; ++i){
			printLevel(file, node, i);
		}
	} else {
		if (node == NULL) {
			return;
		}

		if (option == 0) {
			*file << node->letter;
		}
		writeTree(file, node->left, option);
		if (option == 1) {
			*file << node->letter;
		}
		writeTree(file, node->right, option);
		if (option == 2) {
			*file << node->letter;
		}
	}
}

int getOption(std::string arg) {
	if (!arg.find("preorder")) {
		return 0;
	}
	if (!arg.find("inorder")) {
		return 1;
	}
	if (!arg.find("postorder")){
		return 2;
	}
	return 3;
}

void writeTree(std::string fileName, Node *node) {
	int option = 0;
	std::ofstream file(fileName);

	option = getOption(fileName);
	writeTree(&file, node, option);
    file << std::endl;
	file.close();
}

std::string decipherTree(Node *node, std::string &cipher) {
    Node *currNode = node;
    std::string decipher = "";
    for (unsigned int i = 0; i < cipher.size(); ++i) {
        if (cipher[i] == 0) {
            if (currNode->left) {
                currNode = currNode->left;
            }
        } else if (cipher[i] == 1){
            if (currNode->right) {
                currNode = currNode->right;
            }
        } else {
            decipher += currNode->letter;
            currNode = node;
        }
    }
    return decipher;
}

int main(int argc, char const **argv) {
	std::string str1 = getFileContents(argv[1]);
	std::string str2 = getFileContents(argv[2]);
    std::string cipher = getFileContents(argv[3]);
	std::string arg1 = argv[1];
	int index = 0;
	Node *node;

	if (!arg1.find("preorder")) {
		node = generateTreePrePost(str1, str2, &index, 0, str1.length() - 1, str1.length());
	} else {
		node = generateTreeInLevel(str1, str2, 0, str1.length() - 1, str1.length());
	}

	writeTree(argv[4], node);
	writeTree(argv[5], node);
    std::cout << decipherTree(node, cipher) << std::endl;
	return 0;
}
