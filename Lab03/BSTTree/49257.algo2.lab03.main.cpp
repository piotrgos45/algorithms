// ALGO2 IS1 212A LAB03
// Piotr Gos
// gp49257@zut.edu.pl
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

template <class T>
class Node {
public:
	T value;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	int valueCheck = 0;
};


template<class T>
class Tree {
public:
	Node<T>* root;
	int height = 0;
	int tempheight = 0;
	int size = 0;

	//methods

	Tree(T pValue) {
		Node<T>* n = new Node<T>;
		n->value = pValue;
		n->parent = NULL;
		n->left = NULL;
		n->right = NULL;
		root = n;
	}

	void addElement(T pValue) {
		
		Node<T>* temp = root;
		Node<T>* beforeTemp = NULL;
		while (temp != NULL){
			beforeTemp = temp;
			if (pValue < temp->value) {
				temp = temp->left;
			} 
			else {
				temp = temp->right;
			}
		}

		Node<T>* newNode = new Node<T>;

		if (pValue < beforeTemp->value) {
			newNode->value = pValue;
			beforeTemp->left = newNode;
			newNode->parent = beforeTemp;
			newNode->left = NULL;
			newNode->right = NULL;
		}
		else {
			newNode->value = pValue;
			beforeTemp->right = newNode;
			newNode->parent = beforeTemp;
			newNode->left = NULL;
			newNode->right = NULL;
		}

		//cout << "Before: " << newNode->parent->value<<endl;
		//cout << "This: " << newNode->value<<endl;
	}

	Node<T>* searchElement(T pValue, string key) {

		Node<T>* temp = root;
		while (temp != NULL && temp->value != pValue ) {

			if (pValue < temp->value)
				temp = temp->left;
			else
				temp = temp->right;
		}
		return temp;
			
	}

	void removeNode(Node<T>* node) {
		Node<T>* nodeToChange = searchCandidate(node);
		node->value = nodeToChange->value;
		node->left = NULL;
		node->right = NULL;
	}

	void scanPreorder(Node<T>* node) {
		if (node != NULL) {
			cout << node->value << " ";
			scanPreorder(node->left);
			scanPreorder(node->right);
		}
	}

	void scanInorder(Node<T>* node) {
		if (node != NULL) {
			scanInorder(node->left);
			cout << node->value << " ";
			scanInorder(node->right);
		}
	}

	
	void removeAllNode(Node<T>* node) {
		if (node != NULL) {
			removeAllNode(node->left);
			removeAllNode(node->right);
		
			node->left = NULL;
			node->right = NULL;
			node->parent = NULL;
			node->value = NULL;
		}
	}


	void getString(Node<T>* node) {
		if (node != NULL) {
			cout << to_string(node->value) << " ";
			getString(node->left);
			getString(node->right);
		}
	}

	int getheight() {
		countheight(root);
		int t = height;
		height = 0;
		tempheight = 0;
		return t;
	}

	int getSize() {
		countSize(root);
		return size;
	}


	Node<T>* getRoot() {
		return root;
	}

private:
	Node<T>* searchCandidate(Node<T>* node) {
		bool goLeft = false;
		Node<T>* temp = NULL;
		if (node->left != NULL) {
			temp = node->left;
			goLeft = true;
		}
		else if (node->left == NULL && node->right != NULL)
			temp = node->right;

		else if (node->left == NULL && node->right == NULL)
			return NULL;

		Node<T>* beforeTemp = NULL;
		while (temp != NULL){
			beforeTemp = temp;
			if (goLeft)
				temp = temp->right;
			else
				temp = temp->left;
		}

		return beforeTemp;
	}


	void countheight(Node<T>* node) {



		if (node != NULL) {
			tempheight++;
			countheight(node->left);
			countheight(node->right);
		}
		else {
			if (tempheight > height)
				height = tempheight;

			tempheight = 0;
		}
	}

	void countSize(Node<T>* node) {
		if (node != NULL) {
			size++;
			countSize(node->left);
			countSize(node->right);
		}
	}

};

int main()
{
	Tree<int> n1(23);
	n1.addElement(9);
	n1.addElement(73);
	n1.addElement(16);
	n1.addElement(39);
	n1.addElement(98);
	n1.addElement(76);
	n1.addElement(99);
	n1.addElement(32);
	n1.addElement(31);
	n1.addElement(40);
	n1.addElement(41);
	n1.addElement(42);
	cout << endl;


	srand(time(NULL));

	clock_t time1 = clock();
	
	for (int i = 0; i < 100000; i++)
	{
	n1.addElement(rand() % 10000);
	}
	clock_t time2 = clock();

	

	n1.searchElement(42, "v");


	cout << endl << (time2 - time1) / (double)CLOCKS_PER_SEC << endl;
//	n1.getString(n1.getRoot());

	//int i = NULL;
//	cout << "sadasd: " << to_string(nullptr);
}
