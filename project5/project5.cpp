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
    for (int i = 0; i < n; i++)
    if (search(in, 0, m-1, level[i]) != -1)
    newLevel += level[i], j++;
    return newLevel;
}

Node* buildTree(std::string in, std::string level, int inStrt, int inEnd, int n) {

    // If start index is more than the end index
    if (inStrt > inEnd)
    return NULL;

    /* The first node in level order traversal is root */
    Node *root = new Node(level[0]);

    /* If this node has no children then return */
    if (inStrt == inEnd)
    return root;

    /* Else find the index of this node in Inorder traversal */
    int inIndex = search(in, inStrt, inEnd, root->letter);

    // Extract left subtree keys from level order traversal
    std::string llevel  = extrackKeys(in, level, inIndex, n);

    // Extract right subtree keys from level order traversal
    std::string rlevel  = extrackKeys(in.substr(inIndex + 1, in.size()), level, n-inIndex-1, n);

    /* construct left and right subtress */
    root->left = buildTree(in, llevel, inStrt, inIndex-1, n);
    root->right = buildTree(in, rlevel, inIndex+1, inEnd, n);

    return root;
}

// std::string extractChars(std::string &chars, std::string &str) {
//     std::string newStr = "";
//
//     for (unsigned int i = 0; i < chars.length(); ++i) {
//         for (unsigned int p = 0; p < str.length(); ++p) {
//             if (chars[i] == str[p]) {
//                 newStr += str[p];
//             }
//         }
//     }
//
//     return newStr;
// }
//
// Node* generateTreeInLevel(std::string in, std::string level) {
//     if (level == "" && level == in) {
//         return NULL;
//     }
//
//     Node *root = new Node(level[0]);
//
//     if (in[0] == level[0]) {
//         return root;
//     }
//
//     root->left = generateTreeInLevel(in, extractChars(in, level));
//     root->left = generateTreeInLevel(in, extractChars(in, level));
//
//     return root;
// }

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

void printLevelOrder(Node *node) {
    int h = height(node);
    int i;
    for (i=1; i<=h; ++i){
        printGivenLevel(node, i);
    }
}

void printGivenLevel(Node* node, int level) {
    if (root == NULL) {
        return;
    }

    if (level == 1) {
        std::cout << root->letter;
    }

    else if (level > 1) {
        printGivenLevel(node->left, level-1);
        printGivenLevel(node->right, level-1);
    }
}

void printTree(Node* node, int &option) {
    if (node == NULL) {
        return;
    }

    if (option == 0) {
        std::cout << node->letter;
    }
    printTree(node->left, option);
    if (option == 1) {
        std::cout << node->letter;
    }
    printTree(node->right, option);
    if (option == 2) {
        std::cout << node->letter;
    }
}

int getOption(std::string arg) {
    if (!arg4.find("preorder")) {
        return 0;
    }
    if (!arg4.find("inorder")) {
        return 1;
    }
    if (!arg4.find("postorder")){
        return 2;
    }
    return 3;
}

int main(int argc, char const **argv) {
    std::string str1 = getFileContents(argv[1]);
    std::string str2 = getFileContents(argv[2]);
    std::string arg1 = argv[1];
    std::string arg4 = argv[4];
    std::string arg5 = argv[5];
    int option = 0;
    int index = 0;
    Node *node;

    if (!arg1.find("preorder")) {
        node = generateTreePrePost(str1, str2, &index, 0, str1.length() - 1, str1.length());
    } else {
        node = buildTree(str1, str2, 0, str1.length() - 1, str1.length());
    }

    option = getOption(arg4);
    printTree(node, arg4);
    option = getOption(arg5);
    printTree(node, arg5);

    std::cout << std::endl;

    return 0;
}
