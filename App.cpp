#include "App.h"
#include "shellSort.h"
#include "quickSort.h"
#include "arrayGenerator.h" 
#include "fileReader.h"
#include "heapSort.h"
#include "hybridSort.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

App::App() {
    srand(static_cast<unsigned>(time(nullptr)));
}

App::~App() {
}

//MENU - wybor typu danych
void App::run() {
    int typeChoice = -1;

    cout << "\n=== WYBIERZ TYP DANYCH ===\n";
    cout << "1. Liczby calkowite (int)\n";
    cout << "2. Liczby zmiennoprzecinkowe (float)\n";
    cout << "0. Wyjdz z programu\n";
    cout << "Wybierz opcje: ";
    cin >> typeChoice;

    if (typeChoice == 1) {
        subMenu<int>();
    } else if (typeChoice == 2) {
        subMenu<float>();
    } else if (typeChoice == 0) {
        cout << "Zamykanie programu...\n";
    } else {
        cout << "Nieznana opcja!\n";
    }
}

//PODMENU - obsluguje operacje
template <typename T>
void App::subMenu() {
    //zmienne lokalne  - obsługują obecny typ T
    T* currArray = nullptr;
    T* sortedArray = nullptr;
    int currSize = 0;
    int choice = -1;

    //funkcja do czyszczenia pamięci
    auto clearMem = [&]() {
        if (currArray != nullptr) {
            delete[] currArray;
            currArray = nullptr;
        }
        if (sortedArray != nullptr) {
            delete[] sortedArray;
            sortedArray = nullptr;
        }
        currSize = 0;
    };

    while (choice != 0) {
        cout << "\n================ Wybierz operacje ================\n";
        cout << "1. Wczytaj tablice z pliku\n";
        cout << "2. Wygeneruj losowa tablice\n";
        cout << "3. Wyswietl oryginalna tablice\n";
        cout << "4. Posortuj i wyswietl tablice\n";
        cout << "5. Wyswietl posortowana tablice\n";
        cout << "6. Przeprowadz testy wydajnosciowe\n";
        cout << "0. Wyjdz\n";
        cout << "Wybierz opcje: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string fileName;
                cout << "Podaj nazwe pliku (np. data.txt): ";
                cin >> fileName;

                int newSize = 0;
                T* loadedArray = FileReader::readArray<T>(fileName, newSize);

                if (loadedArray != nullptr) {
                    clearMem();
                    currSize = newSize;
                    currArray = loadedArray;
                    cout << "Wczytano tablice o rozmiarze " << currSize << ".\n";
                }
                break;
            }
            case 2: {
                int newRSize;
                cout << "Podaj rozmiar tablicy: ";
                cin >> newRSize;

                if (newRSize <= 0) {
                    cout << "Rozmiar musi byc wiekszy od 0!\n";
                    break;
                }

                clearMem(); 
                currSize = newRSize;
                currArray = ArrayGenerator::normalArray<T>(currSize);
                
                cout << "Wygenerowano tablice o rozmiarze " << currSize << ".\n";
                break;
            }
            case 3: {
                if (currArray == nullptr) {
                    cout << "Brak tablicy! Wczytaj lub wygeneruj ja najpierw.\n";
                } else {
                    if (currSize <= 50) {
                        cout << "Oryginalna tablica:\n";
                        printArray(currArray, currSize);
                    } else {
                        cout << "Oryginalna tablica (ukryta ze wzgledu na duzy rozmiar: " << currSize << " elementow).\n";
                    }
                }
                break;
            }
            case 4: {
                if (currArray == nullptr) {
                    cout << "Brak tablicy do posortowania!\n";
                    break;
                }

                if (sortedArray != nullptr) {
                    delete[] sortedArray;
                }
                sortedArray = new T[currSize];
                copyArray(currArray, sortedArray, currSize);

                int algoChoice;
                cout << "Wybierz algorytm (1-Shell(Klasyczny), 2-Shell(Knuth), 3-QuickSort, 4-HeapSort, 5-HybridSort): ";
                cin >> algoChoice;

                cout << "Sortowanie...\n";
                switch (algoChoice) {
                case 1:
                    ShellSort<T>::sortWithShell(sortedArray, currSize);
                    break;
                case 2:
                    ShellSort<T>::sortWithKnuth(sortedArray, currSize);
                    break;
                case 3:
                    QuickSort<T>::sort(sortedArray, currSize);
                    break;
                case 4:
                    HeapSort<T>::sort(sortedArray, currSize);
                    break;
                case 5:
                    HybridSort<T>::sort(sortedArray, currSize);
                    break;

                default:
                    cout << "Zly wybor algorytmu!\n";
                    break;
                }

                if (algoChoice < 1 || algoChoice > 5) {
                    break;
                }

                //wizualne wyświetlenie tylko dla małych tablic
                if (currSize <= 50) {
                    cout << "Posortowana tablica:\n";
                    printArray(sortedArray, currSize);
                } else {
                    cout << "Tablica zostala posortowana, ale ze wzgledu na duzy rozmiar nie zostanie wyswietlona.\n";
                }
                
                //weryfikacja poprawności sortowania
                if(isSorted(sortedArray, currSize)) {
                    cout << "=> Weryfikacja: Tablica posortowana poprawnie!\n";
                } else {
                    cout << "=> Weryfikacja: Tablica zle posortowana!\n";
                }
                break;
            }
            case 5: {
                if (sortedArray == nullptr) {
                    cout << "Tablica nie zostala jeszcze posortowana!\n";
                } else {
                    if (currSize <= 50) {
                        cout << "Posortowana tablica:\n";
                        printArray(sortedArray, currSize);
                    } else {
                        cout << "Posortowana tablica (ukryta ze wzgledu na duzy rozmiar: " << currSize << " elementow).\n";
                    }
                }
                break;
            }

            case 6: {
                runPerformanceTest<T>();
                break;
            }

            case 0:
                cout << "Zamykanie programu...\n";
                break;
            default:
                cout << "Nieznana opcja!\n";
        }
    }
    
    //posprzątanie pamięci przed całkowitym wyjściem z podmenu
    clearMem();
}

