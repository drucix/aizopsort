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
    srand(static_cast<unsigned>(time(nullptr)));  //generator liczb losowych, dzięki któremu za każdym razem będą inne dane testowe
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

    //w zależności od wyboru typu danych, wywołuje odpowiednie podmenu z operacjami
    if (typeChoice == 1) {
        subMenu<int>();
    } else if (typeChoice == 2) {
        subMenu<float>();
    } else {
        cout << "Nieznana opcja!\n";
    }
}

//PODMENU - obsluguje operacje
template <typename T>
void App::subMenu() {
    //wskazniki na dynamicznie allokowane tablice
    T* currArray = nullptr;
    T* sortedArray = nullptr;
    int currSize = 0;
    int choice = -1;

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
                FileReader reader;
                T* loadedArray = reader.readArray<T>(fileName, newSize);    //wczytuje tablice z pliku

                if (loadedArray != nullptr) {   //jezeli wczytanie sie powiodlo, to usuwam stare tablice z pamieci
                    if (currArray != nullptr) {
                        delete[] currArray;
                        currArray = nullptr;
                    }
                    if (sortedArray != nullptr) {
                        delete[] sortedArray;
                        sortedArray = nullptr;
                    }
                    currSize = 0;

                    currSize = newSize;         //przypisuje nowy rozmiar i tablice do aktualnych zmiennych
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

                if (currArray != nullptr) {     //zwalaniam pamiec przed generowaniem
                    delete[] currArray;
                    currArray = nullptr;
                }
                if (sortedArray != nullptr) {
                    delete[] sortedArray;
                    sortedArray = nullptr;
                }
                currSize = 0;

                currSize = newRSize;
                ArrayGenerator generator;
                currArray = generator.normalArray<T>(currSize);         //generuje nowa tablice

                cout << "Wygenerowano tablice o rozmiarze " << currSize << ".\n";
                break;
            }
            case 3: {
                if (currArray == nullptr) {
                    cout << "Brak tablicy! Wczytaj lub wygeneruj ja najpierw.\n";
                } else {
                    if (currSize <= 50) {       //wyswietlam tylko dla malych tablic
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

                if (sortedArray != nullptr) {   //najpierw zwalniam pamiec 
                    delete[] sortedArray;
                    sortedArray = nullptr;
                }
                sortedArray = new T[currSize];  //alokuje pamiec dla posortowanej tablicy
                copyArray(currArray, sortedArray, currSize);        //kopiuje oryginalna tablice do posortowanej, zeby nie tracic danych

                int algoChoice;
                cout << "Wybierz algorytm (1-Shell(Klasyczny), 2-Shell(Knuth), 3-QuickSort, 4-HeapSort, 5-HybridSort): ";
                cin >> algoChoice;

                cout << "Sortowanie...\n";
                switch (algoChoice) {       //wywołuje odpowiedni algorytm sortowania w zależności od wyboru uzytkownika
                case 1:
                    ShellSort<T> ss;
                    ss.sortWithShell(sortedArray, currSize);
                    break;
                case 2:
                    ShellSort<T> sk;
                    sk.sortWithKnuth(sortedArray, currSize);
                    break;
                case 3:
                    QuickSort<T> qs;
                    qs.sort(sortedArray, currSize);
                    break;
                case 4:
                    HeapSort<T> hs;
                    hs.sort(sortedArray, currSize);
                    break;
                case 5:
                    HybridSort<T> hybrid;
                    hybrid.sort(sortedArray, currSize);
                    break;

                default:
                    cout << "Zly wybor algorytmu!\n";
                    break;
                }

                if (algoChoice < 1 || algoChoice > 5) {
                    break;
                }

                //wizualne wyswietlenie tylko dla malych tablic
                if (currSize <= 50) {
                    cout << "Posortowana tablica:\n";
                    printArray(sortedArray, currSize);
                } else {
                    cout << "Tablica zostala posortowana, ale ze wzgledu na duzy rozmiar nie zostanie wyswietlona.\n";
                }

                //weryfikacja poprawnosci sortowania
                if (isSorted(sortedArray, currSize)) {
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
                    if (currSize <= 50) {   //wyswietlam posortowana tablice tylko dla malych rozmiarow
                        cout << "Posortowana tablica:\n";
                        printArray(sortedArray, currSize);
                    } else {
                        cout << "Posortowana tablica (ukryta ze wzgledu na duzy rozmiar: " << currSize << " elementow).\n";
                    }
                }
                break;
            }

            case 6: {
                runPerformanceTest<T>();    //wywolanie funkcji do testowania wydajnosci
                break;
            }

            case 0:
                break;
            default:
                cout << "Nieznana opcja!\n";
        }
    }

    //posprzatanie pamieci przed calkowitym wyjsciem z podmenu
    if (currArray != nullptr) {
        delete[] currArray;
        currArray = nullptr;
    }
    if (sortedArray != nullptr) {
        delete[] sortedArray;
        sortedArray = nullptr;
    }
    currSize = 0;
}

