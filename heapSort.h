#ifndef HEAPSORT_H
#define HEAPSORT_H


template <typename T>
class HeapSort {
public:
    void sort(T* arr, int n) {
        //tablica 0 lub 1 elementowa jest już posortowana
        if (n <= 1) return;

        //buduje kopca
        //zaczynam od ostatniego węzła, który ma potomków (n/2 - 1) i idę w górę
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        //wyciągam elementy z kopca.
        //największy element (korzeń) ląduje na końcu tablicy, a kopiec zmniejszam
        for (int i = n - 1; i > 0; i--) {
            T temp = arr[0]; //przeniesienie korzenia na koniec
            arr[0] = arr[i];
            arr[i] = temp;

            //przywracam własności kopca dla pozostałych elementów
            heapify(arr, i, 0); 
        }
    }

private:
    void heapify(T* arr, int n, int rootIndex) {
        int largest = rootIndex;           //zakładam, że korzeń jest największy
        int leftChild = 2 * rootIndex + 1; //indeks lewego potomka
        int rightChild = 2 * rootIndex + 2; //indeks prawego potomka

        //sprawdzam, czy lewy potomek istnieje i czy jest większy od obecnego maksimum
        if (leftChild < n && arr[leftChild] > arr[largest]) {
            largest = leftChild;
        }

        //sprawdzamy, czy prawy potomek istnieje i czy jest większy od obecnego maksimum
        if (rightChild < n && arr[rightChild] > arr[largest]) {
            largest = rightChild;
        }

        //jeśli największy element nie jest korzeniem, zamieniam je miejscami 
        if (largest != rootIndex) {
            T temp = arr[rootIndex];
            arr[rootIndex] = arr[largest];
            arr[largest] = temp;

            //naprawa niższych poziomów kopca
            heapify(arr, n, largest);
        }
    }
};

#endif 