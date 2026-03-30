#include "App.h"
#include "ShellSorter.h" // Aby móc użyć sortowania
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Implementacja konstruktora
App::App() {
    srand(static_cast<unsigned>(time(nullptr)));
}

// Implementacja metody run()
void App::run() {
    cout << "--- TEST ALGORYTMU SHELLA ---\n\n";
    testShellSort();
}

// Implementacja reszty prywatnych metod
void App::fillRandom(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100; 
    }
}

void App::printArray(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void App::copyArray(int* src, int* dest, int n) {
    for (int i = 0; i < n; ++i) {
        dest[i] = src[i];
    }
}

void App::testShellSort() {
    int rozmiar = 15; 
    
    int* tablicaOryginalna = new int[rozmiar];
    int* tablicaDlaShella = new int[rozmiar];
    int* tablicaDlaKnutha = new int[rozmiar];

    fillRandom(tablicaOryginalna, rozmiar);
    copyArray(tablicaOryginalna, tablicaDlaShella, rozmiar);
    copyArray(tablicaOryginalna, tablicaDlaKnutha, rozmiar);

    cout << "Tablica przed sortowaniem:\n";
    printArray(tablicaOryginalna, rozmiar);
    cout << "--------------------------------\n";

    cout << "Sortowanie (odstepy Shella)...\n";
    ShellSorter<int>::sortWithShell(tablicaDlaShella, rozmiar);
    cout << "Wynik: ";
    printArray(tablicaDlaShella, rozmiar);
    
    // Używamy naszej metody isSorted do sprawdzenia poprawności
    if(isSorted(tablicaDlaShella, rozmiar)) cout << "Poprawnie posortowane!\n";
    else cout << "BLAD!\n";
    cout << "--------------------------------\n";

    cout << "Sortowanie (odstepy Knutha)...\n";
    ShellSorter<int>::sortWithKnuth(tablicaDlaKnutha, rozmiar);
    cout << "Wynik: ";
    printArray(tablicaDlaKnutha, rozmiar);
    
    if(isSorted(tablicaDlaKnutha, rozmiar)) cout << "Poprawnie posortowane!\n";
    else cout << "BLAD!\n";

    delete[] tablicaOryginalna;
    delete[] tablicaDlaShella;
    delete[] tablicaDlaKnutha;
}