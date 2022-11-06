// ALGO2 IS1 212A LAB07
// Piotr Gos
// gp49257@zut.edu.pl

#include <iostream>
#include <string>
using namespace std;

//implementacja tablicy dynamicznej z LAB02
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
            array[size] = pValue; //tu coś
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

    void sort()
    {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1 - i; j++) {
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
        array = NULL;
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
//koniec implementacji tablicy dynamicznej

//_______________________________________________________________

//implementacja kopca binarnego z lab06
template <class T>
class Heap
{
public:

    int size = 0;
    int maxSize = 4;
    T* array = new T[maxSize];

    Heap() {
        size = 1;
        array[0] = numeric_limits<int>::max();
    }

    Heap(int tab[], int n) {
        for (int i = 0; i < n; i++)
            add(tab[i]);

        for (int i = n; i > 1; i--) {
            int temp = array[size-1];
            array[size-1] = array[0];
            array[0] = temp;
            check(size-1);
            size = size - 1;
        }

        for (int i = 0; i < n; i++)
            tab[i] = array[i];
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
        while (compare(array[2 * pIndex], array[pIndex]) != 0 || compare(array[2 * pIndex + 1], array[pIndex])) {
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
        while (compare(array[pSize], array[((pSize-1) / 2)]) != 0) {
            T temp = array[pSize];
            array[pSize] = array[((pSize - 1) / 2)];
            array[((pSize - 1) / 2)] = temp;

            pSize = ((pSize - 1) / 2);
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
//koniec implementacji kopca binarnego


void showTable(int tab[], int n) {
    for (int i = 0; i < n; i++)
        cout << tab[i] << " ";
    cout << endl;
}

void showTable(float tab[], int n) {
    for (int i = 0; i < n; i++)
        cout << tab[i] << " ";
    cout << endl;
}


void countingSort(int tab[], int n, int m) {
    int *tabCount=new int[m];

    for (int i = 0; i < m; i++)
        tabCount[i] = 0;

    for (int i = 0; i < n; i++) {
        int index = tab[i];
        tabCount[index]++;
        //tab[i] = 0;
    }


    int cntSortedElements = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < tabCount[i]; j++) {
            tab[cntSortedElements] = i;
            cntSortedElements++;
        }  
    }
}

void bucketSort(int tab[], int n, int m) {
	int amountBuckets = (m*4)+1;
	Array<int>* buckets = new Array<int>[amountBuckets];

	for (int i = 0; i < n; i++) {
        buckets[tab[i] * 4].add(tab[i]);
	}

    for (int i = 0; i < amountBuckets; i++) {
        if (buckets[i].size > 0)
            buckets[i].sort();    
    }

	int countSortElement = 0;
	for (int i = 0; i < amountBuckets; i++) {
        for (int j = 0; j < buckets[i].size; i++) {
            tab[countSortElement] = buckets[i].get(j);
            countSortElement++;
        }
	}
}

template <class T>
void bucketSort(T tab[], int n, T m) {
    int amountBuckets = floor((m * 4) + 1);
    Array<T>* buckets = new Array<T>[amountBuckets];

    for (int i = 0; i < n; i++) {
        buckets[(int)tab[i] * 4].add(tab[i]);
    }

    for (int i = 0; i < amountBuckets; i++) {
        if (buckets[i].size > 0)
            buckets[i].sort();
    }

    int countSortElement = 0;
    for (int i = 0; i < amountBuckets; i++) {
        for (int j = 0; j < buckets[i].size; i++) {
            tab[countSortElement] = buckets[i].get(j);
            countSortElement++;
        }
    }
}




int main()
{
    int tab[7] = { 10,45,12,43,66,54,67 };
    int n = 7;
    int m = 67;

    Heap<int> h1(tab, n);
   // countingSort(tab, n, m);
    //bucketSort(tab, n, m);

   // float tabf[7] = { 10,45,12,43,66,54,67 };
   // float mf = 67;
   // bucketSort(tabf, n, mf);
    showTable(tab, n);
}