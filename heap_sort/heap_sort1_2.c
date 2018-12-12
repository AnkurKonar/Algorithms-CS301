#include <stdio.h>
#include <stdlib.h>

void Max_heapify(int *A, int i, int n)
{
    int x;
    if((2*i+1)<n)
    {
        if((2*i+2)<n){
            if((A[i]<A[(2*i+1)]) || (A[i]<A[((2*i)+2)]))
            {
                if(A[(2*i)+1]>A[((2*i)+2)])
                {
                    x = A[i];
                    A[i]=A[(2*i) +1];
                    A[(2*i)+1]=x;
                    Max_heapify(A,((2*i)+1), n);
                }
                else if(A[(2*i)+2]>A[((2*i)+1)]){
                    x = A[i];
                    A[i]=A[((2*i)+2)];
                    A[((2*i)+2)]=x;
                    Max_heapify(A, ((2*i)+2), n);
                }
            }
        }
        else {
            if(A[i]<A[(2*i+1)]){
                x = A[i];
                A[i]=A[(2*i) +1];
                A[(2*i)+1]=x;
                Max_heapify(A,((2*i)+1), n);
            }
        }
    }
}

void Build_Max_heap(int *A, int n)
{
    int i;
    for(i=n/2;i>=0;i--)
    {
        Max_heapify(A, i, n);
    }
}

void HeapSort(int *A, int n)
{
    int i=n-1, x;
    while(i>=0)
    {
        x = A[0];
        A[0]=A[i];
        A[i]=x;
        Max_heapify(A,0,i);
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
        Max_heapify(A, z, y);
        z=(z-1)/2;
    }
    Max_heapify(A, 0, y);
}

int main()
{
    int A[100], n, i, x;
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d", &A[i]);
    }
    Build_Max_heap(A,n);
    printf("The heap is : ");
    for(i=0;i<n;i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    /* HeapSort(A,n);
    printf("The sorted array is : ");
    for(i=0;i<n;i++){
        printf("%d ", A[i]);
    } */
    printf("\n");
    printf("Enter the new Element : ");
    scanf("%d", &x);
    Insert_Max_heap(A, &n, x);
    printf("The heap is : ");
    for(i=0;i<n;i++){
        printf("%d ", A[i]);
    }
    HeapSort(A,n);
    printf("\n The sorted array is : ");
    for(i=0;i<n;i++){
        printf("%d ", A[i]);
    }


}
