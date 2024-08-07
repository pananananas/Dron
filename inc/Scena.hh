#ifndef SCENA_HH
#define SCENA_HH
/*!
 * \file
 * \brief Definicja klasy Scena
 *
 *    Plik zawiera definicję klasy Scena, która
 *    zarządza wszystkimi niższej rangi klasami.
*/
#include "Plaskowyz.hh"
#include "Pagorek.hh"
#include "Gora.hh"
#include "Dron.hh"
#define PLASZCZYZNA "bryly/plaszczyzna.dat"
#define ZakresOsiX  200
#define ZakresOsiY  200
#define ZakresOsiZ  100
#define WspXDrona1   30
#define WspYDrona1   30
#define WspXDrona2   80
#define WspYDrona2   40
using std:: list;
using std:: shared_ptr;
enum Przeszkody{_Gora, _Pagorek, _Plaskowyz};
/*!
 * \brief Modeluje pojęcie Sceny
 *
 *  Klasa modeluje pojęcie Sceny.
 *  Jej atrybutem jest pole \c Dron zawierające dwuelementową tablicę dronów,
 *  gdyż pracujemy przy dwóch dronach, oraz pole \c LaczeDoGNUPlota
 *  pozwalające nam komunikowac się z programem GNUPlot.
*/
class Scena: public Gora, public Pagorek, public Plaskowyz, public Dron{
private:
                                                           /*!
        * \brief Definiuje przeszkody
        *
        *  Pole definiuje listę wskazników na przeszkody,
        *  przechowuje trzy rodzaje przeszkód:
        *  Góra, Pagórek i Płaskowyż
*/
    list<shared_ptr<BrylaGeometryczna>> ListaPrzeszkod;    /*!
        * \brief Definiuje drony
        *
        *  Pole definiuje listę z dronami, które
        *  będą wykorzystywane przez użytkownika.
*/
    list<shared_ptr<Dron>> ListaDronow;                    /*!
    * \brief Definiuje Łącze
    *
    *  Pole definiuje Lącze pozwalające na komunikację
    *  z GNUPlotem oraz ustawienie parametrów wyświetlania sceny.
*/
    PzG::LaczeDoGNUPlota Lacze;                            /*!
    * \brief Liczy ilość przeszkod postaci gora
    *
    *  Pole służy zapamiętywaniu ilości obiektów klasy gora
*/
    int    IloscGor          = 0;                          /*!
    * \brief Liczy ilość przeszkod postaci pagorek
    *
    *  Pole służy zapamiętywaniu ilości obiektów klasy pagorek
*/
    int    IloscPagorkow     = 0;                          /*!
    * \brief Liczy ilość przeszkod postaci plaskowyz
    *
    *  Pole służy zapamiętywaniu ilości obiektów klasy plaskowyz
*/
    int    IloscPlaskowyzow  = 0;                          /*!
                                     * \brief Liczy ilość Dronów
                                     *
                                     *  Pole służy zapamiętywaniu ilości obiektów klasy dron
*/
    int    IloscDronow       = 0;                          /*!
                                                            * \brief Zapisuje wysokość lądawania drona
                                                            *
                                                            *  Pole służy zapamiętywaniu wysokości na jakiej wylądować ma dron
*/
    double WysokoscLadowania = 2;                          /*!
                                                            * \brief Zapamiętuje czy występuje kolizja z Płaskowyżem
                                                            *
                                                            *  Pole służy zapamiętywaniu faktu kolizii z płaskowyżem
*/
    bool   KolizjaPlaskowyz  = false;
    
public:
                                                           /*!
        * \brief Konstruktor Sceny
        *
        *  Konstruktor ustawiający wymiary sceny, kąt perspektywy, definiujący
        *  skale korpusu i rotorów dronów, ustawiający położenie dronów,
        *  obliczający współrzędne drona oraz rysujący zawartośc w GNUPlocie.
*/
    Scena();                                               /*!
        * \brief Metoda konfigurująca łącze
        *
        *  Metoda uruchamia łącze, oraz pozwala na konfigurację zakresu wyswietlanych osi.
        *
*/
    void KonfigurujLacze();                                /*!
        * \brief Metoda wykonująca przelot drona
        *
        *  Metoda na podstawie podawanych wartości wykonuje
        *  lot drona do podanego punktu. Inicjuje wykonanie
        *  animacji lotu i rysuje każde położenie drona.
        *
        *  \param[in] ID - Pole identyfikujące drona
        *
        *  \param[in,out] Goal - punkt celu lotu drona
*/
    void PolecDronem(int ID, Wektor<3> &Goal);             /*!
                                              * \brief Metoda menu usuwania dronów
                                              *
                                              *  Metoda pozwala na usuwanie istniejących dronów.
                                              *
*/
    void UsunDrona(int Numer);                             /*!
                                              * \brief Metoda menu usuwania przeszkod
                                              *
                                              *  Metoda pozwala na usuwanie istniejących przeszkod.
                                              *
*/
    void UsunPrzeszkode(int Numer);                        /*!
                                                 * \brief Metoda wykrywająca czy występuje kolizja
                                                 *
                                                 *  Metoda pozwala na usuwanie istniejących przeszkod.
*/
    bool WykryjKolizje(shared_ptr<Dron> D);                /*!
    * \brief Metoda dodająca przeszkodę do sceny
    *
    *  Metoda na podstawie podawanych wartości
    *  (rodzaju przeszkody oraz skali dla przeszkody) dodaje
    *  do std:: list nową przeszkodę, metoda zlicza
    *  ilość przeszkód danego rodzaju
    *
    *  \param[in] RodzajPrzeszkody - wybrany rozdaj dodawanej przeszkody
    *
    *  \param[in] Skala - Skala dodawanej przeszkody
*/
    void DodajPrzeszkode(Przeszkody RodzajPrzeszkody, Wektor<3> Skala, Wektor<3> Polozenie);
                                                           /*!
        * \brief Metoda menu przeszkod
        *
        *  Metoda pozwala na obsługe menu związanego z przeszkodami.
        *
*/
    void MenuPrzeszkod();                                  /*!
        * \brief Metoda menu wyswietlania przeszkod
        *
        *  Metoda pozwala na wyswietlenie aktualnych przeszkod.
        *
*/
    void MenuWyswietlPrzeszkody();                         /*!
        * \brief Metoda menu dodawania przeszkod
        *
        *  Metoda pozwala na dodawanie nowych przeszkod.
        *
*/
    void MenuDodajPrzeszkode();                            /*!
                                              * \brief Metoda menu dodawania dronow
                                              *
                                              *  Metoda pozwala na dodawanie nowych dronow.
                                              *
*/
    void MenuDodajDrona();                                 /*!
                                * \brief Metoda menu wyboru drona
                                *
                                *  Metoda pozwala dokonać wyboru aktywnego drona przez użytkownika.
                                *
                                *  \param[in,out] ID - Pole identyfikujące drona
*/
    void MenuWyborDrona(int &ID);                          /*!
                                                            * \brief Metoda wpisująca punkty sasiednie do Goal
                                                            *
                                                            *  Metoda wypisuje w vector punkty w postaci Wektor<3> bedace otoczeniem punktów sąsiednich do celu lotu
                                                            *
                                                            *  \param[in,out] ID - Pole identyfikujące drona
*/
    void TworzPktSasiada(vector<Wektor<3>> &SasiadGoal);   /*!
                                                 * \brief Metoda odświezająca łącze
                                                 *
                                                 *  Metoda pozwala odswiezyc lacze. Jest ona używana w main
                                                 *
                                                 
*/
    void Rysuj() { Lacze.UsunWszystkieNazwyPlikow(); Lacze.Rysuj(); };
    
};

#endif
