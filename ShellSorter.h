#ifndef SHELLSORTER_H
#define SHELLSORTER_H

template <typename T>
class ShellSorter {
public:
    //klasyczne odstępy Shella
    static void sortWithShell(T* arr, int n) {
        for (int gap = n / 2; gap > 0; gap /= 2) { //zmniejszam odstępy o pół aż do 1
            for (int i = gap; i < n; i++) {
                T temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }
    }

    // Wariant 2: Odstępy Knutha
    static void sortWithKnuth(T* arr, int n) {
        int gap = 1;
        while (gap < n / 3) {
            gap = gap * 3 + 1; 
        }
        while (gap > 0) {
            for (int i = gap; i < n; i += 1) {
                T temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
            gap = (gap - 1) / 3;
        }
    }
};

#endif