template <typename T>
void App::printArray(T* arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

template <typename T>
void App::copyArray(T* src, T* dest, int n) {
    for (int i = 0; i < n; ++i) {
        dest[i] = src[i];
    }
}

template <typename T>
void App::runPerformanceTest() {
    int algoChoice;
    cout << "\n--- TESTY WYDAJNOSCIOWE ---\n";
    cout << "Wybierz algorytm do zbadania (1-Shell(Klasyczny), 2-Shell(Knuth), 3-QuickSort, 4-HeapSort, 5-HybridSort): ";
    cin >> algoChoice;

    if (algoChoice < 1 || algoChoice > 5) {
        cout << "Niepoprawny wybor algorytmu!\n";
        return;
    }

    if (algoChoice == 5 && !std::is_same<T, int>::value) {
        cout << "\nHybridSort mozna tylko dla typu int!\n";
        return;
    }
    //7 reprezentatywnych rozmiarów tablic
    int sizes[] = {10000, 20000, 40000, 80000, 160000, 320000, 640000};
    int numSizes = 7;
    int iterations = 100; //100 powtórzeń dla każdego rozmiaru i rozkładu
    int thresholds[] = {5, 10, 20}; //3 progi

    string distributions[] = {
        "losowo", 
        "rosnaco", 
        "malejaco", 
        "czesciowo posortowane (33%)", 
        "czesciowo posortowane (66%)"
    };

    cout << "\nTesty w trakcie...\n";

    //pętla przechodząca przez wszystkie 5 układów danych
    for (int d = 0; d < 5; ++d) {
        cout << "\n--- Uklad danych: " << distributions[d] << " ---\n";
        
        for (int s = 0; s < numSizes; ++s) {
            int currentSize = sizes[s];

            //hybrydowy sort - dla roznych progow
            if (algoChoice == 5) {
                for (int t = 0; t < sizeof(thresholds)/sizeof(thresholds[0]); ++t) {
                    int currentThreshold = thresholds[t];
                    double totalTimeMs = 0.0;

                    for (int i = 0; i < iterations; ++i) {
                        T* testArr = nullptr;
                        switch(d) {
                            case 0: testArr = ArrayGenerator::normalArray<T>(currentSize); break;
                            case 1: testArr = ArrayGenerator::sortedArray<T>(currentSize); break;
                            case 2: testArr = ArrayGenerator::descendingArray<T>(currentSize); break;
                            case 3: testArr = ArrayGenerator::sorted33<T>(currentSize); break;
                            case 4: testArr = ArrayGenerator::sorted66<T>(currentSize); break;
                        }

                        auto start = chrono::high_resolution_clock::now();
                        HybridSort<T>::sort(testArr, currentSize, currentThreshold);
                        auto end = chrono::high_resolution_clock::now();

                        chrono::duration<double, std::milli> elapsed = end - start;
                        totalTimeMs += elapsed.count();
                        delete[] testArr; 
                    }

                    double avgTime = totalTimeMs / iterations;
                    cout << "Rozmiar: " << setw(8) << currentSize 
                         << " | Prog wstawiania: " << setw(2) << currentThreshold
                         << " | Sredni czas: " << fixed << setprecision(3) << avgTime << " ms\n";
                }
            } 
            //pozostałe algorytmy
            else {
                double totalTimeMs = 0.0;

                for (int i = 0; i < iterations; ++i) {
                    T* testArr = nullptr;
                    switch(d) {
                        case 0: testArr = ArrayGenerator::normalArray<T>(currentSize); break;
                        case 1: testArr = ArrayGenerator::sortedArray<T>(currentSize); break;
                        case 2: testArr = ArrayGenerator::descendingArray<T>(currentSize); break;
                        case 3: testArr = ArrayGenerator::sorted33<T>(currentSize); break;
                        case 4: testArr = ArrayGenerator::sorted66<T>(currentSize); break;
                    }

                    auto start = chrono::high_resolution_clock::now();
                    switch(algoChoice){
                        case 1:
                            ShellSort<T>::sortWithShell(testArr, currentSize);
                            break;
                        case 2:
                            ShellSort<T>::sortWithKnuth(testArr, currentSize);
                            break;
                        case 3:
                            QuickSort<T>::sort(testArr, currentSize);
                            break;
                        case 4:
                            HeapSort<T>::sort(testArr, currentSize);
                            break;
                    }
                    auto end = chrono::high_resolution_clock::now();

                    chrono::duration<double, std::milli> elapsed = end - start;
                    totalTimeMs += elapsed.count();
                    delete[] testArr; 
                }

                double avgTime = totalTimeMs / iterations;
                cout << "Rozmiar: " << setw(8) << currentSize 
                     << " | Sredni czas: " << fixed << setprecision(3) << avgTime << " ms\n";
            }
        }
    }
    cout << "--------------------------------------------------\n";
    cout << "Testy zakonczone sukcesem!\n";
}