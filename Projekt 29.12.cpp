#include <iostream>
#include <string>
#include <windows.h>
#include <winbase.h>
#include <assert.h>
#include <cstdlib>
#include <fstream>
#include <limits>
#undef max
using namespace std;

string peselGlob;
string peselGlob2;

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
	string haslo;
	string zarezerwowanyTermin;
	void wczytajDane();
	void wyswietlDane(string pesel);
	static Pacjent logowanie();


};

class Lekarz : public Osoba
{
public:
	bool grafikLekarza[5][14];
	string haslo;
	string specjalizacja;
	int godzinaRozpoczeciaPracy;
	int godzinaZakonczeniaPracy;
	void wczytajDane();
	void wyswietlDane(string pesel);
	static Lekarz logowanie();
};

class KartaChorob
{
public:
	string diagnoza;
	string szczepienia;
	string dataOstatniejWizyty;
	void wyswietlKarteChorob(string pesel);
	void dodajKarteChorob(string pesel);
};

class Termin
{
public:
	string data;
	int godzina;
	bool zarezerwowany;
	void zarezerwujTermin();
	void wyswietlTerminy();
	void wyswietlDostLekarzy(string specjalizacja);
};

class Harmonogram
{
public:
	static void aktualizujGrafik(Lekarz*, int, int);
	static void wyswietlGrafikLekarza(Lekarz L);
	void aktualizujPrzyszleTerminy();
};

class Porada
{
public:
	void dodawanie_porady();
	void wyswPorady(Porada porada1);
	void wyswOdpowiedzi();

};

//FUNKCJE
void Porada::wyswOdpowiedzi()
{
	cout << "1.Nowe odpowiedzi \n2.Stare odpowiedzi" << endl;
	int odp;
	cout << "Wybor: "; 
	cin >> odp;
	cout << endl;
	int i = 0;
	if (odp == 1)
	{
		string nazwa = "internetowe";
		nazwa += peselGlob;
		nazwa += ".txt";
		string tekst;
		fstream Porady(nazwa.c_str());
		if (Porady)
		{
			while (!Porady.eof())
			{
				getline(Porady, tekst);

				if (!(string::npos == tekst.find("Odpowiedz lekarza: ")))
					i++;

			}
			Porady.close();

			if (i > 0)
			{
				Porady.open(nazwa.c_str(), ios::app | ios::in);
				cout << Porady.rdbuf();
				Porady.close();
				remove(nazwa.c_str());
			}

			else
				cout << "Brak nowych odpowiedzi" << endl;
		}

		else
			cout << "Nie masz oczekujacych odpowiedzi" << endl;
	}

	else if (odp == 2)
	{
		string nazwa2 = "internetoweS";

		nazwa2 += peselGlob;
		nazwa2 += ".txt";
		fstream starePorady(nazwa2.c_str());

		

		
		if (starePorady)
		{
			starePorady.open(nazwa2.c_str(), ios::app | ios::in);
			cout << starePorady.rdbuf();
			starePorady.close();
		}
		else
			cout << "Brak zapytan" << endl;
	}
	//fstream Porady;
}

void czyZarezerwowanyTermin(Termin t)
{
	assert(t.zarezerwowany == 1);
	cout << "zarezerwowany" << endl;
}

