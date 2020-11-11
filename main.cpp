#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <cstdio>
#include <stdio.h>

using namespace std;
struct User
{
    int idUser;
    string name, password;
};

struct Uzytkownik
{
    int id, idLoggedUser;
    string imie, nazwisko, nrTelefonu, adresEmail, adres;
};

int returnIdLoggedUserToCompare(string linia)
{
    int idLoggedUser;
    char separator = '|';
    size_t pozycja = 0;
    string pobierz;
    pozycja = linia.find(separator);
    pobierz = linia.substr(0,pozycja);
    linia.erase(0, pozycja+1);
    pozycja = 0;
    pozycja = linia.find(separator);
    pobierz = linia.substr(0,pozycja);
    idLoggedUser = atoi(pobierz.c_str());
    return idLoggedUser;
}
int wczytajOsobyZPliku (vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow, int &idLoggedUser)
{
    int id, idLoggedUserToCompare, nrLinii = 1;
    string imie, nazwisko, nrTelefonu, adresEmail, adres, linia, pobierz;
    char separator = '|';
    size_t pozycja = 0;

    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::in );
     if(plik.good()==true)
        {
            while (getline(plik,linia))
                {
                    idLoggedUserToCompare = returnIdLoggedUserToCompare (linia);
                    if (idLoggedUser == idLoggedUserToCompare)
                        {
                            while ((pozycja = linia.find(separator)) != string::npos)
                            {
                                pobierz = linia.substr(0,pozycja);
                                linia.erase(0, pozycja+1);
                                switch(nrLinii)
                                    {
                                        case 1: id = atoi(pobierz.c_str());              break;
                                        case 2: idLoggedUser = atoi(pobierz.c_str());    break;
                                        case 3: imie = pobierz;                          break;
                                        case 4: nazwisko = pobierz;                      break;
                                        case 5: nrTelefonu = pobierz;                    break;
                                        case 6: adresEmail = pobierz;                    break;
                                        case 7: adres = pobierz; uzytkownicy.push_back (Uzytkownik{id, idLoggedUser, imie, nazwisko, nrTelefonu, adresEmail, adres}); break;
                                    }
                                if( nrLinii >= 7 )
                                    {
                                        nrLinii = 1;
                                        iloscUzytkownikow++;
                                    }
                                else
                                    {
                                        nrLinii ++;
                                    }
                            }
                    }
                }
            plik.close();
        }
    return iloscUzytkownikow;
}

