// FFT.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <complex>
#include <vector>

using namespace std;
const std::complex<double> i(0, 1);

complex<double> FFT(double tab[], int size){
    vector <complex<double>> result;
    
    for (int j = 0; j < size / 2; j=j+2) {
        complex<double> temp = tab[j] * exp(-2 * M_PI * i * (j / (size / 2)));
        cout << temp<<endl;
    }

    for (int i = 1; i < size / 2; i = i + 2) {

    }
    return NULL;
}

int main()
{
    double tab1[3] = { 12.0, 15.0, 10.0 };
    FFT(tab1, 3);
    
}
