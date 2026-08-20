#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#define NOMINMAX
#include <windows.h>

using namespace std;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Функція для розбиття масиву та повернення індексу опорного елемента
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Опорний елемент
    int i = (low - 1);  // Індекс меншого елемента

    for (int j = low; j <= high - 1; j++) {
        // Якщо поточний елемент менший або рівний опорному
        if (arr[j] <= pivot) {
            i++;  // Збільшуємо індекс меншого елемента
            swap(&arr[i], &arr[j]);  // Обмін значень
        }
    }
    swap(&arr[i + 1], &arr[high]);  // Обмін значень
    return (i + 1);
}

// Основна функція для сортування масиву за допомогою алгоритму Quick Sort
void quickSort_(int arr[], int low, int high) {
    if (low < high) {
        // Отримуємо індекс опорного елемента
        int pivotIndex = partition(arr, low, high);

        // Рекурсивно сортуємо елементи перед опорним та після опорного
        quickSort_(arr, low, pivotIndex - 1);
        quickSort_(arr, pivotIndex + 1, high);
    }
}

void quickSort(int arr[], int n){ //Допоміжна функція швидкого сорутвання
    quickSort_(arr, 0, n - 1);
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;  // Індекс мінімального елемента, починаючи з поточної позиції

        // Знаходимо індекс найменшого елемента в підмасиві
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;  // Зберігаємо новий найменший індекс
            }
        }

        // Міняємо місцями найменший елемент з поточним елементом arr[i]
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

void timetask(int var) {
    int numerator = 50;
    string file = "data" + to_string(var) + ".txt";
    ofstream fin;
    fin.open(file);
    cout << "\nК-сть елемнтів \t Час(сек)";
    for (int n = 1000 * numerator; n <= 20000 * numerator; n += 1000 * numerator) {
        double res = 0;
        for (int i = 0; i < 5; i++) {
            int *arr = new int[n];

            for (int i = 0; i < n; i++)
                arr[i] = rand();

            auto start = chrono::high_resolution_clock::now();
            if (var == 1)
                selectionSort(arr, n);
            else
                quickSort(arr, n);
            auto stop = chrono::high_resolution_clock::now();
            double time = chrono::duration_cast<chrono::duration<double>>(stop - start).count();
            res += time / 1000;
            delete[] arr;
        }
        cout << endl << n << "\t" << res / 5;
        fin << endl << n << "\t" << res / 5;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    srand(time(0));

    cout << "Бажаєете запустити заміри часу?(1/0)\nВаш вибір: ";
    int var;
    cin >> var;

    if (var == 1) {
        cout << "Сортування вибором: ";
        timetask(1);
        cout << "Швидке сортування: ";
        timetask(2);
        return 0;
    }

    const int n = 8;
    int *selection = new int[n]{1, -2, 4, -1, 0, 11, -7, 6};
    int *quick = new int[n]{1, -2, 4, -1, 0, 11, -7, 6};

    cout << "Базовий масив: \n";
    printArray(selection, n);

    cout << "Масив після сортування вибором: \n";
    selectionSort(selection, n);
    printArray(selection, n);

    cout << "Масив після пірамідального сортування: \n";
    quickSort(quick, n);
    printArray(quick, n);


    delete[] selection;
    delete[] quick;
    return 0;
}
