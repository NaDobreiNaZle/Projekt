#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <winbase.h>
#include <assert.h>
#include <cstdlib>
#include <fstream>
#include <limits>
#include<mysql.h>
#include <sstream>
#include<stdio.h>
#include <string>


#undef max
using namespace std;

string peselGlob;

///////////////////////////////////////////////MOJE FUNKCJE OD OBSLUGI SQL KTORE POZNIEJ SPAKUJE DO JEDNEJ BIBLIOTEKI ZEBY SYFU NIE ROBIC///////////////////////////////////////////////////////////

void stworzharmonogram(string nazwa)
{

    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    if(conn)
    {
        int qstate = 0, quantity;

        stringstream ss;
        ss << " CREATE TABLE `nadobreinazle`.`"<<nazwa<<"` ( `godzina` INT NOT NULL , `dzien` INT NOT NULL,`miesiac` INT NOT NULL, `dostepnosc` TEXT CHARACTER SET utf8mb4 COLLATE utf8mb4_polish_ci NOT NULL , `pesel pacjenta` TEXT CHARACTER SET utf8mb4 COLLATE utf8mb4_polish_ci NOT NULL )ENGINE = InnoDB;";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
    }

}

void rezerwacja(int godzina,int dzien,int miesiac,string peselL,string peselP)
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    if(conn)
    {
        int qstate = 0, quantity;

        stringstream ss;
        ss << "UPDATE `"<<peselL<<"` SET dostepnosc = \"ZAJETY\", `pesel pacjenta` = \""<<peselP<<"\" WHERE godzina = "<<godzina<<" AND dzien = "<<dzien<<" AND miesiac = "<<miesiac;
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
    if(conn)
    {
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
    if(conn)
    {
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
    if(conn)
    {
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
    if(conn)
    {

        int qstate = mysql_query(conn, q);


        if(!qstate)
        {
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res))
            {

                odp=row[0];
            }
        }
    }


    return odp;
}


string wyswietlzbazylekarzy(string pesel, string co)

{
    string dummy,odp;
    char* wart;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    stringstream ss;


    ss << "SELECT " <<co<<" FROM lekarze WHERE pesel="<<"\""<<pesel<<"\"";
    string query = ss.str();
    const char* q = query.c_str();
    if(conn)
    {

        int qstate = mysql_query(conn, q);

        if(!qstate)
        {

            res = mysql_store_result(conn);


            while(row = mysql_fetch_row(res))
            {


                odp=row[0];
            }
        }
    }


    return odp;
}



string wyswietlspecjalistow(string specjalizacja, string co)

{
    string dummy,odp;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    stringstream ss;
    ss << "SELECT " <<co<<" FROM lekarze WHERE specjalizacja="<<"\""<<specjalizacja<<"\"";
    string query = ss.str();
    const char* q = query.c_str();
    if(conn)
    {

        int qstate = mysql_query(conn, q);


        if(!qstate)
        {
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res))
            {

                odp=row[0];
            }
        }
    }


    return odp;
}

string wyswietlspecjalistow2(string specjalizacja, string co)

{
    int i=0;
    string dummy,odp;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "nadobreinazle", 0, NULL, 0);
    stringstream ss;
    ss << "SELECT " <<co<<" FROM lekarze WHERE specjalizacja="<<"\""<<specjalizacja<<"\"";
    string query = ss.str();
    const char* q = query.c_str();
    if(conn)
    {

        int qstate = mysql_query(conn, q);


        if(!qstate)
        {
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res))
            {

                if(i==0)
                {
                  odp=row[0];

                }

                i++;


            }

        }
        return odp;
    }



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
    if(conn)
    {

        int qstate = mysql_query(conn, q);


        if(!qstate)
        {
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res))
            {

                odp=row[0];
            }
        }
    }


    return odp;
}

///////////////////////////////////////////////BEZPANSKIE FUNKCJE DO ROZWINIECIA I PRZYGARNIECIA PRZEZ KOGOS///////////////////////////////////////////////////////////