template <typename T>       //funkcja pomcnicza do wyswietlania tablicy
void App::printArray(T* arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

template <typename T>       //funkcja pomocnicza do kopiowania tablicy
void App::copyArray(T* src, T* dest, int n) {
    for (int i = 0; i < n; ++i) {
        dest[i] = src[i];
    }
}

template <typename T>       //funkcja do testowania wydajnosci algorytmow sortowania
void App::runPerformanceTest() {
    int algoChoice;
    cout << "\n--- TESTY WYDAJNOSCIOWE ---\n";
    cout << "Wybierz algorytm do zbadania (1-Shell(Klasyczny), 2-Shell(Knuth), 3-QuickSort, 4-HeapSort, 5-HybridSort): ";
    cin >> algoChoice;

    if (algoChoice < 1 || algoChoice > 5) {
        cout << "Niepoprawny wybor algorytmu!\n";
        return;
    }

    //hybrydowy sort jest testowany tylko dla typu int
    if (algoChoice == 5 && !std::is_same<T, int>::value) {      //używam type traits czy podane typy  w nawiasach są takie same, value zwraca true lub false
        cout << "\nHybridSort mozna tylko dla typu int!\n";
        return;
    }

    //zapisanie wynikow do pliku csv
    ofstream plik("wyniki.csv", ios::app);      //otwieram plik w trybie dopisywania, uzywam 
    if (!plik.is_open()) {
        cout << "Nie udalo sie utworzyc pliku wyniki.csv!\n";
        return;
    }

    //naglowki kolumn
    plik << "Algorytm;Rozklad;Rozmiar;Prog;Czas_ms\n";

    //7 reprezentatywnych rozmiarow tablic
    int sizes[] = {10000, 20000, 40000, 80000, 160000, 320000, 640000};
    int numSizes = 7;
    int iterations = 100; //100 powtorzen dla kazdego rozmiaru i rozkladu
    int thresholds[] = {5, 10, 20}; //3 progi
    int numThresholds = 3;

    string distributions[] = {
        "losowo",
        "rosnaco",
        "malejaco",
        "czesciowo posortowane (33%)",
        "czesciowo posortowane (66%)"
    };

    cout << "\nTesty w trakcie...\n";

    ArrayGenerator g;
    //pierwsza pętla przechodzi przez wszystkie 5 distributions
    for (int d = 0; d < 5; ++d) {
        cout << "\n--- Uklad danych: " << distributions[d] << " ---\n";

        //druga pętla przechodzi przez wszystkie rozmiary tablic
        for (int s = 0; s < numSizes; ++s) {
            int currentSize = sizes[s];

            //hybrydowy sort - dla roznych progow
            if (algoChoice == 5) {
                //trzecia pętla przechodzi przez wszystkie progi dla hybrydowego sortu
                for (int t = 0; t < numThresholds; ++t) {
                    int currentThreshold = thresholds[t];
                    double totalTimeMs = 0.0;   //suma czasu dla 100 powtórzeń
                    
                    //pętla wykonuje 100 iteracji dla danego rozmiaru i rozkladu, żeby móc uśrednić wyniki
                    for (int i = 0; i < iterations; ++i) {
                        T* testArr = nullptr;
                        switch (d) {
                            case 0: testArr = g.normalArray<T>(currentSize); break;
                            case 1: testArr = g.sortedArray<T>(currentSize); break;
                            case 2: testArr = g.descendingArray<T>(currentSize); break;
                            case 3: testArr = g.partiallySortedArray<T>(currentSize, 33); break;
                            case 4: testArr = g.partiallySortedArray<T>(currentSize, 66); break;
                        }

                        HybridSort<T> hyb;

                        auto start = chrono::high_resolution_clock::now();  //zaczynam mierzenie czasu dopiero po wygenerowaniu tablic
                        hyb.sort(testArr, currentSize, currentThreshold);   //sortowanie
                        auto end = chrono::high_resolution_clock::now();    //kończę mierzenie czasu zaraz po posortowaniu

                        chrono::duration<double, std::milli> elapsed = end - start;     //obliczam czas trwania sortowania i rzutuje na milisekundy
                        totalTimeMs += elapsed.count();                 //dodaje czas do sumy
                        delete[] testArr;       //zwalniam pamiec po kazdej iteracji, zeby nie bylo przeciekow pamieci
                    }

                    double avgTime = totalTimeMs / iterations;      //obliczam średni czas dzieląc sumę przez liczbę iteracji
                    cout << "Rozmiar: " << setw(8) << currentSize   //ustawiam szerokość pola dla rozmiaru, żeby ładnie się wyrównało w konsoli
                         << " | Prog wstawiania: " << setw(2) << currentThreshold       //tak samo dla progu
                         << " | Sredni czas: " << fixed << setprecision(3) << avgTime << " ms\n";   //ograniczam do 3 miejsc po przecinku 

                    //zapis do pliku
                    plik << algoChoice << ";" << distributions[d] << ";" << currentSize << ";"  
                         << currentThreshold << ";" << fixed << setprecision(3) << avgTime << "\n"; //tutaj oddzielam wszystkie srednikiem, zeby wczytac potem do excela
                }
            }
            //pozostale algorytmy dzialaja tak jak dotychczas, bez progu, wiec wykonuje tylko 100 iteracji dla kazdego rozmiaru i rozkladu
            else {
                double totalTimeMs = 0.0;
                for (int i = 0; i < iterations; ++i) {
                    T* testArr = nullptr;
                    switch (d) {
                        case 0: testArr = g.normalArray<T>(currentSize); break;
                        case 1: testArr = g.sortedArray<T>(currentSize); break;
                        case 2: testArr = g.descendingArray<T>(currentSize); break;
                        case 3: testArr = g.partiallySortedArray<T>(currentSize, 33); break;
                        case 4: testArr = g.partiallySortedArray<T>(currentSize, 66); break;
                    }

                    auto start = chrono::high_resolution_clock::now();
                    switch (algoChoice) {
                        case 1:
                            ShellSort<T> shell;
                            shell.sortWithShell(testArr, currentSize);
                            break;
                        case 2:
                            ShellSort<T> knuth;
                            knuth.sortWithKnuth(testArr, currentSize);
                            break;
                        case 3:
                            QuickSort<T> quick;
                            quick.sort(testArr, currentSize);
                            break;
                        case 4:
                            HeapSort<T> heap;
                            heap.sort(testArr, currentSize);
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

                plik << algoChoice << ";" << distributions[d] << ";" << currentSize << ";-;"
                     << fixed << setprecision(3) << avgTime << "\n";
            }
        }
    }

    plik.close();
    cout << "--------------------------------------------------\n";
    cout << "Testy zakonczone sukcesem!\n";
};