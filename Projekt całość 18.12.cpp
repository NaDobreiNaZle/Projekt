#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <winbase.h>
#include <assert.h>
#include <cstdlib>
#include <fstream>
using namespace std;

									//KLASY
class Osoba
{
public:
	string imie;
	string nazwisko;
	string adres;
	string pesel;
};


class Pacjent : public Osoba
{
public:
	friend class Dane;
	string haslo;
	string zarezerwowanyTermin;
	void wczytajDane();
	void wyswietlDane();
	static Pacjent logowanie();
	Pacjent()
	{
		wczytajDane();
		
	}
};

class Lekarz : public Osoba
{
public:
	friend class Dane;
	bool grafikLekarza[5][14];
	string haslo;
	string specjalizacja;
	int godzinaRozpoczeciaPracy;
	int godzinaZakonczeniaPracy;
	void wczytajDane();
	void wyswietlDane();
	static Lekarz logowanie();
	void wypiszRecepte();
	void udzielPoradyInt();
	Lekarz()
	{
		wczytajDane();
	}
};

class Dane
{
public:
	friend class Pacjent;
	friend class Lekarz;
	//this->imie, this->nazwisko, this->adres, this->pesel, this->haslo
	vector < Pacjent > ZbiorPacjentow;
	vector < Lekarz > ZbiorLekarzy;
};

class KartaChorob
{
public:
	string diagnoza;
	string szczepienia;
	string dataOstatniejChoroby;
	void wyswietlKarteChorob(Pacjent P);
};

class Termin
{
public:
	string data;
	int godzina;
	bool zarezerwowany;
	void zarezerwujTermin();
	//{
		//aktualizujgrafik(wybrany termin);
	//}
	void wyswietlTerminy();
	void wyswietlDostLekarzy(string specjalizacja);
};

class Harmonogram
{
public:
	static void aktualizujGrafik(Lekarz*, int, int);
	static void wyswietlGrafikLekarza(Lekarz L);
	void wyswietlZapytaniaInt();
	void wyswietlReceptyOczek();
	void aktualizujPrzyszleTerminy();
};

class ZapytanieInt
{
public:
	friend class Porada;
	string tresc;
	string specjalizacja;
	int dzien;
	int miesiac;
	int rok;
	int godzina;
	int minuta;
	int sekunda;
	ZapytanieInt(string trescZ, string specjalizacjaZ, int dzienZ, int miesiacZ, int rokZ, int godzinaZ, int minutaZ, int sekundaZ);

};

class Recepta
{
public:
	friend class Porada;
	string tresc;
	string data;
	int dzien;
	int miesiac;
	int rok;
	int godzina;
	int minuta;
	int sekunda;
	Recepta(string trescR, int dzienR, int miesiacR, int rokR, int godzinaR, int minutaR, int sekundaR);
};

class Porada
{
public:
	int koszt;
	string typ;
	friend class Recepta;
	friend class ZapytanieInt;
	void dodawanie_porady();
	vector < Recepta > ReceptyOczekujace;
	vector < ZapytanieInt > ZapytaniaOczekujace;
	void wyswPorady(Porada porada1);

};

											//FUNKCJE
void czyZarezerwowanyTermin(Termin t)
{
	assert(t.zarezerwowany == 1);
	cout << "zarezerwowany" << endl;
}

void Pacjent::wczytajDane()
{
	fstream PacjenciPlik;
	PacjenciPlik.open("PlikZPacjentami.txt", ios::app);
    cout << "Podaj imie: ";
    cin.ignore();
    getline(cin, this -> imie);
    cout << "Podaj nazwisko: ";
    getline(cin, this->nazwisko);
    cout << "Podaj swoj adres: ";
    getline(cin, this->adres);
    cout << "Podaj pesel: ";
    cin >> this->pesel;
    cout << "Podaj haslo: ";
    cin >> this->haslo;
    PacjenciPlik << pesel << " ";
    PacjenciPlik << haslo << "\n";
    PacjenciPlik.close();
}

