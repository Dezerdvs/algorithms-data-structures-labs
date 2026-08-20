#pragma once

class Cherga {
public:
    Cherga();
    virtual ~Cherga();

    int GetSize() {
        return Size;
    }

    void Push(int data);
    int Pop();
    bool IsEmpty();
    void Clear();
private:
    class Node {
    public:
        Node* pNext;
        int Data;

        Node(int data, Node* prev = nullptr, Node* Next = nullptr) {
            this->Data = data;
            this->pNext = Next;
        }
    };
    int Size;
    Node* Front;
    Node* Back;
};