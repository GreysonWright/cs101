#include <iostream>
#include <fstream>

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

int search(std::string &in, int head, int tail, char c) {
    for (unsigned int i = head; i < tail; ++i) {
        if (in[i] == c) {
            return i;
        }
    }
    return -1;
}

Node *generateTreeInLevel(std::string in, std::string level,  int inHead, int inTail, int i) {
    if (inHead > inTail) {
        return NULL;
    }

    Node *root = Node(level[0]);

    if (inHead == inTail) {
        return root;
    }

    int index = search(in, inHead, inTail, level[0]);
}

Node *generateTreePrePost(std::string pre, std::string post, int* index, int l, int h, int size) {
    if (*index >= size || l > h)
        return NULL;

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

void printInorder (Node* node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->left);
    std::cout << node->letter;
    printInorder(node->right);
}

int main(int argc, char const **argv) {
    int index = 0;
    std::string str1 = getFileContents(argv[1]);
    std::string str2 = getFileContents(argv[2]);
    Node *node = generateTreePrePost(str1, str2, &index, 0, str1.length() - 1, str1.length());

    printInorder(node);
    std::cout << std::endl;
    return 0;
}