void Pacjent::wyswietlDane()
{
	cout << "Imie: " << this->imie << endl;
	cout << "Nazwisko: " << this->nazwisko << endl;
	cout << "Adres: " << this->adres << endl;
	cout << "Pesel: " << this->pesel << endl;
}

Pacjent Pacjent::logowanie()
{
	string pesel1;
	cout << "Pesel: " << endl;
	cin >> pesel1;

	string haslo1;

	bool czyZnaleziono = 0;
	bool czyDobreHaslo = 0;
	string ZapisaneHaslo;
	fstream PacjenciPlik;

	PacjenciPlik.open("PlikZPacjentami.txt");
	while (!PacjenciPlik.eof())
	{
		string temp = "";
		getline(PacjenciPlik, temp);

		for (int i = 0; i < pesel1.size(); i++)
		{
			if (temp[i] == pesel1[i])
				czyZnaleziono = 1;
			else
			{
				czyZnaleziono = 0;
				break;
			}
		}	

		if (czyZnaleziono)
		{
			cout << "Haslo: " << endl;
			cin >> haslo1;

			for (int i = pesel1.size() + 1; i < temp.size(); i++)
			{
				ZapisaneHaslo += temp[i];
			}
			if (ZapisaneHaslo == haslo1)
			{
				cout << "Haslo jest poprawne";
				Sleep(1000);
				system("cls");
				//return p;
				//trzeba sprawdzic dla jakiego obiektu zostal wisany pesel 
				//for (
				// if (pesel1==p.pesel)
				//Pacjent p;
				 //return p;
			}
			else
				cout << "Haslo jest niepoprawne!" << endl;
		}
	}

	if (PacjenciPlik.eof() && (!czyZnaleziono))
		cout << "Bledne dane, wpisz ponownie lub zarejestruj sie!\n";
	PacjenciPlik.close();
}

/*void czyWpisanoDanePacjenta(Pacjent p)
{
	assert(p.imie != "");
	cout << "Wpisano imie" << endl;
	assert(p.nazwisko != "");
	cout << "Wpisano nazwisko" << endl;
	assert(p.adres != "");
	cout << "Wpisano adres" << endl;
	assert(p.pesel != 0);
	cout << "Wpisano pesel" << endl;
}*/

void Lekarz::wczytajDane()
{
	fstream LekarzePlik;
	LekarzePlik.open("PlikZLekarzami.txt", ios::app);
    cout << "Podaj imie: ";
    cin.ignore();
    getline(cin, this -> imie);
    cout << "Podaj nazwisko: ";
    getline(cin, this->nazwisko);
    cout << "Podaj swoj adres: ";
    getline(cin, this->adres);
    cout << "Podaj pesel: ";
    cin >> this->pesel;
    cout << "Podaj haslo: ";
    cin >> this->haslo;
    LekarzePlik << pesel << " ";
    LekarzePlik << haslo << "\n";
    LekarzePlik.close();
    cout << "Podaj swoja specjalizacje lekarska: ";
	cin>>this->specjalizacja;
	cout << "Podaj godzine rozpoczecia pracy: ";
	cin>> this->godzinaRozpoczeciaPracy;
	cout << "Podaj godzine zakonczenia pracy: ";
	cin>> this->godzinaZakonczeniaPracy;
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			this->grafikLekarza[i][j] = false;
		}
	}
}

void Lekarz::wyswietlDane()
{
	cout << "Imie: " << this->imie << endl;
	cout << "Nazwisko: " << this->nazwisko << endl;
	cout << "Adres: " << this->adres << endl;
	cout << "Pesel: " << this->pesel << endl;
	cout << "Specjalizacja lekarska: " << this->specjalizacja << endl;
	cout << "Godzina rozpoczecia pracy: " << this->godzinaRozpoczeciaPracy << endl;
	cout << "Godzina zakonczenia pracy: " << this->godzinaZakonczeniaPracy << endl;
}

