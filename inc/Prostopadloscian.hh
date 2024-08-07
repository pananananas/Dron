#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH
/*!
 * \file
 * \brief Definicja klasy Prostopadloscian
 *
 *    Plik zawiera definicję klasy Prostopadloscian, która
 *    przechowuje informacje o figurze prospodaloscian.
 *    Klasa ta dziedziczy po klasie BrylaGeometryczna.
*/
#include "BrylaGeometryczna.hh"
#define PLIK_KORPUSU         "dat/korpus_drona1.dat"

/*!
 * \brief Modeluje pojęcie Prostpadłościanu
 *
 *  Klasa modeluje pojęcie Prostopadłościanu.
 *  Jej atrybutem jest pole \cdouble zawierające Kąt
 *  orientacji, pole \cWektor zawierające punkt położenia bryły.
 *  Klasa zawiera również metody przypisania kąta obrotu
 *  oraz transformacji do układu współrzędnych rodzica.
*/
class Prostopadloscian: public BrylaGeometryczna{
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
    Wektor<3> Polozenie;                                                    /*!
                                                                             * \brief Nazwa pliku korpusu
                                                                             *
                                                                             * Pole zawiera nazwę pliku korpusu
*/
    std:: string NazwaPlikuKorpusu;                                         /*!
                                                                              * \brief Konstruktor Prostopadłościanu
                                                                              *
                                                                              * Definiuje konstruktor prostopadłościanu
                                                                              *
*/
    Prostopadloscian() {};                                                  /*!
                                                                            * \brief Metoda wyświetlająca rodzaj elementu
                                                                            *
                                                                            * metoda została zdefiniowana jako wirtualna,
                                                                            * aby podklasy mogły ją wykorzystać
                                                                            *
*/
    string WyswietlRodzaj() const   { string s = "s"; return s; };          /*!
                                                                                                  * \brief Metoda sprawdzająca kolizję
                                                                                                  * Metoda ta sprawdza czy wystąpiła kolizja między elementami sceny, jeśli tak, to zwraca ona wartość odpowiadającą konkretnej przeszkodzie.
                                                                                                  * metoda została zdefiniowana jako wirtualna,
                                                                                                  * aby podklasy mogły ją wykorzystać
                                                                                                  *
                                                                                                  * \param[in] WspDrona - Współrzędne drona dla którego sprawdzam wystąpienie kolizji
*/
    int  SprawdzKolizje(Wektor<3> WspDrona);                                /*!
    * \brief Metoda obliczania współrzędnych dla figury
    *
    * Metoda oblicza macierz rotacji i na tej podstawie zwraca obliczony wektor.
    *
    * \param[in,out] Wierz - Podawany wierzchołek dla którego
    *                      obliczona jest odwrócona o kąt obrotu wersja
    * \return Wektor z obliczonej współrzędnej.
*/
    const Wektor<3>      TransfDoUklWspRodzicaP(const Wektor<3> &Wierz);    /*!
                                                                             * \brief Metoda zwracająca obrys drona
                                                                             *
                                                                             * Obrys drona jest kołem, podawany wektor przechowuje
                                                                             * współrzędną X, współrzędną Y oraz promień koła
                                                                             * metoda została zdefiniowana jako wirtualna,
                                                                             * aby podklasy mogły ją wykorzystać
                                                                             *
*/
          Wektor<3>      ObrysDrona();                                      /*!
                                                             * \brief Desktuktor Prostopadłościanu
                                                             *
                                                             * Definiuje destruktor prostopadłościanu
                                                             *
*/
    ~Prostopadloscian() {};
};


#endif
