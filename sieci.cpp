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
}

