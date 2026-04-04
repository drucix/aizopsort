#ifndef QUICKS_H
#define QUICKS_H

#include <algorithm>

template <typename T>
class QuickSort {

public:
    static void sort(T* arr, int n) {
        if (n > 1) {
            sortQ(arr, 0, n - 1);
        }
    }

    static int partition(T* arr, int left, int right) {
        T pivot = arr[left + (right - left) / 2];
        int l = left;
        int r = right;

        while (true) {
            while (arr[l] < pivot) {
                l++;
            }
            while (arr[r] > pivot) {
                r--;
            }

            if (l >= r) {
                return r;
            }

            std::swap(arr[l], arr[r]);
            l++;
            r--;
        }
    }

private:
    static void sortQ(T* arr, int left, int right) {
        if (left < right) {
            int m = partition(arr, left, right);
            sortQ(arr, left, m);
            sortQ(arr, m + 1, right);
        }
    }
};

#endif