#include <iostream>
#include <chrono>
#include "Cherga.h"
#include "PriorityCherga.h"

using namespace std;

void FillCherga(Cherga& q,int count) {
    for (int i = 0; i < count; i++) {
        q.Push(i);
    }
}

void FillPriorityCherga(PriorityCherga& q, int count) {
    for (int i = 1; i < count; i++) {
        q.Push(i, rand() % 10);
    }
}

int MultiplyCherga(Cherga& ch_row, Cherga& ch_cols) {
    int sum = 0;
    Cherga ch_row_temp;
    Cherga ch_cols_temp;
    while (!ch_row.IsEmpty() || !ch_cols.IsEmpty()) {
        int row_temp = ch_row.Pop();
        ch_row_temp.Push(row_temp);
        int cols_temp = ch_cols.Pop();
        ch_cols_temp.Push(cols_temp);

        sum += row_temp + cols_temp;
    }
    ch_row = ch_row_temp;
    ch_cols = ch_cols_temp;
    return sum;
}

int MultiplyPriorityCherga(PriorityCherga& ch_row, PriorityCherga& ch_cols) {
    int sum = 0;
    PriorityCherga ch_row_temp;
    PriorityCherga ch_cols_temp;
    int priority = 0;
    while (!ch_row.IsEmpty() || !ch_cols.IsEmpty()) {
        int row_temp = ch_row.Pop();
        ch_row_temp.Push(row_temp, priority);
        int cols_temp = ch_row.Pop();
        ch_cols_temp.Push(cols_temp, priority);

        sum += row_temp + cols_temp;
    }
    ch_row = ch_row_temp;
    ch_cols = ch_cols_temp;
    return sum;
}

void Task1(Cherga& ch_row, Cherga& q_cols) {

    cout << "Перше завдання: " << endl;
    auto start = chrono::high_resolution_clock::now();
    int sum = MultiplyCherga(ch_row, q_cols);
    std::chrono::duration<double> duration = chrono::high_resolution_clock::now() - start;
    cout << fixed << "Черга" << ": " << duration.count() << " Результат: " << sum << endl;
}
void Task2(PriorityCherga& ch_row, PriorityCherga& q_cols) {

    cout << "Друге завдання: " << endl;
    auto start = chrono::high_resolution_clock::now();
    int sum = MultiplyPriorityCherga(ch_row, q_cols);
    std::chrono::duration<double> duration = chrono::high_resolution_clock::now() - start;
    cout << fixed << "Черга з приеоритетом" << ": " << duration.count() << " Результат: " << sum << endl;
}


int main() {
    system("chcp 65001");

    int size = 1000;
    cout << "Впишіть розміри: ";
    cin >> size;
    for (size_t i = 0; i < 10; i++) {
        cout << i + 1 << endl;

        Cherga ch_row;
        FillCherga(ch_row, size);
        Cherga ch_cols;
        FillCherga(ch_cols, size);

        Task1(ch_row, ch_cols);

        PriorityCherga pch_row;
        FillPriorityCherga(pch_row, size);
        PriorityCherga pch_cols;
        FillPriorityCherga(pch_cols, size);

        Task2(pch_row, pch_cols);

        size += 5000;
        cout << endl << endl;
    }
}