void Pacjent::wczytajDane()
{
	fstream DanePacjenci;
	fstream PacjenciPlik;
	PacjenciPlik.open("PlikZPacjentami.txt", ios::app | ios::in);
	DanePacjenci.open("WszystkieDane.txt", ios::app);

	cout << "Podaj pesel: ";

	getline(cin, pesel);
	string tekst;
	int i = 0;
	while (!PacjenciPlik.eof())
	{
		getline(PacjenciPlik, tekst);

		if (!(string::npos == tekst.find(pesel)))
			i = 1;

	}
	PacjenciPlik.close();

	if (i == 1)
	{
		cout << "Konto o takim peselu juz istnieje. Prawdopodobnie wpisales bledny pesel. Zarejestruj sie ponownie." << endl;
		Pacjent::wczytajDane();
	}
	else
	{
		PacjenciPlik.open("PlikZPacjentami.txt", ios::app);

		cout << "Podaj imie: ";
		getline(cin, this->imie);
		cout << "Podaj nazwisko: ";
		getline(cin, this->nazwisko);
		cout << "Podaj swoj adres: ";
		getline(cin, this->adres);
		cout << "Podaj haslo: ";
		cin >> this->haslo;
		PacjenciPlik << pesel << " ";
		PacjenciPlik << haslo << "\n";
		DanePacjenci << pesel << " ";
		DanePacjenci << "    " << "Imie: " << imie << "     ";
		DanePacjenci << "Nazwisko: " << nazwisko << "     ";
		DanePacjenci << "Adres: " << adres << " \n";

		DanePacjenci.close();
		PacjenciPlik.close();
	}
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
				break;
			}
			else
				cout << "Haslo jest niepoprawne!" << endl;
		}
	}

	if (PacjenciPlik.eof() && (!czyZnaleziono))
	{
		cout << "Bledne dane, wpisz ponownie\n";
		Sleep (2000);
		system("cls");
		logowanie();
	}
	PacjenciPlik.close();
	peselGlob = pesel1;
	Pacjent p;
	return p;
}

void Pacjent::wyswietlDane(string pesel)
{
	fstream DanePacjenci;
	DanePacjenci.open("WszystkieDane.txt");

	bool znal = 0;
	while (!DanePacjenci.eof())
	{
		string temp = "";
		getline(DanePacjenci, temp);
		for (int i = 0; i < pesel.size(); i++)
		{
			if (temp[i] == pesel[i])
				znal = 1;
			else
			{
				znal = 0;
				break;
			}
		}

		if (znal)
		{
			cout << "Pesel: ";
			for (int i = 0; i < temp.size(); i++)

				cout << temp[i];
			break;
			cout << "    ";
		}

	}

	if (DanePacjenci.eof() && (!znal))
	{
		cout << "Name not found!\n";
	}

	DanePacjenci.close();

}

void Lekarz::wczytajDane()
{
	fstream DaneLekarze;
	fstream LekarzePlik;
	LekarzePlik.open("PlikZLekarzami.txt", ios::app | ios::in);
	DaneLekarze.open("WszystkieDaneL.txt", ios::app);
	cout << "Podaj pesel: ";
	getline(cin, pesel);
	string tekst;
	int i = 0;
	while (!LekarzePlik.eof())
	{
		getline(LekarzePlik, tekst);

		if (!(string::npos == tekst.find(pesel)))
			i = 1;

	}
	LekarzePlik.close();

	if (i == 1)
	{
		cout << "Konto o takim peselu juz istnieje. Prawdopodobnie wpisales bledny pesel. Zarejestruj sie ponownie." << endl;
		Lekarz::wczytajDane();
	}
	else
	{
		LekarzePlik.open("PlikZLekarzami.txt", ios::app);

		cout << "Podaj imie: ";
		getline(cin, this->imie);
		cout << "Podaj nazwisko: ";
		getline(cin, this->nazwisko);
		cout << "Podaj swoj adres: ";
		getline(cin, this->adres);

		cout << "Podaj swoja specjalizacje lekarska: ";
		cin >> this->specjalizacja;
		cout << "Podaj godzine rozpoczecia pracy: ";
		cin >> this->godzinaRozpoczeciaPracy;
		cout << "Podaj godzine zakonczenia pracy: ";
		cin >> this->godzinaZakonczeniaPracy;
		cout << "Podaj haslo: ";
		cin >> this->haslo;
		LekarzePlik << pesel << " ";
		LekarzePlik << haslo << "\n";
		DaneLekarze << pesel << " ";
		DaneLekarze << "    " << "Imie: " << imie << "     ";
		DaneLekarze << "Nazwisko: " << nazwisko << "     ";
		DaneLekarze << "Adres: " << adres << "     ";
		DaneLekarze << "Specjalizacja: " << specjalizacja << "     ";
		DaneLekarze << "Godziny pracy: " << godzinaRozpoczeciaPracy << " - " << godzinaZakonczeniaPracy << " \n";
		DaneLekarze.close();
		LekarzePlik.close();

	}


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			this->grafikLekarza[i][j] = false;
		}
	}
}


