#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inp(int n,int** x)
{
    int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			x[i][j]=rand()%10;
}

void display(int n,int** x)
{
    int i, j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%d\t",x[i][j]);
		printf("\n");
	}
}

void MatrixMultiply(int n, int** A, int Ar, int Ac, int** B, int Br, int Bc, int **C, int Cr, int Cc)
{
	if(n == 1)
	{
		C[Cr][Cc] += A[Ar][Ac] * B[Br][Bc]	;
	}
	else
	{
		MatrixMultiply(n/2, A, Ar, Ac,B, Br, Bc, C, Cr, Cc);
		MatrixMultiply(n/2, A, Ar, Ac+n/2, B, Br+n/2, Bc, C, Cr, Cc);
		MatrixMultiply(n/2, A, Ar, Ac, B, Br, Bc+n/2, C, Cr, Cc+n/2);
		MatrixMultiply(n/2, A, Ar, Ac+n/2, B, Br+n/2, Bc+n/2, C, Cr, Cc+n/2);
		MatrixMultiply(n/2, A, Ar+n/2, Ac, B, Br, Bc, C, Cr+n/2, Cc);
		MatrixMultiply(n/2, A, Ar+n/2, Ac+n/2, B, Br+n/2, Bc, C, Cr+n/2, Cc);
		MatrixMultiply(n/2, A, Ar+n/2, Ac, B, Br, Bc+n/2, C, Cr+n/2, Cc+n/2);
		MatrixMultiply(n/2, A, Ar+n/2, Ac+n/2, B, Br+n/2, Bc+n/2, C, Cr+n/2, Cc+n/2);
	}

}

int main()
{
	int n,i, j;
	printf("Dimension of matrices : ");
	scanf("%d", &n);


	int **A = (int **)malloc(n * sizeof(int *));
	for (i=0; i<n; i++)
		A[i] = (int *)malloc(n * sizeof(int));

	int **B = (int **)malloc(n * sizeof(int *));
	for (i=0; i<n; i++)
		B[i] = (int *)malloc(n * sizeof(int));

	int **C = (int **)malloc(n * sizeof(int *));
	for (i=0; i<n; i++)
		C[i] = (int *)malloc(n * sizeof(int));


	srand(time(0));
	inp(n,A);
	inp(n,B);
	for(i=0 ; i<n ; i++)
		for(j=0 ; j<n ; j++)
			C[i][j] = 0;


	MatrixMultiply(n , A, 0, 0, B, 0, 0, C, 0, 0);


	printf("\nMatrix A:\n");
	display(n,A);
	printf("\nMatrix B:\n");
	display(n,B);
	printf("\nMatrix A x B:\n");
	display(n,C);


	return 0;
}