void saveNewPersonToFile (vector<User> &users, int &numberUsers)
{
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if (plik.good() == true)
        {
            plik << users[numberUsers].idUser << "|" << users[numberUsers].name << "|" << users[numberUsers].password << "|" << endl;
        }
    else
        {
            cout << "Nie udalo sie utworzyc pliku" << endl;
        }
    plik.close();
}
int loadUsersFromFile (vector<User> &users, int &numberUsers)
{
    int idUser, nrLinii = 1;
    string name, password, linia, pobierz;
    char separator = '|';
    size_t pozycja = 0;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in );
     if(plik.good()==true)
        {
            while (getline(plik,linia))
                {
                    while ((pozycja = linia.find(separator)) != string::npos)
                        {
                            pobierz = linia.substr(0,pozycja);
                            linia.erase(0, pozycja+1);
                            switch(nrLinii)
                                {
                                    case 1: idUser = atoi(pobierz.c_str());    break;
                                    case 2: name = pobierz;                    break;
                                    case 3: password = pobierz; users.push_back (User{idUser, name, password}); break;
                                }
                            if( nrLinii >= 3 )
                                {
                                    nrLinii = 1;
                                    numberUsers++;
                                }
                            else
                                {
                                    nrLinii ++;
                                }
                        }
                }
            plik.close();
        }
    return numberUsers;
}
int rejestracja( vector<User> &users, int &numberUsers )
{
    User obiekt;
    string name, password;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> obiekt.name;
    int i=0;
    while (i<numberUsers)
    {
        if (users[i].name == name)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> name;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> obiekt.password;
    obiekt.idUser = numberUsers+1;
    users.push_back( obiekt );
    cout << "Konto zalozone" << endl;
    saveNewPersonToFile(users,numberUsers);
    Sleep(1000);
    return numberUsers+1;
}

int logowanie(vector<User> &users,int &numberUsers, int &idUser)
{
    string name, password;

    cout << "Podaj nazwe: " << endl;
    cin >> name;

    int i=0;
    while (i<numberUsers)
    {
        if (users[i].name == name)
        {
            for (int proby = 0; proby<3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob : " << 3-proby << ": ";
                cin >> password;
                if (users[i].password == password)
                {
                    cout << "Zalogowales sie. " << endl;
                    Sleep (1000);
                    idUser = users[i].idUser;
                    return idUser;
                }
            }
            Sleep (3000);
        }
        i++;
    }
    cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba " << endl;
    Sleep(1500);
    return 0;

}

int wyszukajPoImieniu (vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    string imie;
    system ("cls");
    cout << "Podaj imie osoby ktora chcesz wyszukac: ";
    cin >> imie;
    for (int i = 0; i<uzytkownicy.size(); i++)
        {
            if (uzytkownicy[i].imie == imie)
                {
                    cout << "ID uzytkownika " << uzytkownicy[i].id << ": " << uzytkownicy[i].imie << " " << uzytkownicy[i].nazwisko
                         << ", telefon: " << uzytkownicy[i].nrTelefonu << ", adres e-mail: " << uzytkownicy[i].adresEmail
                         << ", adres zamieszkania: " << uzytkownicy[i].adres << endl;
                }
        }
    system("pause");
    return 1;
}

int wyszukajPoNazwisku (vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    string nazwisko;
    system ("cls");
    cout << "Podaj imie osoby ktora chcesz wyszukac: ";
    cin >> nazwisko;
    for (int i = 0; i<uzytkownicy.size(); i++)
        {
            if (uzytkownicy[i].nazwisko == nazwisko)
                {
                    cout << "ID uzytkownika " << uzytkownicy[i].id << ": " << uzytkownicy[i].imie << " " << uzytkownicy[i].nazwisko
                         << ", telefon: " << uzytkownicy[i].nrTelefonu << ", adres e-mail: " << uzytkownicy[i].adresEmail
                         << ", adres zamieszkania: " << uzytkownicy[i].adres << endl;
                }
        }
    system("pause");
    return 1;
}

void wyswietlKsiazke(vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    for (int i=0; i<uzytkownicy.size(); i++)
    {
        cout << "ID uzytkownika " << uzytkownicy[i].id << ": " << uzytkownicy[i].imie << " " << uzytkownicy[i].nazwisko << ", telefon: " << uzytkownicy[i].nrTelefonu
        << ", adres e-mail: " << uzytkownicy[i].adresEmail << ", adres zamieszkania: " << uzytkownicy[i].adres << endl;
    }
    system("pause");
}

void zapiszNowaOsobeDoPliku (vector<Uzytkownik> uzytkownicy, int iloscUzytkownikow)
{

    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::out | ios::app);
    if (plik.good() == true)
        {
            plik << uzytkownicy[iloscUzytkownikow].id << "|" << uzytkownicy[iloscUzytkownikow].idLoggedUser << "|" << uzytkownicy[iloscUzytkownikow].imie << "|" << uzytkownicy[iloscUzytkownikow].nazwisko
                 << "|" << uzytkownicy[iloscUzytkownikow].nrTelefonu << "|" << uzytkownicy[iloscUzytkownikow].adresEmail << "|" << uzytkownicy[iloscUzytkownikow].adres << "|" << endl;
        }
    else
        {
            cout << "Nie udalo sie utworzyc pliku" << endl;
        }
    plik.close();
    cout << "Dane zostaly wprowadzone poprawnie. Za chwile nastapi powrot do glownego menu " << endl;
}

