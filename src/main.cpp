#include "Scena.hh"
/*!
* \file
* \brief Plik główny programu Dron.
*//*!
 *   \mainpage Dokumentacja
 *    \brief Program prezentujący animacje poruszania się drona w przestrzeni 3D
 *
 * \section Sekcja2 Zasada działania
 *
 * Program realizuje sterowanie dronami na planecie Tytan.
 * Drony modelowane są przez bryły geometryczne symulujące ich najważniejsze cechy.
 *
 *Pierwszą z nich jest Prostopadłościan, stanowiący bazę drona, kolejnymi zaś są graniastosłupy odwzorowujące rotory drona.
 *
 *Kolejnymi są Góra, Pagórek oraz Płaskowyż, brył które są przeszkodami drona.
 *
 * Program został wyposażony w metodę pozwalającą na omijanie przeszkód, gdy dron wykryje pod sobą przeszkodę, na chwilę zatrzyma się w mijescu i następnie przesunie się o dany krok.
 *
* Dron potrafi wylądować na Płaskowyżu.
*
 *
 *
 *\section Sekcja3 Prezentacja ruchu Drona
 *
 *\image html Lot.gif "Przemieszczenie się z punktu do punktu"
  *\section Sekcja4 Menu obsługi Drona
 *
 *\image html Menu.jpg "Menu główne"
 *
 *
 * \author Eryk Wójcik
 *   \date 17.06.2021
 *   \version 3.0
 *
 * Wykorzystany został moduł "LaczeDoGnuplota" autorstwa Dr Bogdana Kreczmera.
*//*!
 *\page strona-diagramu-klas   Diagram klas
 *\section s Diagram zależności między klasami
* \image html DiagramKlas.jpg
 *
*/
using std :: cout;
using std :: cin;
using std :: endl;
void Menu(int i){
    if (i == 1)
        cout << endl
             << " * * * * * * * * * * * * * * * * * * * * * * * * *" << endl
             << " *                    Menu                       *" << endl
             << " *     l   -   Wskaż cel lotu dla danego drona   *" << endl
             << " *     d   -   Pokaż menu aktywnych dronów       *" << endl
             << " *     w   -   Pokaż ilość obiektów Wektor       *" << endl
             << " *     p   -   Pokaż elementy przeszkód          *" << endl
             << " *     m   -   Wyświetl menu                     *" << endl
             << " *     u   -   Usuń wszystkie pliki sceny        *" << endl
             << " *     k   -   Zakoncz pracę                     *" << endl
             << " *                                               *" << endl
             << " * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    else
        cout << "\n\n * * * * * * *\n *   Menu    *\n * * * * * * *\n";
}
void UsunPliki(){
    system("exec find /Users/erykwojcik/Documents/Studia/Nadrabianko/PO/z5/Program/dat -mindepth 1 -exec rm {} ';'");
    cout << endl;
}
int main(){
    
    Wektor<3> Goal;
    Scena S;
    int ID = 1;
    char wybor = 'm';
    
    while (wybor != 'k') {
        switch (wybor) {
                
            case 'd':
                S.MenuWyborDrona(ID);
                Menu(0);
                break;

            case 'l':
                cout << "\n Podaj współrzędne celu drona ( w postaci [x,y] ): ";
                cin >> Goal;
                S.PolecDronem(ID-1,Goal);
                Menu(0);
                break;

            case 'w':
                cout << endl << " * Aktualna ilość obiektów \"Wektor\": "
                     << Goal.AktualnaIloscObiektow
                     << endl << " * Ogólna ilość obiektów \"Wektor\": "
                     << Goal.OgolnaIloscObiektow << endl;
                Menu(0);
                break;
                
            case 'p':
                S.MenuPrzeszkod();
                Menu(0);
                break;

            case 'u':
                UsunPliki();
                S.Rysuj();
                Menu(0);
                break;
                
            case 'm':
                Menu(1);
                break;

            default:
                cout << "\n Nie ma opcji: \"" << wybor << "\" w menu. :c \n";
                Menu(0);
                break;
        }
        cout << endl << " Wybór menu: ";
        cin >> wybor;
    }
    UsunPliki();
    return 0;
}
