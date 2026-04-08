#ifndef APP_H
#define APP_H

class App {
public:
    App();       
    ~App();      
    void run(); //menu z typem danych

    //funkcja do weryfikacji sortowania
    template <typename T>
    bool isSorted(T* arr, int n) {
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {  //jezeli element jest większy od następnego, to tablica nie jest posortowana
                return false; 
            }
        }
        return true; 
    }

private:
    //menu z operacjami 
    template <typename T>
    void subMenu(); 

    //funkcje pomocnicze 
    template <typename T>
    void printArray(T* arr, int n);

    template <typename T>
    void copyArray(T* src, T* dest, int n);

    //funkcja do testowania wydajności
    template <typename T>
    void runPerformanceTest();
};

#endif