int pobierzIdUzytkownikaNaOstatniejPozycji ()
{
    int idToCompare;
    string linia, pobierz;
    char separator = '|';
    size_t pozycja = 0;

    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::in );
    if(plik.good()==true)
        {
            while (getline(plik,linia))
                {
                    pozycja = linia.find(separator);
                    pobierz = linia.substr(0,pozycja);
                    idToCompare = atoi(pobierz.c_str());
                }
        }
    else
        {
            cout << "Nie udalo sie utworzyc pliku" << endl;
            idToCompare = 0;
        }
    plik.close();
    return idToCompare+1;
}

int wprowadzNowaOsobe(vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow,int &idLoggedUser)
{
    Uzytkownik obiekt;
    int id = pobierzIdUzytkownikaNaOstatniejPozycji();
    obiekt.id = id;
    obiekt.idLoggedUser = idLoggedUser;

    system ("cls");
    cout << "Podaj imie: ";
    cin >> obiekt.imie;
    cout << "Podaj nazwisko: ";
    cin >> obiekt.nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, obiekt.nrTelefonu);
    cout << "Podaj adres e-mail: ";
    cin >> obiekt.adresEmail;
    cout << "Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin, obiekt.adres);
    uzytkownicy.push_back( obiekt );

    zapiszNowaOsobeDoPliku(uzytkownicy,iloscUzytkownikow);
    Sleep(1500);

    return iloscUzytkownikow+1;
}

string zwroc(string linia, string id)
{
    size_t pozycja = 0;
    char separator = '|';
    string pobierz, idDoPorownania = "";
    while (pozycja = linia.find(separator))
        {
            pobierz = linia.substr(0,pozycja);
            if (id == pobierz)
                {
                    idDoPorownania = linia.erase(pozycja, linia.length() );
                }
            break;
        }
    return idDoPorownania;
}

int usunPozycje (vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    string linia, id;
    int porownanie;

    system ("cls");
    cout << "Podaj ID uzytkownika, ktorego chcesz usunac"<<endl;
    cin >> id;
    fstream plikPierwszy;
    ofstream plikDrugi;
    plikPierwszy.open("Ksiazka adresowa.txt", ios::in );
    plikDrugi.open("Ksiazka adresowa1.txt", ios::out | ios::app);
    if((plikPierwszy.good()==true) && (plikDrugi.good()==true))
        {
        while (getline(plikPierwszy,linia))
            {
                if (id != zwroc(linia, id))
                    {
                        plikDrugi << linia << endl;
                    }
                else
                    {
                        for( int i = 0; i < uzytkownicy.size(); i++ )
                            {
                                porownanie = atoi(id.c_str());
                                if (uzytkownicy[i].id == porownanie)
                                {
                                    uzytkownicy.erase(uzytkownicy.begin()+i);
                                    iloscUzytkownikow-=1;
                                }
                            }
                    }
            }
        }
            plikPierwszy.close();
            plikDrugi.close();
            remove( "Ksiazka adresowa.txt" );
            rename("Ksiazka adresowa1.txt", "Ksiazka adresowa.txt");
    return iloscUzytkownikow;
}

string zwrocEdycja(string linia, string id)
{
    size_t pozycja = 0;
    char separator = '|';
    string pobierz, idDoPorownania = "";
    while (pozycja = linia.find(separator))
        {
            idDoPorownania = linia.substr(0,pozycja);
            break;
        }
    return idDoPorownania;
}

