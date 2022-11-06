// ALGO2 IS1 212A LAB09
// Piotr Gos
// gp49257@zut.edu.pl


#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

using namespace std;
int getAmoutPointsInFile();


//string nameFileToOpen = "points1.txt";
string nameFileToOpen = "points2.txt";
//string nameFileToOpen = "points3.txt";
//string nameFileToOpen = "points4.txt";
//string nameFileToOpen = "points5.txt";

class Point {
public:
    float cordinateX;
    float cordinateY;
    int number;
};
bool compare(Point p1, Point p2);

class PointsInCordinateSystem {
public:
    Point* points;
    int amountPointFromFile;
    int indexOfMin;

    PointsInCordinateSystem(int pAmountPointFromFile) {
        amountPointFromFile = pAmountPointFromFile;
        points = new Point[pAmountPointFromFile];
        Point* hullGraham = new Point[amountPointFromFile];
        fstream file;
        file.open(nameFileToOpen);
        
        string firstLineTemp;
        file >> firstLineTemp;

        for (int i = 0; i < pAmountPointFromFile; i++) {
            file >> points[i].cordinateX >> points[i].cordinateY;
            points[i].number = i;
        }

        file.close();


        

        indexOfMin = searchMinCordinateY(points);
        Point minimum = points[indexOfMin];

        Point* translatePoints = new Point[amountPointFromFile-1];

        bool flag = false;
        for (int i = 0; i < pAmountPointFromFile; i++) { 
            if (i == indexOfMin) {
                flag = true;
                continue;
            }
            if (flag == true) {
                translatePoints[i-1] = points[i];
                translatePoints[i-1].cordinateX = translatePoints[i-1].cordinateX - minimum.cordinateX;
                translatePoints[i-1].cordinateY = translatePoints[i-1].cordinateY - minimum.cordinateY;
            }
            else {
                translatePoints[i] = points[i];
                translatePoints[i].cordinateX = translatePoints[i].cordinateX - minimum.cordinateX;
                translatePoints[i].cordinateY = translatePoints[i].cordinateY - minimum.cordinateY;
            }
        }
        
        sort(translatePoints, translatePoints+amountPointFromFile-1, compare);
       

        hullGraham[0] = points[indexOfMin];
        hullGraham[1] = translatePoints[0];
        int hullSize = 1;
        for (int i = 1; i < amountPointFromFile-1; i++) {
            hullSize++;
            hullGraham[hullSize] = translatePoints[i];

            Point temp1;
            Point temp2;
            temp1.cordinateX = hullGraham[hullSize].cordinateX - hullGraham[hullSize - 1].cordinateX;
            temp1.cordinateY = hullGraham[hullSize].cordinateY - hullGraham[hullSize - 1].cordinateY;
            temp2.cordinateY = hullGraham[hullSize-1].cordinateY - hullGraham[hullSize - 2].cordinateY;
            temp2.cordinateX = hullGraham[hullSize-1].cordinateX - hullGraham[hullSize - 2].cordinateX;
            
            while (compare(temp1,temp2) == true) {
                hullGraham[hullSize - 1] = hullGraham[hullSize];
                hullSize--;

                temp1.cordinateX = hullGraham[hullSize].cordinateX - hullGraham[hullSize - 1].cordinateX;
                temp1.cordinateY = hullGraham[hullSize].cordinateY - hullGraham[hullSize - 1].cordinateY;
                temp2.cordinateY = hullGraham[hullSize - 1].cordinateY - hullGraham[hullSize - 2].cordinateY;
                temp2.cordinateX = hullGraham[hullSize - 1].cordinateX - hullGraham[hullSize - 2].cordinateX;
            }
        }

        

        for (int i = 0; i < hullSize+1; i++)
            cout << hullGraham[i].number << endl;


        delete[] hullGraham;
        delete[] translatePoints;

    }
   
    ~PointsInCordinateSystem() {
        delete[] points;
    }

    int searchMinCordinateY(Point pPoints[]) {
        float min = pPoints[0].cordinateY;
        int tempIndexOfMin = 0;

        for (int i = 1; i < amountPointFromFile; i++) {
            if (pPoints[i].cordinateY < min) {
                min = pPoints[i].cordinateY;
                tempIndexOfMin = i;
            }
               

            if (pPoints[i].cordinateY == min && pPoints[i].cordinateX < points[tempIndexOfMin].cordinateX) {
                min = pPoints[i].cordinateY;
                tempIndexOfMin = i;
            }

        }
        return tempIndexOfMin;
    }
};



int main()
{
    PointsInCordinateSystem p1(getAmoutPointsInFile());

    cout << "Koniec" << endl;
    return 0;
}

int getAmoutPointsInFile()
{
    fstream file;
    file.open(nameFileToOpen);
    int amountPointsInFile = 0;

    file >> amountPointsInFile;
    file.close();

    return amountPointsInFile;
}

bool compare(Point p1, Point p2) {
    return((p2.cordinateX * p1.cordinateY - p1.cordinateX* p2.cordinateY) < 0);
}