//KLASY
class Osoba
{
public:
	string imie;
	string nazwisko;
	string adres;
	string pesel;
	string haslo;
	void logowanie();
	void wyswietlDane(string pesel);
};

class Pacjent : public Osoba
{
public:

    static string wybierz_specjalizacje();
	void wczytajDane();
	static void umow_wizyte(Pacjent P);
	static string wybor_lekarza(string specjalizacja);


};

class Lekarz : public Osoba
{
public:

	string specjalizacja;
	int godzinaRozpoczeciaPracy;
	int godzinaZakonczeniaPracy;
	void wczytajDane(Lekarz l);

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

class Harmonogram
{
public:
	static void aktualizujGrafik(Lekarz, int, int);
	static void wyswietlGrafikLekarza(Lekarz L);
	static void wybor_terminu(string lekarz,Pacjent P);
	static void nowyGrafikLekarza(Lekarz L);

};



class Porada
{
public:
	void dodawanie_porady();
	void wyswPorady();
	void wyswOdpowiedzi();

};

//FUNKCJE
void Porada::wyswOdpowiedzi()
{
	cout << "1.Nowe odpowiedzi \n2.Stare odpowiedzi" << endl;
	int odp;
	cin >> odp;
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
		fstream starePorady;

		string nazwa2 = "internetoweS";

		nazwa2 += peselGlob;
		nazwa2 += ".txt";

		starePorady.open(nazwa2.c_str(), ios::app | ios::in);
		cout << starePorady.rdbuf();
		starePorady.close();

	}



}

void Pacjent::wczytajDane()
{
	fstream Dane;
	fstream Hasla;
	Hasla.open("PlikZHaslami.txt", ios::app | ios::in);
	Dane.open("Dane.txt", ios::app);

	cout << "Podaj pesel: ";

	getline(cin, pesel);
	string tekst;
	int i = 0;
	while (!Hasla.eof())
	{
		getline(Hasla, tekst);

		if (!(string::npos == tekst.find(pesel)))
			i = 1;

	}
	Hasla.close();

	if (i == 1)
	{
		cout << "Konto o takim peselu juz istnieje. Prawdopodobnie wpisales bledny pesel. Zarejestruj sie ponownie." << endl;
		Pacjent::wczytajDane();
	}
	else
	{
		Hasla.open("PlikZHaslami.txt", ios::app);

		cout << "Podaj imie: ";
		getline(cin, this->imie);
		cout << "Podaj nazwisko: ";
		getline(cin, this->nazwisko);
		cout << "Podaj swoj adres: ";
		getline(cin, this->adres);
		cout << "Podaj haslo: ";
		cin >> this->haslo;
		Hasla << pesel << " ";
		Hasla << haslo << "\n";
		Dane << pesel << " ";
		Dane << "    " << "Imie: " << imie << "     ";
		Dane << "Nazwisko: " << nazwisko << "     ";
		Dane << "Adres: " << adres << " \n";

		Dane.close();
		Hasla.close();
		dodaj_pacjenta_do_bazy(imie,nazwisko,adres,pesel,haslo);

	}
}

string Pacjent::wybierz_specjalizacje()
{
 int x;
 cout<<"1. Dentysta"<<endl<<"2. Dermatolog"<<endl<<"3. Urolog"<<endl<<"4. Laryngolog"<<endl<<"5. Psycholog" <<endl<<"6. Okulista"<<endl<<"7. Fizjoterapeuta"<<endl;
 cout<<"Wybor: ";
 cin>>x;
 if(x==1)return "dentysta";
 else if(x==2)return "dermatolog";
 else if(x==3)return "urolog";
 else if(x==4)return "laryngolog";
 else if(x==5)return "psycholog";
 else if(x==6)return "okulista";
 else if(x==7)return "fizjoterapeuta";

 else return "0";


}

