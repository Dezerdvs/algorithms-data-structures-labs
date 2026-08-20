#pragma once

enum Color { RED, BLACK };
class RedBlackTree {
private:
    class Node {
    public:
        int data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(int value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    Node* root;

    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void fixInsertViolation(Node* node);
    void fixDeleteViolation(Node* node);
    void transplant(Node* u, Node* v);
    Node* minimum(Node* node);
    void printTreeHelper(Node* node, int indent = 0, bool isLeft = false);
public:
    RedBlackTree() : root(nullptr) {}

    void insert(int value);
    void remove(int value);
    void printTree();
    double calculateLeafMean(int k, int r);

};