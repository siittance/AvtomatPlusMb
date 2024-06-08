#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <thread>
#include <functional>
#pragma execution_character_set("utf-8")
using namespace std;

class MergeSort {
public:
    void Sort(vector<int>&  zam) {
        if ( zam.size() > 1) {
            size_t mid =  zam.size() / 2;
            vector<int> left( zam.begin(),  zam.begin() + mid);
            vector<int> right( zam.begin() + mid,  zam.end());


            thread leftThread(&MergeSort::Sort, this, ref(left));
            thread rightThread(&MergeSort::Sort, this, ref(right));

            leftThread.join();
            rightThread.join();

            Merge( zam, left, right);
        }
    }

private:
    void Merge(vector<int>&  zam, const vector<int>& left, const vector<int>& right) {
        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                 zam[k++] = left[i++];
            }
            else {
                 zam[k++] = right[j++];
            }
        }

        while (i < left.size()) {
             zam[k++] = left[i++];
        }

        while (j < right.size()) {
             zam[k++] = right[j++];
        }
    }
};

int main() {
    SetConsoleCP(65001); // устанавливаем кодировку входящего потока данных на UTF-8
    SetConsoleOutputCP(65001); // устанавливаем кодировку исходящего потока данных на UTF-8
    vector<int>  zam(10);

    cout << "Введите 10 чисел: " << endl;
    for (int i = 0; i < 10; ++i) {
        cin >>  zam[i];
    }

    MergeSort mergeSort;

    auto sortFunc = [&mergeSort](vector<int>&  zam) {
        mergeSort.Sort(zam);
        };

    thread mergeSortThread(sortFunc, ref( zam));

    mergeSortThread.join();

    cout << "Сортированный массив: " << endl;
    for (const auto& num :  zam) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}