//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);   <--- ustawienie kolorku nr 14

#include <iostream> 
#include <windows.h> 
using namespace std;
int main() 
{ 
    int wybor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout <<"\t"<< "PRZYCHODNIA LEKARSKA" << endl<<endl;
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
    		cout<<endl<<"WITAJ LEKARZU";
    		break;
    	case 2:
    		cout<<endl<<"WITAJ PACJENCIE";
    		break;
	}
    return 0; 
}
