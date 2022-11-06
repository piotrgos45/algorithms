// ALGO2 IS1 212A LAB08
// Piotr Gos 
// gp49257@zut.edu.pl

#include <iostream>
#include <fstream>
#include <string> 
#include <time.h>

using namespace std;
int getAmountOfNode(string pNameFileToOpen);

string nameOfFileToOpen = "g1.txt";
//string nameOfFileToOpen = "g2.txt";
//string nameOfFileToOpen = "g3.txt";



class Node {
public:
	double cordinateX;
	double cordinateY;

	Node(){}

	Node(double pCordinateX, double pCordinateY) {
		cordinateX = pCordinateX;
		cordinateY = pCordinateY;
	}
};

class Edge {
public:
	int indexA;
	int indexB;
	float cost;
};

class Graph {
public:
	int amountOfNodes;
	Node* nodesInGraph;
	int amountOfEdges=0;
	Edge* edgesInGraph;

	float* tabCost;
	int* tabIndexA;
	int* tabIndexB;

	Graph() {
		amountOfNodes = getAmountOfNode(nameOfFileToOpen);
		edgesInGraph = new Edge[amountOfNodes];
	}


	Graph(int pAmountOfNodes) {
		amountOfNodes = pAmountOfNodes;
		nodesInGraph = new Node[pAmountOfNodes];
		getAllNodesFromFile(pAmountOfNodes);
		getAllEdgesFromFile(pAmountOfNodes);
		rewriteTabs();
		cout << "Zaczynam sortowac..." << endl;
		clock_t t1 = clock();
		sortEdgesByCost(tabCost,0,amountOfEdges-1);
		clock_t t2 = clock();
		double sortTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Czas sortowania: " << sortTime << endl;
		rewriteAfterSort();
	}

	void addEdge(int pIndexA, int pIndexB, float pCost) {
		edgesInGraph[currentAmountOfNodeForFinallyMST].indexA = pIndexA;
		edgesInGraph[currentAmountOfNodeForFinallyMST].indexB = pIndexB;
		edgesInGraph[currentAmountOfNodeForFinallyMST].cost = pCost;


		currentAmountOfNodeForFinallyMST++;
	}

	~Graph() {
		delete[] nodesInGraph;
		delete[] edgesInGraph;
	}

private:
	int currentAmountOfNodeForFinallyMST = 0;
	int iloscZamian = 0;

	void getAllNodesFromFile(int pAmountOfNodes) {
		fstream file;
		file.open(nameOfFileToOpen);

		for (int i = -1; i < pAmountOfNodes; i++) {
			if (i == -1) {
				string temp;
				file >> temp;
			}
			else {
				file >> nodesInGraph[i].cordinateX >> nodesInGraph[i].cordinateY;
			}
		}
		file.close();
	}

	void getAllEdgesFromFile(int pAmountOfNodes) {
		fstream file;
		file.open(nameOfFileToOpen);
		int countLine = 0;
		int countLine2 = 0;
		while (!file.eof()) {
			if (countLine <= pAmountOfNodes) {
				string tempLine;
				getline(file, tempLine);
			}
			else if (countLine == (pAmountOfNodes + 1)) {
				file >> amountOfEdges;
				edgesInGraph = new Edge[amountOfEdges];
			}
			else {

				file >> edgesInGraph[countLine2].indexA
					>> edgesInGraph[countLine2].indexB
					>> edgesInGraph[countLine2].cost;

				countLine2++;
			}
			countLine++;
		}
	}

	void sortEdgesByCost(float *tabCost, int left, int right) {
		float half = tabCost[(left + right) / 2];
		float x;
		int i = left;
		int j = right;

		do {
			while (tabCost[i] < half)
				i++;
			while (tabCost[j] > half)
				j--;

			if (i <= j) {
				swap(i, j);
				i++;
				j--;
			}
		} while (i <= j);


		if (j > left)
			sortEdgesByCost(tabCost, left, j);
		if (i < right)
			sortEdgesByCost(tabCost, i, right);
	}