void aktualizujPlikTekstowyPoEdycjiDanychUzytkownika (vector<Uzytkownik> uzytkownicy, int id)
{
    string linia, idDoPorownania;
    char znak;
    int porownanie;
    fstream plikPierwszy;
    ofstream plikDrugi;
    plikPierwszy.open("Ksiazka adresowa.txt", ios::in );
    plikDrugi.open("Ksiazka adresowa1.txt", ios::out | ios::app);
    if((plikPierwszy.good()==true) && (plikDrugi.good()==true))
        {
        while (getline(plikPierwszy,linia))
            {
                porownanie = atoi(zwrocEdycja(linia, idDoPorownania).c_str());
                if (id != porownanie)
                    {
                        plikDrugi << linia << endl;
                    }
                else
                    {
                        for (int pozycjaNaLiscie = 0; pozycjaNaLiscie<uzytkownicy.size(); pozycjaNaLiscie++)
                        {
                            if (id == uzytkownicy[pozycjaNaLiscie].id)
                            {
                                plikDrugi << uzytkownicy[pozycjaNaLiscie].id << "|" << uzytkownicy[pozycjaNaLiscie].idLoggedUser << "|" << uzytkownicy[pozycjaNaLiscie].imie << "|" << uzytkownicy[pozycjaNaLiscie].nazwisko
                                          << "|" << uzytkownicy[pozycjaNaLiscie].nrTelefonu << "|" << uzytkownicy[pozycjaNaLiscie].adresEmail << "|" << uzytkownicy[pozycjaNaLiscie].adres << "|" << endl;
                            }
                        }
                    }
            }
            plikPierwszy.close();
            plikDrugi.close();
            remove( "Ksiazka adresowa.txt" );
            rename("Ksiazka adresowa1.txt", "Ksiazka adresowa.txt");
        }
}

int edytujAdresata (vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    Uzytkownik obiekt;
    int id, pozycjaNaLiscie;
    char daneAdresataDoZmiany;
    string imie, nazwisko, nrTelefonu, adresEmail, adres;

    system ("cls");
    cout << "Podaj ID uzytkownika, ktorego chcesz edytowac"<<endl;
    if (!uzytkownicy.empty())
        {
            cin >> id;
            for (int pozycjaNaLiscie = 0; pozycjaNaLiscie<uzytkownicy.size(); pozycjaNaLiscie++)
                {
                    if (uzytkownicy[pozycjaNaLiscie].id == id)
                        {
                            system ("cls");
                            cout << "Wybierz dane adresata, ktore chcesz edytowac:" << endl;
                            cout <<  "1. Imie" << endl;
                            cout <<  "2. Nazwisko" << endl;
                            cout <<  "3. Numer telefonu" << endl;
                            cout <<  "4. Email" << endl;
                            cout <<  "5. Adres zamieszkania" << endl;
                            cout <<  "6. Powrot do glownego menu" << endl;
                            cin >> daneAdresataDoZmiany;

                            if (daneAdresataDoZmiany == '1')
                                {
                                    cout << "Podaj nowe imie" << endl;
                                    cin >> uzytkownicy[pozycjaNaLiscie].imie;
                                }
                            else if (daneAdresataDoZmiany == '2')
                                {
                                    cout << "Podaj nowe nazwisko" << endl;
                                    cin >> uzytkownicy[pozycjaNaLiscie].nazwisko;
                                }
                            else if (daneAdresataDoZmiany == '3')
                                {
                                    cout << "Podaj nowy numer telefonu" << endl;
                                    cin.sync();
                                    getline(cin, uzytkownicy[pozycjaNaLiscie].nrTelefonu);

                                }
                            else if (daneAdresataDoZmiany == '4')
                                {
                                    cout << "Podaj nowy adres email" << endl;
                                    cin >> uzytkownicy[pozycjaNaLiscie].adresEmail;
                                }
                            else if (daneAdresataDoZmiany == '5')
                                {
                                    cout << "Podaj nowy adres" << endl;
                                    cin.sync();
                                    getline(cin, uzytkownicy[pozycjaNaLiscie].adres);
                                }
                            else if (daneAdresataDoZmiany == '6')
                                return 1;
                        }
                }
                aktualizujPlikTekstowyPoEdycjiDanychUzytkownika (uzytkownicy, id);
        }
    return 1;
}

