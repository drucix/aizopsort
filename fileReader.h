#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <fstream>
#include <iostream>

class FileReader {
public:
    //zwraca wskaźnik na nową tablicę, a do zmiennej tabSize wpisuje jej rozmiar
    template<typename T>
    T* readArray(const std::string& filename, int& tabSize) {
        std::ifstream file(filename);       //otwarcie pliku w trybie do odczytu
        if (!file.is_open()) {              //sprawdzam czy plik został poprawnie otwarty
            std::cout << "Nie mozna otworzyc pliku " << filename << "!\n";
            tabSize = 0;
            return nullptr;
        }

        file >> tabSize;                    //wczytuje rozmiar tablicy

        if (tabSize <= 0) {                 //sprawdzam czy rozmiar jest poprawny
            std::cout << "Zly rozmiar w pliku!\n";
            tabSize = 0;
            file.close();
            return nullptr;
        }
        
        //tworze nowa tablice i wczytuje dane z pliku
        T* arr = new T[tabSize];
        for (int i = 0; i < tabSize; ++i) {
            file >> arr[i];
        }

        file.close();               //zamykam plik
        return arr;
    }
};

#endif 