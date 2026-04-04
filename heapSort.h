#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <algorithm>

template <typename T>
class HeapSort {
public:
    static void sort(T* arr, int n) {
        // Krok 1: Budowanie kopca (reorganizacja tablicy)
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // Krok 2: Ekstrakcja elementów z kopca
        for (int i = n - 1; i > 0; i--) {
            // Przeniesienie obecnego korzenia (największego elementu) na koniec
            std::swap(arr[0], arr[i]);
            // Przywrócenie własności kopca dla zmniejszonej tablicy
            heapify(arr, i, 0);
        }
    }

private:
    static void heapify(T* arr, int n, int i) {
        int largest = i; // Inicjalizujemy największy jako korzeń
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Jeśli lewe dziecko jest większe niż korzeń
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        // Jeśli prawe dziecko jest większe niż dotychczasowy 'largest'
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        // Jeśli największy nie jest korzeniem
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            // Rekurencyjnie naprawiamy poddrzewo
            heapify(arr, n, largest);
        }
    }
};

#endif // HEAPSORT_H