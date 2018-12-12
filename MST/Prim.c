#include<stdio.h>
#include<stdlib.h>
#define N 10

struct Edge
{
    int u,v;
    int weight;
};
int all_vertex(int S[], int len)
{
    int i;
    for(i=0; i<len; i++)
        if(S[i]==0)
            return 0;
    return 1;
}
int main()
{
    int n, m, i, j, c=0, w=0, matrix[N][N] = {0}, S[N] = {0};
    struct Edge result[N], ed;
    FILE *file1 = fopen("input.txt", "r");
    fscanf(file1, "%d %d\n", &n, &m);
    for(i = 0; i < m; i++)
    {
        int u, v, weight;
        fscanf(file1, "%d %d %d\n", &u, &v, &weight);
        matrix[u][v] = weight;
        matrix[v][u] = weight;
    }


    S[0] = 1;
    while(!all_vertex(S, n))
    {

        ed.weight = 999;
        for(i=0; i<n; i++)
        {
            if(S[i]==1)
            {
                for(j=0; j<n; j++)
                {
                    if(matrix[i][j] && !S[j] && matrix[i][j]<ed.weight)
                    {
                        ed.u = i;
                        ed.v = j;
                        ed.weight = matrix[i][j];

                    }
                }
            }
        }

        S[ed.v]=1;
        result[c++] = ed;
        w+=ed.weight;
    }

    FILE *file2 = fopen("output2.txt", "w");
    for(i=0; i<c; i++)
        fprintf(file2, "%d %d %d\n", result[i].u, result[i].v, result[i].weight);
    fprintf(file2, "%d", w);

    return 0;
}