Lekarz Lekarz::logowanie()
{
	string pesel1;
	cout << "Pesel: " << endl;
	cin >> pesel1;

	string haslo1;

	bool czyZnaleziono = 0;
	bool czyDobreHaslo = 0;
	string ZapisaneHaslo;
	fstream LekarzePlik;

	LekarzePlik.open("PlikZLekarzami.txt");
	while (!LekarzePlik.eof())
	{
		string temp = "";
		getline(LekarzePlik, temp);

		for (int i = 0; i < pesel1.size(); i++)
		{
			if (temp[i] == pesel1[i])
				czyZnaleziono = 1;
			else
			{
				czyZnaleziono = 0;
				break;
			}
		}	

		if (czyZnaleziono)
		{
			cout << "Haslo: " << endl;
			cin >> haslo1;

			for (int i = pesel1.size() + 1; i < temp.size(); i++)
			{
				ZapisaneHaslo += temp[i];
			}
			if (ZapisaneHaslo == haslo1)
			{
				cout << "Haslo jest poprawne";
				Sleep(1000);
				system("cls");
				//return l;
				//trzeba sprawdzic dla jakiego obiektu zostal wisany pesel 
				//for (
				// if (pesel1==l.pesel)
				//Lekarz l;
				 //return l;
			}
			else
				cout << "Haslo jest niepoprawne!" << endl;
		}
	}

	if (LekarzePlik.eof() && (!czyZnaleziono))
		cout << "Bledne dane, wpisz ponownie lub zarejestruj sie!\n";
	LekarzePlik.close();
}

void Harmonogram::wyswietlGrafikLekarza(Lekarz L)

{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << endl << "Harmonogram lekarza " << L.imie << " " << L.nazwisko << endl;
	cout << endl << "Poniedzia3ek:" << endl;
	for (int i = 6; i < 20; i++)
	{
		if (L.godzinaRozpoczeciaPracy <= i && L.godzinaZakonczeniaPracy - 1 >= i)
		{
			cout << "Godzina " << i;
			if (L.grafikLekarza[0][i - 6] == false)
			{

				SetConsoleTextAttribute(kolor, 2);
				cout << " DOSTEPNY" << endl;
				SetConsoleTextAttribute(kolor, 7);
			}
			else
			{
				SetConsoleTextAttribute(kolor, 4);
				cout << " ZAJETY" << endl;
				SetConsoleTextAttribute(kolor, 7);
			}
		}
	}

	cout << endl << "Wtorek:" << endl;
	for (int i = 6; i < 20; i++)
	{
		if (L.godzinaRozpoczeciaPracy <= i && L.godzinaZakonczeniaPracy - 1 >= i)
		{
			cout << "Godzina " << i;
			if (L.grafikLekarza[1][i - 6] == false)
			{
				SetConsoleTextAttribute(kolor, 2);
				cout << " DOSTEPNY" << endl;
				SetConsoleTextAttribute(kolor, 7);
			}
			else
			{
				SetConsoleTextAttribute(kolor, 4);
				cout << " ZAJETY" << endl;
				SetConsoleTextAttribute(kolor, 7);
			}
		}
	}
	cout << endl << "Sroda:" << endl;
	for (int i = 6; i < 20; i++)
	{
		if (L.godzinaRozpoczeciaPracy <= i && L.godzinaZakonczeniaPracy - 1 >= i)
		{
			cout << "Godzina " << i;
			if (L.grafikLekarza[2][i - 6] == false)
			{
				SetConsoleTextAttribute(kolor, 2);
				cout << " DOSTEPNY" << endl;
				SetConsoleTextAttribute(kolor, 7);
			}
			else
			{
				SetConsoleTextAttribute(kolor, 4);
				cout << " ZAJETY" << endl;
				SetConsoleTextAttribute(kolor, 7);

			}

		}
	}
	cout << endl << "Czwartek:" << endl;
	for (int i = 6; i < 20; i++)
	{
		if (L.godzinaRozpoczeciaPracy <= i && L.godzinaZakonczeniaPracy - 1 >= i)
		{
			cout << "Godzina " << i;
			if (L.grafikLekarza[3][i - 6] == false)
			{
				SetConsoleTextAttribute(kolor, 2);
				cout << " DOSTEPNY" << endl;
				SetConsoleTextAttribute(kolor, 7);
			}
			else
			{
				SetConsoleTextAttribute(kolor, 4);
				cout << " ZAJETY" << endl;
				SetConsoleTextAttribute(kolor, 7);

			}
		}
	}
	cout << endl << "Piatek:" << endl;
	for (int i = 6; i < 20; i++)
	{
		if (L.godzinaRozpoczeciaPracy <= i && L.godzinaZakonczeniaPracy - 1 >= i)
		{
			cout << "Godzina " << i;
			if (L.grafikLekarza[4][i - 6] == false)
			{
				SetConsoleTextAttribute(kolor, 2);
				cout << " DOSTEPNY" << endl;
				SetConsoleTextAttribute(kolor, 7);
			}
			else
			{
				SetConsoleTextAttribute(kolor, 4);
				cout << " ZAJETY" << endl;
				SetConsoleTextAttribute(kolor, 7);

			}
		}
	}
}

