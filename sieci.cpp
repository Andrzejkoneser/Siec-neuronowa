#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<fstream>

using namespace std;









class neuron{
	private:
		int stan; //aktywny 1 nieaktywny -1
		int sygnal;
		double x,y;
		double progSygnalu;
	public:
		void WypiszStan(int s){stan=s;}
		void WypiszPolozenie(double xx,double yy){x=xx; y=yy;}
		int PodajStan( ){return stan;}

};

class synapsa{
	private:
		int silabond;
	public:
		void ResetSynapsy(){silabond=0;}
		void WprowadzWartoscSynapsy(int s){silabond+=s;}
		int PodajWartoscSynapsy(){return silabond;}
};





typedef
std::vector<neuron*> Komorki;
Komorki Neur;
typedef std::vector<synapsa*> Polaczenia;
Polaczenia Synap;

void AlokujNeurony(Komorki &Neur, int LLx, int LLy){
		int L=LLx*LLy;

		for(int k=0;k<L;k++) Neur.push_back(new neuron);
}

void AlokujSynapsy (Polaczenia &Synap, int LLx, int LLy){
		int LL=LLx*LLy;

		for(int k=0;k<LL;k++) Synap.push_back(new synapsa);
}

void ResetujNeurony(Komorki &Neur){
cout<<"Reset neuronow ... "<<endl;
int L=Neur.size();
	for(int k=0;k<L;k++) Neur[k]->WpiszStan(-1);
}

void ResetujSynapsy(Polaczenia &synap){
	cout<<"Reset synaps ... "<<endl;

	int L=Synap.size();
		for(int k=k;k<L;k++) Synap[k]->ResetSynapsy();
}

void WczytajParametryObrazka(char *nazwapliku, int &Lx, int &Ly){
		fstream WE;

		WE.open(nazwapliku,ios::In);
		if(WE.good()==false){
			cout<<"nie moge otworzyc pliku"<<nazwapliku<<endl;
			cout<<"wychodze do systemu"<<endl;
			exit(1);
		}

	string linia;
	int dlug;
	Lx=0,Ly=0; //wartosci poczatkowe
			//ktore zostana wyliczone z pliku z obrazkiem

	while(1){
		getline(WE, linia);
		if(WE.eof()) break;

		dlug=linia.size();
		if(Lx<dlug)Lx=dlug; //lx przyjmuje wartosc maksymalna
					//parametru dlug
		Ly++; //numeruje kolejne linie az do wartosci maksymalnej
	}

	WE.close();
}

void WczytajObrazek (Komorki &Neur, char *nazwapliku ){
	fstream WE;

	WE.open (nazwapliku, ios::in);
	if(WE.good()==false){
		cout<<"Nie moge otworzyc pliku "<<nazwapliku<<endl;
		cout<<"Wychodze do systemu :("<<endl;
		exit (1);
	}

	string linia;
	int dlug;
	int LICZNIK=0;
	char znak;

	while(1){
		getline(WE, linia);
		if(WE.eof()) break;

		dlug=linia.size();
		for(int k=0;k<dlug; k++){
			znak=linia[k];
			if (znak==’*’){
				Neur[LICZNIK]->WpiszStan(1);
			}

		LICZNIK++;

		}
	}

WE.close();

}

void PokazStanyNeuronow(Komorki &Neur, int Lx, int Ly){
	int j ;
	int L=Neur.size();

	for(int k=0; k<L; k++){
		j=k%Lx;
		if(Neur[k]->PodajStan()==1) cout<<"+";
		else cout<<" ";
		if(j==Lx-1) cout<<endl;
	}

}

void WczytajSynapsy(Komorki &Neur, Polaczenia &Synap, int Lx, int Ly){
int polacz=0;
int LL=Lx*Ly;
int ij;

			for(int i=0; i<LL; i++){
				for(int j=0; j<LL; j++){
					if(i==j) continue;
						ij=i*LL+j;
					if(Neur[i]->PodajStan()==Neur[j]->PodajStan())
						Synap[ij]->WprowadzWartoscSynapsy(1);
					else Synap[ij]->WprowadzWartoscSynapsy(-1);
				}
			}
}

void WczytajDowolnyObrazek ( Komorki &Neur , char * nazwapliku , int Lx , int Ly ){
fstream WE;

WE.open ( nazwapliku , i o s : : i n ) ;
if (WE.good()==false ){
cout<<"Nie moge otworzyc pliku "<<nazwapliku<<endl ;
cout<<"Wychodze do systemu :("<<endl ;
exit(1) ;
}

stringlinia ;
int dlug ;
int LICZNIK=0;
char znak ;
int numerlinii =0;

while (1) {
getline (WE, l i n i a ) ;
if (WE.eof ( ) ) break ;

dlug=linia.size ( );

if ( dlug>Lx ){
cout<<"Wczytany obrazek jest obciety w linii "<<Lx * Ly / LICZNIK<<endl ;
}

for ( int k=0;k<dlug ; k++){
if ( k>=Lx ) continue ; // obciecie horyzontalne
znak=linia [ k ] ;
if ( znak==’*’){
Neur [ LICZNIK]->WpiszStan (1) ;
}

LICZNIK++;

}
numerlinii++;
if ( numerlinii>=Ly ) break ; // obciecie w pionie
}

WE.close ( ) ;

}


int Rozpoznaj ( Komorki &Neur , P ol a c z e ni a &Synap , int Lx , int Ly ){

int LL=Lx*Ly ;
int ij ;
int i_rand ;
int iteruj =0;
int sila ; // potencjal aktywacyjny neuron

for ( int i=0 ; i<LL ; i++){
sila =0; // zerujemy dla kazdego neuronu i
i_rand =(int ) (LL*( rand ( ) / ( 1. 0+RANDMAX) ) ) ;

for ( int j =0; j<LL ; j ++){ //wyliczamy sile pozostalych neuronow
if ( i_rand==j ) continue ;
ij=i_rand *LL+j ;
sila+=Neur [ j ]->Poda jStan ( ) * Synap [ i j ]->PodajWartoscSynapsy ( ) ;
}
if ( sila <0) {
if ( Neur [i_rand]->Poda jStan ()==1) iteruj =1;
Neur [ i_rand ]->WpiszStan ( -1);
}
else {
if ( Neur [ i_rand]->PodajStan ()==-1) iteruj =1;
Neur [ i_rand]->WpiszStan ( 1 ) ;
}
}



 return iteruj ;
}

