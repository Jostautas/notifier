#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
//#include <chrono> //uncomment for compatibility with windows
//#include <ctime> //uncoment for compatibility with windows

using namespace std;

time_t t = time(0);     // Suzino laika
tm*now = localtime(&t);    // suzino dabartini laika
int Vasario_menesio_dienos(){   // skaiciuojama kiek dienu yra vasario menesi
    if(((now->tm_year + 1900) % 400 == 0) || ((now->tm_year + 1900) % 4 == 0 && (now->tm_year + 1900) %100 !=0))
        return 29;
    else
        return 28;
}
string Men[12] = {"Sausis", "Vasaris", "Kovas", "Balandis", "Geguze", "Birzelis", "Liepa", "Rugpjutis", "Rugsejis", "Spalis", "Lapkritis", "Gruodis"};
string Duomenys(int x = 0){ // kai bus ziurima i sekanti menesi, x bus 1 (Duomenys(1))
    int kintamasis = now->tm_mon + 1 + x;
    string pradzia = "duom_failai/";
    string pabaiga = ".txt";
    stringstream ss;
    ss << kintamasis;
    string string_kintamasis;
    ss >> string_kintamasis;
    return pradzia + string_kintamasis + Men[kintamasis-1] + pabaiga;
}
int Dienos[12] = {31, Vasario_menesio_dienos(), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // kiek kiekviename menesyje yra dienu
void sprendimas(){
    ofstream R("rez.txt");
    R << " _________ " << (now->tm_year + 1900) << "-" << setw(2) << setfill('0') << (now->tm_mon + 1) << "-" << setw(2) << setfill('0') << now->tm_mday << " _________" << endl << endl; // Spausdinam dabartini laika (YYY-MM-DD)
    ifstream F(Duomenys());    // paruosia sekancio menesio gimtadieniu nurasyma
    int k1 = 0; // jei yra ateinanciu gimtadieniu, ir dar nebuvo atspaudintas to gimtadinio menuo, ji atspausdins. Jei nebusbus ateinanciu gitmadieniu, k1 = 0 ir bus parasyta, kad ateinanciu gimtadieniu nera.
    int k2 = 0; // ziuri ar yra ateinanciu sekancio menesio gimtadieniu
    int d; // laikina vieta gimimo datai
    string v, p; // laikina vieta vardui ir pavardei
    while(F >> v >> p >> d){ // while ciklas suka tiek, kiek tame menesyje yra gimtadieniu. nuskaitomas vardas, pavarde, gimimo diena
        if((now->tm_mday + 7 >= d) && (d >= now->tm_mday)){ // jei gimimo diena yra 7 arba maziau dienu i prieki ir ne maziau uz dabartine diena
            if(k1 == 0){
                R << "     " << Men[now->tm_mon] << ":" << endl; // dabartinio menesio pavadinimas
                k1++;
            }
            R << v << " " << p << " " << setw(2) << setfill('0') << d << "d." << endl;    // spausdina varda, pavarde ir gimimo diena
        }
    }
    //------- Sekantis menesis
    if(now->tm_mday > Dienos[now->tm_mon] - 7){   // jei iki menesio pabaigos liko maziau negu savaite, ziuri i ateinancio menesio gimtadienius
        if(now->tm_mon < 11){ // jei menessi yra ne Gruodis (nes 12 + 1 = 13)
            ifstream F(Duomenys(1));    // paruosia sekancio menesio gimtadieniu nurasyma
            while(F >> v >> p >> d){ // for ciklas suka tiek, kiek tame menesyje yra gimtadieniu ir jie nuskaitomi
                if(((d - 7) >= -7) && (d - 7 <= now->tm_mday - Dienos[now->tm_mon])){   // jei is sekancio menesio gimimo dienos atemus savaite, gaunamas minusinis skaicius nemazesnis uz -7 ir mazesnis uz is dabartines dienos atemus menesio dienu skaiciu.
                    if(k2 == 0){
                        R << endl << "     " << Men[now->tm_mon+1] << ":" << endl; // sekancio menesio pavadinimas
                        k2++;
                    }
                    R << v << " " << p << " " << setw(2) << setfill('0') << d << "d." << endl;
                }
            }
        }
        else if(now->tm_mon == 11){ // jei dabartinis menesis yra gruodis, reikia duomenis imti is Duom[0] (Duom1.txt)
            ifstream F(Duomenys(-11));    // paruosia sekancio menesio gimtadieniu nurasyma
            while(F >> v >> p >> d){ 
                if(((d - 7) >= -7) && (d - 7 <= now->tm_mday - Dienos[0])){   // jei is sekancio menesio gimimo dienos atemus savaite, gaunamas minusinis skaicius nemazesnis uz -7 ir mazesnis uz is dabartines dienos atemus menesio dienu skaiciu.
                    if(k2 == 0){
                        R << endl << "     " << Men[0] << ":" << endl; // sekancio menesio pavadinimas
                        k2++;
                    }
                    R << v << " " << p << " " << setw(2) << setfill('0') << d << "d." << endl;
                }
            }
        }
        else
            R << "Error" << endl;
    }
    if((k1 == 0) && (k2 == 0)) // jei nera ateinanciu gimtadieniu, spausdinti:
	    R << "Ateinanciu gimtadieniu nera." << endl;
    F.close();
    R.close();
}
int main()
{
    sprendimas();
    return 0;
}
