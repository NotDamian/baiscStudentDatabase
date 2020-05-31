#define _CRT_SECURE_NO_WARNINGS  
#define _USE_MATH_DEFINES  
#include <math.h>  
#include <iomanip>  
#include<iostream>  
#include<conio.h>  
#include <cstdlib>  
#include <ctime>  
#include<string.h>  
#include <string>  
#include <fstream>  
#include<Windows.h> 
#include <algorithm> //biblioteka dzieki ktorej urzyje funkcji bibliotecznej sort która posortuje dane studentó w kolejnosci alfabetycznej 
#include <functional> 

using namespace std;

struct student {
    string imie;
    string nazwisko;
    int nr_albumu;
    int wiek;
    double srednia_ocen;
    bool operator < (const student& x)const //zdefiniowanie zachowania siê 
    {                //operatora < potrzebnego przy sortowaniu 
        return nazwisko > x.nazwisko;
    }
};

student dane[20];
int iloscStu = 0;
void menu();

void wylistowanie() {
    system("cls");
    for (int i = 0; i <= iloscStu; i++) {
        transform(dane[i].imie.begin(), dane[i].imie.end(), dane[i].imie.begin(), ::toupper);
        transform(dane[i].nazwisko.begin(), dane[i].nazwisko.end(), dane[i].nazwisko.begin(), ::toupper);
    }
    sort(dane, dane + iloscStu);
    int x = 1;
    for (int j = iloscStu - 1; j >= 0; j--) {
        cout << "Student " << x << " :" << endl;
        cout << "Nazwisko: " << dane[j].nazwisko << endl;
        cout << "Imie: " << dane[j].imie << endl;
        cout << "Wiek: " << dane[j].wiek << endl;
        cout << "Nr albumu: " << dane[j].nr_albumu << endl;
        cout << "Srednia ocen: " << dane[j].srednia_ocen << endl;
        cout << endl;
        x++;
    }
    _getch();
    menu();
}

void dodaj() {
    system("cls");
    if (iloscStu == 20) {
        cout << "Baza danych jest pe³na..." << endl;
        Sleep(4000);
        menu();
    }
    cout << "Wprowadz imie: " << endl;
    cin >> dane[iloscStu].imie;
    cout << "Wprowadz nazwisko: " << endl;
    cin >> dane[iloscStu].nazwisko;
    cout << "Wprowadz Wiek: " << endl;
    cin >> dane[iloscStu].wiek;
    cout << "Wprowadz nr albumu: " << endl;
    cin >> dane[iloscStu].nr_albumu;
    cout << "Wprowadz srednia ocen: " << endl;
    cin >> dane[iloscStu].srednia_ocen;
    iloscStu++;
    menu();
}

void usun() {
    for (int i = 0; i <= iloscStu - 1; i++) {
        if (dane[i].srednia_ocen <= 2.5) {
            for (int j = i; j <= iloscStu - 1; j++) {
                dane[j].imie = dane[j + 1].imie;
                dane[j].nazwisko = dane[j + 1].nazwisko;
                dane[j].wiek = dane[j + 1].wiek;
                dane[j].nr_albumu = dane[j + 1].nr_albumu;
                dane[j].srednia_ocen = dane[j + 1].srednia_ocen;
            }
            iloscStu--;
            i--;
        }
    }
    menu();
}

void zakoncz() {
    system("cls");
    fstream plik;
    //zapis 
    plik.open("bazastudentow.txt", ios::out | ios::app);
    for (int i = 0; i <= iloscStu - 1; i++) {
        plik << dane[i].imie << endl;
        plik << dane[i].nazwisko << endl;
        plik << dane[i].wiek << endl;
        plik << dane[i].nr_albumu << endl;
        plik << dane[i].srednia_ocen << endl;
    }
    plik.close();
    cout << "Zapis oraz zamykanie programu..." << endl;
    Sleep(1000);
    exit(0);
}

void menu() {
    system("cls");
    cout << "L: wylistowanie nazwisk, imion i wieku wszystkich studentów w porz¹dku alfabetycznym oraz zamiana wszystkich liter na du¿e" << endl;
    cout << "D: dodanie nowego studenta " << endl;
    cout << "U: usuniêcie studenta ze srednia ocen ponizej 2,5 " << endl;
    cout << "K: zakonczenie programu i zapisanie bazy studentów do pliku" << endl;
    cout << endl;
    cout << "wybierz opcje: " << endl;
    char x;
    cin >> x;
    switch (x)
    {
    case 'l':
        wylistowanie();
        break;
    case 'd':
        dodaj();
        break;
    case 'u':
        usun();
        break;
    case 'k':
        zakoncz();
        break;
    case 'L':
        wylistowanie();
        break;
    case 'D':
        dodaj();
        break;
    case 'U':
        usun();
        break;
    case 'K':
        zakoncz();
        break;
    default:
        break;
    }
}

void wyswietlDane() {
    fstream plik;
    string imieee, nazwiskooo;
    int wiek, nr_albumu;
    float srednia;
    plik.open("bazastudentow.txt", ios::in);
    if (plik.good() == false)
    {
        cout << "Nie ma takiego pliku" << endl;
        Sleep(2000);
        menu();
    }
    string linia;
    int j = 0;
    int nr_li = 1;
    while (getline(plik, linia))
    {
        switch (nr_li)
        {
        case 1: dane[iloscStu].imie = linia;
            break;
        case 2: dane[iloscStu].nazwisko = linia;
            break;
        case 3: dane[iloscStu].wiek = atoi(linia.c_str());  //atoi konwersja z string na int  
            break;
        case 4: dane[iloscStu].nr_albumu = atoi(linia.c_str());
            break;
        case 5: dane[iloscStu].srednia_ocen = atof(linia.c_str());
        }
        nr_li++;
        if (nr_li > 5) {
            nr_li = 1;
            j++;
            iloscStu = j;
        }
    }
    //iloscStu = j; 
    plik.close();
    for (int j = 0; j <= iloscStu - 1; j++) {
        cout << "Student " << j + 1 << ":" << endl;
        cout << "Nazwisko: " << dane[j].nazwisko << endl;
        cout << "Imie: " << dane[j].imie << endl;
        cout << "Wiek: " << dane[j].wiek << endl;
        cout << "Nr albumu: " << dane[j].nr_albumu << endl;
        cout << "Srednia ocen: " << dane[j].srednia_ocen << endl;
    }
    _getch();
}

int main() {
    wyswietlDane();
    menu();
    //_getch(); 
    return 0;
}