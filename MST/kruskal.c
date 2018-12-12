#include <stdio.h>
#include <stdlib.h>

/*

6 9
0 1 1
1 3 4
3 0 5
3 4 1
1 4 2
1 2 7
5 2 6
2 4 3
5 4 5

*/

struct subset
{
    int p;
    int rank;
};

struct Edge
{
    int beg;
    int end;
    int weight;
};

struct Graph
{
    int vertices;
    int edges;
    struct Edge* edge;
};

struct Graph * createGraph(int E, int V)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->vertices = V;
	graph->edges = E;
	graph->edge = (struct Edge*)malloc(graph->edges *sizeof(struct Edge));

	return graph;
}

void printGraph(struct Graph* graph)
{
	int i=0;
	printf("The number of edges: %d \n", graph->edges);
	printf("the number of vertices: %d \n", graph->vertices);
	while(i<graph->edges)
	{
		printf("beginning: %d ; end: %d ; weight: %d \n",graph->edge[i].beg,graph->edge[i].end,graph->edge[i].weight);
		i++;
	}
}

void sort(struct Graph* graph)
{
	int i, j, noOfEdges = graph->edges;
	struct Edge* tempEdge = (struct Edge*) malloc (sizeof(struct Edge));
	for (i = 1; i < noOfEdges; i++) {
		for (j = 0; j < noOfEdges - i; j++) {

			if (graph->edge[j].weight > graph->edge[j+1].weight) {

				tempEdge->beg = graph->edge[j].beg;
				tempEdge->end = graph->edge[j].end;
				tempEdge->weight = graph->edge[j].weight;

				graph->edge[j] = graph->edge[j+1];

				graph->edge[j+1].beg = tempEdge->beg;
				graph->edge[j+1].end = tempEdge->end;
				graph->edge[j+1].weight = tempEdge->weight;

			}
		}
	}
}

int find(struct subset * subsets, int i)
{
    if (subsets[i].p != i)
        subsets[i].p = find(subsets, subsets[i].p);

    return subsets[i].p;
}

void link(struct subset *subsets, int x, int y)
{
    if (subsets[x].rank < subsets[y].rank)
        subsets[x].p = y;
    else if (subsets[x].rank > subsets[y].rank)
        subsets[y].p = x;
    else
    {
        subsets[y].p = x;
        subsets[x].rank++;
    }
}

void Union(struct subset subsets[], int x, int y)
{
    link(subsets, find(subsets, x),find(subsets, y));
}


void kruskalMST(struct Graph* graph)
{
    int e_count=0, c=1, i=0, final_weight=0;
    sort(graph);
    struct Edge * final_edges = (struct Edge*) malloc (graph->vertices*sizeof(struct Edge));

    // Make set function
    struct subset *subsets =(struct subset*) malloc(graph->vertices* sizeof(struct subset) );
    int v;
    for (v = 0; v < graph->vertices; v++)
    {
        subsets[v].p = v;
        subsets[v].rank = 0;
    }

    // searching for the edges by selecting one by one
    while(e_count < graph->vertices-1)
    {
        struct Edge selected_edge = graph->edge[i++];
        int x = find(subsets, selected_edge.beg);
        int y = find(subsets, selected_edge.end);
        if (x != y)
        {
            final_edges[e_count++] = selected_edge;
            Union(subsets, x, y);
        }
    }
    printf("The final edges are: \n");
    i=0;
    while(i<e_count)
	{
		printf("beginning: %d ; end: %d ; weight: %d \n",final_edges[i].beg,final_edges[i].end,final_edges[i].weight);
		final_weight+= final_edges[i].weight;
		i++;
	}
	printf("total minimum distance: %d", final_weight);
}

int main()
{
	int e, v, i=0, a, b, c;
    scanf("%d %d",&v,&e);
    struct Graph* graph = createGraph(e,v);
    while(i<e)
    {
    	scanf("%d %d %d",&a,&b,&c);
    	graph->edge[i].beg = a;
        graph->edge[i].end = b;
        graph->edge[i].weight = c;
    	i++;
    }
    printGraph(graph);
    kruskalMST(graph);
    return 0;
}

