#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <winbase.h>
#include <assert.h>
#include <cstdlib>
#include <fstream>
#include<mysql.h>
#include <sstream>
#include<stdio.h>
#include <string>



using namespace std;


void stworzharmonogram(string nazwa)
{

    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    if(conn){
    int qstate = 0, quantity;

        stringstream ss;
        ss << " CREATE TABLE `nadobreinazle`.`"<<nazwa<<"` ( `godzina` INT NOT NULL , `dzien` INT NOT NULL,`miesiac` INT NOT NULL, `dostepnosc` TEXT CHARACTER SET utf8mb4 COLLATE utf8mb4_polish_ci NOT NULL , `pesel pacjenta` TEXT CHARACTER SET utf8mb4 COLLATE utf8mb4_polish_ci NOT NULL )ENGINE = InnoDB;";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
    }

    	}


int dodaj_lekarza_do_bazy(string imie,
	string nazwisko,
	string adres,
	string pesel,
	string haslo,
	string specjalizacja,
	int godzinaRozpoczeciaPracy,
	int godzinaZakonczeniaPracy)
	{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    if(conn){
    int qstate = 0, quantity;

        stringstream ss;
        ss << "INSERT INTO lekarze VALUES('" << imie << "','" << nazwisko<< "','" << adres<< "','"<< pesel<< "','" << haslo<< "','" << specjalizacja<< "','" << godzinaRozpoczeciaPracy << "'," << godzinaZakonczeniaPracy <<")";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
    }



}
int dodaj_wizyte_do_bazy(int godzina,
	int dzien,
	int miesiac,
	string dostepnosc,
	string pesellekarza)

	{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    if(conn){
    int qstate = 0, quantity;

        stringstream ss;
        string brak = "brak";
        ss << "INSERT INTO `"<<pesellekarza<<"` (`godzina`, `dzien`, `miesiac`, `dostepnosc`, `pesel pacjenta`) VALUES ('"<<godzina<<"', '"<<dzien<<"', '"<<miesiac<<"', '"<<dostepnosc<<"', '"<<brak<<"')";


        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

    }
	}






int dodaj_pacjenta_do_bazy(string imie,
	string nazwisko,
	string adres,
	string pesel,
	string haslo)
	{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    if(conn){
    int qstate = 0, quantity;

        stringstream ss;
        ss << "INSERT INTO pacjenci VALUES('" << imie << "','" << nazwisko<< "','" << adres<< "','"<< pesel<<
         "','" << haslo <<"')";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

    }
	}

string wyswietlzharmonogramu(string pesel, string co, int dzien, int miesiac, int godzina)

{
 string dummy,odp;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    stringstream ss;
        ss << "SELECT `"<<co<<"` FROM `"<<pesel<<"` WHERE `godzina` = "<<godzina<<" AND `dzien` = "<<dzien<<" AND `miesiac` = "<<miesiac;
        string query = ss.str();
        const char* q = query.c_str();
        if(conn){

        int qstate = mysql_query(conn, q);


        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){

             odp=row[0];
             }
        }
    }


return odp;
}
string wyswietlzbazylekarzy(string pesel, string co)

{
 string dummy,odp;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    stringstream ss;
        ss << "SELECT " <<co<<" FROM lekarze WHERE pesel="<<"\""<<pesel<<"\"";
        string query = ss.str();
        const char* q = query.c_str();
        if(conn){

        int qstate = mysql_query(conn, q);


        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){

             odp=row[0];
             }
        }
    }


return odp;
}
string wyswietlzbazypacjentow(string pesel, string co)

{
 string dummy,odp;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    stringstream ss;
        ss << "SELECT " <<co<<" FROM pacjenci WHERE pesel="<<"\""<<pesel<<"\"";
        string query = ss.str();
        const char* q = query.c_str();
        if(conn){

        int qstate = mysql_query(conn, q);


        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){

             odp=row[0];
             }
        }
    }


