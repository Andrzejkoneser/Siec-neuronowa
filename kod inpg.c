int main ( int argc , char ** argv )
{
if ( argc != 4 )
    {
    cout<<"Poprawny format polecenia: "<<endl ;
    cout<<argv [0]<<" PlikWEObrazek1 PlikWEObrazek2 PlikWE3"<<endl ;
return 0 ;
}

cout<<endl<<endl<<"Siec neuronowa uczy sie wzorcow ..."<<endl ;

int Lx , Ly ;
int Lx_temp , Ly_temp ;

    WczytajParametryObrazka ( argv [1] , Lx , Ly ) ;
    Lx_temp=Lx ; Ly_temp=Ly ;

    WczytajParametryObrazka ( argv [2] , Lx , Ly ) ;
    if ( Lx_temp!=Lx || Ly_temp!=Ly ){
        cout<<"Rozne rozmiary siatki pikseli"<<endl ;
        cout<<"Wychodze do systemu ..."<<endl ;
        exit (1);
        }

    cout<<"Odczytane wartosci Lx="<<Lx<<"\t"<<"Ly="<<Ly<<endl ;

    AlokujNeurony ( Neur , Lx , Ly ) ;

    AlokujSynapsy ( Synap , Lx*Ly , Lx*Ly ) ;

    ResetujNeurony ( Neur ) ;
    ResetujSynapsy ( Synap ) ;

    WczytajObrazek ( Neur , argv [1] ) ;
    WczytajSynapsy ( Neur , Synap , Lx , Ly ) ;
cout<<"Obrazek 1:"<<endl ;
    PokazStanyNeuronow ( Neur , Lx , Ly ) ;

    ResetujNeurony ( Neur ) ;
    WczytajObrazek ( Neur , argv [2] ) ;
    WczytajSynapsy ( Neur , Synap , Lx , Ly ) ;
cout<<"Obrazek 2:"<<endl ;
    PokazStanyNeuronow ( Neur , Lx , Ly ) ;

   ResetujNeurony ( Neur ) ;
    WczytajDowolnyObrazek ( Neur , argv [3] , Lx , Ly ) ;
    cout<<"Obrazek przeznaczony do rozpoznania:"<<endl ;
    PokazStanyNeuronow ( Neur , Lx , Ly ) ;


int iteruj =1;
int krok =1;
    while ( iteruj){
        iteruj=Rozpoznaj ( Neur , Synap , Lx , Ly ) ;

cout<<"--------------------------------------------"<<endl ;
cout<<"Rozpoznanie - krok "<<krok<<endl ;

    PokazStanyNeuronow ( Neur , Lx , Ly ) ;
    krok++;
    }

return 0 ;
}
