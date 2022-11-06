// My implementation of hash table

#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>

using namespace std;

//Copy double connected list from other file
//to line 258
template <class T>
class Element {
public:
	Element<T>* previus;
	T value;
	string key;
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
	Lista() {

		Element<T>* el = new Element<T>;
		el->value = NULL;
		el->next = NULL;
		el->previus = NULL;
		head = el;
		tail = el;
	}
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
	
	void addElementEnd(string pKey, T pValue)
		//wstawia element na końcu listy
	{
			Element<T>* el1 = tail;
			Element<T>* elNew = new Element<T>;
			elNew->value = pValue;
			elNew->key = pKey;
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

	Element<T>* searchElement(string key)
	{
		Element<T>* tempElement = head;

		for (int i = 0; i < countElements; i++)
		{
			if (compare(key, tempElement->key) == 0)
				return tempElement;
			else
				tempElement = tempElement->next;
		}
		return NULL;
	}

	bool searchRemoveElement(string key)
	{
		Element<T>* result = searchElement(key);
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

	void returnString()
	{
			Element<T>* start = head;
			for (int i = 0; i < countElements; i++)
			{
				start = start->next;
				if (start->value != NULL)
					cout << to_string(start->value) << " ";
				else
					break;
			}
	}

private:
	int compare(string obj1, string obj2)
	{
		if (obj1 == obj2)
			return 0;

		return 1;
	}
};


template <class T>
class Array
{
public:
    int size = 0;
    int maxSize = 2;
    Lista<T>* array = new Lista<T>[maxSize];
	
    void add(string key,T pValue)
    {
        if (size <= 0.75*maxSize)
        {
            addNodeToHashTable(key, pValue);
            size++;
        }
        else
        {
            Lista<T>* tempArray = new Lista<T>[maxSize];
            for (int j = 0; j < size; j++)
                tempArray[j] = array[j];

            array = new Lista<T>[2 * maxSize];
            maxSize = maxSize * 2;

            for (int i = 0; i < size; i++) {
                array[i] = tempArray[i];
            }


			for (int i = size; i < maxSize; i++) {
			}
            addNodeToHashTable(key, pValue);
            size++;

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
            array = new Lista<T>[maxSize];
        }
    }

    void returnString(int a)
    {
		while (a < size) {
			Lista<T>& view = array[a];
			view.returnString();
			
			a++;
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


	Element<T>* search(string pKey) {
		int hashKey = hashFunction(pKey);
		Lista<T>& refElementArray = array[hashKey];
		Element<T>* foundElement = refElementArray.searchElement(pKey);
		return foundElement;
	}


	bool removeElement(string pKey) {
		int hashKey = hashFunction(pKey);
		Lista<T>& refElementArray = array[hashKey];
		if (refElementArray.searchRemoveElement(pKey))
			return true;

		return false;

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

    void addNodeToHashTable(string pKey, T value) {
		int hashKey = hashFunction(pKey);
		cout << "Hash: " << hashKey << endl;
		Lista<T>& refListOfElement = array[hashKey];
		refListOfElement.addElementEnd(pKey, value);	
    }

	int hashFunction(string pValue) {
		int hashKey = 0;
		for (int i = 0; i < pValue.size(); i++) {
			hashKey = hashKey + (pValue[i] * (pow(31, pValue.size() - (i + 1))));
		}
		hashKey = hashKey % maxSize;
		return abs(hashKey);
	}
}; //koniec implementacji Tablicy dynamicznej




int main()
{
	Array <int> a1;
	a1.add("nijbyhbnfubc",3);
	a1.add("sdlfid", 45);
	a1.add("abyytdc", 32);
	a1.add("swewrewtr", 423);
	a1.add("swejkjkjkhjwtr", 42);
	a1.add("swjhejkjkjkhjwtr", 47);

	a1.returnString(0);
}