void Harmonogram::aktualizujGrafik(Lekarz* L, int dzien, int godzina)
{
	L->grafikLekarza[dzien - 1][godzina - 6] = true;


}

ZapytanieInt::ZapytanieInt(string trescZ, string specjalizacjaZ, int dzienZ, int miesiacZ, int rokZ, int godzinaZ, int minutaZ, int sekundaZ)
{
	tresc = trescZ;
	specjalizacja = specjalizacjaZ;
	dzien = dzienZ;
	miesiac = miesiacZ;
	rok = rokZ;
	godzina = godzinaZ;
	minuta = minutaZ;
	sekunda = sekundaZ;
}

Recepta::Recepta(string trescR, int dzienR, int miesiacR, int rokR, int godzinaR, int minutaR, int sekundaR)
{
	tresc = trescR;
	dzien = dzienR;
	miesiac = miesiacR;
	rok = rokR;
	godzina = godzinaR;
	minuta = minutaR;
	sekunda = sekundaR;
}

void Porada::wyswPorady(Porada porada1)
{
	cout << "1.Oczekujace zapytania internetowe \n2.Oczekujace recepty " << endl;
	int odp2;
	cin >> odp2;

	if (odp2 == 1)
	{
		system("cls");
		cout << "ZAPYTANIA INTERNETOWE" << endl;

		for (int i = 0; i < porada1.ZapytaniaOczekujace.size(); i++)
		{
			cout << endl;
			cout << "Tresc: " << porada1.ZapytaniaOczekujace[i].tresc << endl;
			cout << "specjalziacja: " << porada1.ZapytaniaOczekujace[i].specjalizacja << endl;
			cout << "Data dodania: " << porada1.ZapytaniaOczekujace[i].dzien << "." << porada1.ZapytaniaOczekujace[i].miesiac << "." << porada1.ZapytaniaOczekujace[i].rok << endl;
			cout << "Godzina dodania: " << porada1.ZapytaniaOczekujace[i].godzina << ":" << porada1.ZapytaniaOczekujace[i].minuta << ":" << porada1.ZapytaniaOczekujace[i].sekunda << endl;
		}
	}
	
	else if (odp2 == 2)
	{
		system("cls");
		cout << "RECEPTY" << endl;
		for (int i = 0; i < porada1.ReceptyOczekujace.size(); i++)
		{
			cout << endl;
			cout << "Tresc: " << porada1.ReceptyOczekujace[i].tresc << endl;
			cout << "Data dodania: " << porada1.ReceptyOczekujace[i].dzien << "." << porada1.ReceptyOczekujace[i].miesiac << "." << porada1.ReceptyOczekujace[i].rok << endl;
			cout << "Godzina dodania: " << porada1.ReceptyOczekujace[i].godzina << ":" << porada1.ReceptyOczekujace[i].minuta << ":" << porada1.ReceptyOczekujace[i].sekunda << endl;
		}
	}
}

