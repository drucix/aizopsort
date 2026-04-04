#ifndef HYBRIDSORT_H
#define HYBRIDSORT_H

#include "quickSort.h"
#include <algorithm>

template <typename T>
class HybridSort {
public:
    //parametr thresold (prog) pozwala dostosować, kiedy przełączyć się na Insertion Sort
    static void sort(T* arr, int n, int threshold = 10) {
        hybridQuickSort(arr, 0, n - 1, threshold);
    }

private:
    static void insertionSort(T* arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // Przekazujemy 'threshold' w dół do rekurencji
    static void hybridQuickSort(T* arr, int left, int right, int threshold) {
        while (left < right) {
            // Używamy podanego progu w warunku
            if (right - left + 1 <= threshold) {
                insertionSort(arr, left, right);
                break;
            } else {
                int pivotIndex = QuickSort<T>::partition(arr, left, right);

                if (pivotIndex - left < right - pivotIndex) {
                    hybridQuickSort(arr, left, pivotIndex - 1, threshold);
                    left = pivotIndex + 1;
                } else {
                    hybridQuickSort(arr, pivotIndex + 1, right, threshold);
                    right = pivotIndex - 1;
                }
            }
        }
    }
};

#endif 