Lekarz Lekarz::logowanie()
{
	string pesel2;
	cout << "Pesel: " << endl;
	cin >> pesel2;

	string haslo2;

	bool czyZnaleziono2 = 0;
	bool czyDobreHaslo2 = 0;
	string ZapisaneHaslo2;
	fstream LekarzePlik;

	LekarzePlik.open("PlikZLekarzami.txt");
	while (!LekarzePlik.eof())
	{
		string temp = "";
		getline(LekarzePlik, temp);

		for (int i = 0; i < pesel2.size(); i++)
		{
			if (temp[i] == pesel2[i])
				czyZnaleziono2 = 1;
			else
			{
				czyZnaleziono2 = 0;
				break;
			}
		}

		if (czyZnaleziono2)
		{
			cout << "Haslo: " << endl;
			cin >> haslo2;

			for (int i = pesel2.size() + 1; i < temp.size(); i++)
			{
				ZapisaneHaslo2 += temp[i];
			}
			if (ZapisaneHaslo2 == haslo2)
			{
				cout << "Haslo jest poprawne";
				Sleep(1000);
				system("cls");
				break;
			}
			else
				cout << "Haslo jest niepoprawne!" << endl;
		}
	}

	if (LekarzePlik.eof() && (!czyZnaleziono2))
	{
		cout << "Bledne dane, wpisz ponownie\n";
		Sleep (2000);
		system("cls");
		logowanie();
	}

	LekarzePlik.close();
	peselGlob2 = pesel2;
	Lekarz l;
	return l;
}

