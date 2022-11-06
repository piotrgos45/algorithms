//ALGO2 IS1 212A LAB04
//Piotr Gos
//gp49257@zut.edu.pl
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
    bool isRed;
};

template <class T>
class Tree {
public: 
    Node<T>* root;
    int height = 0;
    int tempheight = 0;


    Tree(T pValue) {
        Node<T>* n = new Node<T>;
        n->value = pValue;
        n->parent = NULL;
        n->left = new Node<T>;
        n->right = new Node<T>;
        n->left->parent = n;
        n->left->left = NULL;
        n->left->right = NULL;
        n->left->value = NULL;

        n->right->parent = n;
        n->right->left = NULL;
        n->right->right = NULL;
        n->right->value = NULL;
        
        root = n;
        n->isRed = false;
        n->left->isRed = false;
        n->right->isRed = false;
    }

    void addElement(T pValue) {
        //klasyczne wstawiania nowego węzła i ustawienie koloru na czerwony
        Node<T>* temp = root;
        Node<T>* beforeTemp = NULL;
        while (temp != NULL) {
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

        //koniec klasycznego wstawiania

        while ((newNode != root) && (newNode->parent->isRed == true)) {
            if (newNode->parent == newNode->parent->parent->left) {
                Node<T>* uncle = new Node<T>;
                uncle = newNode->parent->parent->right;
                if (uncle->isRed) {
                    newNode->parent->isRed = false;
                    uncle->isRed = false;
                    newNode->parent->parent->isRed = true;
                    newNode = newNode->parent->parent;
                }
                else {
                    if (newNode == newNode->parent->right) {
                        rotateLeft(newNode->parent->parent, newNode, newNode->parent);
                        newNode = newNode->parent;
                    }
                    newNode->parent->isRed = false;
                    newNode->parent->parent->isRed = true;
                    rotateRight(newNode->parent->parent, newNode, newNode->parent);
                }
            }
            else {
                Node<T>* uncle = new Node<T>;
                uncle = newNode->parent->parent->left;
                if (uncle->isRed) {
                    newNode->parent->isRed = false;
                    uncle->isRed = false;
                    newNode->parent->parent->isRed = true;
                    newNode = newNode->parent->parent;
                }
                else {
                    if (newNode == newNode->parent->left) {
                        rotateRight(newNode->parent->parent, newNode->parent, newNode);
                        newNode = newNode->parent;
                    }
                    newNode->parent->isRed = false;
                    newNode->parent->parent->isRed = true;
                    rotateLeft(newNode->parent->parent, newNode->parent, newNode);
                }
            }
        }
        root->isRed = false;
    }

    Node<T>* searchElement(T pValue, string key) {
        if (key == "int") {
            Node<T>* temp = root;
            while (temp != NULL && temp->value != pValue) {

                if (compare(pValue,temp->value))
                    temp = temp->left;
                else
                    temp = temp->right;
            }
            return temp;
        }
    }


    void scanPreorder(Node<T>* node) {
        if (node != NULL) {
            if (node->value != NULL)
                cout << node->value << " ";
            scanPreorder(node->left);
            scanPreorder(node->right);
        }
    }

    void scanInorder(Node<T>* node) {
        if (node != NULL) {
            scanInorder(node->left);
            if(node->value!=NULL)
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

    int getHeight() {
        countHeight(root);
        int t = height;
        height = 0;
        tempheight = 0;
        return t+1;
    }

    void getString(Node<T>* node) {
        if (node != NULL) {
            if(node->value != NULL)
            cout << to_string(node->value) << " ";
            getString(node->left);
            getString(node->right);
        }
    }

    Node<T>* getRoot() {
        return root;
    }

private:
    bool compare(int a, int b) {
        if (a < b)
            return true;
        else
            return false;
    }

    void rotateRight(Node<T>* grandfather, Node<T>* parent,Node<T>* child){
        if (grandfather != NULL) {
            if (grandfather->right == parent)
                grandfather->right = child;
            else
                grandfather->left = child;
        }
        else
            root = child;

        Node<T>* temp = child->right;
        child->right = parent;
        parent->left = temp;
    }

    void rotateLeft(Node<T>* grandfather, Node<T>* parent, Node<T>* child) {
        if (grandfather != NULL) {
            if (grandfather->right == parent)
                grandfather->right = child;
            else
                grandfather->left = child;
        }
        else
            root = parent;

        Node<T>* temp = child->left;
        child->left = parent;
        parent->right = temp;
    }


    void countHeight(Node<T>* node) {
        if (node != NULL) {
            tempheight++;
            countHeight(node->left);
            countHeight(node->right);
        }
        else {
            if (tempheight > height)
                height = tempheight;

            tempheight = 0;
        }
    }
};

int main()
{
    Tree<int> n1(7);
    srand(time(NULL));

    clock_t time1 = clock();

    for (int i = 0; i < 1000; i++)
    {
    //    n1.addElement(rand() % 10000);
    }
    clock_t time2 = clock();
    
    
    n1.addElement(2);
    n1.addElement(1);
    n1.addElement(5); 
    n1.addElement(14);
    n1.addElement(8);
    n1.addElement(11);
    n1.addElement(15);
    n1.addElement(13);
    n1.addElement(17);
    n1.addElement(9);
    n1.addElement(12);

    n1.getString(n1.getRoot());
    cout << endl << n1.getHeight();
    cout << endl << n1.searchElement(8, "int");
}