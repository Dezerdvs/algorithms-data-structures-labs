#include <iostream>
#include "AVLTree.h"
#include "RedBlackTree.h"
#include <chrono>
#include <unordered_set>
#include <random>

using namespace std;

void FillAVLtree( AVLTree & tree, int count) {
    unordered_set<int> mySet;
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(1, count * 14);
    while (mySet.size() < count) {
        int value = distribution(generator);
        mySet.insert(value);
    }

    for (int value : mySet) {
        tree.insert(value);
    }
}

void FillRedBlackTree( RedBlackTree & tree, int count) {
    unordered_set<int> mySet;
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(1, count * 14);
    while (mySet.size() < count) {
        int value = distribution(generator);
        mySet.insert(value);
    }

    for (int value : mySet) {
        tree.insert(value);
    }
}

void Task1(AVLTree & tree, int fillCount,int k,int r) {

    FillAVLtree(tree, fillCount);

    auto start = chrono::high_resolution_clock::now();
    double result = tree.calculateLeafMean(k,r);
    std::chrono::duration<double> duration = chrono::high_resolution_clock::now() - start;
    cout << fixed << "Час: " << duration.count() << " Результат: " << result << endl;
    cout << endl;
}

void Task2(RedBlackTree & tree, int fillCount,int k,int r) {

    FillRedBlackTree(tree, fillCount);

    auto start = chrono::high_resolution_clock::now();
    double result = tree.calculateLeafMean(k,r);
    std::chrono::duration<double> duration = chrono::high_resolution_clock::now() - start;
    cout << fixed << "Час: " << duration.count() << " Резульат: " << result << endl;
    cout << endl;
}


int main() {
    system("chcp 65001");

    int size = 0;
    cout << "Enter size: ";
    cin >> size;
    int c = size;

    int k = 0, r = 0;
    cout << "\nEnter a range from k to r to calculate the arithmetic mean of the leaf nodes of the AVL-Tree\nk: ";
    cin >> k;
    cout << "r: ";
    cin >> r;

    for (size_t i = 0; i < 10; i++)
    {
        cout << to_string(i + 1) + " size: " + to_string(size) << endl;
        cout << to_string(i + 1) + " AVL-Tree" << endl;
        AVLTree avlTree;
        Task1(avlTree,size,k,r);

        cout << to_string(i + 1) + " BlackRed-Tree / size: " + to_string(size) << endl;
        RedBlackTree redBlackTree;
        Task2(redBlackTree,size,k, r);

        cout << endl;

        size += c;
    }
    return 0;
}
