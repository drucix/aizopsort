#ifndef HYBRIDSORT_H
#define HYBRIDSORT_H

#include "quickSort.h"

template <typename T>
class HybridSort {
public:
    //parametr thresold (prog) pozwala dostosować, kiedy przełączyć się na Insertion - domyslnie 10
    void sort(T* arr, int n, int threshold = 10) {
        hybridQuickSort(arr, 0, n - 1, threshold);
    }

private:
    //sortowanie przez wstawianie dla malych podtablic
    void insertionSort(T* arr, int left, int right) {       
        for (int i = left + 1; i <= right; i++) {            //zaczynam od drugiego elementu
            T key = arr[i];                                  //klucz do wstawienia
            int j = i - 1;

            while (j >= left && arr[j] > key) {              //przesuwam elementy większe od klucza w prawo, żeby zrobić miejsce dla klucza
                arr[j + 1] = arr[j];
                j--;
            }

            arr[j + 1] = key;                                //wstawiam klucz na właściwe miejsce
        }
    }

    void hybridQuickSort(T* arr, int left, int right, int threshold) {
        if (left < right) {
            //używam podanego progu 
            if (right - left + 1 <= threshold) {
                insertionSort(arr, left, right);             //jezeli go nie przekraczam to sortuje przez wstawianie
            } else {                                         //w przeciwnym razie kontynuuje z quicksortem
                QuickSort<T> quick;
                int pivotIndex = quick.partition(arr, left, right);

                //wywołuje rekurencyjnie dla obu połówek
                hybridQuickSort(arr, left, pivotIndex, threshold);
                hybridQuickSort(arr, pivotIndex + 1, right, threshold);
            }
        }
    }
};

#endif