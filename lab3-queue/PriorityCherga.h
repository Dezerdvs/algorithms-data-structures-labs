#pragma once

class PriorityCherga {
public:
    PriorityCherga();
    virtual ~PriorityCherga();

    int GetSize() {
        return Size;
    }

    int Pop();
    void Push(int data,unsigned priority);
    void Clear();
    bool IsEmpty();
private:
    class Node {
    public:
        Node* pNext;
        int Data;
        unsigned Priority;
        Node(int data, unsigned priority, Node* Next = nullptr) {
            this->pNext = Next;
            this->Data = data;
            this->Priority = priority;
        }
    };
    int Size;
    Node* Head;
};