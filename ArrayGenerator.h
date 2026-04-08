#ifndef ARRAYGENERATOR_H
#define ARRAYGENERATOR_H

#include <cstdlib>
#include "quickSort.h"

class ArrayGenerator {

//generuje tablice o roznych cechach, kazda funkcja zwraca wskaznik do tablicy
public:
    //tablica calkowicie losowa
    template<typename T>
    T* normalArray(int size) {
        T* tab = new T[size];
        for (int i = 0; i < size; i++) {
            double randomValue = static_cast<double>(rand()) / RAND_MAX;    //losowy double z zakresu [0, 1]
            tab[i] = static_cast<T>(randomValue * 500);         //skalowanie do zakresu 0-500 i rzutuje na typ T
        }
        return tab;
    }

    //tablica posortowana rosnaco
    template<typename T>
    T* sortedArray(int size) {
        T* tab = normalArray<T>(size);
        QuickSort<T> quick;
        quick.sort(tab, size);  //używam tu quicksorta
        return tab;
    }

    //tablica posortowana malejaco
    template<typename T>
    T* descendingArray(int size) {
        T* tab = sortedArray<T>(size);  //najpierw sortuje rosnaco

        //odwracam tablice, żeby była posortowana malejaco
        for (int i = 0; i < size / 2; i++) {
            T temp = tab[i];
            tab[i] = tab[size - 1 - i];
            tab[size - 1 - i] = temp;
        }
        return tab;
    }

    //tablica czesciowo posortowana 
    template<typename T>
    T* partiallySortedArray(int size, int percentSorted) {
        T* tab = normalArray<T>(size);
        
        int sortedSize = (size * percentSorted) / 100;      //obliczam ile dokladnie elementów ma być posortowanych

        if (sortedSize > 1) {
            QuickSort<T> quick;
            quick.sort(tab, sortedSize);        //sortuje te elementy
        }
        
        //dodatkowo mieszam reszte elementów, żeby nie były posortowane
        if (sortedSize < size) {
            for (int i = sortedSize; i < size; i++) {
                int j = sortedSize + rand() % (size - sortedSize);
                
                //zamieniam bieżący element z losowym elementem z nieposortowanej części tablicy
                T temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }

        return tab;
    }
};

#endif