void Lekarz::wyswietlDane(string pesel)
{
	fstream DaneLekarze;
	DaneLekarze.open("WszystkieDaneL.txt");
	bool znal1 = 0;
	while (!DaneLekarze.eof())
	{
		string temp = "";
		getline(DaneLekarze, temp);
		for (int i = 0; i < pesel.size(); i++)
		{
			if (temp[i] == pesel[i])
				znal1 = 1;
			else
			{
				znal1 = 0;
				break;
			}
		}

		if (znal1)
		{
			cout << "Pesel: ";
			for (int i = 0; i < temp.size(); i++)

				cout << temp[i];
			break;
			cout << "    ";
		}

	}

	if (DaneLekarze.eof() && (!znal1))
	{
		cout << "Name not found!\n";
	}

	DaneLekarze.close();
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

void Porada::wyswPorady(Porada porada1)
{
	cout << "Oczekujace zapytania internetowe oraz recepty " << endl;

	system("cls");
	cout << "ZAPYTANIA INTERNETOWE" << endl;
	fstream Porady;
	fstream starePorady;
	string tresc;

	fstream PacjenciPlik;
	PacjenciPlik.open("PlikZPacjentami.txt");
	string slowo;

	cin.ignore();

	while (PacjenciPlik >> slowo)
	{
		string nazwa = "internetowe";
		PacjenciPlik.ignore(numeric_limits<streamsize>::max(), '\n');
		nazwa += slowo;
		nazwa += ".txt";

		Porady.open(nazwa.c_str(), ios::in);
		cout << Porady.rdbuf();
		Porady.close();
		Porady.open(nazwa.c_str(), ios::app);
		cout << "Odpowiedz: " << endl;
		getline(cin, tresc);
		cout << "\n";
		Porady << "Odpowiedz lekarza: " << tresc << endl;
		Porady.close();

		string nazwa2 = "internetoweS";
		PacjenciPlik.ignore(numeric_limits<streamsize>::max(), '\n');
		nazwa2 += slowo;
		nazwa2 += ".txt";

		starePorady.open(nazwa2.c_str(), ios::app);

		starePorady << "Odpowiedz lekarza: " << tresc << endl;
		starePorady.close();
	}

	PacjenciPlik.close();
}


void Porada::dodawanie_porady()
{
	SYSTEMTIME st;
	GetSystemTime(&st);

	cout << "Dodaj zapytanie internetowe lub recepte oczekujaca" << endl;

	system("cls");
	fstream Porady;

	fstream starePorady;
	string nazwa = "internetowe";
	string nazwa2 = "internetoweS";

	nazwa += peselGlob;
	nazwa += ".txt";
	nazwa2 += peselGlob;
	nazwa2 += ".txt";

	Porady.open(nazwa.c_str(), ios::app);
	starePorady.open(nazwa2.c_str(), ios::app);
	cout << "DODAWANIE ZAPYTANIA INTERNETOWEGO" << endl;
	cout << "Podaj tresc: ";
	string trescZapytania;
	cin.ignore();
	getline(cin, trescZapytania);
	Porady << trescZapytania << "  ";
	starePorady << trescZapytania << "  ";

	cout << "Data dodania: ";
	cout << st.wDay << "." << st.wMonth << "." << st.wYear << endl;
	cout << "Godzina dodania: ";

	cout << st.wHour << ":";
	if (st.wMinute < 10)
		cout << "0" << st.wMinute << ":";
	else
		cout << st.wMinute << ":";
	if (st.wSecond < 10)
		cout << "0" << st.wSecond << endl;
	else
		cout << st.wSecond << endl;
	Porady << "\nData dodania: " << st.wDay << "." << st.wMonth << "." << st.wYear << "  ";
	Porady << "Godzina dodania: " << st.wHour << ":";
	if (st.wMinute < 10)
		Porady << "0" << st.wMinute << ":";
	else
		Porady << st.wMinute << ":";
	if (st.wSecond < 10)
		Porady << "0" << st.wSecond << endl;
	else
		Porady << st.wSecond << endl;

	starePorady << "\nData dodania: " << st.wDay << "." << st.wMonth << "." << st.wYear << "  ";
	starePorady << "Godzina dodania: " << st.wHour << ":";
	if (st.wMinute < 10)
		starePorady << "0" << st.wMinute << ":";
	else
		starePorady << st.wMinute << ":";
	if (st.wSecond < 10)
		starePorady << "0" << st.wSecond << endl;
	else
		starePorady << st.wSecond << endl;
}

void KartaChorob::dodajKarteChorob(string pesel)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	fstream KartyChorob;

	string nazwa = "kartyChorob";

	nazwa += pesel;
	nazwa += ".txt";

	KartyChorob.open(nazwa.c_str(), ios::app);
	cout << "EDYTOWANIE KARTY CHOROB" << endl;
	string diagnoza;
	string szczepienia;
	string dataOstatniejChoroby;
	cin.ignore();
	KartyChorob << "Pesel: " << pesel << "  ";
	cout << "Podaj diagnoze: ";
	getline(cin, diagnoza);
	KartyChorob << "Diagnoza: " << diagnoza << "  ";
	cout << "Podaj wykonane szczepienia: ";
	getline(cin, szczepienia);
	KartyChorob << "Szczepienia: " << szczepienia << "  ";

	cout << "Data ostatniej wizyty: ";
	cout << st.wDay << "." << st.wMonth << "." << st.wYear << endl;
	KartyChorob << "Data ostatniej wizyty: " << st.wDay << "." << st.wMonth << "." << st.wYear << " " << "\n";
}

void KartaChorob::wyswietlKarteChorob(string pesel)
{
	system("cls");
	string nazwa = "kartyChorob" + pesel + ".txt";
	cout << "KARTA CHOROB" << endl;
	fstream KartyChorob(nazwa.c_str());


	if (KartyChorob)
	{
		KartyChorob.open(nazwa.c_str(), ios::in);
		cout << KartyChorob.rdbuf();
		KartyChorob.close();
	}

	else
		cout << "Karta chorob jest obecnie pusta" << endl;
}