void Porada::dodawanie_porady()
{
	SYSTEMTIME st;
	GetSystemTime(&st);

	cout << "1.Dodaj zapytanie internetowe \n2.Dodaj recepte oczekujaca" << endl;
	int odp;
	cin >> odp;

	if (odp == 1)
	{
		system("cls");
		cout << "DODAWANIE ZAPYTANIA INTERNETOWEGO" << endl;
		cout << "Podaj tresc: ";
		string trescZapytania;
		cin >> trescZapytania;
		cout << "Podaj specjalizacje :";
		string specZapytania;
		cin >> specZapytania;
		cout << "Data dodania: ";
		cout << st.wDay << "." << st.wMonth << "." << st.wYear << endl;
		cout << "Godzina dodania: ";
		cout << st.wHour << ":" << st.wMinute << ":" << st.wSecond << endl;
		ZapytaniaOczekujace.push_back(ZapytanieInt(trescZapytania, specZapytania, st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond));

	}
	else if (odp == 2)
	{
		system("cls");
		cout << "DODAWANIE RECEPTY" << endl;
		cout << "Podaj tresc: ";
		string trescRecepty;
		cin >> trescRecepty;
		cout << "Data dodania: ";
		cout << st.wDay << "." << st.wMonth << "." << st.wYear << endl;
		cout << "Godzina dodania: ";
		cout << st.wHour << ":" << st.wMinute << ":" << st.wSecond << endl;
		ReceptyOczekujace.push_back(Recepta(trescRecepty, st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond));

	}
}

												//MAIN
int main()
{
	Porada porada;
	
	//Recepta tablicaRecept[10];
//	for (int i = 0; i < 10; i++)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "\t" << "PRZYCHODNIA LEKARSKA";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	Sleep(1000);
	system("cls");
	cout << "WYBIERZ:" << endl;
	cout << "-------------" << endl;
	cout << "1. Zarejestruj " << endl;
	cout << "2. Zaloguj" << endl;
	cout << "-------------" << endl;
	cout << "Wybor: ";
	int w1;
	cin >> w1;
	system("cls");
	int wybor;
	cout << "JAKO:" << endl;
	cout << "-------------" << endl;
	cout << "1. Lekarz " << endl;
	cout << "2. Pacjent" << endl;
	cout << "-------------" << endl;
	cout << "Wybor: ";
	cin >> wybor;
	system("cls");	
	
	if(w1==1)
	{
		if(wybor==1)
			Lekarz l;
		else if(wybor==2)
			Pacjent p;
	}
						
	
	switch (wybor)
	{
		case 1:
		{
			system("cls");
			cout << endl << "WITAJ LEKARZU";
			Sleep(1000);
			system("cls");
			cout<<"---------" << endl;
			cout<<"LOGOWANIE"<<endl;
			cout<<"---------" << endl;
			Lekarz l=Lekarz::logowanie();

			cout << "\tMENU" << endl;
			cout << "-----------------------------" << endl;
			cout << "1. Wyswietl swoje dane " << endl;
			cout << "2. Wyswietl porady oczekujace" << endl;
			cout << "-----------------------------" << endl;
			cout << "Wybor: ";
			int nr1;
			cin >> nr1;
			
			switch (nr1)
			{
				case 1:
				{
					cout << "\t" << "TWOJE DANE" << endl;
					l.wyswietlDane();
					break;
				}
				case 2:
				{
					system("cls");
					porada.wyswPorady(porada);
					break;
				}
			}
			break;
		}
	
		case 2:
		{
			system("cls");
			cout << endl << "WITAJ PACJENCIE";
			Sleep(1000);
			system("cls");
			
			cout<<"---------" << endl;
			cout<<"LOGOWANIE"<<endl;
			cout<<"---------" << endl;
			Pacjent p=Pacjent::logowanie();

			system("cls");
			cout << "\tMENU" << endl;
			cout << "--------------------------" << endl;
			cout << "1. Wyswietl swoje dane " << endl;
			cout << "2. Dodaj porade oczekujaca" << endl;
			cout << "--------------------------" << endl;
			cout << "Wybor: ";
			int nr2;
			cin >> nr2;
			
			switch (nr2)
			{
				case 1:
				{
					cout << "\t" << "TWOJE DANE" << endl;
					p.wyswietlDane();
					break;
				}
				case 2:
				{
					system("cls");
					porada.dodawanie_porady();
					break;
				}
			}
			break;
		}

	}
}

