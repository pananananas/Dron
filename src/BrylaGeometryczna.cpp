#include "BrylaGeometryczna.hh"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
/*!
 * \file
 * \brief Definicja metody BrylaGeometryczna
 *
 *    Plik zawiera definicję metod klasy BrylaGeometryczna, która
 *    jest podstawą całego programu.
*/


const Wektor<3> BrylaGeometryczna:: Skaluj(const Wektor<3> &Wierz){
    
    Wektor<3> Tmp;
    Tmp.set(0,Wierz[0]*Skala[0]);
    Tmp.set(1,Wierz[1]*Skala[1]);
    Tmp.set(2,Wierz[2]*Skala[2]);
    return Tmp;
}
