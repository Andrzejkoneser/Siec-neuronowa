#include <stdio.h>
#include <cuda.h>

__global__ void add(int *a, int *b, int *c)
{
    //obliczam numer w¹tku na podstawie numeru bloku, w¹tku w bloku i iloœci w¹tków w bloku
    
    //tych "w¹tków" nie rozumiem, rozumiem podawanie rozmiaru bloku, ale takie kody s¹ w internecie i dzia³aj¹
    //wiêc te¿ takich u¿ywam
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	c[index] = a[index] + b[index];
}

#define N 100

int main()
{
    int *a, *b, *c;
	int *d_a, *d_b, *d_c;
	int size = N * sizeof( int );

	//alokujê pamiêæ w karcie graficznej

	cudaMalloc( (void **) &d_a, size );
	cudaMalloc( (void **) &d_b, size );
	cudaMalloc( (void **) &d_c, size );

	//alokujê pamieæ w procesorze

	a = (int *)malloc( size );
	b = (int *)malloc( size );
	c = (int *)malloc( size );

	for( int i = 0; i < N; i++ )
	{
		a[i] = i;
		b[i] = i*5
		c[i] = 0;
	}

	//kopiujê zawartoœæ z procesorka do karty graicznej
	
	cudaMemcpy( d_a, a, size, cudaMemcpyHostToDevice );
	cudaMemcpy( d_b, b, size, cudaMemcpyHostToDevice );

	//podajê rozmiar bloku na karcie //block_size - rozmiar bloku
	
	int block_size = 4;
	
	// Obliczenie liczby bloków koniczecznych do przetworzenia ca³ej tablicy  //n_blocks - liczba bloków
	
	int n_blocks = N / block_size + (N%block_size == 0 ? 0 : 1);  /*jak nieprawda to dodam jeszcze jeden blok,
	jak prawda to nie dodam, bo mieœci siê w iloœci bloków przy dzieleniu (bez reszty) *\
	
	add<<< (n_blocks, block_size>>>( d_a, d_b, d_c );
	//add<<< (N + (THREADS_PER_BLOCK-1)) / THREADS_PER_BLOCK, THREADS_PER_BLOCK >>>( d_a, d_b, d_c );

	//kopiujê wartoœci z tablicy c z karty graficznej do c na procesorze
	cudaMemcpy( c, d_c, size, cudaMemcpyDeviceToHost );


	//wyniki mojej pracy, sprawdzenie czy siê uda³o
	int i;
	for (i=0; i<N; i++) {
	printf( "c[%i] = %d\n",i,c[i] );
	}

	//zwalniam pamieæ w karcie i na procesorze
	
	free(a);
	free(b);
	free(c);
	cudaFree( d_a );
	cudaFree( d_b );
	cudaFree( d_c );
	
	return 0;
}
