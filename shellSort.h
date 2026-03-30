#ifndef SHELLSORT
#define SHELLSORT

template <typename T>
class ShellSort {
public:
    //klasyczne odstępy Shella
    static void sortWithShell(T* arr, int n) {
        for (int gap = n / 2; gap > 0; gap /= 2) { //zmniejszam odstępy o pół aż gap będzie 0
            for (int i = gap; i < n; i++) { //od gap do końca tablicy
                T temp = arr[i]; //element do wstawienia
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) { //sprawdzam czy element jest większy od temp 
                    arr[j] = arr[j - gap]; //przesuwam element o gap w prawo
                }
                arr[j] = temp; //wstawiam temp na właściwe miejsce
            }
        }
    }

    //odstępy Knutha
    static void sortWithKnuth(T* arr, int n) {
        int gap = 1;
        while (gap < n / 3) { //zwiekszam odstępy według wzoru Knutha aż gap będzie większy niż n/3
            gap = gap * 3 + 1; 
        }
        while (gap > 0) {//działa tak samo przez wstawianie tylko zmienia jest w obliczaniu gap
            for (int i = gap; i < n; i += 1) {
                T temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
            gap = (gap - 1) / 3; //odwrotność wzoru, który pozwala na cofanie się w ciągu
        }
    }
};

#endif