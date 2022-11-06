

#include <iostream>
#include <string>

using namespace std;
//implementacja tablicy dynamicznej z LAB 02
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

}; //koniec implementacji tablicy dynamicznej
//koniec implementacji tablicy dynamicznej

//implementacja listy dwukierunkowej z lab 01
template <class T>
class Element {
public:
	Element<T>* previus;
	T value;
	Element<T>* next;
};

template <class T>
class Lista
{
	Element<T>* head;
	Element<T>* tail;
	int countElements = 0;

	//methods
public:
	Lista(T pValue)
	{
		Element<T>* el = new Element<T>;
		el->value = pValue;
		el->next = NULL;
		el->previus = NULL;
		head = el;
		tail = el;
		countElements++;
	}

	void addElementEnd(T pValue)
		//wstawia element na końcu listy
	{
		Element<T>* el1 = tail;
		Element<T>* elNew = new Element<T>;
		elNew->value = pValue;
		elNew->previus = el1;
		elNew->next = NULL;
		el1->next = elNew;
		tail = elNew;
		countElements++;
		//cout << elNew->previus->value;
	}

	void addElementHead(T pValue)
		//wstawia element na początku listy
	{
		Element<T>* el1 = head;
		Element<T>* elNew = new Element<T>;
		elNew->value = pValue;
		elNew->previus = NULL;
		elNew->next = el1;
		el1->previus = elNew;
		head = elNew;
		countElements++;
		//cout << tail->value;
	}

	void removeElementEnd()
		//usuwa ostatni element
	{
		//cout << tail->value;
		Element<T>* elEnd = tail; //element do usunięcia
		Element<T>* el1 = elEnd->previus;
		tail = el1;
		el1->next = NULL;
		delete elEnd;
		elEnd = NULL;
		countElements--;
		cout << tail->value;
	}

	void removeElementHead()
		//usuwa pierwszy element
	{
		Element<T>* elHead = head;
		Element<T>* el1 = elHead->next;
		head = el1;
		el1->previus = NULL;
		delete elHead;
		elHead = NULL;
		countElements--;
		//cout << head->value;
	}

	T getElement(int index)
	{
		Element<T>* returnElement = head;
		if (index > countElements || index < 0) return false;

		if (index != 0)
		{
			for (int i = 1; i <= index; i++)
			{
				returnElement = returnElement->next;
			}
		}
		return returnElement->value;
	}

	bool setElement(int index, T pValue)
	{
		if (index > countElements || index < 0) return false;
		Element<T>* set = head;

		for (int i = 0; i <= index; i++)
		{
			if (i == index)
				set->value = pValue;
			else
				set = set->next;
		}
	}

	Element<T>* searchElement(T pPattern, string key)
		//Key - can be "v" - value
	{
		Element<T>* tempElement = head;

		if (key == "v")
			for (int i = 0; i < countElements; i++)
			{
				if (compare(pPattern, tempElement->value) == 0)
					return tempElement;
				else
					tempElement = tempElement->next;
			}
		return NULL;
	}

	bool searchRemoveElement(T pPattern, string key)
	{
		Element<T>* result = searchElement(pPattern, key);
		if (result != NULL)
		{
			Element<T>* prevElement = result->previus;
			Element<T>* nextElement = result->next;

			prevElement->next = result->next;
			nextElement->previus = result->previus;
			delete result;
			result = NULL;

			//check head and tail
			if (prevElement->previus == NULL)
				head = prevElement;
			if (prevElement->next == NULL)
				tail = prevElement;
			if (nextElement->previus == NULL)
				head = nextElement;
			if (nextElement->next == NULL)
				tail = nextElement;

			countElements--;
			return true;
		}
		return false;
	}

	void addSortElement(T pValue, string key)
	{
		if (key == "v")
		{
			addElementHead(pValue);

			//Element<T>* object2 = head->next;
			for (int i = 0; i < countElements; i++)
			{
				Element<T>* object1 = head;
				Element<T>* object2 = head->next;
				for (int j = 0; j < countElements + 1 - i; j++)
				{
					int res = compare(object1->value, object2->value);
					if (res > 0)
					{
						T tempValue = object1->value;

						//Element<T>* tempObj2 = object2;

						object1->value = object2->value;
						object2->value = tempValue;

						//cout << object1->value << " " << object2->value << endl;

					}
					if (object2->next != NULL)
					{
						object1 = object1->next;
						object2 = object2->next;
					}
					else
						break;
				}
			}

		}
	}

	void removeAllElements()
	{
		Element<T>* start = head->next;

		while ((start->previus) == NULL)
		{
			Element<T>* prevStart = start->previus;
			delete prevStart;
			prevStart = NULL;

			start = start->next;
		}
		delete start;
		start = NULL;
		countElements = 0;
	}

	void returnString(int a)
	{
		cout << "The list has " << to_string(countElements) << " elements" << endl;


		if (a > 0 && a <= countElements)
		{
			cout << "This is first " << to_string(a) << " elements:" << endl;
			Element<T>* start = head;
			cout << to_string(head->value) << " ";
			for (int i = 1; i < a; i++)
			{
				start = start->next;
				if (start->value != NULL)
					cout << to_string(start->value) << " ";
				else
					break;
			}
		}
		else
			cout << "Your instruction is wrong. The list has only " << to_string(countElements) << " elements.";
	}

private:
	int compare(T obj1, T obj2)
	{
		int diff = obj1 - obj2;
		if (diff != 0)
			return diff;
		return obj2 - obj2;
	}
};
//koniec implementacji listy dwukierunkowej

template <class T>
class hashTable {
public:
	int size = 0;
	int maxSize = 2;
	int value = 10;
	Array<Lista <T>> arrayWithValue;
	Array
	arrayWithValue.add(Lista<T> list1);
};

int main()
{
    std::cout << "Hello World!\n";
}

