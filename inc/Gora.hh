#ifndef GORA_HH
#define GORA_HH
/*!
 * \file
 * \brief Definicja klasy Gora
 *
 *    Plik zawiera definicję klasy Gora, która
 *    przechowuje informacje o figurze, która jest przeszkodą
 *    dla drona.
 *    Klasa ta dziedziczy po klasie BrylaGeometryczna.
*/
#include "BrylaGeometryczna.hh"

#define PLIK_GORY         "bryly/gora_z_ostrym_szczytem.dat"
using std :: string;

/*!
 * \brief Modeluje pojęcie Góry
 *
 *  Klasa modeluje pojęcie Góry.
*/
class Gora: public BrylaGeometryczna{
private:
        /*!
    * \brief Ilość elementów typu gora
    *
    *  Pole podawane jest tutaj ze względu na
    *  metodę ObliczWsp(), która wypisuje wierzchołki
    *  przeskalowanej figury do odpowiedniego pliku,
    *  w którego nazwie jest numer elementu.
*/
    int IloscGor;
    int NumerNaLiscie;
    
public:
                                                                                /*!
            * \brief Punkt położenia bryły
            *
            * Pole zawiera punkt podstawowy w którym znajduje
            * się środek bryły, z którego rysowana jest cała bryła.
*/
    Wektor<3> Polozenie;                                                        /*!
    * \brief Metoda wyświetlająca położenie
    *
    * Wirtualna metoda podająca wektor położenia,
    * aby można było go wypisać w menu obsługi przeszkód.
    *
*/
    Wektor<3> WyswietlPolozenie() const   { return Polozenie;          };       /*!
    * \brief Metoda wyświetlająca rodzaj fogury
    *
    * Wirtualna metoda podająca nazwę figury,
    * aby można było ją wypisać w menu obsługi przeszkód.
    *
*/
    string    WyswietlRodzaj()    const   { string N="Góra"; return N; };       /*!
    * \brief Metoda tworząca nazwę pliku przeszkody
    *
    * Metoda ta, zapisuje ścieżkę i nazwę pliku przeszkody
    * w zależności od jej rodzaju dla podanego drona
    *
    * \param[in] I -  numer który będzie znajdował się w nazwie pliku
*/
    string    TworzNazwePlikuGory(int I);                                       /*!
                                                                                 * \brief Metoda ustawiająca numer na liscie
                                                                                 *
                                                                                 * metoda została zdefiniowana jako wirtualna,
                                                                                 * aby podklasy mogły ją wykorzystać
                                                                                 *
*/
    void      UstawNumerNaLiscie(int i)   { NumerNaLiscie = i;          };      /*!
                                                                                        * \brief Metoda ppodająca numer elementu
                                                                                        *
                                                                                        * metoda została zdefiniowana jako wirtualna,
                                                                                        * aby podklasy mogły ją wykorzystać
                                                                                        *
*/
    int       PokazNumerNaLiscie()        { return NumerNaLiscie;       };      /*!
                                                                                                  * \brief Metoda sprawdzająca kolizję
                                                                                                  * Metoda ta sprawdza czy wystąpiła kolizja między elementami sceny, jeśli tak, to zwraca ona wartość odpowiadającą konkretnej przeszkodzie.
                                                                                                  * metoda została zdefiniowana jako wirtualna,
                                                                                                  * aby podklasy mogły ją wykorzystać
                                                                                                  *
                                                                                                  * \param[in] WspDrona - Współrzędne drona dla którego sprawdzam wystąpienie kolizji
*/
    int       SprawdzKolizje(Wektor<3> WspDrona);                               /*!
                                                                      * \brief Metoda obliczająca współrzędne fogury
                                                                      *
                                                                      *  Metoda wirtualna odpowiednio skalująca współrzędne
                                                                      *  przeszkody, aby następnie wypisać je do pliku,
                                                                      *  z którego GNUPlot będzie czytał.
*/
    bool      ObliczWsp();                                                      /*!
                                                                                 * \brief Metoda ustawiająca położenie
                                                                                 *
                                                                                 * Witrualna metoda ustawiająca podawany wektor na położenie figury.
                                                                                 *
                                                                                 * \param[in] P - wektor oznajzający położenie
*/
    void      UstawPolozenie(Wektor<3> P) { Polozenie = P; };                   /*!
    * \brief Metoda zapisująca ilość aktualnych obiektów
    *
    * Metoda ta, zapisuje aktualną ilość obiektów klasy,
    * która jest wykorzystywana w metodzie ObliczWsp().
    *
    * \param[in] i -  numer który będzie aktualną ilością obiektów klasy
*/
    void      UstawIloscObiektow(int i)   { IloscGor = i;  };                   /*!
                                                                     * \brief Metoda zwracająca obrys brył
                                                                     *
                                                                     * Obrys bryły jest prostokątem, definiowanym
                                                                     * przez dwa przeciwległe wierzchołki
                                                                     * metoda została zdefiniowana jako wirtualna,
                                                                     * aby podklasy mogły ją wykorzystać
                                                                     *
*/
    vector<Wektor<3>>    ObrysBryly();                                          /*!
                                                                                 * \brief Desktuktor Góry
                                                                                 *
                                                                                 * Definiuje destruktor góry
                                                                                 *
*/
    ~Gora() {};
};

#endif

