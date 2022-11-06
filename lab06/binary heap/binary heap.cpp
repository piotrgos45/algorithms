 //
//

#include <iostream>
#include <string>
#include <limits>

using namespace std;

template <class T>
class Array
{
public:
    
    int size = 1;
    int maxSize = 4;
    T * array = new T[maxSize];
    
    Array() {
        array[0] = numeric_limits<int>::max();
    }

    void add(T pValue)
    {
        if (size <= maxSize)
        {
            array[size] = pValue;
            check(size);
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
            check(size);
            size++;

            tempArray = NULL;
            delete[] tempArray;
        }
    }

    T get(int index)
    {
        if (index<0 || index>size)
            return false;
        else
            return array[index];
    }


    void removeMaxVariable()
    {
        array[1] = array[size - 1];
        size--;
        checkRemove(1);
    }

    void removeAllElements() {
        for (int i = 0; i < size; i++)
        {
            array[i] = NULL;
        }
        maxSize = 4;
        size = 1;
        array = new T[maxSize];
        array[0] = numeric_limits<int>::max();
    }

    void returnString(int a)
    {
        cout << "The array has " << to_string(size) << " elements." << endl;

        if (a - 1 >= 0 && a - 1 < size) {
            cout << "This is first " << to_string(a) << " elements:" << endl;
            for (int i = 0; i < a - 1; i++)
                cout << to_string(get(i)) << " ";
        }
        else {
            cout << "Your instruction is wrong" << endl;
        }

    }

    

    
private:

    void checkRemove(int pIndex) 
    {
        while (compare(array[2*pIndex], array[pIndex]) !=0|| compare(array[2*pIndex+1],array[pIndex])) {
            if (compare(array[2 * pIndex], array[2 * pIndex + 1]) != 0) {
                //jeżeli lewy większy od prawego
                T temp = array[pIndex];
                array[pIndex] = array[2 * pIndex];
                array[2 * pIndex] = temp;
                pIndex = 2 * pIndex;
            }
            else {
                //jeżeli prawy większy od lewego
                T temp = array[pIndex];
                array[pIndex] = array[2 * pIndex + 1];
                array[2 * pIndex + 1] = temp;
                pIndex = 2 * pIndex + 1;
            }
        }
        
    }

    void check(int pSize)
    {
        while (compare(array[pSize],array[pSize/2])!=0) {
           T temp = array[pSize];
            array[pSize] = array[pSize / 2];
            array[pSize / 2] = temp;

            pSize = pSize / 2;
        }
    }

    int compare(T val1, T val2)
    {
        if (val1 > val2)
            return 1;
        else
            return 0;

    }

};
int main()
{
    Array<int> a1;
    a1.add(1);
    a1.add(3);
    a1.add(2);
    a1.add(17);
    a1.add(14);

    a1.removeMaxVariable();
    a1.removeAllElements();
    a1.add(2);
    cout << a1.get(1) << endl;
    
}