//MAIN
int main()
{
	Porada porada;
	KartaChorob kartaChorob;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "\t" << "PRZYCHODNIA LEKARSKA";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	Sleep(1000);
	system("cls");
	int w1=0;
	while(w1!=3)
	{
		cout << "WYBIERZ:" << endl;
		cout << "------------------" << endl;
		cout << "1. Zarejestruj " << endl;
		cout << "2. Zaloguj" << endl;
		cout << "3. Zakoncz program" << endl;
		cout << "------------------" << endl;
		cout << "Wybor: ";
		cin >> w1;
		system("cls");
		if (w1!=3)
		{
			int wybor;
			cout << "JAKO:" << endl;
			cout << "-------------" << endl;
			cout << "1. Lekarz " << endl;
			cout << "2. Pacjent" << endl;
			cout << "-------------" << endl;
			cout << "Wybor: ";
			cin >> wybor;
			system("cls");
			Lekarz l;
			Pacjent p;

			if (w1 == 1)
			{
				if (wybor == 1)
				{
					cin.ignore();
					l.wczytajDane();
				}
				else if (wybor == 2)
				{
					cin.ignore();
					p.wczytajDane();
				}

			}

			int nr = 0;

			switch (wybor)
			{
			case 1:
			{
				system("cls");
				cout << endl << "WITAJ LEKARZU";
				Sleep(1000);
				system("cls");
				cout << "---------" << endl;
				cout << "LOGOWANIE" << endl;
				cout << "---------" << endl;
				l.logowanie();
		
				while (nr != 4)
				{
					cout << "\tMENU" << endl;
					cout << "-----------------------------" << endl;
					cout << "1. Wyswietl swoje dane " << endl;
					cout << "2. Wyswietl porady oczekujace" << endl;
					cout << "3. Edytuj karte pacjenta" << endl;
					cout << "4. Wyloguj" << endl;
					cout << "-----------------------------" << endl;
					cout << "Wybor: ";
					cin >> nr;
					system("cls");
					switch (nr)
					{
					case 1:
					{
						int w = 0;
						while (w != 1)
						{
							cout << "\t" << "TWOJE DANE" << endl;
							l.wyswietlDane(peselGlob2);
							cout << endl << endl << "1. Powrot do menu " << endl;
							cout << "Wybor: ";
							cin >> w;
						}
						break;
					}
					case 2:
					{
						porada.wyswPorady(porada);
						Sleep(2000);
						break;
					}
					case 3:
					{
						string pesel;
						cout << "Podaj pesel pacjenta: ";
						cin >> pesel;
						system("cls");
						kartaChorob.dodajKarteChorob(pesel);
						Sleep(2000);
						break;
					}
					}
					system("cls");
				}
				cout << "\t" << "WYLOGOWANO";
				break;
			}

			case 2:
			{
				system("cls");
				cout << endl << "WITAJ PACJENCIE";
				Sleep(1000);
				system("cls");

				cout << "---------" << endl;
				cout << "LOGOWANIE" << endl;
				cout << "---------" << endl;
				p.logowanie();

				while (nr != 5)
				{
					system("cls");
					cout << "\tMENU" << endl;
					cout << "--------------------------------" << endl;
					cout << "1. Wyswietl swoje dane " << endl;
					cout << "2. Dodaj porade oczekujaca" << endl;
					cout << "3. Wyswietl swoje zapytania" << endl;
					cout << "4. Wyswietl swoja karte chorob" << endl;
					cout << "5. Wyloguj" << endl;
					cout << "--------------------------------" << endl;
					cout << "Wybor: ";
					cin >> nr;
					system("cls");
					switch (nr)
					{
					case 1:
					{
						int w = 0;
						while (w != 1)
						{
							cout << "\t" << "TWOJE DANE" << endl;
							p.wyswietlDane(peselGlob);
							cout << endl << endl << "1. Powrot do menu " << endl;
							cout << "Wybor: ";
							cin >> w;
						}
						break;
					}
					case 2:
					{
				
							porada.dodawanie_porady();
							Sleep(2000);
						break;
					}
					case 3:
					{
						int w = 0;
						while (w != 1)
						{
						porada.wyswOdpowiedzi();
						cout << endl << endl << "1. Powrot do menu " << endl;
						cout << "Wybor: ";
						cin >> w;
						}
						break;
					}
					case 4:
					{
						int w = 0;
						while (w != 1)
						{
							kartaChorob.wyswietlKarteChorob(peselGlob);
							cout << endl << endl << "1. Powrot do menu " << endl;
							cout << "Wybor: ";
							cin >> w;
						}
						break;
					}
					}
					system("cls");
				}
				cout << "\t" << "WYLOGOWANO";
				break;
			}
			}
		}
	}
}
