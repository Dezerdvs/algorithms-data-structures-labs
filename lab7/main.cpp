#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "windows.h"

using namespace std;
using namespace std::chrono;

class hopscotch_table {
protected:
    struct cell {
        int value;
        bool occupied;
        vector<int> hops;
    };

    cell *table;
    int table_size;

    virtual int convert(int key) = 0; // Віртуальна функція, яка буде перевизначена в похідних класах

public:
    hopscotch_table() {
        table_size = 0;
        table = nullptr;
    }

    virtual ~hopscotch_table() {
        delete[] table;
    }

    void print() {
        for (int i = 0; i < table_size; i++) {
            if (table[i].occupied)
                cout << "№" << i << ": " << table[i].value << endl;
        }
    }

    void setTableSize(int size) {
        table_size = size + 1;
        table = new cell[table_size];
        for (int i = 0; i < table_size; i++) {
            table[i].value = -1;
            table[i].occupied = false;
        }
    }

    void clearTable() {
        for (int i = 0; i < table_size; i++) {
            table[i].value = -1;
            table[i].occupied = false;
            table[i].hops.clear();
        }
    }

    void insert(int value) {
        int index = convert(value);
        int probe = 0;

        while (probe < 32) {
            if (!table[index].occupied) {
                table[index].value = value;
                table[index].occupied = true;
                return;
            }
            probe++;

            int hop_range = std::min(4, table_size - index);
            int empty_slot = -1;

            for (int i = 0; i < hop_range; i++) {
                if (!table[index + i].occupied) {
                    empty_slot = index + i;
                    break;
                }
            }

            if (empty_slot != -1) {
                table[empty_slot].value = value;
                table[empty_slot].occupied = true;
                table[empty_slot].hops.push_back(empty_slot - index);
                return;
            }

            int hop_start = index + 1;
            int hop_end = index + hop_range;

            for (int i = hop_start; i < hop_end; i++) {
                for (int j = 0; j < table[i].hops.size(); j++) {
                    int hop_index = i - table[i].hops[j];
                    if (!table[hop_index].occupied) {
                        table[hop_index].value = table[i].value;
                        table[hop_index].occupied = true;
                        table[hop_index].hops.push_back(hop_index - index);
                        table[i].value = value;
                        table[i].occupied = true;
                        table[i].hops.push_back(hop_index - index);
                        return;
                    }
                }
            }

            index = (index + hop_range) % table_size;
        }
        cout << "Не вдалося вставити число " << value << endl;
    }

    int search(int value) {
        int index = convert(value);

        for (int probe = 0; probe < 32; probe++) {
            if (table[index].occupied && table[index].value == value)
                return index;
            index = (index + 1) % table_size;
        }

        return -1;
    }

    bool remove(int value) {
        int index = search(value);
        if (index != -1) {
            table[index].occupied = false;
            return true;
        }
        return false;
    }
};

class multiply_table : public hopscotch_table {
private:
    int convert(int key) override { // Функція множення
        const float A = 0.6180339887;
        return static_cast<int>(table_size * (key * A - static_cast<int>(key * A)));
    }

public:
    multiply_table() : hopscotch_table() {}

    ~multiply_table() override {}
};

class folding_table : public hopscotch_table {
private:
    int convert(int key) override {
        int hash = key;
        hash ^= (hash >> 20) ^ (hash >> 12);
        hash ^= (hash >> 7) ^ (hash >> 4);
        hash %= table_size;
        return hash;
    }

public:
    folding_table() : hopscotch_table() {}

    ~folding_table() override {}
};

void time_tasks_mult() {
    string file = "data_mult.txt";
    ofstream fin;
    fin.open(file);
    cout << "\nХеш-фунція множення:\n";
    cout << "Заповнення \t Розмір \t Час(сек)\n";
    for (int i = 1000; i < 20000; i += 1000) {
        for (double j = 0.1; j < 0.9; j += 0.1) {
            multiply_table table;
            table.setTableSize(i);
            for (int k = 0; k < i * j; k++)
                table.insert(k + 20);

            double res = 0.0;
            for (int k = 0; k < 5; k++) {
                time_point start = high_resolution_clock::now();
                for (int m = 0; m <= 1000000; m++) {
                    table.insert(15);
                    table.search(15);
                    table.remove(15);
                }
                time_point stop = high_resolution_clock::now();
                double time = duration_cast<milliseconds>(stop - start).count();
                time /= 1000;
                res += time;
            }
            cout << j << "\t" << i << "\t" << res / 5 << endl;
            fin << j << "\t" << i << "\t" << res / 5 << endl;
        }
    }
    fin.close();
}

void time_tasks_fold() {
    string file = "data_fold.txt";
    ofstream fin;
    fin.open(file);

    cout << "\nХеш-фунція згортання:\n";
    cout << "Заповнення \t Розмір \t Час(сек)\n";
    for (int i = 1000; i < 20000; i += 1000) {
        for (double j = 0.1; j < 0.9; j += 0.1) {
            folding_table table;
            table.setTableSize(i);
            for (int k = 0; k < i * j; k++)
                table.insert(k + 20);

            double res = 0.0;
            for (int k = 0; k < 5; k++) {
                time_point start = high_resolution_clock::now();
                for (int m = 0; m <= 1000000; m++) {
                    table.insert(15);
                    table.search(15);
                    table.remove(15);
                }
                time_point stop = high_resolution_clock::now();
                double time = duration_cast<milliseconds>(stop - start).count();
                time /= 1000;
                res += time;
            }
            cout << j << "\t" << i << "\t" << res / 5 << endl;
            fin << j << "\t" << i << "\t" << res / 5 << endl;
        }
    }
    fin.close();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Бажаєте провести заміри часу?(1/0)\nВаш вибір: ";
    int var = 0;
    cin >> var;
    if (var) {
        time_tasks_mult();
        time_tasks_fold();
        return 0;
    }

    cout << "\nМноження:\n";
    multiply_table ht;
    ht.setTableSize(10);
    ht.insert(5);
    ht.insert(15);
    ht.insert(25);
    ht.insert(35);
    ht.print();

    cout << "\nЗгортання:\n";
    folding_table ft;
    ft.setTableSize(10);
    ft.insert(5);
    ft.insert(15);
    ft.insert(25);
    ft.insert(35);
    ft.print();

    return 0;
}