return odp;
}





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
	void wypiszRecepte();
	void udzielPoradyInt();
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
	static void nowyGrafikLekarza(Lekarz L);
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
	fstream DanePacjenci;
	fstream PacjenciPlik;
	PacjenciPlik.open("PlikZPacjentami.txt", ios::app);
	DanePacjenci.open("WszystkieDane.txt", ios::app);
	cout << "Podaj imie: ";
	cin.ignore();
	getline(cin, this->imie);
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
	DanePacjenci << pesel << " ";
	DanePacjenci << "    " << "Imie: " << imie << "     ";
	DanePacjenci << "Nazwisko: " << nazwisko << "     ";
	DanePacjenci << "Adres: " << adres << " \n";


	DanePacjenci.close();
	PacjenciPlik.close();
}


string peselGlob;
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
			{
				cout << "Haslo jest niepoprawne!" << endl;
				Sleep(1000);
				system("cls");
			}
		}
	}

	if (PacjenciPlik.eof() && (!czyZnaleziono))
	{
		cout << "Bledne dane, wpisz ponownie\n";
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
	//	string pesel1;

		//cout << "Please enter a name: ";
	//	cin >> pesel;
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

	//cout << "Imie: " << this->imie << endl;
	//cout << "Nazwisko: " << this->nazwisko << endl;
	//cout << "Adres: " << this->adres << endl;
	//cout << "Pesel: " << this->pesel << endl;

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
	fstream DaneLekarze;
	fstream LekarzePlik;
	LekarzePlik.open("PlikZLekarzami.txt", ios::app);
	DaneLekarze.open("WszystkieDaneL.txt", ios::app);
	cout << "Podaj imie: ";
	//cin.ignore();
	getline(cin, this->imie);
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

	cout << "Podaj swoja specjalizacje lekarska: ";
	cin >> this->specjalizacja;
	cout << "Podaj godzine rozpoczecia pracy: ";
	cin >> this->godzinaRozpoczeciaPracy;
	cout << "Podaj godzine zakonczenia pracy: ";
	cin >> this->godzinaZakonczeniaPracy;
	DaneLekarze << pesel << " ";
	DaneLekarze << "    " << "Imie: " << imie << "     ";
	DaneLekarze << "Nazwisko: " << nazwisko << "     ";
	DaneLekarze << "Adres: " << adres << "     ";
	DaneLekarze << "Specjalizacja: " << specjalizacja << "     ";
	DaneLekarze << "Godziny pracy: " << godzinaRozpoczeciaPracy << " - " << godzinaZakonczeniaPracy << " \n";
	DaneLekarze.close();
	LekarzePlik.close();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			this->grafikLekarza[i][j] = false;
		}
	}
}

