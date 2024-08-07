#include "Graniastoslup.hh"
/*!
 * \file
 * \brief Definicja metody Graniastoslup
 *
 *    Plik zawiera definicje metod klasy Graniastosłup, która
 *    przechowuje informacje o figurze graniastosłup.
 *    Klasa ta dziedziczy po klasie BrylaGeometryczna.
 */

const Wektor<3> Graniastoslup:: TransfDoUklWspRodzicaG(const Wektor<3> &Wierz){
    Macierz<3> Rotacja;
    
    Rotacja.obliczmacierz('z',KatOrientacji);
    
    return Rotacja * Wierz + Polozenie;
}
