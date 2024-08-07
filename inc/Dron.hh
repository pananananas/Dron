#ifndef DRON_HH
#define DRON_HH
/*!
 * \file
 * \brief Definicja klasy Dron
 *
 *    Plik zawiera definicję klasy Dron, wewnątrz której wykonywane
 *    są najbardziej skomplikowane obliczenia programu, klasa
 *    definiuje całego Drona i operacje wykonywane na nim.
*/
#include "lacze_do_gnuplota.hh"
#include "Prostopadloscian.hh"
#include "Graniastoslup.hh"
#include <cmath>    // Stałe dotyczące animacji
#define Krok                   2
#define WysokoscLotu          80
#define PredkoscObrotuRotora  20
#define PredkoscObrotuDrona    5*M_PI/180
using std :: string;
using std :: vector;
using std :: shared_ptr;
enum Kierunek{DoGory, NaDol};
/*!
 * \brief Modeluje pojęcie Drona
 *
 *  Klasa modeluje pojęcie Drona.
 *  Jej atrybutem są pola \c double zawierające Kąt
 *  orientacji, pole \c unsigned \c int identyfikujące drona,
 *  pole \c Prostopadloscian zawierające korpus drona,
 *  tablica \c Graniastoslup zawierające cztery rotory drona,
 *  oraz pole \c Wektor zawierające punkt położenia całego drona.
 *  Klasa zawiera również metody obliczania współrzędnych korpusu,
 *  współrzędnych rotora, ogólnych współrzędnych drona. Metody
 *  tworzące nazwy plików operacyjnych dla drona, metodę tworzącą
 *  drona, rysującą jego ścieżkę lotu, wyokunjącą animację lotu,
 *  obliczjającą współrzędne drona, ustawiającą kąt rotorów,
 *  kąt orientacji,położenie, skalę korpusi oraz skalę rotorów.
*/
class Dron: public Graniastoslup, public Prostopadloscian{
private:
                                   /*!
     * \brief Kąt orientacj drona
     *
     * Pole zawiera kąt orientacji drona, na czym opiera
     * się transformacja do układu współrzędnych rodzica.
*/
    double KatOrientacji;          /*!
     * \brief Identyfikacja drona
     *
     * Pole to pozwala na zidentyfikowanie drona,
     * dla którego wykonywane będą operacje.
*/
    unsigned int ID;               /*!
    * \brief Definicja korpusu drona
    *
    * Pole to definiuje korpus drona,
    * którym jest jeden prostopadłościan.
*/
    Prostopadloscian KorpusDrona;  /*!
    * \brief Definicja rotorów drona
    *
    * Pole to definiuje rotory drona, którymi są cztery graniastoslupy
*/
    Graniastoslup Rotor[4];        /*!
    * \brief Metoda obliczająca i zapisująca współrzędne korpusu do pliku
    *
    * Metoda ta, poruszając się po trzech pętlach for,
    * zapisuje współrzędne korpusu do odpowiednich plików,
    * odwołując się do metody TworzNazwePlikuKorupsa().
    * Metoda oblicza również układ współrzędnych korpusu
    *
    * \return Metoda zwraca informacje o powodzeniu operacji
*/
    bool ObliczWspKorpusu();       /*!
    * \brief Metoda obliczająca i zapisująca współrzędne rotora do pliku
    *
    * Metoda ta, poruszając się po trzech pętlach for,
    * zapisuje współrzędne konkretnego rotora do odpowiednego pliku,
    * odwołując się do metody TworzNazwePlikuRotora().
    * Metoda oblicza również układ współrzędnych rotora
    *
    * \param[in] Ind - pole identyfikujące jeden z czterech rotorów
    *
    * \return Informację o powodzeniu operacji
*/
    bool ObliczWspRotora(int Ind); /*!
                                    * \brief Identyfikacja drona
                                    *
                                    * Pole to pozwala na zidentyfikowanie drona,
                                    * dla którego wykonywane będą operacje.
*/
    int  NumerDrona;
    
public:
                                                                                        /*!
    * \brief Punkt położenia drona
    *
    * Pole zawiera punkt podstawowy w którym znajduje
    * się środek bryły, z którego rysowana jest cała bryła.
*/
    Wektor<3> Polozenie;                                                                /*!
                         * \brief Metoda obliczania współrzędnych dla drona
                         *
                         * Metoda realizuje przejście od współrzędnych
                         * lokalnych drona do współrzędnych lokalnych sceny.
                         *
                         * \param[in,out] Wierz - Podawany wierzchołek dla którego
                         *                      obliczona jest odwrócona o kąt obrotu wersja
                         * \return Wektor z obliczonej współrzędnej.
*/
    const Wektor<3> TransfDoUklWspRodzica(const Wektor<3> &Wierz);                      /*!
    * \brief Metoda tworząca nazwę pliku korpusu drona
    *
    * Metoda ta, zapisuje ścieżkę i nazwę pliku korpusu dla podanego drona
    *
    * \param[in] NrDrona -  Numer identyfikujący drona
*/
    string TworzNazwePlikuKorpusa(unsigned int NrDrona);                                /*!
    * \brief Metoda tworząca nazwę pliku ścieżki lotu drona
    *
    * Metoda ta, zapisuje ścieżkę i nazwę pliku drogi, którą ma wykonać podany dron
    *
    * \param[in] NrDrona -  Numer identyfikujący drona
*/
    string TworzNazwePlikuSciezki(unsigned int NrDrona);                                /*!
    * \brief Metoda tworząca nazwę pliku konkretnego rotora
    *
    * Metoda ta, zapisuje ścieżkę i nazwę pliku rotora,
    * dla podanego numeru drona i numeru rotora
    *
    * \param[in] NrDrona -  Numer identyfikujący drona
    *
    * \param[in] NrRotora -  Numer identyfikujący konkretny rotor
*/
    string TworzNazwePlikuRotora (unsigned int NrDrona, unsigned int NrRotora);         /*!
                                                                                         * \brief Metoda tworząca nazwę pliku skanera
                                                                                         *
                                                                                         * Metoda ta, zapisuje ścieżkę i nazwę pliku skanera.
                                                                                         *
*/
    string TworzNazwePlikuSkanera();                                                    /*!
                                             * \brief Metoda tworząca drona
                                             *
                                             * Metoda ta, ściąga nazwy plików wszystkich rotorów oraz pliku
                                             * korpusu i za pośrednictwem łącza do GNUPlota rysuje drona.
                                             *
                                             * \param[in] NrDrona -  Numer identyfikujący drona
                                             *
                                             * \param[in,out] Lacze -  Pozwala nam na komunikację z GNUPlotem
*/
    void   TworzDrona(unsigned int   NrDrona,        PzG::LaczeDoGNUPlota &Lacze);      /*!
    * \brief Metoda ścieżkę lotu drona
    *
    * Metoda ta, korzystając z punktu położenia drona oraz podawanego
    * wektora zawierającego cel lotu drona rysuje ścieżkę do pliku, która
    * wyświetli się na interfejsie GNUPlota przed rozpoczęciem lotu.
    *
    * \param[in] Goal - punkt celu lotu drona
    *
    * \param[in,out] Lacze -  Pozwala nam na komunikację z GNUPlotem
    *
    * \return Informację o powodzeniu operacji
*/
    bool   SciezkaLotu( Wektor<3> P, Wektor<3> Goal, PzG::LaczeDoGNUPlota &Lacze);      /*!
                                                                                         * \brief Metoda obliczająca punkty przelotu drona i wykonująca animację lotu wertykalnego
                                                                                         *
                                                                                         * Metoda ta, wykorzystując podawane parametry, prędkość obrotu
                                                                                         * rotora i drona oraz krok ruchu drona wykonuje animację lotu.
                                                                                         *
                                                                                         * \param[in] K    - Kierunek lotu (góra lub dół
                                                                                         * \param[in] Goal - punkt celu lotu drona
                                                                                         *
                                                                                         * \param[in,out] Lacze - Umożliwia rysowanie punktów w GNUPlocie
*/
    void   LotWertykalny(Kierunek K, Wektor<3> Goal, PzG::LaczeDoGNUPlota &Lacze);      /*!
                                                                                         * \brief Metoda obliczająca punkty przelotu drona i wykonująca animację lotu horyzontalnego
                                                                                         *
                                                                                         * Metoda ta, wykorzystując podawane parametry, prędkość obrotu
                                                                                         * rotora i drona oraz krok ruchu drona wykonuje animację lotu.
                                                                                         *
                                                                                         * \param[in] Goal - punkt celu lotu drona
                                                                                         *
                                                                                         * \param[in,out] Lacze - Umożliwia rysowanie punktów w GNUPlocie
*/
    void   LotHoryzontalny(          Wektor<3> Goal, PzG::LaczeDoGNUPlota &Lacze);      /*!
                                                                                         * \brief Metoda obliczająca punkty obrotu drona i wykonująca animację tego ruchu
                                                                                         *
                                                                                         * Metoda ta, wykorzystując podawane parametry, prędkość obrotu
                                                                                         * rotora i drona oraz krok ruchu drona wykonuje animację lotu.
                                                                                         *
                                                                                         * \param[in] Goal - punkt celu lotu drona
                                                                                         *
                                                                                         * \param[in,out] Lacze - Umożliwia rysowanie punktów w GNUPlocie
*/
    void   ObrotDrona(               Wektor<3> Goal, PzG::LaczeDoGNUPlota &Lacze);      /*!
                                                                                         * \brief Metoda uaktualniająca punkty ze ścieżki
                                                                                         *
                                                                                         * Metoda ta, wykorzystując podawane parametry, prędkość obrotu
                                                                                         * rotora i drona oraz krok ruchu drona wykonuje animację lotu.
                                                                                         *
                                                                                         * \param[in,out] Sciezka - pole przechowujące najważniejsze informacje
                                                                                         *                               o droenie: punkty położenia drona,
                                                                                         *                               kąt orientacji oraz orbót rotora
                                                                                         *
                                                                                         * \param[in,out] Lacze - Umożliwia rysowanie punktów w GNUPlocie
*/
    void   WykonajSciezke(vector<Wektor<5>> Sciezka, PzG::LaczeDoGNUPlota &Lacze);      /*!
     * \brief Metoda animująca skanowanie przestrzeni
     *
     * Metoda ta tworzy animację skanowania przestrzeni w poszukiwaniu wolnego miejsca do lądowania
     *
     * \param[in,out] Lacze -  Pozwala komunikować się z GNUPlotem
     *
*/
    void   SkanujPrzestrzen(PzG::LaczeDoGNUPlota &Lacze);                               /*!
        * \brief Metoda obliczająca współrzędne drona
        *
        * Metoda ta, oblicza współrzędne korpusu oraz współrzędne czterech rotorów.
        *
        * \return Informację o powodzeniu operacji
*/
    bool   ObliczWspDrona();                                                            /*!
    * \brief Metoda ustawiająca kąt dla rotorów
    *
    * Metoda ta ustawia kąt rotorów, upewnia się, żeby
    * naprzeciwległe rotory kręciły się w odpowiednią stronę.
    *
*/
    void   UstawKatRotorow(double Kat);                                                 /*!
                                                                                         * \brief Metoda przekazująca wskażnik na korpus drona
                                                                                         *
                                                                                         * Metoda ta, przekazuje korpus drona przez wskaznik.
                                                                                         *
*/
    Prostopadloscian* PntrNaKorpus() { return &KorpusDrona;};
                                                                                        /*!
                                                                                * \brief Metoda zwracająca kąt orientacji
                                                                                *
                                                                                * Metoda ta zwraca kąt orientacji drona
                                                                                *
*/
    double ZwrocKat()                     { return KatOrientacji*M_PI/180;   };         /*!
                                                                                         * \brief Metoda zwracająca położenie drona
                                                                                         *
                                                                                         * Metoda ta zwraca położenie drona.
                                                                                         *
*/
    Wektor<3> ZwrocPolozenie()            { return Polozenie;                };         /*!
                                                                                         * \brief Metoda zwracająca obrys drona.
                                                                                         *
                                                                                         * Metoda ta zwraca obrys drona w postaci koła, parametry x i y wektora stanowią współrzędne położenie drona, zaś współrzędna z zawiera promień koła.
                                                                                         *
*/
    Wektor<3> ObrysDrona()                { return KorpusDrona.ObrysDrona(); };         /*!
    * \brief Metoda przypisująca podawany wektor do położenia
    *
    * Metoda ta ustawia położenie drona na podawany punkt.
    *
    * \param[in] Wek - Wektor mający być położeniem Drona
*/
    void   UstawPolozenie(Wektor<3> Wek)  { Polozenie = Wek;                 };         /*!
    * \brief Metoda przypisująca podawaną wartośc na kąt orientacji
    *
    * Metoda ta ustawia kąt orientacji drona na podawaną wartość
    *
    * \param[in] Kat - Wartość mająca być kątem orientacji drona.
*/
    void   UstawKat(double Kat)           { KatOrientacji = Kat;             };         /*!
    * \brief Metoda ustawiająca skalę korpusu
    *
    * Metoda ta ustawia skalę korpusu na podawany wektor
    *
    * \param[in] W - Wartość mająca być skalą korpusu drona
*/
    void   UstawSkaleKorpusu(Wektor<3> W) { KorpusDrona.UstawSkale(W);       };         /*!
                                                                                         * \brief Metoda ustawiająca numer drona
                                                                                         *
                                                                                         * Metoda ta ustawia numer drona na podawany
                                                                                         *
                                                                                         * \param[in] i - numer drona
*/
    void   UstawNumerDrona(int i)         { NumerDrona = i;                  };         /*!
                                                                             * \brief Metoda zwracajaca numer drona
                                                                             *
                                                                             * Metoda zwraca numer drona
                                                                             *
                                                                             
*/
    int    ZwrocNumerDrona()              { return NumerDrona;               };         /*!
    * \brief Metoda ustawiająca skalę rotorów
    *
    * Metoda ta ustawia skalę rotorów na podawany wektor
    *
    * \param[in] W - Wartość mająca być skalą rotorów drona
*/
    void   UstawSkaleRotorow(Wektor<3> W) { for (Graniastoslup &Rot: Rotor) Rot.UstawSkale(W); };
};
#endif
