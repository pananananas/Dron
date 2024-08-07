#include "Dron.hh"
#include <unistd.h>
#include <iomanip>
/*!
 * \file
 * \brief Definicja metody Dron
 *
 *    Plik zawiera definicję metod klasy Dron.
*/
using std :: ostringstream;
using std :: ofstream;
using std :: ifstream;
using std :: fstream;
using std :: string;
using std :: vector;
using std :: cerr;
using std :: cout;
using std :: endl;
using std :: ios;


const Wektor<3> Dron:: TransfDoUklWspRodzica(const Wektor<3> &Wierz){
    Macierz<3> Rotacja;
    
    Rotacja.obliczmacierz('z',KatOrientacji);
    
    return Rotacja * Wierz + Polozenie;
}


string Dron:: TworzNazwePlikuKorpusa(unsigned int NrDrona){
    
    ostringstream StrmWy;
    
    StrmWy << "dat/PlikWlasciwyDron" << NrDrona << "Korpus.dat";
    
    NazwaPlikuKorpusu = StrmWy.str();
    return StrmWy.str();
}


string Dron:: TworzNazwePlikuSciezki(unsigned int NrDrona){
    
    ostringstream StrmWy;
    
    StrmWy << "dat/PlikWlasciwyDron" << NrDrona << "Sciezka.dat";
    return StrmWy.str();
}


string Dron:: TworzNazwePlikuSkanera(){
    
    ostringstream StrmWy;
    
    StrmWy << "dat/PlikWlasciwySkaner.dat";
    return StrmWy.str();
}


string Dron:: TworzNazwePlikuRotora(unsigned int NrDrona, unsigned int NrRotora){
    
    ostringstream StrmWy;
    
    StrmWy << "dat/PlikWlasciwyDron" << NrDrona << "Rotor" << NrRotora << ".dat";
    return StrmWy.str();
}


void   Dron:: TworzDrona(unsigned int NrDrona, PzG::LaczeDoGNUPlota &Lacze){
    
    unsigned int Ind = 0;
    string NazwaPliku;
    ID = NrDrona;
    for (Graniastoslup &Rot: Rotor) {
        NazwaPliku = TworzNazwePlikuRotora(NrDrona, Ind++);
        Rot.UstawNazwePlikWlasciwy(NazwaPliku);
        Lacze.DodajNazwePliku(NazwaPliku.c_str());
    }
    NazwaPliku = TworzNazwePlikuKorpusa(NrDrona);
    KorpusDrona.UstawNazwePlikWlasciwy(NazwaPliku);
    Lacze.DodajNazwePliku(NazwaPliku.c_str());
}


bool   Dron:: SciezkaLotu(Wektor<3> P,Wektor<3> Goal, PzG::LaczeDoGNUPlota &Lacze){
    
    string SciezkaLotu = TworzNazwePlikuSciezki(ID);
    Lacze.DodajNazwePliku(SciezkaLotu.c_str());
    ofstream  Plik_Sciezka(SciezkaLotu);
    if (!Plik_Sciezka.is_open()) {
        cerr << endl
        << " Blad otwarcia do odczytu pliku: " << PLIK_SZESCIANU << endl
        << endl;
        return false;
    }
    
    Plik_Sciezka << P << endl
                 << P + Wektor<3>(0, 0, WysokoscLotu - P[2]) << endl
                 << Goal      + Wektor<3>(0, 0, WysokoscLotu - 2) << endl
                 << Goal      << endl << endl;
    
    if (Plik_Sciezka.fail())
        return false;
    Lacze.Rysuj();
    return true;
}


void   Dron:: SkanujPrzestrzen(PzG::LaczeDoGNUPlota &Lacze){
    
    fstream Plik_Sciezka;
    string Skaner = TworzNazwePlikuSkanera();
    Lacze.DodajNazwePliku(Skaner.c_str());
    
    vector<Wektor<3>> PunktySkanera(49 , Wektor<3> (0,0,0));
    
    int indeks;
    
    for (int i = 0; i < 7; ++i) {
        
        Plik_Sciezka.open(Skaner, ios::out | ios::trunc);
        
        for (int j = 0 ; j < 7; ++j) {
            
            indeks = i * 7 + j;
            
            PunktySkanera[indeks] = TransfDoUklWspRodzica(Wektor<3>((-30+j*10), (30-10*i), 0));
            PunktySkanera[indeks][2] = 0;
            
            Plik_Sciezka << Polozenie << endl << PunktySkanera[indeks] << endl;
        }
        Lacze.Rysuj();
        
        usleep(100000);
        Plik_Sciezka.close();
    }
    Lacze.UsunOstatniaNazwe();
    Lacze.Rysuj();
}


