#include <cassert>
#include <cmath>
#include "Macierz.hh"
/*!
 * \file
 * \brief Definicja metody Macierz
 *
 *    Plik zawiera definicję metod klasy Macierz, która
 *    jest podstawą całego programu.
 */

template <int ROZ>
Macierz<ROZ>:: Macierz(const std:: initializer_list<double> Lista){
    
    assert(Lista.size() <= ROZ*ROZ);
    double Tmp[ROZ*ROZ];
    int ind = -1;
    
    for(double Wsp : Lista)
        Tmp[++ind] = Wsp;
        
    ind = -1;
    for(int i = 0; i < ROZ; ++i){
        for(int j = 0; j < ROZ; ++j){
            Mac[i][j] = Tmp[++ind];
        }
    }
}


template <int ROZ>
Macierz<ROZ> Macierz<ROZ>:: operator * (Macierz<ROZ> M) const{
    
    Macierz<ROZ> Wynik;
    double  Tmp[ROZ];
    double d;
    
    for(int i = 0; i < ROZ; ++i){
        for(int j = 0; j < ROZ; ++j){
            for( int k = 0; k < ROZ; ++k){
            
                Tmp[k] = M.Mac[i][k] * Mac[k][j];
                d = d + Tmp[k];
            }
            Wynik.Mac[i][j] = d;
            d = 0;
        }
    }
    return Wynik;
}


template <int ROZ>
Wektor<ROZ>  Macierz<ROZ>:: operator * (const Wektor<ROZ>  W) const{
    
    Wektor<ROZ> Wynik;
    double  tmp;
    
    for(int i = 0; i < ROZ; ++i){
        for(int j = 0; j < ROZ; ++j){
            
            tmp += Mac[i][j] * W[j];
        }
        Wynik.set(i,tmp);
        tmp = 0;
    }
    return Wynik;
}


template <int ROZ>
void Macierz<ROZ>:: obliczmacierz(char os, double kat){
    
    kat = kat * M_PI / 180;
    
    switch (os) {
        case 'x':
            Mac[0][0] = 1;
            Mac[0][1] = 0;
            Mac[0][2] = 0;
            Mac[1][0] = 0;
            Mac[1][1] = cos(kat);
            Mac[1][2] = -sin(kat);
            Mac[2][0] = 0;
            Mac[2][1] = sin(kat);
            Mac[2][2] = cos(kat);
            break;
            
        case 'y':
            Mac[0][0] = cos(kat);
            Mac[0][1] = 0;
            Mac[0][2] = sin(kat);
            Mac[1][0] = 0;
            Mac[1][1] = 1;
            Mac[1][2] = 0;
            Mac[2][0] = -sin(kat);
            Mac[2][1] = 0;
            Mac[2][2] = cos(kat);
            break;

        case 'z':
            Mac[0][0] = cos(kat);
            Mac[0][1] = -sin(kat);
            Mac[0][2] = 0;
            Mac[1][0] = sin(kat);
            Mac[1][1] = cos(kat);
            Mac[1][2] = 0;
            Mac[2][0] = 0;
            Mac[2][1] = 0;
            Mac[2][2] = 1;
            break;
            
        default:
            std:: cout << "Błąd :c niepoprawna nazwa osi, popraw.\n";
            break;
    }
}


template <int ROZ>
std::ostream& operator << (std::ostream &strm, Macierz<ROZ> M){
    for (int i = 0; i < ROZ; ++i){
        for (int j = 0; j < ROZ; ++j){
            strm << M.get(i,j) << "    ";
        }
        strm << std:: endl;
    }
    return strm;
}


template class Macierz<3>;
template:: std::ostream& operator << (std::ostream &strm, Macierz<3> m);

