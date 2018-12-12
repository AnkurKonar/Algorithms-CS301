#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char A[1000][20];
int w=0;

void Max_heapify(int i, int n)
{
    char x[20];
    if((2*i+1)<n)
    {
        if((2*i+2)<n){
            if((strcmpi(A[i],A[(2*i+1)])<0) || (strcmpi(A[i],A[((2*i)+2)])<0))
            {
                if(strcmpi(A[(2*i+1)],A[(2*i+2)])>0)
                {
                    strcpy(x, A[i]);
                    strcpy(A[i],A[(2*i) +1]);
                    strcpy(A[(2*i)+1],x);
                    Max_heapify(((2*i)+1), n);
                }
                else if(strcmpi(A[(2*i+1)],A[(2*i+2)])<0){
                    strcpy(x, A[i]);
                    strcpy(A[i],A[(2*i) +2]);
                    strcpy(A[(2*i)+2],x);
                    Max_heapify(((2*i)+2), n);
                }
            }
        }
        else {
            if(strcmpi(A[(2*i+1)],A[(2*i+2)])>0){
                strcpy(x, A[i]);
                strcpy(A[i],A[(2*i) +1]);
                strcpy(A[(2*i)+1],x);
                Max_heapify(((2*i)+1), n);
            }
        }
    }
}

void Build_Max_heap(int n)
{
    int i;
    for(i=n/2;i>=0;i--)
    {
        Max_heapify(i, n);
    }
}

void HeapSort(int n)
{
    int i=n-1; char x[20];
    while(i>=0)
    {
        strcpy(x,A[0]);
        strcpy(A[0], A[i]);
        strcpy(A[i],x);
        Max_heapify(0,i);
        i--;
    }
}

void Insert_Max_heap(int *A, int *n, int x)
{
    int z,y;
    *n=*n +1;
    y =*n;
    A[y-1]=x;
    z=((y-1)/2) - 1;
    while(z>0)
    {
        Max_heapify(z, y);
        z=(z-1)/2;
    }
    Max_heapify(0, y);
}

void Read_From_File()
{
	int l;
	FILE *fp=fopen("strings_in.txt","r");
	char c=fgetc(fp);
	while(c!=EOF)
	{
		l=0;
		A[w][l]=c;
		l++;
		c=fgetc(fp);
		while(c!=' '&&c!=EOF)
		{
			A[w][l]=c;
			l++;
			c=fgetc(fp);
		}
		c=fgetc(fp);
		w++;
	}
	fclose(fp);
}

void Write_In_File()
{
	FILE *fp=fopen("strings_out.txt","w");
	int j=0,i;
	for(i=0;i<w;i++)
	{	j=0;
		while(A[i][j]!='\0')
		{
			fprintf(fp,"%c",A[i][j]);
			j++;
		}
		fprintf(fp,"%c",' ');
	}
	fclose(fp);
}

int main()
{
    Read_From_File();
    Build_Max_heap(w);
    /* HeapSort(A,n);
    printf("The sorted array is : ");
    for(i=0;i<n;i++){
        printf("%d ", A[i]);
    } */
    /*printf("\n");
    printf("Enter the new Element : ");
    scanf("%d", &x);
    Insert_Max_heap(A, &n, x);
    printf("The heap is : ");
    for(i=0;i<n;i++){
        printf("%d ", A[i]);
    }*/
    HeapSort(w);
    Write_In_File();


}
