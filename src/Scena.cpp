#include "Scena.hh"
#include <unistd.h>
#include <memory>
#include <cmath>
#include <list>
/*!
 * \file
 * \brief Definicja metody Scena
 *
 *    Plik zawiera definicję klasy BrylaGeometryczna, która
 *    jest podstawą całego programu. Klasa ta jest dziedziczona
 *    przez kolejne klasy.
*/
using std :: cin;
using std :: cerr;
using std :: cout;
using std :: endl;
using std :: vector;
using std :: string;
using std :: shared_ptr;
using std :: make_shared;


Scena:: Scena(){
    
    Lacze.DodajNazwePliku(PLASZCZYZNA);
    KonfigurujLacze();
    
    
    // Tworzę pierwszego drona
    
    ListaDronow.push_back(make_shared<Dron>(Dron()));
    ListaDronow.back()->TworzDrona(IloscDronow,Lacze);
    ListaDronow.back()->UstawSkaleKorpusu(Wektor<3>(10, 8, 4));
    ListaDronow.back()->UstawSkaleRotorow(Wektor<3>(8, 8, 1.5));
    
    Wektor<3> WspDrona1 = { WspXDrona1, WspYDrona1, 2 };
    
    ListaDronow.back()->UstawPolozenie(WspDrona1);
    
    if(!ListaDronow.back()->ObliczWspDrona())
        cout << "Błąd obliczania Wsp Drona " << IloscDronow << "!!! :C" << endl;
    
    shared_ptr<Prostopadloscian> WskD1;
    WskD1.reset(ListaDronow.back()->PntrNaKorpus());
    ListaPrzeszkod.push_back(WskD1);
    
    
    // Tworzę drugiego drona
    
    ListaDronow.push_back(make_shared<Dron>(Dron()));
    ListaDronow.back()->TworzDrona(++IloscDronow,Lacze);
    ListaDronow.back()->UstawSkaleKorpusu(Wektor<3>(8, 4, 4));
    ListaDronow.back()->UstawSkaleRotorow(Wektor<3>(4, 4, 1.2));
    
    Wektor<3> WspDrona2 = { WspXDrona2, WspYDrona2, 2 };
    
    ListaDronow.back()->UstawPolozenie(WspDrona2);
    
    if(!ListaDronow.back()->ObliczWspDrona())
        cout << "Błąd obliczania Wsp Drona " << IloscDronow << "!!! :C" << endl;
    
    shared_ptr<Prostopadloscian> WskD2;
    WskD2.reset(ListaDronow.back()->PntrNaKorpus());
    ListaPrzeszkod.push_back(WskD2);
    
    
    // Tworzę przeszkody
    
    DodajPrzeszkode(_Gora,      Wektor<3>(20, 40, 60), Wektor<3>(130, 70,2));
    DodajPrzeszkode(_Pagorek,   Wektor<3>(20, 40, 40), Wektor<3>(150,120,2));
    DodajPrzeszkode(_Plaskowyz, Wektor<3>(20, 40, 40), Wektor<3>(60 ,120,2));
    DodajPrzeszkode(_Gora,      Wektor<3>(10, 20, 30), Wektor<3>(65 ,160,2));
    
    
    Lacze.Rysuj();
    std:: cin.ignore(10000,'\n');
    
}


void  Scena:: KonfigurujLacze(){
    
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj();
    Lacze.UstawZakresY(0,ZakresOsiY);
    Lacze.UstawZakresX(0,ZakresOsiX);
    Lacze.UstawZakresZ(0,ZakresOsiZ);
    Lacze.UstawRotacjeXZ(64,64);
}


void  Scena:: PolecDronem(int ID, Wektor<3> &Goal){
    int i = 0;
    
    for(shared_ptr<Dron> Element: ListaDronow){
        
        if (i == ID) {
            Wektor<3> Tmp = Element->Polozenie;
            
            Element->SciezkaLotu(Tmp, Goal, Lacze);
            Element->LotWertykalny(DoGory,Goal,Lacze);
            Element->ObrotDrona(Goal,Lacze);
            Element->LotHoryzontalny(Goal,Lacze);
            Element->SkanujPrzestrzen(Lacze);
            
            if (WykryjKolizje(Element)){
                
                if (KolizjaPlaskowyz) {
                    Goal[2] = WysokoscLadowania;
                    WysokoscLadowania = 2;
                    KolizjaPlaskowyz = false;
                    
                }else{
                    vector<Wektor<3>> SasiadGoal;
                    TworzPktSasiada(SasiadGoal);
                    
                    Wektor<3> AktPolozenie = Element->ZwrocPolozenie();
                    
                    for (int j= 0; j < 7; ++j) {
                        
                        Wektor<3> TmpGoal = Goal;
                        Macierz<3> Rotacja;
                        Rotacja.obliczmacierz('z',Element->ZwrocKat()*180/M_PI);
                        TmpGoal = Rotacja * SasiadGoal[j] + AktPolozenie;
                        
                        Element->UstawPolozenie(TmpGoal);
                        Element->ObliczWspDrona();
                        
                        if((WykryjKolizje(Element) == 0) || (KolizjaPlaskowyz) ){
                            
                            Goal = TmpGoal;
                            
                            if (KolizjaPlaskowyz) {
                                Goal[2] = WysokoscLadowania;
                                WysokoscLadowania = 2;
                                KolizjaPlaskowyz = false;
                            }else Goal[2] = 2;
                            
                            Element->UstawPolozenie(AktPolozenie);
                            Element->ObliczWspDrona();
                            AktPolozenie[2] = 2;
                            Element->SciezkaLotu(AktPolozenie, Goal, Lacze);
                            Element->ObrotDrona(Goal,Lacze);
                            Element->LotHoryzontalny(Goal,Lacze);
                            break;
                        }
                    }
                    cout << endl << " UWAGA!! WYKRYTO PRZESZKODĘ!";
                }
            }else
                cout << endl << " Nie wykryto kolizji, można bezpiecznie lądować.";
            Element->LotWertykalny(NaDol,Goal,Lacze);
        }
        ++i;
    }
}


