#include "Cherga.h"
#include <iostream>

using namespace std;

Cherga::Cherga() {
    Front = nullptr;
    Back = nullptr;
    Size = 0;
}

Cherga::~Cherga() {
    Clear();
}

int Cherga::Pop() {
    if (IsEmpty()) {
        cout << "Черга пуста" << endl;
        return -1;
    }
    Node* temp = Front;
    int data = temp->Data;

    Front = Front->pNext;
    if (Front == nullptr) {
        Back = nullptr;
    }
    Size--;
    return data;
}

void Cherga::Push(int data) {
    Node* new_node = new Node(data);
    new_node->pNext = nullptr;
    if (Back == nullptr) {
        Front = new_node;
    }
    else {
        Back->pNext = new_node;
    }
    Back = new_node;
    Size++;
}

bool Cherga::IsEmpty() {
    return Front == nullptr;
}

void Cherga::Clear() {
    while (Size) {
        Pop();
    }
}