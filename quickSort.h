#ifndef QUICKS_H
#define QUICKS_H

template <typename T>
class QuickSort {

public:
    void sort(T* arr, int n) {
        //wywołanie funkcji sortującej, jeśli tablica zawiera więcej niż jeden element
        if (n > 1) {
            sortQ(arr, 0, n - 1);
        }
    }

    int partition(T* arr, int left, int right) {
        //wybór pivota jako elementu środkowego
        T pivot = arr[left + (right - left) / 2];
        //lewy i prawy wskaznik do porównywania z pivotem
        int l = left;
        int r = right;

        //przesuwanie lewego i prawego wskaźnika w kierunku środka, aż znajdą elementy do zamiany
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

            //element po lewej, który jest większy/równy pivotowi 
            //i element po prawej, który jest mniejszy/równy, zamieniam je miejscami
            T temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
            l++;
            r--;
        }
    }

private:
    void sortQ(T* arr, int left, int right) {

        //warunek zakończenia rekurencji, ma conajmniej 2 elementy
        if (left < right) {
            int m = partition(arr, left, right);    //punkt dzielenia wedlug pivota
            sortQ(arr, left, m);                    //sortowanie lewej części
            sortQ(arr, m + 1, right);               //sortowanie prawej części
        }
    }
};

#endif