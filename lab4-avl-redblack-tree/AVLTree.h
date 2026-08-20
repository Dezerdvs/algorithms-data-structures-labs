#pragma once

using namespace std;

class AVLTree {
private:
    class Node
    {
    public:
        int value;
        Node* left;
        Node* right;
        int height;

        Node(int v) : value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int height(Node* node);
    int balanceFactor(Node* node);
    void fixHeight(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* balance(Node* node);
    Node* insertNode(Node* node, int value);
    Node* findMin(Node* node);
    Node* removeMin(Node* node);
    Node* removeNode(Node* node, int value);
    void printTree(Node* node, int indent = 0);
public:
    double calculateLeafMean(int k, int r);
    AVLTree() : root(nullptr) {}

    void insert(int value);
    void remove(int value);
    void print();
};