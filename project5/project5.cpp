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
	std::string contents = "";
	char c;

	while(file.get(c)) {
		contents += c;
	}
	file.close();
	return contents;
}

int search(std::string str, int head, int tail, char c) {
	for (int i = head; i <= tail; ++i){
		if (str[i] == c) {
			return i;
		}
	}

	return -1;
}

std::string extrackKeys(std::string in, std::string level, int levelSize, int inSize) {
	std::string newLevel = "";
	int j = 0;

	for (int i = 0; i < inSize; ++i) {
		if (search(in, 0, levelSize - 1, level[i]) != -1) {
			newLevel += level[i];
			++j;
		}
	}

	return newLevel;
}

Node* generateTreeInLevel(std::string in, std::string level, int inHead, int inEnd, int inSize) {
	if (inHead > inEnd) {
		return NULL;
	}

	Node *root = new Node(level[0]);

	if (inHead == inEnd) {
		return root;
	}

	int inIndex = search(in, inHead, inEnd, root->letter);
	std::string left = extrackKeys(in, level, inIndex, inSize);
	std::string right = extrackKeys(in.substr(inIndex + 1, in.size()), level, inSize - inIndex - 1, inSize);

	root->left = generateTreeInLevel(in, left, inHead, inIndex - 1, inSize);
	root->right = generateTreeInLevel(in, right, inIndex+1, inEnd, inSize);

	return root;
}

Node *generateTreePrePost(std::string pre, std::string post, int* index, unsigned int head, unsigned int tail, int size) {
	if ((*index) >= size || head > tail) {
		return NULL;
	}

	Node *root = new Node(pre[*index]);
	++(*index);

	if (head == tail) {
		return root;
	}

	unsigned int i = 0;
	for (i = head; i <= tail; ++i) {
		if (pre[*index] == post[i]) {
			break;
		}
	}

	if (i <= tail) {
		root->left = generateTreePrePost(pre, post, index, head, i, size);
		root->right = generateTreePrePost(pre, post, index, i + 1, tail, size);
	}

	return root;
}

void writeLevel(std::ofstream *file, Node* node, int level) {
	if (node == NULL) {
		return;
	}

	if (level == 1) {
		*file << node->letter;
	}

	else if (level > 1) {
		writeLevel(file, node->left, level - 1);
		writeLevel(file, node->right, level - 1);
	}
}

int getHeight(Node *node) {
	if (node == NULL) {
		return 0;
	}

	int left = getHeight(node->left);
	int right = getHeight(node->right);

	if (left > right) {
		return left + 1;
	}
	return right + 1;
}

void writeTree(std::ofstream *file, Node* node, int &option) {
	if (option != 3) {
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
	} else {
		unsigned int height = getHeight(node);
		for (unsigned int i = 1; i <= height; ++i){
			writeLevel(file, node, i);
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
		if (cipher[i] == '\n') {
			decipher += currNode->letter;
			currNode = node;
			decipher += '\n';
		} else if (cipher[i] == '0' && currNode->left) {
			currNode = currNode->left;
		} else if (cipher[i] == '1' && currNode->right){
			currNode = currNode->right;
		} else {
			--i;
			decipher += currNode->letter;
			currNode = node;
		}
	}

	return decipher;
}

void writeText(std::string fileName, std::string text) {
	std::ofstream file(fileName);
	file << text;
	file.close();
}

int main(int argc, char const **argv) {
	std::string str1 = getFileContents(argv[1]);
	std::string str2 = getFileContents(argv[2]);
	std::string cipher = getFileContents(argv[3]);
	int index = 0;
	Node *node;

	if (str1[0] == str2[str2.length() - 1]) {
		node = generateTreePrePost(str1, str2, &index, 0, str1.length() - 1, str1.length());
	} else {
		node = generateTreeInLevel(str1, str2, 0, str1.length() - 1, str1.length());
	}

	writeTree(argv[4], node);
	writeTree(argv[5], node);

	std::string text = decipherTree(node, cipher);
	writeText(argv[6], text);

	return 0;
}
