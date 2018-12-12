#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct point{
    int x;
    int y;
};

double dist (struct point a, struct point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)-(a.y-b.y)*(a.y-b.y));
}

int aux_x_comp(struct point *a, struct point *b)
{
    if(a->x > b->x)
        return -1;
    else if(a->x < b->x)
        return 1;
    else
         return 0;
}

int aux_y_comp(struct point *a, struct point *b)
{
    if(a->y > b->y)
        return -1;
    else if(a->y < b->y)
        return 1;
    else
         return 0;
}

double minimum(double a, double b)
{
    return (a<b)? a : b;
}

double brute_force(struct point *a, int size)
{
    double d=9999;
    int i=0, j=0;
    for(i=0;i<size;i++)
    {
        for(j=i+1;j<size;j++)
        {
            if(dist(a[i], a[j])<d)
            {
                d=dist(a[i],a[j]);
            }
        }
    }
    return d;
}

double closestpair(struct point *x,struct point *y, int size)
{
    if(size<=3)
    {
        return brute_force(x, size);
    }

    int x_mid = size/2;
    struct point left_array[100];
    struct point right_array[100];
    int lindex = 0;
    int rindex = 0;
    struct point strip[100];
    int strip_size = 0,i;

    for(i=0;i<size;i++)
    {
       if(y[i].x <= x[x_mid].x)
       {
           left_array[lindex].x = y[i].x;
           left_array[lindex].y = y[i].y;
           lindex++;
       }
       else
       {
           right_array[rindex].x = y[i].x;
           right_array[rindex].y = y[i].y;
           rindex++;
       }
    }

    double d1 = closestpair(x, left_array,x_mid);
    double d2 = closestpair(x + x_mid, right_array,size-x_mid);
    double d = minimum(d1, d2);

    for(i=0;i<size;i++)
    {
        if(abs(x[x_mid].x - x[i].x) < d)
        {
            strip[strip_size]=x[i];
            strip_size++;
        }
    }

    int j;
    for(i=0;i<size;i++)
    {
        for(j=i+1;j<strip_size && dist(x[i], x[j])<d;j++)
        {
            d = dist(x[i], x[j]);
        }
    }

    return d;
}

int main()
{
    struct point points[100];
    struct point x[100];
    struct point y[100];
    int i=0;

    int size = 10;
    for(i=0;i<size;i++)
    {
        points[i].x=rand()%100;
        points[i].y=rand()%100;
    }

    printf("The points are: ");
    for(i=0;i<size;i++)
    {
        printf("%d %d \n", points[i].x, points[i].y);
    }

    memcpy(x, points, sizeof(points));
    memcpy(y, points, sizeof(points));

    qsort(x, size, sizeof(x[0]), aux_x_comp);
    qsort(y, size, sizeof(y[0]), aux_y_comp);

    double ans = closestpair(x, y, size);
    printf("\n%lf",ans);
}
