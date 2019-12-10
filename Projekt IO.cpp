#include <iostream> 
#include <windows.h> 
#include <assert.h>
#include <string>
using namespace std;


class Osoba
{
public:
	string imie;
	string nazwisko;
	string adres;
	long int pesel;
};

class Pacjent : public Osoba
{
public:
	string haslo;
	//zrobic funkcje zmiany hasla
	string zarezerwowanyTermin;
	void wczytajDane();
	void wyswietlDane();
	Pacjent()
	{
		wczytajDane();
	}
};


class Lekarz : public Osoba
{
public:
	string haslo;
	//zrobic funkcje zmiany hasla
	string specjalizacja;
	int godzinaRozpoczeciaPracy;
	int godzinaZakonczeniaPracy;
	void wczytajDane();
	void wyswietlDane();
	void wypiszRecepte();
	void udzielPoradyInt();
	Lekarz()
	{
		wczytajDane();
	}
};


class KartaChorob
{public:
	string diagnoza;
	string szczepienia;
	string dataOstatniejChoroby;
	void wyswietlKarteChorob(Pacjent P);
};

class Porada
{public:
	int koszt;
	string typ;
	void dodaniePorady(string specjalizacja);
	string dodanieZapytaniaInt();
	bool zatwierdzeniePorady();
	string dodanieReceptyOczek();
	string wyborTypu();
};

class Rejestracja
{
public:
	void sprawdzenieDanych();
	bool potwierdzeniePlatnosci();
};


class Recepta : public Porada 
{
public:
	string tresc;
	string data;
};

class ZapytanieInt : public Porada 
{
public:
	string tresc;
	string data;
};

class Cennik
{
public:
	int poradaOgolna;
	int dentysta;
	int laryngolog;
	int dermatolog;
	int ortodonta;
	int kardiolog;
	int neurolog;
	int psycholog;
	int okulista;
	void wyswietlCennik();
};


class Termin
{public:
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
{public:
	bool grafikLekarza[5][14];
	static void aktualizujGrafik();
	void wyswietlGrafikLekarza(Lekarz L);
	static void wyswietlZapytaniaInt();
	static void wyswietlReceptyOczek();
	void aktualizujPrzyszleTerminy();
};

void czyZarezerwowanyTermin(Termin t)
{
	assert(t.zarezerwowany == 1);
	cout << "zarezerwowany" << endl;
}

void Pacjent::wczytajDane()
{
	cout<<"Podaj imie: ";
	cin>>this->imie;
	cout<<"Podaj nazwisko: ";
	cin>>this->nazwisko;
	cout<<"Podaj swoj adres: ";
	cin>>this->adres;
	cout<<"Podaj pesel: ";
	cin>>this->pesel;
}

void Pacjent::wyswietlDane()
{
	cout<<"Imie: "<<this->imie<<endl;
	cout<<"Nazwisko: "<<this->nazwisko<<endl;
	cout<<"Adres: "<<this->adres<<endl;
	cout<<"Pesel: "<<this->pesel<<endl;
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
	cout<<"Podaj imie: ";
	cin>>this->imie;
	cout<<"Podaj nazwisko: ";
	cin>>this->nazwisko;
	cout<<"Podaj swoj adres: ";
	cin>>this->adres;
	cout<<"Podaj pesel: ";
	cin>>this->pesel;
	cout<<"Podaj swoja specjalizacje lekarska: ";
	cin>>this->specjalizacja;
	cout<<"Podaj godzine rozpoczecia pracy: ";
	cin>>this->godzinaRozpoczeciaPracy;
	cout<<"Podaj godzine zakonczenia pracy: ";
	cin>>this->godzinaZakonczeniaPracy;
}

void Lekarz::wyswietlDane()
{
	cout<<"Imie: "<<this->imie<<endl;
	cout<<"Nazwisko: "<<this->nazwisko<<endl;
	cout<<"Adres: "<<this->adres<<endl;
	cout<<"Pesel: "<<this->pesel<<endl;
	cout<<"Specjalizacja lekarska: "<<this->specjalizacja<<endl;
}

/*
void czyWpisanoDaneLekarza(Lekarz l)
{
	assert(l.imie != "");
	cout << "Wpisano imie" << endl;
	assert(l.nazwisko != "");
	cout << "Wpisano nazwisko" << endl;
	assert(l.adres != "");
	cout << "Wpisano adres" << endl;
	assert(l.pesel != 0);
	cout << "Wpisano pesel" << endl;
	assert(l.specjalizacja != "");
	cout << "Wpisano specjalizacje" << endl;
}
*/

void Lekarz::wypiszRecepte()
{
//	Harmonogram::wyswietlReceptyOczek();
	// jak wybrac ktora recepta
}



int main()
{
	int wybor;
	Recepta tablicaRecept[10];
	for(int i=0;i<10;i++)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout <<"\t"<< "PRZYCHODNIA LEKARSKA";
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    Sleep(1000);
    system("cls"); 
    cout<<"ZALOGUJ JAKO:"<<endl;
    cout << "-------------" << endl;
    cout << "1. Lekarz " << endl;
    cout << "2. Pacjent" << endl;
    cout << "-------------" << endl;
    cout<<"Wybor: ";
    cin>>wybor; 
    system("cls"); 
    switch(wybor)
    {
    	case 1:
    		{
    		cout<<endl<<"WITAJ LEKARZU";
    		Sleep(1000);
    		system("cls"); 
    		Lekarz l;
    		l.wczytajDane();
    		system("cls");
    		cout<<"\t"<<"TWOJE DANE"<<endl;
    		l.wyswietlDane();
    		break;
    		}
    	case 2:
    		{
    		cout<<endl<<"WITAJ PACJENCIE";
    		Sleep(1000);
    		system("cls"); 
    		Pacjent p;
    		p.wczytajDane();
    		system("cls");
    		cout<<"\t"<<"TWOJE DANE"<<endl;
    		p.wyswietlDane();
    		break;
    		}
    }
}
