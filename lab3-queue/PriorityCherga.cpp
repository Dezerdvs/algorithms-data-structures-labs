#include "PriorityCherga.h"
#include <iostream>

using namespace std;

PriorityCherga::PriorityCherga() {
    Size = 0;
    Head = nullptr;
}

PriorityCherga::~PriorityCherga() {
    Clear();
}

int PriorityCherga::Pop() {
    if (IsEmpty()) {
        cout << "Черга пуста" << endl;
        return -1;
    }
    Node* temp = Head;
    int data = temp->Data;
    Head = Head->pNext;

    Size--;
    return data;
}

void PriorityCherga::Push(int data, const unsigned priority) {
    Node* newNode = new Node(data,priority);
    if (Head == nullptr || priority < Head->Priority) {
        newNode->pNext = Head;
        Head = newNode;
    }
    else {
        Node* temp = Head;
        while (temp->pNext != nullptr && priority >= temp->pNext->Priority) {
            temp = temp->pNext;
        }
        newNode->pNext = temp->pNext;
        temp->pNext = newNode;
    }
    Size++;
}
bool PriorityCherga::IsEmpty() {
    return Head == nullptr;
}

void PriorityCherga::Clear() {
    while (Size) {
        Pop();
    }
}