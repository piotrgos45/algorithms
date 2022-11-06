//My implementation od dynamic array
#include <iostream>
#include <cstdio>
#include <string>
#include <time.h>

using namespace std;

template <class T>
class Array
{
public:
    //Array(){}
    int size = 0;
    int maxSize = 1;
    T* array = new T[maxSize];

    void add(T pValue)
    {
        if (size <= maxSize)
        {
            array[size] = pValue;
            size++;
        }
        else
        {
            T* tempArray = new T[maxSize];
            for (int j = 0; j < size; j++)
                tempArray[j] = array[j];

            array = new T[2 * maxSize];
            maxSize = maxSize * 2;

            for (int i = 0; i < size; i++) {
                array[i] = tempArray[i];
            }
            array[size] = pValue;
            size++;

            tempArray = NULL;
            delete[] tempArray;


            cout << "Max size: " << maxSize << endl;
        }
    }

    T get(int index)
    {
        if (index<0 || index>size)
            return false;
        else
            return array[index];
    }

    T set(int index, T pValue)
    {
        if (index >= 0 && index < size)
            array[index] = pValue;
        else
            return false;
    }

    void remove()
    {
        for (int i = 0; i < size; i++)
        {
            array[i] = NULL;
            maxSize = 1;
            size = 0;
            array = new T[maxSize];
        }
    }

    void returnString(int a)
    {
        cout << "The array has " << to_string(size) << " elements."<<endl;

        if (a-1 >= 0 && a-1 < size) {
            cout << "This is first " << to_string(a) << " elements:" << endl;
            for (int i = 0; i < a-1; i++)
                cout <<to_string(get(i)) << " ";
        }
        else {
            cout << "Your instruction is wrong" << endl;
        }
        
    }

    void sort()
    {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size-1 - i; j++) {
                if (compare(array[j], array[j + 1]) < 0) {
                    T temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    ~Array()
    {
        delete[] array;
    }

private:

    int compare(T val1, T val2)
    {
        int diff = val2 - val1;
        if (diff != 0)
            return diff;
        return val2 - val2;

    }

};

int main()
{
    Array<int> a1;
    srand(time(NULL));
    
    for (int i = 0; i < 10; i++) {
        a1.add(rand() % 100);
    }
    a1.returnString(10);
    clock_t time1 = clock();
    a1.sort();
    clock_t time2 = clock();
    a1.returnString(10);
}