#ifndef MACIERZ3X3_HH
#define MACIERZ3X3_HH
/*!
*  \file
*  \brief
*  Definicja klasy Macierz
*/
#include "Wektor.hh"  /*!
 *  \brief
 *     Klasa Macierz przechowuje punkty macierzy
 *     i metody wykonujące operacje na macierzy
 *  \details
 *  \n
 *  Punkty macierzy w klasie Macierz są przechowywwane w postaci
 *  dwuwymiarowej tablicy w której elementy są typu \c double \.
 *  \n
 *  \n
 *  W klasie definiowane są metody:
 *  \n
 *  \> inicjalizująca wektor z wartościami zerowymi
 *  \n
 *  \> inicjalizująca wektor z podanymi wartościami
 *  \n
 *  \> przeciążenia operatora mnożenia dwóch macierzy
 *  \n
 *  \> przeciążenia operatora mnożenia macierzy z liczbą wektorem
 *  \n
 *  \> metoda licząca macierz obrotu względem podanej osi i kąta
 *  \n
 *  \> metoda pozwalająca ustawić daną liczbę dla konkretnego punktu macierzy
 *  \n
 *  \> metoda pozwalająca wyciągnąć daną liczbę dla konkretnego punktu macierzy
 *  \n
 *  Napisałem również przeciążenie operatorów przesunięcia bitowego
 *  w lewo, pozwalający na wypisanie macierzy\.
*/

template <int ROZ>
class Macierz {
private:
    double Mac[ROZ][ROZ];
    
public:
    
    Macierz() {for(double* ElemTab: Mac) *ElemTab = 0;};
    Macierz(const std:: initializer_list<double> Lista);
    
    Macierz<ROZ> operator *  (      Macierz<ROZ> M) const;
    Wektor<ROZ>  operator *  (const Wektor<ROZ>  W) const;
    
    void   obliczmacierz(char os, double kat);
    void   set(int x, int y, double w) { Mac[x][y] = w;    };
    double get(int x, int y)           { return Mac[x][y]; };
};

template <int ROZ>
std::ostream& operator << (std::ostream &strm, Macierz<ROZ> M);

#endif
