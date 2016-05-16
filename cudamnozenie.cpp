#include "stdafx.h" // (czyli przekompilowane naglowki). Jest to biblioteka przyspieszajaca kompilacje programu, charakterystyczne dla Visual Studio.
#include <stdio.h>
#include <cuda.h>
#define ROW1 2
#define COL1 3
#define ROW2 3
#define COL2 2


__global__ float *tab mnozenie(float *tab1, float *tab2, float *tab3)
{
int i,j,k;
for(i=0;i<ROW1;i++)
    {
        for(j=0;j<COL2;j++)
            {
                 for(k=0;k<COL1;k++)
                  {
                     tab3[i][j]+=tab1[i][k]*tab2[k][j];            
                  }
            }
    }
    return tab3;
}


int main(void)
{
	float tab1[ROW1][COL1]={
            {1,2,3},
            {4,5,6}
               };
	float tab2[ROW2][COL2]={
            {7,8},
            {4,7},
            {2,1}
               };
	float tab3[ROW1][COL2]={};  

	rozmiar1 = (float *)malloc(ROW1*COL1*sizeof(float);       //liczymy rozmiary
	cudaMalloc1((void **)&tab1, rozmiar1);	//alokujemy pamiec na cpu
	rozmiar2 = (float *)malloc(ROW2*COL2*sizeof(float);        
	cudaMalloc2((void **)&tab2, rozmiar2);
	rozmiar3 = (float *)malloc(ROW1*COL2*sizeof(float);     
	cudaMalloc3((void **)&tab3, rozmiar3);  

								

	cudaMemcpy(tab1, tab2, tab3, rozmiar1, roamiar2,rozmiar3, cudaMemcpyHostToDevice);

	// Ustalenie rozmiaru bloku
	int rozmiar_bloku = 4;
	// Obliczenie liczby bloków koniczecznych do przetworzenia ca³ej tablicy 
	int liczba_blokow = N / rozmiar_bloku + (N%rozmiar_bloku == 0 ? 0 : 1);
		//co to jest to N tutaj? Bylo podane tak z niczego

	mnozenie << < liczba_blokow, rozmiar_bloku >> > (tab1,tab2,tab3); //skladnai wywolania funkcji
	cudaMemcpy(tab1, tab2, tab3 sizeof(float)*ilosc_blokow, cudaMemcpyDeviceToHost);


	for (int i = 0; i<N; i++) printf("%d %f\n", i, a_h[i]); 
	free(tab1); cudaFree(tab1);
	free(tab2); cudaFree(tab2);
	free(tab3); cudaFree(tab3);
}
