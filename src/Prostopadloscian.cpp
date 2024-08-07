#include "Prostopadloscian.hh"
#include <cmath>
using std :: ostringstream;
using std :: ofstream;
using std :: ifstream;
using std :: string;
using std :: cerr;
using std :: cout;
using std :: endl;
/*!
 * \file
 * \brief Definicja metody Prostopadloscian
 *
 *    Plik zawiera definicję klasy Prostopadloscian, która
 *    jest podstawą całego programu. Klasa ta jest dziedziczona
 *    przez kolejne klasy.
 */

const Wektor<3> Prostopadloscian:: TransfDoUklWspRodzicaP(const Wektor<3> &Wierz){
    
    Macierz<3> Rotacja;
    
    Rotacja.obliczmacierz('z',KatOrientacji);
    
    return Rotacja * Wierz + Polozenie;
}


Wektor<3>       Prostopadloscian:: ObrysDrona(){
    
    ifstream  Plik_Bryla(NazwaBrylaFinalna());
    if (!Plik_Bryla.is_open())
        cerr << endl << " Blad otwarcia do odczytu pliku: " << NazwaBrylaFinalna() << endl << endl;
    
    Wektor<3> Wek;
    
    Wektor<2> P1, P2;
    double D1, D2;
    string S;
    
    for (int i = 0; i < 10; ++i)
        std:: getline(Plik_Bryla,S);
    
    std:: getline(Plik_Bryla,S);
    for (int j = 0; j < 2; ++j) {
        Plik_Bryla >> D1;
        P1.set(j,D1);
    }
    
    for (int i = 0; i < 5; ++i)
        std:: getline(Plik_Bryla,S);
    
    std:: getline(Plik_Bryla,S);
    for (int j = 0; j < 2; ++j) {
        Plik_Bryla >> D2;
        P2.set(j,D2);
    }
    
    double Wynik=0;
    for (int i = 0; i < 2; ++i)
        Wynik = pow(P2[i] - P1[i], 2) + Wynik;
    
    Wek[2] = sqrt(Wynik)/2;
    
    Wek[0] = ( P1[0] + P2[0] ) /2;
    Wek[1] = ( P1[1] + P2[1] ) /2;

    return Wek;
}


int             Prostopadloscian:: SprawdzKolizje(Wektor<3> WspDrona){
    
    Wektor<3> Wek = ObrysDrona();
    
    if ( (pow((WspDrona[0]-Wek[0]),2) + pow((WspDrona[1]-Wek[1]),2)) <= pow((WspDrona[2]+Wek[2]),2) )
        return 1;
    return 0;
}
