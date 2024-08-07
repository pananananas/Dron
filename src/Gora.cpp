#include "Gora.hh"
using std :: ostringstream;
using std :: ofstream;
using std :: ifstream;
using std :: string;
using std :: cerr;
using std :: cout;
using std :: endl;
/*!
 * \file
 * \brief Definicja metody Gora
 *
 *    Plik zawiera definicję klasy Gora, która
 *    jest podstawą całego programu. Klasa ta jest dziedziczona
 *    przez kolejne klasy.
 */

bool   Gora:: ObliczWsp(){
    
    ifstream  Plik_Bryla(PLIK_GORY);
    ofstream  Plik_Przeszkody(TworzNazwePlikuGory(IloscGor));
    
    if (!Plik_Bryla.is_open()) {
        cerr << endl
        << " Blad otwarcia do odczytu pliku: " << PLIK_GORY << endl
        << endl;
        return false;
    }
    
    if (!Plik_Przeszkody.is_open()) {
        cerr << endl
        << " Blad otwarcia do zapisu pliku: " << PLIK_GORY << endl
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
            W = Skaluj(W) + Polozenie;
            
            Plik_Przeszkody << W << endl;
            if (Plik_Przeszkody.fail())
                return false;
        }
        Plik_Przeszkody << endl;
    }
    if (Plik_Przeszkody.fail())
        return false;
    return true;
}


int    Gora:: SprawdzKolizje(Wektor<3> WspDrona){
    
    vector<Wektor<3>> Wek = ObrysBryly();
    
    Wektor<3> W2 = Wek[0];
    Wektor<3> W1 = Wek[1];
    Wektor<3> Tmp = WspDrona;
    
         if (WspDrona[0] < W1[0])   Tmp[0] = W1[0];
    else if (WspDrona[0] > W2[0])   Tmp[0] = W2[0];
         if (WspDrona[1] < W2[1])   Tmp[1] = W2[1];
    else if (WspDrona[1] > W1[1])   Tmp[1] = W1[1];
    
    double distance = Tmp.dlodcinka(WspDrona);
    
    if (distance <= WspDrona[2])   return 2;
    return 0;
}


string Gora:: TworzNazwePlikuGory(int I){
    
    std:: ostringstream StrmWy;
    
    StrmWy << "dat/PlikWlasciwy" << WyswietlRodzaj() << I << ".dat";
    
    return StrmWy.str();
}


vector<Wektor<3>> Gora:: ObrysBryly(){
    
    // Ściągam współrzędne z pliku z linii 12 i 18
    
    string NazwaPliku = TworzNazwePlikuGory(IloscGor);
    ifstream  Plik_Bryla(NazwaPliku);
    if (!Plik_Bryla.is_open())
        cerr << endl << " Blad otwarcia do odczytu pliku: " << NazwaPliku << endl << endl;
    
    vector<Wektor<3>> W;
    Wektor<3> Tmp;
    double D;
    string S;
    
    for (int i = 0; i < 10; ++i)
        std:: getline(Plik_Bryla,S);
    
    std:: getline(Plik_Bryla,S);
    for (int j = 0; j < 2; ++j) {
        Plik_Bryla >> D;
            
        Tmp.set(j,D);
    }
    W.push_back(Tmp);
    
    for (int i = 0; i < 5; ++i)
        std:: getline(Plik_Bryla,S);
    
    std:: getline(Plik_Bryla,S);
    for (int j = 0; j < 2; ++j) {
        Plik_Bryla >> D;
        
            
        Tmp.set(j,D);
    }
    W.push_back(Tmp);
    return W;
}