	void rewriteTabs() {
		tabCost = new float[amountOfEdges];
		tabIndexA = new int[amountOfEdges];
		tabIndexB = new int[amountOfEdges];
		for (int i = 0; i < amountOfEdges; i++) {
			tabCost[i] = edgesInGraph[i].cost;
			tabIndexA[i] = edgesInGraph[i].indexA;
			tabIndexB[i] = edgesInGraph[i].indexB;
		}
	}

	void swap(int i, int j) {
		iloscZamian++;
		float tempCost = tabCost[i];
		int tempA = tabIndexA[i];
		int tempB = tabIndexB[i];

		tabCost[i] = tabCost[j];
		tabIndexA[i] = tabIndexA[j];
		tabIndexB[i] = tabIndexB[j];

		tabCost[j] = tempCost;
		tabIndexA[j] = tempA;
		tabIndexB[j] = tempB;
	}

	void rewriteAfterSort() {
		for (int i = 0; i < amountOfEdges; i++) {
			edgesInGraph[i].cost = tabCost[i];
			edgesInGraph[i].indexA = tabIndexA[i];
			edgesInGraph[i].indexB = tabIndexB[i];
		}
	}

};


class UnionFind {
public:
	int* parentArray;
	int* rankArray;
	int amountOfNodeInGraph;
	string nameOfFile;
	Graph finallyMST;


	UnionFind(int amountOfNode) {
		amountOfNodeInGraph = amountOfNode;
		parentArray = new int[amountOfNode];
		rankArray = new int[amountOfNode];

		for (int i = 0; i < amountOfNode; i++) {
			parentArray[i] = i;
			rankArray[i] = 0;
		}

		Graph insertGraph(amountOfNode);

		

		
		clock_t t1 = clock();
		//pętla główna
		for (int i = 0; i < insertGraph.amountOfEdges; i++) {
			int resultFindForA = find(insertGraph.edgesInGraph[i].indexA);
			int resultFindForB = find(insertGraph.edgesInGraph[i].indexB);
			amountOfFindOperation++;

			if (resultFindForA != resultFindForB) {
				unionIndex(resultFindForA, resultFindForB);

				finallyMST.addEdge(insertGraph.edgesInGraph[i].indexA, insertGraph.edgesInGraph[i].indexB, insertGraph.edgesInGraph[i].cost);
				if (amountOfUnionDone == amountOfNode - 1)
					break;
			}
		} //koniec pętli głownej
		clock_t t2 = clock();
		double mainLoopTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Czas wykonania glownej petli: " << mainLoopTime << endl;
		getResult();
	} //koniec konstruktora


	~UnionFind() {
		delete[] parentArray;
		delete[] rankArray;
	}


	void getResult() {
		cout << "Liczba krawedzi wynikowego grafu: " << amountOfUnionDone<<endl;
		cout << "Liczba operacji find: " << amountOfFindOperation<<endl;

		float suma = 0;

		for (int i = 0; i < 10; i++)
			suma = suma + finallyMST.edgesInGraph[i].cost;

		cout << "Suma: " << suma << endl;
	}


private:
	int amountOfUnionDone = 0;
	int amountOfFindOperation = 0;

	void unionIndex(int pIndexA, int pIndexB) {
		if (rankArray[pIndexA] < rankArray[pIndexB]) {
			parentArray[pIndexA] = pIndexB;
		}
		else if (rankArray[pIndexB] < rankArray[pIndexA]) {
			parentArray[pIndexB] = pIndexA;
		}

		else {
			parentArray[pIndexA] = pIndexB;
			rankArray[pIndexB]++;
		}

		amountOfUnionDone++;
	}



	int find(int pIndex) {
		if (pIndex == parentArray[pIndex])
			return pIndex;

		int root = find(parentArray[pIndex]);
		if (root != parentArray[pIndex])
			parentArray[pIndex] = root;
		
		return root;
	}




/* 
	int find(int pIndex) {	
		if (pIndex == parentArray[pIndex])
			return pIndex;

		return find(parentArray[pIndex]);
	}

*/


};



int main()
{
	UnionFind uf(getAmountOfNode(nameOfFileToOpen));
	
}

//funkcja uzyskująca ilość węzłów
int getAmountOfNode(string pNameFileToOpen) {
	fstream file;
	file.open(pNameFileToOpen);
	int amountOfNode;

	file >> amountOfNode;
	file.close();

	return amountOfNode;
}