void   Dron:: LotWertykalny(Kierunek K, Wektor<3> Goal, PzG::LaczeDoGNUPlota &Lacze){
    
    vector<Wektor<5>> PunktySciezki;
    Wektor<5> Tmp;
    Tmp[0] = Polozenie[0];
    Tmp[1] = Polozenie[1];
    Tmp[2] = Polozenie[2];
    Tmp[3] = KatOrientacji*M_PI/180;
    Tmp[4] = 0;
    
    switch (K) {
        case DoGory:
            while ( Tmp[2] != WysokoscLotu ) {
                Tmp[2] += Krok;
                Tmp[4] += PredkoscObrotuRotora;
                
                if (Tmp[2] > WysokoscLotu)
                    Tmp[2] = WysokoscLotu;
                PunktySciezki.push_back(Tmp);
            }
            break;
            
        case NaDol:
            while ( Tmp[2] != Goal[2] ) {
                Tmp[2] -= Krok;
                Tmp[4] -= PredkoscObrotuRotora;

                if (Tmp[2] < Goal[2])
                    Tmp[2] = Goal[2];
                PunktySciezki.push_back(Tmp);
            }
            break;
    }
    WykonajSciezke(PunktySciezki,Lacze);
}


void   Dron:: LotHoryzontalny(Wektor<3> Goal,  PzG::LaczeDoGNUPlota &Lacze){
    
    vector<Wektor<5>> PunktySciezki;
    Wektor<5> Tmp;
    Tmp[0] = Polozenie[0];
    Tmp[1] = Polozenie[1];
    Tmp[2] = Polozenie[2];
    Tmp[3] = KatOrientacji*M_PI/180;
    Tmp[4] = 0;
    
    double KatDocelowy = KatOrientacji*M_PI/180;
    
    int WspolczynnikX = 1, WspolczynnikY = 1;
    
    if (KatDocelowy < M_PI/2) {
        
    if (Goal[0] > Polozenie[0])     WspolczynnikX =  1;
    else                            WspolczynnikX = -1;
    if (Goal[1] > Polozenie[1])     WspolczynnikY =  1;
    else                            WspolczynnikY = -1;
    }
    
    
    while ( ( Tmp[0] != Goal[0] ) && ( Tmp[1] != Goal[1] ) ) {
        
        Tmp[0] += Krok * cos( KatDocelowy ) * WspolczynnikX;
        Tmp[1] += Krok * sin( KatDocelowy ) * WspolczynnikY;
        Tmp[4] += PredkoscObrotuRotora;
        
        if ( pow(Tmp[0] - Goal[0],2) + pow(Tmp[1]-Goal[1],2) < Krok ){
            Tmp[0] = Goal[0];
            Tmp[1] = Goal[1];
        }
        PunktySciezki.push_back(Tmp);
    }
    WykonajSciezke(PunktySciezki,Lacze);
}


void   Dron:: ObrotDrona(Wektor<3> Goal,  PzG::LaczeDoGNUPlota &Lacze){
    
    vector<Wektor<5>> PunktySciezki;
    Wektor<5> Tmp;
    Tmp[0] = Polozenie[0];
    Tmp[1] = Polozenie[1];
    Tmp[2] = Polozenie[2];
    Tmp[3] = KatOrientacji*M_PI/180;
    Tmp[4] = 0;
    
    double KatDocelowy = atan(( Polozenie[1] - Goal[1] )/( Polozenie[0] - Goal[0] ));
    
    while(KatDocelowy < 0)
        KatDocelowy += M_PI;
    
    
    while ( Tmp[3] != KatDocelowy ) {
        Tmp[3] += PredkoscObrotuDrona;
        Tmp[4] += PredkoscObrotuRotora;
        
        if (Tmp[3] > abs(KatDocelowy ))
            Tmp[3] = KatDocelowy;
        
        PunktySciezki.push_back(Tmp);
    }
    WykonajSciezke(PunktySciezki,Lacze);
}


