#ifndef ARRAYGENERATOR_H
#define ARRAYGENERATOR_H

#include <cstdlib>
#include <algorithm> //potrzebne do szybkiego posortowania 33% i 66% tablicy

class ArrayGenerator {
public:
    //tablica całkowicie losowa
    template<typename T>
    static T* normalArray(int size) {
        T* tab = new T[size];
        for (int i = 0; i < size; i++) {
            tab[i] = rand() % 50;
        }
        return tab;
    }

    //tablica posortowana rosnąco
    template<typename T>
    static T* sortedArray(int size) {
        T* tab = new T[size];
        for (int i = 0; i < size; i++) {
            tab[i] = i; 
        }
        return tab;
    }

    //tablica posortowana malejąco
    template<typename T>
    static T* descendingArray(int size) {
        T* tab = new T[size];
        for (int i = 0; i < size; i++) {
            tab[i] = size - i;
        }
        return tab;
    }

    //tablica posortowana w 33%
    template<typename T>
    static T* sorted33(int size) {
        T* tab = normalArray<T>(size); //tworze losową
        int sortedSize = size / 3;
        std::sort(tab, tab + sortedSize); //szybko sortowane tylko początkowe 33%
        return tab;
    }

    //tablica posortowana w 66%
    template<typename T>
    static T* sorted66(int size) {
        T* tab = normalArray<T>(size); //tworze losową
        int sortedSize = (size * 2) / 3;
        std::sort(tab, tab + sortedSize); //szybko sortowane tylko początkowe 66%
        return tab;
    }
};

#endif