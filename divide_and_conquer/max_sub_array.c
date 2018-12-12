#include <stdio.h>
#include <stdlib.h>

int mid_sub_array(int *a, int low, int high)
{
    int i;
    int mid=(low+high)/2;
    int lsum = -9999;
    int rsum = -9999;
    int sum = 0;
    for(i=mid;i>=low;i--)
    {
        sum+=a[i];
        if(sum>lsum)
        {
            lsum=sum;
        }
    }
    sum=0;
    for(i=mid+1;i<=high;i++)
    {
        sum+=a[i];
        if(sum>rsum)
        {
            rsum=sum;
        }
    }

    return (rsum+lsum);
}

int max_sub_array(int *a, int low, int high)
{
    int mid;
    if(low==high){
        return a[low];
    }
    mid=(low+high)/2;
    int lsum=max_sub_array(a,low,mid);
    int rsum=max_sub_array(a,mid+1,high);
    int csum= mid_sub_array(a,low,high);
    if(lsum>rsum && lsum>csum){
            return lsum;
    }
    else if (rsum>lsum && rsum>csum)
    {
        return rsum;
    }
    else
        return csum;
}

int main()
{
    int arr[]={1, 2, -1, 4, 5, 6, 7, 8};
    int size = sizeof(arr)/sizeof(arr[0]);
    int x=max_sub_array(arr,0,size-1);
    printf("%d", x);
    return 0;
}
