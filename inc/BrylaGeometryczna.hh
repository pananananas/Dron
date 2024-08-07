#ifndef BRYLAGEOMETRYCZNA_HH
#define BRYLAGEOMETRYCZNA_HH
/*!
 * \file
 * \brief Definicja klasy BrylaGeometryczna
 *
 *    Plik zawiera definicję klasy BrylaGeometryczna, która
 *    jest podstawą całego programu. Klasa ta jest dziedziczona
 *    przez kolejne klasy.
*/
#include "Macierz.hh"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#define PLIK_SZESCIANU       "bryly/szescian.dat"
using std :: string;
using std :: vector;

/*!
 * \brief Modeluje pojęcie Bryły Geometrycznej
 *
 *  Klasa modeluje pojęcie danej  Bryły Geometrycznej.
 * Bryła geometryczna przechowuje najbardziej podstawowe
 * informacje o poszczególnych bryłach i opcję skalowania brył
*/
class BrylaGeometryczna{
private:
                                /*!
                                 * \brief Nazwa Bryły Wzorcowej
                                 *
                                 * Pole zawiera nazwę bryły wzorcowej.
                                 * Jest ona wykorzystywana w klasach,
                                 * które dziedziczą po tej.
*/
    string BrylaWzorcowa;       /*!
                                 * \brief Nazwa Bryły Finalnej
                                 *
                                 * Pole zawiera nazwę bryły finalnej.
                                 * Jest ona wykorzystywana w klasach,
                                 * które dziedziczą po tej.
*/
    string BrylaFinalna;        /*!
                                  * \brief Wartość Skali dla bryły
                                  *
                                  * Pole zawiera wartość skali dla bryły.
                                  * Jest ona wykorzystywana w klasach,
                                  * które dziedziczą po tej, oraz w metodzie Skaluj().
*/
    
public:

            Wektor<3>  Skala;                                                                    /*!
                                                * \brief Metoda licząca skalę dla punktu
                                                *
                                                * przemnaża podany wektor przez
                                                * skalę i zwraca wynik działania
                                                *
                                                * \param[in,out] Wierz - wierzchołek dla
                                                *  którego obliczana jest wartośc przeskalowana
*/
    const   Wektor<3>  Skaluj(const Wektor<3> &Wierz);                                           /*!
                                                         * \brief Metoda ustawiająca skalę
                                                         *
                                                         * Ustawia wartość skali, która przed pewnymi
                                                         * zmianami była polem prywatnym, na wartość
                                                         * podawanego wektora.
                                                         
                                                         * \param[in] W - nowa wartość skali
*/
            void       UstawSkale(Wektor<3> W)            { Skala = W;                     };    /*!
                                                                                           * \brief Metoda ustawiająca nazwę
                                                                                           *
                                                                                           * Przypisuje nową nazwę pliku nazwie dotychczasowej.
                                                                                           *
                                                                                           *   \param[in] Nazwa - Nazwa pliku do przypisania
*/
            void       UstawNazwePlikWlasciwy(string N)   { BrylaFinalna = N;              };    /*!
                                                                                           * \brief Metoda zwracająca nazwę bryły finalnej
                                                                                           *
                                                                                           * Zwraca nazwę pliku bryły finalnej
                                                                                           *
*/
            string     NazwaBrylaFinalna()                { return BrylaFinalna;           };    /*!
                                                                                           * \brief Metoda wyświetlająca rodzaj elementu
                                                                                           *
                                                                                           * metoda została zdefiniowana jako wirtualna,
                                                                                           * aby podklasy mogły ją wykorzystać
                                                                                           *
*/
    virtual string     WyswietlRodzaj()    const          { string s = "s"; return s;      };    /*!
                                                                                        * \brief Metoda ustawiająca numer na liscie
                                                                                        *
                                                                                        * metoda została zdefiniowana jako wirtualna,
                                                                                        * aby podklasy mogły ją wykorzystać
                                                                                        *
*/
    virtual void       UstawNumerNaLiscie(int i)          {                                };    /*!
                                                * \brief Metoda ustawiająca położenie
                                                *
                                                * metoda została zdefiniowana jako wirtualna,
                                                * aby podklasy mogły ją wykorzystać
                                                *
                                                * \param[in] P - wektor oznajzający położenie
*/
    virtual void       UstawPolozenie(Wektor<3> P)        {                                };    /*!
                                                                                                    * \brief Metoda ppodająca numer elementu
                                                                                                    *
                                                                                                    * metoda została zdefiniowana jako wirtualna,
                                                                                                    * aby podklasy mogły ją wykorzystać
                                                                                                    *
*/
    virtual int        PokazNumerNaLiscie()               { return 0;                      };    /*!
                                                                                                * \brief Metoda sprawdzająca kolizję
                                                                                                * Metoda ta sprawdza czy wystąpiła kolizja
                                                                                                * między elementami sceny, jeśli tak, to
                                                                                                * zwraca ona wartość odpowiadającą konkretnej przeszkodzie.
                                                                                                * metoda została zdefiniowana jako wirtualna,
                                                                                                * aby podklasy mogły ją wykorzystać
                                                                                                * Zwraca int w zależności od wykrytej przeszkody:
                                                                                                *  0 - Brak przeszkody
                                                                                                *  1 - Wykryto innego drona
                                                                                                *  2 - Wykryto górę
                                                                                                *  3 - Wykryto pagórek
                                                                                                *  4 - Wykryto płaskowyż
                                                                                                *
                                                                                                * \param[in] WspDrona - Współrzędne drona dla którego sprawdzam wystąpienie kolizji
*/
    virtual int        SprawdzKolizje(Wektor<3> WspDrona) { return 0;                      };    /*!
    * \brief Metoda obliczająca współrzędne
    *
    * metoda została zdefiniowana jako wirtualna,
    * aby podklasy mogły ją wykorzystać
    *
*/
    virtual bool       ObliczWsp()                        { return 1;                      };    /*!
                                           * \brief Metoda ustawiająca ilość obiektów
                                           *
                                           * metoda została zdefiniowana jako wirtualna,
                                           * aby podklasy mogły ją wykorzystać
                                           *
                                           * \param[in] i - liczba mająca zostać ilością obiektów
*/
    virtual void       UstawIloscObiektow(int i)          {                                };    /*!
                                                                                           * \brief Metoda wyświetlająca położenie
                                                                                           *
                                                                                           * metoda została zdefiniowana jako wirtualna,
                                                                                           * aby podklasy mogły ją wykorzystać
                                                                                           *
*/
    virtual Wektor<3>  WyswietlPolozenie() const          { Wektor<3> W; return W;         };    /*!
     * \brief Metoda zwracająca obrys drona
     *
     * Obrys drona jest kołem, podawany wektor przechowuje
     * współrzędną X, współrzędną Y oraz promień koła
     * metoda została zdefiniowana jako wirtualna,
     * aby podklasy mogły ją wykorzystać
     *
*/
    virtual Wektor<3>  ObrysDrona()                       { Wektor<3> W; return W;         };    /*!
    * \brief Metoda zwracająca obrys brył
    *
    * Obrys drona jest prostokątem, definiowanym
    * przez dwa przeciwległe wierzchołki
    * metoda została zdefiniowana jako wirtualna,
    * aby podklasy mogły ją wykorzystać
    *
*/
    virtual vector<Wektor<3>> ObrysBryly()                { vector<Wektor<3>> W; return W; };    /*!
    * \brief Desktuktor Bryły geometrycznej
    *
    * Definiuje destruktor bryły geometrycznej
    *
*/
    virtual ~BrylaGeometryczna() {};
};

#endif
