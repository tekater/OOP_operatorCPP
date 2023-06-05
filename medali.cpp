#pragma warning(disable:4996)

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

using namespace std;

class Array {
    int* arr;
    int size;
public:
    Array(int usize = 5) : arr{ new int[usize] }, size{ usize }
    {
        randomize(10, 20);
        cout << "Конструктор с параметром\n";
    }
    Array(const Array& obj) : arr{ new int[obj.size] }, size{ obj.size } {
        for (int i = 0; i < size; i++)
        {
            arr[i] = obj.arr[i];
        }

    }
    Array(Array&& obj) : arr{ obj.arr }, size{ obj.size } {
        obj.arr = nullptr;
        obj.size = 0;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    Array& operator=(Array&& obj) {

        if (this != nullptr) {
            delete[] arr;
        }
        arr = obj.arr;
        size = obj.size;

        obj.arr = nullptr;
        obj.size = 0;

        return *this;
    }

    ~Array()
    {
        if (arr)
        {
            delete[]arr;
        }
        cout << "Деструктор\n";
    }

    void randomize(int a, int b) //10 20
    {
        for (int i = 0; i < size; i++)
        {
            arr[i] = a + rand() % (b - a + 1); //10-29
        }
    }
    void setElem(int ind, int x)
    {
        arr[ind] = x;
    }
    int getElem(int ind) 
    {
        return arr[ind];
    }
    int getSize()  {
        return size;
    }

    int& operator[](int index) {

        return arr[index];
    }

    int operator[](int index)const  {
        return arr[index];
    }
};

enum medals {gold,silver,bronze};

class Olimpyc {
    char country[4];
    int medals[3];

public:

    Olimpyc(const char* ucountry, int* umedals) {

        /*if (ucountry != nullptr && umedals != nullptr) {
            strcpy(country, ucountry);
            for (int i = 0; i < 3; i++) {
                medals[i] = umedals[i];
            }
        }
        else {
            strcpy(country, "NON");
            for (int i = 0; i < 3; i++) {
                medals[i] = 0;
            }
        }*/

        for (int i = 0; i < 3; i++) {
            medals[i] = umedals ? umedals[i] : 0;
        }

        strcpy(country, ucountry ? ucountry : "NON");
    }

    Olimpyc() :Olimpyc{ nullptr, nullptr } { };

    void print() const {
        cout << country << " - [";
        for (int i = 0; i < 3; i++) {
            cout << medals[i] << " ";
        }
        cout << "]\n";
    }

    /*void setMed(int index, int num) {
        medals[index] = num;
    }
    int getMed(int index) {
        return medals[index];
    }*/

    Olimpyc& setCountry(const char* ecount) {
        strcpy(country, ecount ? ecount : "NON");
        return *this;
    }
    const char* getCountry() const {
        return country;
    }

    int& operator[](int index) {

        return medals[index];
    }

    int operator[](int index)const {
        return medals[index];
    }

};

class MedalkiTab {
    Olimpyc table[10];
    int max = 10;
    int current = 0;
    int findCount(const char* ucount) const {
        for (int i = 0; i < current; i++) {

            if (strcmp(table[i].getCountry(), ucount)==0) {
                return i;
            }

        }
        return -1;
    }
public:
    MedalkiTab() :max{ 10 }, current{ 0 } {};
    void print() const {
        for (int i = 0; i < current; i++) {
            cout << i << ": ";
            table[i].print();
        }
    }

    Olimpyc& operator[](const char* ucount) {
        int ind = findCount(ucount);
        if (ind == -1) {
            ind = current;
            table[ind].setCountry(ucount);
            current++;
        }
        return table[ind];
    }

    Olimpyc operator[](const char* ucount) const {
        int ind = findCount(ucount);
        return table[ind];
    }


};
int main() {

    setlocale(0, "");
    srand(time(NULL));

    Olimpyc o1;
    o1.print();
    o1[gold] = 2;
    cout << o1[gold] << endl;
    //o1.print();

    Olimpyc o2{ "RUS", new int[3] {3,2,1} };
    o2.print();
    o2[silver] = 4;
    //o2.print();
    cout << o2[silver] << endl; cout << "\n\n";
    o1.print(); o2.print(); cout << "\n\n";

    MedalkiTab MT;
    
    MT["RUS"][gold] = 5;
    MT["USA"][bronze] = 7;
    MT["RUS"][silver] = 100;
    MT.print();
}