void   Dron:: WykonajSciezke(vector<Wektor<5>> Sciezka, PzG::LaczeDoGNUPlota &Lacze){
    
    for (Wektor<5> &Punkt: Sciezka) {
        
        UstawPolozenie(Wektor<3>(Punkt[0], Punkt[1], Punkt[2]));
        UstawKat(Punkt[3]*180/M_PI);
        UstawKatRotorow(Punkt[4]);
        ObliczWspDrona();
        Lacze.Rysuj();
        usleep(100000);
    }
}


bool   Dron:: ObliczWspKorpusu(){
    
    ifstream  Plik_Bryla(PLIK_SZESCIANU);
    ofstream  Plik_Korpus(TworzNazwePlikuKorpusa(ID));
    
    if (!Plik_Bryla.is_open()) {
        cerr << endl
        << " Blad otwarcia do odczytu pliku: " << PLIK_SZESCIANU << endl
        << endl;
        return false;
    }
    
    if (!Plik_Korpus.is_open()) {
        cerr << endl
        << " Blad otwarcia do zapisu pliku: " << PLIK_KORPUSU << endl
        << endl;
        return false;
    }
    
    for (int i = 0; i < 5; ++i) {
        Wektor<3> W;
        double tmp;
        
        for (int j = 0; j < 4; ++j) {
            
            for (int k = 0; k < 3; ++k) {
                
                Plik_Bryla >> tmp;
                if(Plik_Bryla.fail())
                    return false;
                W.set(k,tmp);
            }
            W = KorpusDrona.Skaluj(W);
            W = KorpusDrona.TransfDoUklWspRodzicaP(W);
            W = TransfDoUklWspRodzica(W);
            
            Plik_Korpus << W << endl;
            if (Plik_Korpus.fail())
                return false;
        }
        Plik_Korpus << endl;
    }
    if (Plik_Korpus.fail())
        return false;
    return true;
}


bool   Dron:: ObliczWspRotora(int Ind){
    
    ifstream  Plik_Bryla(PLIK_GRANIASTOSLUPA6);
    ofstream  Plik_Korpus(TworzNazwePlikuRotora(ID,Ind));
    
    if (!Plik_Bryla.is_open()) {
        cerr << endl
        << " Blad otwarcia do odczytu pliku: " << PLIK_SZESCIANU << endl
        << endl;
        return false;
    }
    if (!Plik_Korpus.is_open()) {
        cerr << endl
        << " Blad otwarcia do zapisu pliku: " << PLIK_KORPUSU << endl
        << endl;
        return false;
    }
    
    Wektor<3> TabWspRot[4] = {
        Wektor<3>( 0.8, 0.8, 1.5),
        Wektor<3>(-0.8, 0.8, 1.5),
        Wektor<3>(-0.8,-0.8, 1.5),
        Wektor<3>( 0.8,-0.8, 1.5)
    };
    for(int i = 0; i < 3; ++i)
        Rotor[Ind].Polozenie.set(i, TabWspRot[Ind][i] * Rotor[Ind].Skala[i]);
    
    for (int i = 0; i < 7; ++i) {
        Wektor<3> W;
        double tmp;
        
        for (int j = 0; j < 4; ++j) {
            
            for (int k = 0; k < 3; ++k) {
                
                Plik_Bryla >> tmp;
                if(Plik_Bryla.fail())
                    return false;
                W.set(k,tmp);
            }
            W = Rotor[Ind].Skaluj(W);
            W = Rotor[Ind].TransfDoUklWspRodzicaG(W);
            W = TransfDoUklWspRodzica(W);
            
            Plik_Korpus << W << endl;
            if (Plik_Korpus.fail())
                return false;
            
        }
        Plik_Korpus << endl;
    }
    if (Plik_Korpus.fail())
        return false;
    
    return true;
}


bool   Dron:: ObliczWspDrona(){
    
    if(!ObliczWspKorpusu())
        return false;
    for(int i = 0; i < 4; ++i){
        if (!ObliczWspRotora(i))
            return false;
    }
    return true;
}


void   Dron:: UstawKatRotorow(double Kat){
    
    for (int i = 0; i < 4; ++i) {
        if ((i == 0) || (i == 2)) {
            Rotor[i].KatObrotu(Kat);
        }
        
        if ((i == 1) || (i == 3)) {
            Rotor[i].KatObrotu(-Kat);
        }
    }
}
