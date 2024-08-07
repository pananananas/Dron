#ifndef WEKTOR3D_HH
#define WEKTOR3D_HH
#include <iostream>

/*!
 *  \file
 *  \brief
 * Definicja klasy Wektor.
 */
/*!
 *  \brief
 *     Klasa Wektor przechowuje punkty wektoru
 *     i metody przekształcające wektor
 *  \details
 *  \n
 *  Punkty w klasie Wektor są przechowywwane w postaci tablicy
 *  w której elementy są typu \c double \. Zdefiniowany w klasie
 *  wektor przechowuje współrzędne odpowiednio:  x, y i z\.
 *  \n
 *  \n
 *  W klasie definiowane są metody:
 *  \n
 *  \> inicjalizująca wektor z wartościami zerowymi
 *  \n
 *  \> inicjalizująca wektor z podanymi wartościami
 *  \n
 *  \> przeciążenia operatora dodawania wektorów
 *  \n
 *  \> przeciążenia operatora odejmowania wektorów
 *  \n
 *  \> przeciążenia operatora mnożenia dwóch wektorów
 *  \n
 *  \> przeciążenia operatora mnożenia wektora z liczbą \c double
 *  \n
 *  \> przeciążenie operatora nawiasów kwadratowych, aby móc odwołać się do konkretnego punktu
 *  \n
 *  \> metoda licząca długość odcinka między dwoma wektorami
 *  \n
 *  \> metoda pozwalająca ustawić daną liczbę dla konkretnego punktu wektora
 *  \n
 *  \n
 *  Napisałem również przeciążenie operatorów przesunięcia bitowego
 *  w lewo i w prawo, które pozwalają wypisanie wektora oraz jego wczytanie\.
 */

template <int ROZ>
class Wektor {
private:
    
    double Wek[ROZ];
    
public:
    
    static int AktualnaIloscObiektow, OgolnaIloscObiektow;
    Wektor<ROZ>()                             { for(double ElemTab: Wek) ElemTab = 0; ++AktualnaIloscObiektow; ++OgolnaIloscObiektow; };    
    Wektor<ROZ>(double x, double y, double z) { Wek[0] = x;  Wek[1] = y;  Wek[2] = z; ++AktualnaIloscObiektow; ++OgolnaIloscObiektow; };
    Wektor<ROZ>(const Wektor<ROZ>& W){ AktualnaIloscObiektow++; ++OgolnaIloscObiektow; for (int i=0; i< ROZ; i++){Wek[i]=W.Wek[i];} };
    
    Wektor<ROZ> operator +  (const Wektor<ROZ> W)  const;
    Wektor<ROZ> operator -  (const Wektor<ROZ> W)  const;
    Wektor<ROZ> operator *  (const double      x)  const;
    double      operator *  (const Wektor<ROZ> W)  const;
    double      operator [] (const int x) const  { return Wek[x]; };
    double     &operator [] (const int x)        { return Wek[x]; };
    double      dlodcinka   (const Wektor<ROZ> &W) const;
    void set(int i, double x) { Wek[i] = x; };
    
    ~Wektor<ROZ>() { --AktualnaIloscObiektow; };
};

template<int ROZ>
int Wektor<ROZ>:: AktualnaIloscObiektow = 0;
template<int ROZ>
int Wektor<ROZ>:: OgolnaIloscObiektow = 0;
template <int ROZ>
std::istream& operator >> (std::istream &strm, Wektor<ROZ> &w);
template <int ROZ>
std::ostream& operator << (std::ostream &strm, Wektor<ROZ>  w);

#endif
