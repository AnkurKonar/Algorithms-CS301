#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void swap(int *A, int *B)
{
    int x=*A;
    *A=*B;
    *B=x;
}

int partition(int *a, int beg, int end)
{
    int pivot = a[end];
    int part = beg-1;
    int i=0;
    for(i=beg;i<=end-1;i++)
    {
        if(a[i]<=pivot)
        {
            part++;
            swap(&a[i],&a[part]);
        }
    }

    swap(&a[part+1],&a[end]);
    return part+1;
}

void quicksort(int *A, int beg, int end)
{
    if(beg<end)
    {
        int part = partition(A,beg,end);
        quicksort(A,beg,part-1);
        quicksort(A,part+1,end);
    }
}
int main()
{
    int A[100],i,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        A[i]=rand()%1000;
    }
    printf("The array is: ");
    for(i=0;i<n;i++)
    {
        printf(" %d",A[i]);
    }

    struct timeval time_start, time_end;
    struct timezone tz;
    long int cpu_time=0;
    int t1=0,t2=0;

    t1=gettimeofday(&time_start,&tz);

    quicksort(A,0,n-1);

    t2=gettimeofday(&time_end,&tz);
    /* printf("t2=%d",t2);*/
    cpu_time= ((time_end.tv_sec*1000000)+ time_end.tv_usec)-((time_start.tv_sec*1000000)+time_start.tv_usec);

    printf("\nCPU time for your_function = %ld microsecs.= %9.6f secs.\n",cpu_time,(float)cpu_time/1000000);


    printf("\n The sorted array is: ");
    for(i=0;i<n;i++)
    {
        printf(" %d",A[i]);
    }
    return 0;
}
