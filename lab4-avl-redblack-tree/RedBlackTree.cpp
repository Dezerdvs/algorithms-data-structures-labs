#include "RedBlackTree.h"
#include <iostream>
#include <iomanip>
#include <stack>

void RedBlackTree::rotateLeft(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != nullptr)
        rightChild->left->parent = node;

    rightChild->parent = node->parent;

    if (node->parent == nullptr)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::rotateRight(Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != nullptr)
        leftChild->right->parent = node;

    leftChild->parent = node->parent;

    if (node->parent == nullptr)
        root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

void RedBlackTree::fixInsertViolation(Node* node) {
    while (node != root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;

            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRight(node->parent->parent);
            }
        }
        else {
            Node* uncle = node->parent->parent->left;

            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(node->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

void RedBlackTree::fixDeleteViolation(Node* node) {
    while (node != root && node->color == BLACK) {
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }

            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                node = node->parent;
            }
            else {
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                rotateLeft(node->parent);
                node = root;
            }
        }
        else {
            Node* sibling = node->parent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateRight(node->parent);
                sibling = node->parent->left;
            }

            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                node = node->parent;
            }
            else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                rotateRight(node->parent);
                node = root;
            }
        }
    }

    node->color = BLACK;
}

void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}



void RedBlackTree::insert(int value) {
    Node* newNode = new Node(value);
    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr) {
        parent = current;
        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;

    if (parent == nullptr)
        root = newNode;
    else if (value < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixInsertViolation(newNode);
}

void RedBlackTree::remove(int value) {
    Node* node = root;

    while (node != nullptr) {
        if (value == node->data)
            break;
        else if (value < node->data)
            node = node->left;
        else
            node = node->right;
    }

    if (node == nullptr)
        return;

    Node* x;
    Node* y = node;
    Color yOriginalColor = y->color;

    if (node->left == nullptr) {
        x = node->right;
        transplant(node, node->right);
    }
    else if (node->right == nullptr) {
        x = node->left;
        transplant(node, node->left);
    }
    else
    {
        y = minimum(node->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == node)
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }

        transplant(node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }

    delete node;

    if (yOriginalColor == BLACK)
        fixDeleteViolation(x);
}

void RedBlackTree::printTreeHelper(Node* node, int indent, bool isLeft) {
    if (node == nullptr)
        return;

    printTreeHelper(node->right, indent + 4);

    if (indent > 0)
        std::cout << std::setw(indent) << " ";

    std::cout << (isLeft ? "├──" : "└──") << node->data << " (" << (node->color == RED ? "Red" : "Black") << ")" << std::endl;

    printTreeHelper(node->left, indent + 4, true);
}
void RedBlackTree::printTree() {
    std::cout << "root:" << root->data << std::endl;

    printTreeHelper(root);
}
double RedBlackTree::calculateLeafMean(int k, int r) {
    if (root == nullptr)
        return 0;

    double sum = 0;

    std::stack<Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Node* current = nodeStack.top();
        nodeStack.pop();

        if (current->left == nullptr && current->right == nullptr && (current->data >= k && current->data <= r)) {
            sum += current->data;
        }

        if (current->right != nullptr)
            nodeStack.push(current->right);

        if (current->left != nullptr)
            nodeStack.push(current->left);
    }
    return sum;

}

RedBlackTree::Node *RedBlackTree::minimum(RedBlackTree::Node *node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}
