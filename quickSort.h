#ifndef QUICKS
#define QUICKS
#include <algorithm> //dla funkcji swap

template <typename T>
class QuickSort {
private:
    void sortQ(T* arr, int left, int right) {
        if (left >= right) return; 
            int m = partition(arr, left, right); //znajduję punkt podziału
            sortQ(arr, left, m); //rekurencyjnie sortuję lewą część
            sortQ(arr, m + 1, right); //rekurencyjnie sortuję prawą część
    }

    static int partition (T* arr, int left, int right) {
        T pivot = arr[left]; //wybieram skrajny lewy element jako pivot
        int l = left; //indeks dla mniejszych elementów
        int r = right; //indeks dla większych elementów

        while (true) {
            while (arr[l] < pivot) l++; //przesuwam l w prawo aż znajdę element większy lub równy pivot
            while (arr[r] > pivot) r--; //przesuwam r w lewo aż znajdę element mniejszy lub równy pivot

            if(l<r){ //jeżeli indeksy się nie minęły
                std::swap(arr[l], arr[r]); //zamieniam miejscami elementy na indeksach l i r
                l++; //przesuwam l w prawo
                r--; //przesuwam r w lewo
            } else { 
                if(r==right) r--;
                return r; //zwracam indeks podziału
            }

        }
    }
    
public:
    static void sort(T* arr, int n) {
        if(n>1){
            sortQ(arr, 0, n - 1); //wywołuję sortowanie na całej tablicy
        }
    }
};

#endif