string Pacjent:: wybor_lekarza(string specjalizacja)
{
   int x;
   string tab[10];
   cout<<"1."<<wyswietlspecjalistow(specjalizacja, "imie")<<" " << wyswietlspecjalistow(specjalizacja, "nazwisko")<<endl;

   if (specjalizacja=="dentysta")
   {
       cout<<"2."<<wyswietlspecjalistow2(specjalizacja, "imie")<<" " << wyswietlspecjalistow2(specjalizacja, "nazwisko")<<endl;
   }



   cin>>x;
    return wyswietlspecjalistow(specjalizacja, "pesel");


}

void Osoba::logowanie()
{
	cout << "Pesel: " << endl;
	cin >> pesel;


	bool czyZnaleziono = 0;
	string ZapisaneHaslo;
	fstream Hasla;
	Hasla.open("PlikZHaslami.txt");
	while (!Hasla.eof())
	{
		string temp = "";
		getline(Hasla, temp);

		for (int i = 0; i < pesel.size(); i++)
		{
			if (temp[i] == pesel[i])
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
			cin >> haslo;

			for (int i = pesel.size() + 1; i < temp.size(); i++)
			{
				ZapisaneHaslo += temp[i];
			}
			if (ZapisaneHaslo == haslo)
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

	if (Hasla.eof() && (!czyZnaleziono))
	{
		cout << "Bledne dane, wpisz ponownie\n";
		Sleep(2000);
		system("cls");
		logowanie();
	}
	Hasla.close();
	peselGlob = pesel;
}



void Lekarz::wczytajDane(Lekarz l)
{
	fstream Dane;
	fstream Hasla;
	Hasla.open("PlikZHaslami.txt", ios::app | ios::in);
	Dane.open("Dane.txt", ios::app);
	cout << "Podaj pesel: ";
	getline(cin, pesel);
	string tekst;
	int i = 0;
	while (!Hasla.eof())
	{
		getline(Hasla, tekst);

		if (!(string::npos == tekst.find(pesel)))
			i = 1;

	}
	Hasla.close();

	if (i == 1)
	{
		cout << "Konto o takim peselu juz istnieje. Prawdopodobnie wpisales bledny pesel. Zarejestruj sie ponownie." << endl;
		Lekarz::wczytajDane(l);
	}
	else
	{
		Hasla.open("PlikZHaslami.txt", ios::app);

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
		Hasla << pesel << " ";
		Hasla << haslo << "\n";
		Dane << pesel << " ";
		Dane << "    " << "Imie: " << imie << "     ";
		Dane << "Nazwisko: " << nazwisko << "     ";
		Dane << "Adres: " << adres << "     ";
		Dane << "Specjalizacja: " << specjalizacja << "     ";
		Dane << "Godziny pracy: " << godzinaRozpoczeciaPracy << " - " << godzinaZakonczeniaPracy << " \n";
		Dane.close();
		Hasla.close();
		dodaj_lekarza_do_bazy(imie,nazwisko,adres,pesel,haslo,specjalizacja,godzinaRozpoczeciaPracy,godzinaZakonczeniaPracy);

	}

l.imie=wyswietlzbazylekarzy(pesel,"imie");
	l.nazwisko=wyswietlzbazylekarzy(pesel,"nazwisko");
	l.adres=wyswietlzbazylekarzy(pesel,"adres");
	l.pesel=wyswietlzbazylekarzy(pesel,"pesel");
	l.haslo=wyswietlzbazylekarzy(pesel,"haslo");
	l.specjalizacja=wyswietlzbazylekarzy(pesel,"specjalizacja");
	stringstream temp1(wyswietlzbazylekarzy(pesel,"godzinarozpoczecia"));
	temp1>>l.godzinaRozpoczeciaPracy;
	stringstream temp2(wyswietlzbazylekarzy(pesel,"godzinazakonczenia"));
	temp2>>l.godzinaZakonczeniaPracy;
}







void Porada::wyswPorady()
{
	cout << "Oczekujace zapytania internetowe oraz recepty " << endl;

	system("cls");
	cout << "ZAPYTANIA INTERNETOWE" << endl;
	fstream starePorady;
	string tresc;

	fstream Hasla;
	Hasla.open("PlikZHaslami.txt");
	string pobranePesele;

	cin.ignore();

	while (Hasla >> pobranePesele)
	{
		string nazwa = "internetowe";
		Hasla.ignore(numeric_limits<streamsize>::max(), '\n');
		nazwa += pobranePesele;
		nazwa += ".txt";

		fstream Porady(nazwa.c_str());


		if (Porady)
		{
			Porady.open(nazwa.c_str(), ios::in);
			cout << Porady.rdbuf();
			Porady.open(nazwa.c_str(), ios::app);
			cout << "Odpowiedz: " << endl;
			getline(cin, tresc);
			cout << "\n";
			Porady << "Odpowiedz lekarza: " << tresc << endl;
			Porady.close();

			string nazwa2 = "internetoweS";
			nazwa2 += pobranePesele;
			nazwa2 += ".txt";
			starePorady.open(nazwa2.c_str(), ios::app);

			starePorady << "Odpowiedz lekarza: " << tresc << endl;

		}



	}

	Hasla.close();
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

void Osoba::wyswietlDane(string pesel)
{
	fstream Dane;
	Dane.open("Dane.txt");

	bool znalezione = 0;
	while (!Dane.eof())
	{
		string temp = "";
		getline(Dane, temp);
		for (int i = 0; i < pesel.size(); i++)
		{
			if (temp[i] == pesel[i])
				znalezione = 1;
			else
			{
				znalezione = 0;
				break;
			}
		}

		if (znalezione)
		{
			cout << "Pesel: ";
			for (int i = 0; i < temp.size(); i++)

				cout << temp[i];
			break;
			cout << "    ";
		}

	}

	if (Dane.eof() && (!znalezione))
	{
		cout << "Name not found!\n";
	}

	Dane.close();

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

void Harmonogram::nowyGrafikLekarza(Lekarz L)
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    int dzien = st.wDay;
    int miesiac = st.wMonth;
    stworzharmonogram(L.pesel);

    for(int j=dzien,k=0; k<14; k++,j++)
    {

        if(j==32)
        {
            j=1;
            miesiac=1;
        }

        for(int i=L.godzinaRozpoczeciaPracy; i<L.godzinaZakonczeniaPracy; i++)
        {
            dodaj_wizyte_do_bazy(i,j,miesiac,"DOSTEPNY",L.pesel);
        }

    }

}

void Harmonogram::wybor_terminu(string lekarz,Pacjent P)
{
    cout <<lekarz;
    SYSTEMTIME st;
    GetSystemTime(&st);
    int tabdd [12];
    int tabmm [12];
    int tabgg [12];
    int n=0;
    int l =2;
    int dd =st.wDay;
    int mm =st.wMonth;
    string sgodzrozp=wyswietlzbazylekarzy(lekarz,"godzinarozpoczecia");
    string sgodzzak=wyswietlzbazylekarzy(lekarz,"godzinazakonczenia");
    stringstream temp1(sgodzrozp);
    stringstream temp2(sgodzzak);
    int godzrozp;
    temp1>>godzrozp;
    int godzzak;
    temp2>>godzzak;
    string imie=wyswietlzbazylekarzy(lekarz,"imie");
    string nazwisko=wyswietlzbazylekarzy(lekarz,"nazwisko");
    int godz=godzrozp;

    string dostepnosc;
    char wybor;

    HANDLE kolor;
    kolor = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    do
    {
        n=0;
        cout << endl << "Wolne terminy do lekarza ";
        SetConsoleTextAttribute(kolor, 4);
        cout<< imie << " " << nazwisko << endl;
        SetConsoleTextAttribute(kolor, 7);



        cout << endl << dd<<"."<<mm << endl<<endl;



        for(; godz<godzzak; godz++)
        {
//dostepnosc = "DOSTEPNY";
            dostepnosc = wyswietlzharmonogramu(lekarz,"dostepnosc",dd,mm,godz);
            if (dostepnosc=="DOSTEPNY")
            {
                cout<<n+1<<" ";
                cout<<godz<<":00  ";
                SetConsoleTextAttribute(kolor, 2);
                cout << dostepnosc << endl;
                SetConsoleTextAttribute(kolor, 7);
                tabdd[n]=dd;
                tabmm[n]=mm;
                tabgg[n]=godz;
                n++;
            }

        }
        cout<<"Wybierz numer odpowiadajacego terminu lub ";
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
            godz=godzrozp;
        }
        else if(wybor=='p' || wybor=='P')
        {
            dd--;
            godz=godzrozp;
        }
        else if(wybor=='z' || wybor=='Z')
        {
            l=0;
        }
        else if(wybor=='1' || wybor=='2' || wybor=='3' || wybor=='4' || wybor=='5' || wybor=='6' || wybor=='7' || wybor=='8' || wybor=='9' )
        {

            int temp3 = wybor - '0';
            cout<<"Zostales zarejestrowany na "<<tabdd[temp3-1]<<"."<<tabmm[temp3-1]<<" na godzine "<<tabgg[temp3-1]<<".00"<<endl;

            rezerwacja(tabgg[temp3-1],tabdd[temp3-1],tabmm[temp3-1],lekarz, P.pesel);
            l=0;
            break;
            cin>>temp3;

        }
        system("cls");

    }
    while(l==2);

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
                cout << dostepnosc;
                SetConsoleTextAttribute(kolor, 7);
                if(wyswietlzharmonogramu(L.pesel,"pesel pacjenta",dd,mm,godz)!="brak")
                {
                    cout<< "  Pesel pacjenta:";
                    cout << wyswietlzharmonogramu(L.pesel,"pesel pacjenta",dd,mm,godz)<<endl;
                }
                else
                {
                    cout<<endl;
                }

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

    }while(l==2);
}

void Pacjent::umow_wizyte(Pacjent P)
{

string specjalizacja=Pacjent::wybierz_specjalizacje();

string lekarz=Pacjent::wybor_lekarza(specjalizacja);

Harmonogram::wybor_terminu(lekarz,P);
}
//MAIN
int main()
{
	Porada porada;
	KartaChorob kartaChorob;
	Osoba o;
	Lekarz l;
	Pacjent p;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "\t" << "PRZYCHODNIA LEKARSKA";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	Sleep(1000);
	system("cls");
	int w1 = 0;
	while (w1 != 3)
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
		if (w1 != 3)
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


			if (w1 == 1)
			{
				if (wybor == 1)
				{
					cin.ignore();
					l.wczytajDane(l);
					Harmonogram::nowyGrafikLekarza(l);
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
				o.logowanie();

				while (nr != 5)
				{
					cout << "\tMENU" << endl;
					cout << "-----------------------------" << endl;
					cout << "1. Wyswietl swoje dane " << endl;
					cout << "2. Wyswietl porady oczekujace" << endl;
					cout << "3. Edytuj karte pacjenta" << endl;
					cout << "4. Wyswietl swoj harmonogram" << endl;
					cout << "5. Wyloguj" << endl;
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
							o.wyswietlDane(peselGlob);
							cout << endl << endl << "1. Powrot do menu " << endl;
							cout << "Wybor: ";
							cin >> w;
						}
						break;
					}
					case 2:
					{
						porada.wyswPorady();
						Sleep(500);
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
					case 4:
					{

						Harmonogram::wyswietlGrafikLekarza(l);
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
				o.logowanie();

				while (nr != 6)
				{
					system("cls");
					cout << "\tMENU" << endl;
					cout << "--------------------------------" << endl;
					cout << "1. Wyswietl swoje dane " << endl;
					cout << "2. Dodaj porade oczekujaca" << endl;
					cout << "3. Wyswietl swoje zapytania" << endl;
					cout << "4. Wyswietl swoja karte chorob" << endl;
					cout << "5. Umow sie na wizyte" << endl;
					cout << "6. Wyloguj" << endl;
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
							o.wyswietlDane(peselGlob);
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

					case 5:
					{int w = 0;
						while (w != 1)
						{
							system("cls");
                        Pacjent::umow_wizyte(p);
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
				Sleep(1000);
				system("cls");
				break;
			}
			}
		}
	}



}
