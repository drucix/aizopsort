#ifndef APP_H
#define APP_H

class App {
public:
    App();       // Konstruktor
    void run();  // Główna pętla/menu

    // Metoda szablonowa musi zostać w pliku nagłówkowym
    template <typename T>
    bool isSorted(T* arr, int n) {
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                return false; 
            }
        }
        return true; 
    }

private:
    void fillRandom(int* arr, int n);
    void printArray(int* arr, int n);
    void copyArray(int* src, int* dest, int n);
    void testShellSort();
};

#endif