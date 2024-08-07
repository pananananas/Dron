#include <cmath>
#include "Wektor.hh"
/*!
 * \file
 * \brief Definicja metody Wektor
 *
 *    Plik zawiera definicję metod klasy Wektor, która
 *    jest podstawą całego programu.
 */

template <int ROZ>
Wektor<ROZ> Wektor<ROZ>:: operator + (const Wektor<ROZ> W)  const{
    Wektor<ROZ> Wynik;
    for (int i = 0; i < ROZ; ++i){
        Wynik.Wek[i] = W.Wek[i] + Wek[i];
    }
    return Wynik;
}


template <int ROZ>
Wektor<ROZ> Wektor<ROZ>:: operator - (const Wektor<ROZ> W)  const{
    Wektor<ROZ> Wynik;
    for (int i = 0; i < ROZ; ++i){
        Wynik.Wek[i] = W.Wek[i] - Wek[i];
    }
    return Wynik;
}


template <int ROZ>
Wektor<ROZ> Wektor<ROZ>:: operator * (const double      x)  const{
    
    Wektor<ROZ> Wynik;
    for (int i = 0; i < ROZ; ++i){
        Wynik.Wek[i] = Wek[i] * x;
    }
    return Wynik;
}


template <int ROZ>
double      Wektor<ROZ>:: operator * (const Wektor<ROZ> W)  const{
    
    Wektor<ROZ> Wynik;
    double x = 0;
    
    for (int i = 0; i < ROZ; ++i){
        Wynik.Wek[i] = Wek[i] * W.Wek[i];
    }
    for (int i = 0; i < ROZ; ++i){
        x = x + Wynik.Wek[i];
    }
    return x;
}


template <int ROZ>
double      Wektor<ROZ>:: dlodcinka  (const Wektor<ROZ> &W) const{
    
    double Wynik = 0;
    for (int i = 0; i < ROZ; ++i) {
        Wynik = pow(Wek[i] - W.Wek[i], 2) + Wynik;
    }
    return sqrt(Wynik);
    
}


template <int ROZ>
std::istream& operator >> (std::istream &strm, Wektor<ROZ> &w){
    char tmp;
    double x;
    
    strm >> tmp >> x;
    w.set(0,x);
    strm >> tmp >> x;
    w.set(1,x);
    strm >> tmp;
    
    if (tmp == ']')
        w.set(2,2);
    else{              
        strm >> x;
        w.set(2,x);
        strm >> tmp;
    }
    return strm;
}


template <int ROZ>
std::ostream& operator << (std::ostream &strm, Wektor<ROZ>  w){
    
    
    for (int i = 0; i < ROZ; ++i){
        if ((ROZ - i) != 1)
            strm << w[i] << "  ";
        else
            strm << w[i];
    }
    
    return strm;
}


template class Wektor<3>;
template:: std::istream& operator >> (std::istream &strm, Wektor<3> &w);
template:: std::ostream& operator << (std::ostream &strm, Wektor<3>  w);