void  Scena:: DodajPrzeszkode(Przeszkody RodzajPrzeszkody, Wektor<3> Skala, Wektor<3> Polozenie){
    
    string NazwaPliku;
    
    switch (RodzajPrzeszkody) {
            
        case _Gora:
            ListaPrzeszkod.push_back(make_shared<Gora>(Gora()));  // Tworzy nowy obiekt i przerzuca go jako wskaźnik na Listę
            ++IloscGor;
            ListaPrzeszkod.back()->UstawIloscObiektow(IloscGor);
            NazwaPliku = TworzNazwePlikuGory(IloscGor);
            break;
            
        case _Pagorek:
            ListaPrzeszkod.push_back(make_shared<Pagorek>(Pagorek()));
            ++IloscPagorkow;
            ListaPrzeszkod.back()->UstawIloscObiektow(IloscPagorkow);
            NazwaPliku = TworzNazwePlikuPagorka(IloscPagorkow);
            break;
            
        case _Plaskowyz:
            ListaPrzeszkod.push_back(make_shared<Plaskowyz>(Plaskowyz()));
            ++IloscPlaskowyzow;
            ListaPrzeszkod.back()->UstawIloscObiektow(IloscPlaskowyzow);
            NazwaPliku = TworzNazwePlikuPlaskowyza(IloscPlaskowyzow);
            break;
    }
    
    ListaPrzeszkod.back()->UstawSkale(Skala);
    ListaPrzeszkod.back()->UstawPolozenie(Polozenie);
    ListaPrzeszkod.back()->ObliczWsp();
    
    Lacze.DodajNazwePliku(NazwaPliku.c_str());
}


void  Scena:: UsunPrzeszkode(int Numer){
    
    int i = 0;

    for(shared_ptr<BrylaGeometryczna> Element: ListaPrzeszkod){
        
        i = Element->PokazNumerNaLiscie();
        
        if (i == Numer) {
            Element->UstawSkale(Wektor<3>());
            Element->UstawPolozenie(Wektor<3>());
            Element->ObliczWsp();
        }
    }
    std::list<shared_ptr<BrylaGeometryczna>>::iterator Element = ListaPrzeszkod.begin();
    advance(Element, (i-1));
    ListaPrzeszkod.erase(Element);
}


bool  Scena:: WykryjKolizje(shared_ptr<Dron> D){
    
    int i = 0;  
    Wektor<3> WspD = D->ObrysDrona();
    
    for(shared_ptr<BrylaGeometryczna> Element: ListaPrzeszkod){
        
        if (Element.get() != D->PntrNaKorpus()){       // Jeśli element jest różny od samego siebie
        
            int Kolizja = Element->SprawdzKolizje(WspD);
            if (Kolizja != 0){
                
                ++i;
                if(Kolizja == 4){
                    KolizjaPlaskowyz = true;
                    WysokoscLadowania = Element->ObrysBryly()[0][2]+2;
                }
            }
        }
    }
    return i != 0;
}


void  Scena:: MenuPrzeszkod(){
    
    MenuWyswietlPrzeszkody();
    
    cout << " * " << endl
         << " * Co zrobić z przeszkodami? " << endl
         << " * 1 - Dodaj nową przeszkodę"  << endl
         << " * 2 - Usuń istniejącą przeszkodę" << endl
         << " * 3 - Powróć do menu drona"       << endl
         << " * " << endl
         << " * Wybieram: ";
    int wybor;
    cin >> wybor;
    
    switch (wybor) {
        case 1:
            MenuDodajPrzeszkode();
            break;

        case 2:
            int Numer;
            cout << endl << " Wybierz którą przeszkodę usunąć: ";
            cin  >> Numer;
            UsunPrzeszkode(Numer);
            cout << endl << " Udało się usunąć wybraną przeszkodę C:" << endl;
            Lacze.Rysuj();
            break;
    }
}