string peselGlob2;
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
			{
				cout << "Haslo jest niepoprawne!" << endl;
				Sleep(1000);
				system("cls");
			}
		}
	}

	if (LekarzePlik.eof() && (!czyZnaleziono2))
	{
		cout << "Bledne dane, wpisz ponownie\n";
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
	//	string pesel1;

		//cout << "Please enter a name: ";
	//	cin >> pesel;
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

void Harmonogram::nowyGrafikLekarza(Lekarz L)
{
 SYSTEMTIME st;
 GetSystemTime(&st);
 int dzien = st.wDay;
 int miesiac = st.wMonth;
 stworzharmonogram(L.pesel);

 for(int j=dzien,k=0;k<14;k++,j++)
 {

 if(j==32)
    {
        j=1;
        miesiac=1;
    }

 for(int i=L.godzinaRozpoczeciaPracy;i<L.godzinaZakonczeniaPracy;i++)
 {
   dodaj_wizyte_do_bazy(i,j,miesiac,"DOSTEPNY",L.pesel);
 }

 }





}




void Harmonogram::wyswietlGrafikLekarza(Lekarz L)

{
    SYSTEMTIME st;
    GetSystemTime(&st);

    int l =2;
    int dd =st.wDay;
    int mm =st.wMonth;
    int godz=L.godzinaRozpoczeciaPracy;
    string dostepnosc;
    char wybor;

    HANDLE kolor;
    kolor = GetStdHandle(STD_OUTPUT_HANDLE);

system("cls");
    do
    {

    cout << endl << "Harmonogram lekarza ";
    SetConsoleTextAttribute(kolor, 4);
    cout<< L.imie << " " << L.nazwisko << endl;
    SetConsoleTextAttribute(kolor, 7);



        cout << endl << dd<<"."<<mm << endl<<endl;

        for(; godz<L.godzinaZakonczeniaPracy; godz++)
        {
            cout<<godz<<":00  ";
            dostepnosc = wyswietlzharmonogramu(L.pesel,"dostepnosc",dd,mm,godz);
            if (dostepnosc=="DOSTEPNY")
            {
                SetConsoleTextAttribute(kolor, 2);
                cout << dostepnosc << endl;
                SetConsoleTextAttribute(kolor, 7);
            }
            else
            {
                SetConsoleTextAttribute(kolor, 4);
                cout << dostepnosc << endl;
                SetConsoleTextAttribute(kolor, 7);
            }
        }
        if(dd!=st.wDay)
        {
            cout<<"'P' Poprzedni dzien  ";
        }
        cout <<"'N' Nastepny dzien  'Z' Zamknij"<<endl;

        cout <<"wybor: ";
        cin >> wybor;

        if(wybor=='n' || wybor=='N')
        {
            dd++;
            godz=L.godzinaRozpoczeciaPracy;
        }
        else if(wybor=='p' || wybor=='P')
        {
            dd--;
            godz=L.godzinaRozpoczeciaPracy;
        }
        else if(wybor=='z' || wybor=='Z')
        {
            l=0;
        }
system("cls");

    }
    while(l==2);

/*
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

*/
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

//void Porada::wyswPorady(Porada porada1)
//{
//	cout << "1.Oczekujace zapytania internetowe \n2.Oczekujace recepty " << endl;
//	int odp2;
//	cin >> odp2;

	//if (odp2 == 1)
	//{
//		system("cls");
//		cout << "ZAPYTANIA INTERNETOWE" << endl;

	//	for (int i = 0; i < porada1.ZapytaniaOczekujace.size(); i++)
	//	{
	//		cout << endl;
	//		cout << "Tresc: " << porada1.ZapytaniaOczekujace[i].tresc << endl;
	//		cout << "specjalziacja: " << porada1.ZapytaniaOczekujace[i].specjalizacja << endl;
	//		cout << "Data dodania: " << porada1.ZapytaniaOczekujace[i].dzien << "." << porada1.ZapytaniaOczekujace[i].miesiac << "." << porada1.ZapytaniaOczekujace[i].rok << endl;
	//		cout << "Godzina dodania: " << porada1.ZapytaniaOczekujace[i].godzina << ":" << porada1.ZapytaniaOczekujace[i].minuta << ":" << porada1.ZapytaniaOczekujace[i].sekunda << endl;
	//	}
	//}

//	else if (odp2 == 2)
//	{
	//	system("cls");
//		cout << "RECEPTY" << endl;
//		for (int i = 0; i < porada1.ReceptyOczekujace.size(); i++)
//		{
//			cout << endl;
//			cout << "Tresc: " << porada1.ReceptyOczekujace[i].tresc << endl;
//			cout << "Data dodania: " << porada1.ReceptyOczekujace[i].dzien << "." << porada1.ReceptyOczekujace[i].miesiac << "." << porada1.ReceptyOczekujace[i].rok << endl;
//			cout << "Godzina dodania: " << porada1.ReceptyOczekujace[i].godzina << ":" << porada1.ReceptyOczekujace[i].minuta << ":" << porada1.ReceptyOczekujace[i].sekunda << endl;
//		}
//	}
//}

/*void ::dodawanie_porady()
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
}*/
//MAIN
int main()
{

//dodaj_lekarza_do_bazy("Artur","Hamerski","Krakow","731","kot","dentysta",8,16);
//dodaj_pacjenta_do_bazy("Karol","Hamski","WWA","123","pies");
//cout<<wyswietlzbazylekarzy("56789", "haslo");
//cout<<wyswietlzbazypacjentow("123456789", "imie");


    Lekarz L;
    L.wczytajDane();
    Pacjent P;
    P.wczytajDane();

    //do
   // {
//
//
  //  L.wczytajDane();
   // dodaj_lekarza_do_bazy(L.imie,L.nazwisko,L.adres,L.pesel,L.haslo,L.specjalizacja,L.godzinaRozpoczeciaPracy,L.godzinaZakonczeniaPracy);
   // }while(1==1);
    //Harmonogram::nowyGrafikLekarza(L);
   // cout<<wyswietlzharmonogramu("731","dostepnosc",30,12,12);
   Harmonogram::wyswietlGrafikLekarza(L);

}