string zwrocZmianaHasla(string linia, string id)
{
    size_t pozycja = 0;
    char separator = '|';
    string pobierz, idDoPorownania = "";
    while (pozycja = linia.find(separator))
        {
            idDoPorownania = linia.substr(0,pozycja);
            break;
        }
    return idDoPorownania;
}

void aktualizujPlikTekstowyPoZmianieHasla (vector<User> &users, int &idUser)
{
    string linia, idDoPorownania;
    int porownanie;
    fstream plikPierwszy;
    ofstream plikDrugi;
    plikPierwszy.open("Uzytkownicy.txt", ios::in );
    plikDrugi.open("Uzytkownicy1.txt", ios::out | ios::app);
    if((plikPierwszy.good()==true) && (plikDrugi.good()==true))
        {
        while (getline(plikPierwszy,linia))
            {
                porownanie = atoi(zwrocZmianaHasla(linia, idDoPorownania).c_str());
                if (idUser != porownanie)
                    {
                        plikDrugi << linia << endl;
                    }
                else
                    {

                        for (int pozycjaNaLiscie = 0; pozycjaNaLiscie < users.size(); pozycjaNaLiscie++)
                        {
                            if (idUser == users[pozycjaNaLiscie].idUser)
                            {
                                plikDrugi << users[pozycjaNaLiscie].idUser << "|" << users[pozycjaNaLiscie].name << "|" << users[pozycjaNaLiscie].password << "|" << endl;
                            }
                        }
                    }
            }
            plikPierwszy.close();
            plikDrugi.close();
            remove( "Uzytkownicy.txt" );
            rename("Uzytkownicy1.txt", "Uzytkownicy.txt");
        }
}

int zmianaHasla (vector<User> &users, int &idUser)
{
    string password, newPassword;

    for (int i = 0; i < users.size (); i++)
        {
            if (users[i].idUser == idUser)
                {
                    cout << "Podaj stare haslo;";
                    cin >> password;
                    if (password == users[i].password)
                        {
                            cout << "Podaj nowe haslo: ";
                            cin >> users[i].password;
                            cout << "Haslo zostalo pomyslnie zmienione. Za chwile nastapi powrot do glownego menu";
                            Sleep (3000);
                            aktualizujPlikTekstowyPoZmianieHasla (users, idUser);
                        }
                }
        }
    return 1;
}

int main()
{
    vector<User> users;
    int idLoggedUser = 0, numberUsers = 0, licznik = 0, idUser;
    vector<Uzytkownik> uzytkownicy;
    int iloscUzytkownikow = 0;
    char choice;

    while (1)
    {
        if (idLoggedUser == 0)
        {
            uzytkownicy.clear ();
            numberUsers = loadUsersFromFile(users, numberUsers);
            iloscUzytkownikow = 0;
            system ("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> choice;

            if (choice == '1')
                numberUsers = rejestracja(users,numberUsers);
            else if (choice == '2')
            {
                idLoggedUser = logowanie(users,numberUsers, idUser);
                wczytajOsobyZPliku(uzytkownicy, iloscUzytkownikow, idLoggedUser);
            }
            else if (choice == '9')
                exit (0) ;
        }
        else
        {
            system ("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;
            cin >> choice ;

            if (choice == '1')
                iloscUzytkownikow = wprowadzNowaOsobe(uzytkownicy, iloscUzytkownikow, idLoggedUser);
            else if (choice == '2')
                wyszukajPoImieniu (uzytkownicy, iloscUzytkownikow);
            else if (choice == '3')
                wyszukajPoNazwisku (uzytkownicy, iloscUzytkownikow);
            else if (choice == '4')
                wyswietlKsiazke( uzytkownicy, iloscUzytkownikow);
            else if (choice == '5')
                usunPozycje (uzytkownicy, iloscUzytkownikow);
            else if (choice == '6')
                edytujAdresata(uzytkownicy, iloscUzytkownikow);
            else if (choice == '7')
                zmianaHasla(users, idUser);
            else if (choice == '8')
                idLoggedUser = 0;
        }
    }
    return 0;
}
