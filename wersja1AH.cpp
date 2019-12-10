#include <iostream> 
#include <windows.h> 
#include <assert.h>
#include <string>
#include <cstdlib>
using namespace std;

class Osoba
{
public:
	string imie;
	string nazwisko;
	string adres;
	long int pesel;
};

class Lekarz :public Osoba
{
public:
	bool grafikLekarza[5][14];
	string specjalizacja;
	int godzinaRozpoczeciaPracy;
	int godzinaZakonczeniaPracy;
	void wczytajDane();
	void wyswietlDane();
	class Lekarz nowyLekarz(Osoba L1);
	void wypiszRecepte();
	void udzielPoradyInt();
};


class Harmonogram
{
public:
	
	static void aktualizujGrafik(Lekarz*,int,int);
	static void wyswietlGrafikLekarza(Lekarz L);
	void wyswietlZapytaniaInt();
	void wyswietlReceptyOczek();
	void aktualizujPrzyszleTerminy();
};



void Lekarz::wczytajDane()
{
	cout << "Podaj imie: ";
	cin >> this->imie;
	cout << "Podaj nazwisko: ";
	cin >> this->nazwisko;
	cout << "Podaj swoj adres: ";
	cin >> this->adres;
	cout << "Podaj pesel: ";
	cin >> this->pesel;
	cout << "Podaj swoja specjalizacje lekarska: ";
	cin >> this->specjalizacja;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			this->grafikLekarza[i][j] = false;
		}

	}
	
	cout << "Podaj godzine rozpoczecia pracy: ";
	cin >> this->godzinaRozpoczeciaPracy;
	cout << "Podaj godzine zakonczenia pracy: ";
	cin >> this->godzinaZakonczeniaPracy;
}

void Lekarz::wyswietlDane()
{
	cout << "Imie: " << this->imie << endl;
	cout << "Nazwisko: " << this->nazwisko << endl;
	cout << "Adres: " << this->adres << endl;
	cout << "Pesel: " << this->pesel << endl;
	cout << "Specjalizacja lekarska: " << this->specjalizacja << endl;
}

void Harmonogram::wyswietlGrafikLekarza(Lekarz L)

{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << endl<<"Harmonogram lekarza " << L.imie << " " << L.nazwisko << endl;
	cout << endl<<"Poniedziałek:"<<endl;
		for (int i = 6; i < 20; i++)
		{
			if (L.godzinaRozpoczeciaPracy <= i && L.godzinaZakonczeniaPracy-1 >= i)
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

void Harmonogram::aktualizujGrafik(Lekarz* L,int dzien,int godzina)
{
	L->grafikLekarza[dzien - 1][godzina - 6] = true;


}

int main()
{
	Harmonogram h;
	Lekarz wilk;
	wilk.wczytajDane();
	Harmonogram::aktualizujGrafik(&wilk, 1, 10);
	Harmonogram::aktualizujGrafik(&wilk, 1, 13);
	Harmonogram::wyswietlGrafikLekarza(wilk);

	
}

