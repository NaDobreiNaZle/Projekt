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
string peselGlob2;



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
string wybierz_specjalizacje()
{
 int x;
 cout<<"1.dentysta"<<endl<<"2.dermatolog"<<endl;
 cin>>x;
 if(x==1)return "dentysta";
 else if(x==2)return "dermatolog";
 else return "0";


}

string wybor_lekarza(string specjalizacja)
{
   int x;
   cout<<"1."<<wyswietlspecjalistow(specjalizacja, "imie")<<" " << wyswietlspecjalistow(specjalizacja, "nazwisko")<<endl;

   cin>>x;
    return wyswietlspecjalistow(specjalizacja, "pesel");


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
	static void umow_wizyte(Pacjent P);


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
	static Lekarz logowanie(Lekarz);
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
	void wyswietlTerminy();
	void wyswietlDostLekarzy(string specjalizacja);
};

class Harmonogram
{
public:
	static void aktualizujGrafik(Lekarz, int, int);
	static void wyswietlGrafikLekarza(Lekarz L);
	//void aktualizujPrzyszleTerminy();
	static void wybor_terminu(string lekarz,Pacjent P);
	static void nowyGrafikLekarza(Lekarz L);

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



	else if ( odp ==2)

	{
		fstream starePorady;

		string nazwa2 = "internetoweS";

		nazwa2 += peselGlob;
		nazwa2 += ".txt";

		starePorady.open(nazwa2.c_str(), ios::app | ios::in);
		cout << starePorady.rdbuf();
		starePorady.close();

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

	getline (cin, pesel);
	string tekst;
	int i = 0;
	while (!PacjenciPlik.eof())
	{
		getline(PacjenciPlik, tekst);

		if (!(string::npos == tekst.find(pesel)))
			i=1;

	}
	PacjenciPlik.close();

	if (i ==1)
	{
		cout << "Konto o takim peselu juz istnieje. Prawdopodobnie wpisales bledny pesel. Zarejestruj sie ponownie." << endl;
			Pacjent:: wczytajDane();
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
		dodaj_pacjenta_do_bazy(imie,nazwisko,adres,pesel,haslo);
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

void Pacjent::umow_wizyte(Pacjent P)
{

string specjalizacja=wybierz_specjalizacje();

string lekarz=wybor_lekarza(specjalizacja);

Harmonogram::wybor_terminu(lekarz,P);

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
           cin>>temp3;

        }
system("cls");

    }
    while(l==2);

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
		dodaj_lekarza_do_bazy(imie,nazwisko,adres,pesel,haslo,specjalizacja,godzinaRozpoczeciaPracy,godzinaZakonczeniaPracy);

	}


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			this->grafikLekarza[i][j] = false;
		}
	}
}


Lekarz Lekarz::logowanie(Lekarz l)
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
		logowanie(l);
	}

	LekarzePlik.close();
	peselGlob2 = pesel2;




	l.imie=wyswietlzbazylekarzy(pesel2,"imie");
	l.nazwisko=wyswietlzbazylekarzy(pesel2,"nazwisko");
	l.adres=wyswietlzbazylekarzy(pesel2,"adres");
	l.pesel=wyswietlzbazylekarzy(pesel2,"pesel");
	l.haslo=wyswietlzbazylekarzy(pesel2,"haslo");
	l.specjalizacja=wyswietlzbazylekarzy(pesel2,"specjalizacja");
	stringstream temp1(wyswietlzbazylekarzy(pesel2,"godzinarozpoczecia"));
	temp1>>l.godzinaRozpoczeciaPracy;
	stringstream temp2(wyswietlzbazylekarzy(pesel2,"godzinazakonczenia"));
	temp2>>l.godzinaZakonczeniaPracy;

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


void Porada :: dodawanie_porady()
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
		cout << st.wMinute <<":";
	if (st.wSecond < 10)
		cout << "0" << st.wSecond << endl;
	else
		cout << st.wSecond << endl;
	Porady << "\nData dodania: " <<  st.wDay << "." << st.wMonth << "." << st.wYear << "  ";
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





//MAIN
int main()
{
	Porada porada;

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
	Lekarz l;
	Pacjent p;


	if (w1 == 1)
	{
		if (wybor == 1)
		{
			cin.ignore();
			l.wczytajDane();
			Harmonogram::nowyGrafikLekarza(l);
		}
		else if (wybor == 2)
		{
			cin.ignore();
			p.wczytajDane();
		}

	}


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
			l=Lekarz::logowanie(l);

			cout << "\tMENU" << endl;
			cout << "-----------------------------" << endl;
			cout << "1. Wyswietl swoje dane " << endl;
			cout << "2. Wyswietl porady oczekujace" << endl;
			cout << "3. Wyswietl swoj harmonogram" << endl;
			cout << "-----------------------------" << endl;
			cout << "Wybor: ";
			int nr1;
			cin >> nr1;

			switch (nr1)
			{
				case 1:
				{
					cout << "TWOJE DANE" << endl;
					l.wyswietlDane(peselGlob2);
					break;
				}
				case 2:
				{
				system("cls");
				porada.wyswPorady(porada);
				break;
				}
				case 3:
				{
				system("cls");
				Harmonogram::wyswietlGrafikLekarza(l);
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

			cout << "---------" << endl;
			cout << "LOGOWANIE" << endl;
			cout << "---------" << endl;
			p.logowanie();

			system("cls");
			cout << "\tMENU" << endl;
			cout << "--------------------------" << endl;
			cout << "1. Wyswietl swoje dane " << endl;
			cout << "2. Dodaj porade oczekujaca" << endl;
			cout << "3. Wyswietl swoje zapytania" << endl;
			cout << "4. Umow sie na wizyte" << endl;
			cout << "--------------------------" << endl;
			cout << "Wybor: ";
			int nr2;
			cin >> nr2;

			switch (nr2)
			{
				case 1:
				{
					cout << "\t" << "TWOJE DANE" << endl;
					p.wyswietlDane(peselGlob);
					break;
				}
				case 2:
				{
					system("cls");
					porada.dodawanie_porady();
					break;
				}
				case 3:
				{
					system("cls");
					porada.wyswOdpowiedzi();
				}
				case 4:
				{
					system("cls");
					Pacjent::umow_wizyte(p);
				}
			}
				break;
		}

	}



}
