#include "AVLTree.h"
#include <iostream>
#include <iomanip>
#include <stack>

int AVLTree::height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::balanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

void AVLTree::fixHeight(Node* node) {
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

AVLTree::Node* AVLTree::rotateRight(Node* node) {
    Node* left = node->left;
    node->left = left->right;
    left->right = node;
    fixHeight(node);
    fixHeight(left);
    return left;
}

AVLTree:: Node* AVLTree::rotateLeft(Node* node) {
    Node* right = node->right;
    node->right = right->left;
    right->left = node;
    fixHeight(node);
    fixHeight(right);
    return right;
}

AVLTree:: Node* AVLTree::balance(Node* node) {
    fixHeight(node);
    int bf = balanceFactor(node);
    if (bf == 2) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (bf == -2) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

AVLTree:: Node* AVLTree::insertNode(Node* node, int value)
{
    if (node == nullptr) {
        return new Node(value);
    }
    if (value < node->value) {
        node->left = insertNode(node->left, value);
    }
    else {
        node->right = insertNode(node->right, value);
    }
    return balance(node);
}

AVLTree::Node* AVLTree::findMin(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

AVLTree::Node* AVLTree::removeMin(Node* node) {
    if (node->left == nullptr) {
        return node->right;
    }
    node->left = removeMin(node->left);
    return balance(node);
}

AVLTree::Node* AVLTree::removeNode(Node* node, int value) {
    if (node == nullptr) {
        return nullptr;
    }
    if (value < node->value) {
        node->left = removeNode(node->left, value);
    }
    else if (value > node->value) {
        node->right = removeNode(node->right, value);
    }
    else {
        Node* left = node->left;
        Node* right = node->right;
        delete node;
        if (right == nullptr)
        {
            return left;
        }
        Node* min = findMin(right);
        min->right = removeMin(right);
        min->left = left;
        return balance(min);
    }
    return balance(node);
}

void AVLTree::printTree(Node* node, int indent) {
    if (node == nullptr) {
        return;
    }

    if (node->right != nullptr) {
        printTree(node->right, indent + 4);
    }

    if (indent > 0) {
        cout << setw(indent) << ' ';
    }

    cout << node->value << endl;

    if (node->left != nullptr) {
        printTree(node->left, indent + 4);
    }
}

double AVLTree::calculateLeafMean(int k, int r) {
    if (root == nullptr)
        return 0;

    double sum = 0;

    std::stack<Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Node* current = nodeStack.top();
        nodeStack.pop();

        if (current->left == nullptr && current->right == nullptr && (current->value >= k && current->value <= r)) {
            sum += current->value;
        }

        if (current->right != nullptr)
            nodeStack.push(current->right);

        if (current->left != nullptr)
            nodeStack.push(current->left);
    }
    return sum;

}

void AVLTree::insert(int value) {
    root = insertNode(root, value);
}

void AVLTree::remove(int value) {
    root = removeNode(root, value);
}

void AVLTree::print() {
    printTree(root, 0);
}