void  Scena:: MenuWyswietlPrzeszkody(){
    
    cout << endl << " * Aktywne przeszkody:" << endl;
    int i = 0;
    for(shared_ptr<BrylaGeometryczna> Element: ListaPrzeszkod){
        
        if (Element->WyswietlRodzaj() != "s"){
            ++i;
            Element->UstawNumerNaLiscie(i);
            cout << " * "<< i << ". [" << Element->WyswietlPolozenie() << "] - "
                 << Element->WyswietlRodzaj() << endl;
        }
    }
}


void  Scena:: MenuDodajPrzeszkode(){
    
    Wektor<3> S, P;
    int Rodzaj;
    cout << endl << " Podaj rodzaj przeszkody (1 - Gora, 2 - Pagorek, 3 - Płaskowyż): ";
    cin  >> Rodzaj;
    cout << " Podaj w postaci [x,y,z] skalę przeszkody: ";
    cin  >> S;
    cout << " Podaj w postaci [x,y] punkty położenia przeszkody: ";
    cin  >> P;
    
    switch (Rodzaj) {
        case 1:
            DodajPrzeszkode(_Gora,S,P);
            break;

        case 2:
            DodajPrzeszkode(_Pagorek,S,P);
            break;

        case 3:
            DodajPrzeszkode(_Plaskowyz,S,P);
            break;
    }
    
    cout << endl << " Przeszkoda dodana. C:" << endl;
    Lacze.Rysuj();
}


void  Scena:: MenuWyborDrona(int &ID){
    
    cout << endl << " * Aktywne drony:" << endl;
    int i = 0, wybor;
    for(shared_ptr<Dron> Element: ListaDronow){
        ++i;
        Element->UstawNumerDrona(i);
        cout << " * "<< i << ". [" << Element->Polozenie << "]";
        
        if (ID == i)
            cout << " <<-- Aktywny" << endl;
        else
            cout << endl;
    }
    cout << " *" << endl << "Co chcesz zrobić z dronami?" << endl
         << " * 1 - Wybierz aktywnego drona" << endl
         << " * 2 - Dodaj nowego drona" << endl
         << " * 3 - Usuń istniejącego drona" << endl
         << " *" << endl << " * Wybieram: ";
    cin >> wybor;
    
    switch (wybor) {
        case 1:
            cout << " Wybierz aktywnego drona: ";
            cin  >> ID;
            break;
        case 2:
            MenuDodajDrona();
            ID = ++i;
            break;
        case 3:
            int Numer;
            cout << endl << " Wybierz którego drona usunąć: ";
            cin  >> Numer;
            UsunDrona(Numer);
            cout << endl << " Udało się usunąć wybranego drona C:" << endl;
            Lacze.Rysuj();
            
            break;
    }
}


void  Scena:: MenuDodajDrona(){
    
    Wektor<3> S1, S2, P;
    cout << " Podaj w postaci [x,y,z] skalę korpusu: ";
    cin  >> S1;
    cout << " Podaj w postaci [x,y,z] skalę rotorow: ";
    cin  >> S2;
    cout << " Podaj w postaci [x,y] punkty położenia drona: ";
    cin  >> P;
    
    ++IloscDronow;
    
    ListaDronow.push_back(make_shared<Dron>(Dron()));
    ListaDronow.back()->TworzDrona(IloscDronow,Lacze);
    ListaDronow.back()->UstawSkaleKorpusu(S1);
    ListaDronow.back()->UstawSkaleRotorow(S2);
    ListaDronow.back()->UstawPolozenie(P);
    
    if(WykryjKolizje(ListaDronow.back())){
        cout << " NIE MOŻNA DODAĆ TU DRONA. To miejsce jest zajęte. :c";
        ListaDronow.pop_back();
        --IloscDronow;
    }else
        cout << endl << " Dron dodany. C:" << endl;
    
    if(!ListaDronow.back()->ObliczWspDrona())
        cout << "Błąd obliczania Wsp Drona " << IloscDronow << "!!! :C" << endl;
    
    shared_ptr<Prostopadloscian> WskD;
    WskD.reset(ListaDronow.back()->PntrNaKorpus());
    ListaPrzeszkod.push_back(WskD);
    
    Lacze.Rysuj();
}


void  Scena:: UsunDrona(int Numer){
    
    int i = 0;

    for(shared_ptr<Dron> Element: ListaDronow){
        i = Element->ZwrocNumerDrona();
        if (i == Numer) {
            Element->UstawSkaleKorpusu(Wektor<3>());
            Element->UstawSkaleRotorow(Wektor<3>());
            Element->UstawPolozenie(Wektor<3>());
            Element->ObliczWspDrona();
        }
    }
}


void  Scena:: TworzPktSasiada(vector<Wektor<3>> &SasiadGoal){
    
    SasiadGoal.push_back(Wektor<3>(  0, 15,0));
    SasiadGoal.push_back(Wektor<3>( 15, 15,0));
    SasiadGoal.push_back(Wektor<3>( 15,  0,0));
    SasiadGoal.push_back(Wektor<3>( 15,-15,0));
    SasiadGoal.push_back(Wektor<3>(-15,-15,0));
    SasiadGoal.push_back(Wektor<3>(-15,  0,0));
    SasiadGoal.push_back(Wektor<3>(-15, 15,0));
}
