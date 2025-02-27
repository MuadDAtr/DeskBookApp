#include <iostream>
#include <string>
#include <fstream>


using namespace std;

struct Pracownik{
	string nazwisko;
	int godzina;
};

bool poprawna_godzina(int h);

string del_res(string desk_number, int u_hour, string u_name);

int main(){

	cout<<"WITAJ W PROGRAMIE DO REZERWACJI BIUREK W PRACY" <<endl<<endl;
	cout<<"Rozklad biurek"<<endl;

	string tab[4][4]={
	{"0", "0", "0", "0"},
	{"0", "0", "0", "0"},
	{"0", "0", "0", "0"},
	{"0", "0", "0", "0"}};

	int q,w;
	for(q=0;q<4;q++)
	{
		for(w=0;w<4;w++)
		{
			cout<<"\t"<<tab[q][w];
		}
		cout<<endl;
	}
	

	struct Pracownik uzytkownik;
	int godz;
	
	cout<<"Podaj swoje nazwisko"<<endl;
	cin>>uzytkownik.nazwisko;
	
	cout<<"Wybierz biurko (nr):"<<endl;
	int nr_biurka;
	cin>> nr_biurka; 
	cout<<endl;

	tab[(nr_biurka-1)/4][(nr_biurka-1)%4]=uzytkownik.nazwisko;

	for(q=0;q<4;q++)
	{
		for(w=0;w<4;w++)
		{
			cout<<"\t"<<tab[q][w];
		}
		cout<<endl;
	}

	string biurko_nr_plik;
	biurko_nr_plik = to_string(nr_biurka) + ".txt";
	//cout <<biurko_nr_plik<<endl;

	cout<<"W ktorych godzinach chcesz pracowac? Wpisz \"0\" dla 0:00-1:00, \n\"15\" dla 15:00-16:00 "<<endl;
	cin>>godz;
	
	while(poprawna_godzina(godz) ==  false){
	printf("Prosze podac poprawna godzine:  ");
	cin>> godz;
	cout<<endl;
	};
	uzytkownik.godzina = godz;

	 // inicjalizacja tablicy z godzinami, domyslnie "0" wolne biurko w tej godzinie
  	string hours[24]
      	= {"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};


 	fstream desk;
 	desk.open(biurko_nr_plik, ios::in);
 	if (desk.good()==false)
	{
		desk.close();
		desk.open(biurko_nr_plik, ios::out);
		for (int i=0; i<24; i++){
		desk<< hours[i]<<endl;
		}
		desk.close();
	}
	
	desk.close();

  	cout<<endl;

  	//wczytywanie z pliku ktore godziny sa zajete i zapisywanie w tablicy
	  string new_hours[24];
	  desk.open(biurko_nr_plik, ios::in);
	  for (int i=0; i<24; i++) {
				getline(desk, new_hours[i]);
				};  
		desk.close();

	//sprawdzanie czy w danej godzinie biurko jest zajete i rezerwowanie miejsca
	if (poprawna_godzina(godz)==true)
	{
		desk.open(biurko_nr_plik, ios::out);

		if (new_hours[uzytkownik.godzina] == "0"){
			new_hours[uzytkownik.godzina] = uzytkownik.nazwisko;
		 		}
		else {
		 	cout<<"Ta godzina jest zajeta"<<endl;
		 	
		 		};
		for (int i=0; i<24; i++){
			desk<< new_hours[i]<<endl;
				};
		desk.close();
	}
	cout<<endl;
	
	//cout<< poprawna_godzina(godz) <<endl;
	/*for (int i=0;i<24;i++){
	cout<< new_hours[i]<<endl;
	};
	*/
	cout<<"Czy chcesz zapisac zmiany? Nacisnij \"z\""<<endl;
	cout<<"Czy chcesz usunac rezerwacje (wpisz \"u\", zeby usunac, \"e\" zeby wyjsc) "<<endl;
	string usun;
	cin>>usun;
	if (usun == "u") 
	{
	int u_godz;
	u_godz = uzytkownik.godzina;
	string u_nazw;
	u_nazw = uzytkownik.nazwisko;
	del_res(biurko_nr_plik, u_godz, u_nazw);
	};

	return 0;

}


//funkcja sprawdzajaca poprawnosc wpisanej liczby (zakres 0-23)
bool poprawna_godzina(int h)
{
	if (h>=0 && h<24) {
		return true;
	}
	else {
		return false;
	}
}

//funkcja usuwajaca rezerwacje
string del_res(string desk_number, int u_hour, string u_name)
{
	string nowa[24];
	fstream desk;
 	desk.open(desk_number, ios::in);
	for (int i=0; i<24; i++) {
			getline(desk, nowa[i]);
			};  
	desk.close();

	string zero = "0";
	desk.open(desk_number, ios::out);

		if (nowa[u_hour] == u_name){
			nowa[u_hour] = zero;
		 		}
		for (int i=0; i<24; i++){
			desk<< nowa[i]<<endl;
				};
		desk.close();
	//for (int i=0; i<24; i++) {
		//cout<<nowa[i]<<" ";
			//};  

	return nowa[u_hour];
}

