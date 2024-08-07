#ifndef GRANIASTOSLUP_HH
#define GRANIASTOSLUP_HH
/*!
 * \file
 * \brief Definicja klasy Graniastoslup
 *
 *    Plik zawiera definicję klasy Graniastosłup, która
 *    przechowuje informacje o figurze graniastosłup.
 *    Klasa ta dziedziczy po klasie BrylaGeometryczna.
*/
#include "BrylaGeometryczna.hh"
#define PLIK_GRANIASTOSLUPA6 "bryly/graniastoslup6.dat"
/*!
 * \brief Modeluje pojęcie Graniastosłupa
 *
 *  Klasa modeluje pojęcie Graniastosłupa.
 *  Jej atrybutem jest pole \cdouble zawierające Kąt
 *  orientacji, pole \cWektor zawierające punkt położenia bryły.
 *  Klasa zawiera również metody przypisania kąta obrotu
 *  oraz transformacji do układu współrzędnych rodzica.
*/
class Graniastoslup: public BrylaGeometryczna{
private:
    /*!
     * \brief Kąt orientacji bryły
     *
     * Pole zawiera kąt orientacji bryły, na czym
     * opiera się obliczenie współrzędnych rodzica.
*/
    double KatOrientacji;
    
public:
                                                                    /*!
        * \brief Punkt położenia bryły
        *
        * Pole zawiera punkt podstawowy w którym znajduje
        * się środek bryły, z którego rysowana jest cała bryła.
*/
    Wektor<3> Polozenie;                                            /*!
                                      * \brief Metoda przypisania podawanego kąta
                                      *
                                      * Metoda przypisuje podawany kąt zdefiniowanemu wyżej kątowi orientacji.
                                      *
                                      * \param[in] Kat - Podawany kąt, który przypisujemy kątowi obrotu
*/
    void KatObrotu(double Kat) { KatOrientacji = Kat; };            /*!
     * \brief Metoda obliczania współrzędnych dla figury
     *
     * Metoda oblicza macierz rotacji i na tej podstawie zwraca obliczony wektor.
     *
     * \param[in,out] Wierz - Podawany wierzchołek dla którego
     *                      obliczona jest odwrócona o kąt obrotu wersja
     * \return Wektor z obliczonej współrzędnej.
*/
    const Wektor<3> TransfDoUklWspRodzicaG(const Wektor<3> &Wierz); /*!
                                                                     * \brief Desktuktor Graniastosłupa
                                                                     *
                                                                     * Definiuje destruktor graniastosłupa
                                                                     *
*/
    ~Graniastoslup() {};
};


#endif
