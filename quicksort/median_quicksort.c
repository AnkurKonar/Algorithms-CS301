#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

struct timeval time_start, time_end;
struct timezone tz;
long int cpu_time=0;
int t1=0,t2=0;

void input(int *a,int n)
{
    int i;
	srand(time(0));
	for(i=0;i<n;i++)
		a[i]=rand()%1000;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *a, int l, int r, int x)
{
	int i,j;
	for (i=l; i<r; i++)
		if (a[i] == x)
			break;
	swap(&a[i], &a[r]);
	i = l;
	for (j = l; j <= r - 1; j++)
	{
		if (a[j] <= x)
		{
			swap(&a[i], &a[j]);
			i++;
		}
	}
	swap(&a[i], &a[r]);
	return i;
}

int findMedian(int *a, int n)
{
	int key,i;
	for (i = 1; i < n; i++)
	{
		key = a[i];
		int j = i-1;
		while (j >= 0 && a[j] > key)
		{
			a[j+1] = a[j];
			j = j-1;
		}
		a[j+1] = key;
	}
	return a[n/2];
}

int smallest(int *a, int l, int r, int k)
{
	if (k > 0 && k <= r - l + 1)
	{
		int n = r-l+1;
		int i, median[(n+4)/5];
		for (i=0; i<n/5; i++)
			median[i] = findMedian(a+l+i*5, 5);
		if (i*5 < n)
		{
			median[i] = findMedian(a+l+i*5, n%5);
			i++;
		}
        int medOfMed = (i == 1)? median[i-1]:
                                 smallest(median, 0, i-1, i/2);
	int pos = partition(a, l, r, medOfMed);
	if (pos-l == k-1)
            return a[pos];
        if (pos-l > k-1)
            return smallest(a, l, pos-1, k);
        return smallest(a, pos+1, r, k-pos+l-1);
	}
}

void quicksort(int *a, int low, int high)
{
	if (low < high)
	{
		int n = high-low+1;
		int med = smallest(a, low, high, n/2);
		int pi = partition(a, low, high, med);
		quicksort(a, low, pi - 1);
		quicksort(a, pi + 1, high);
	}
}

void output(int *a, int n)
{
    int i;
	printf("\nSorted Array : \n");
	for (i=0;i<n;i++)
		printf("%d ",a[i]);
	cpu_time= ((time_end.tv_sec*1000000)+ time_end.tv_usec)-((time_start.tv_sec*1000000)+time_start.tv_usec);
	printf("\n\nCPU time for Quicksort = %ld microseconds= %9.6f seconds\n",cpu_time,(float)cpu_time/1000000);
}

void display(int *a, int n)
{
    int i;
	printf("\nInput Array : \n");
	for (i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}

int main()
{
	int n=1000;
	int a[n];
	input(a,n);
	display(a,n);
	t1=gettimeofday(&time_start,&tz);
	quicksort(a,0,n-1);
	t2=gettimeofday(&time_end,&tz);
	output(a,n);
	return 0;
}
