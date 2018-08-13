#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct node {
	char element;
	int freq;
	struct node *left, *right;
};

struct node node_array[8];
int size=0;

struct codes {
    char element;
    char *code;
};

struct codes codes_array[8];
int k=0;

void swap(struct node *x, struct node *y)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	*temp = *x;
	*x = *y;
	*y = *temp;
}

int parent(int i)
{
    return i/2;
}

void minheap(int i)
{
    if(i==0)
        return;
    int f = node_array[i].freq;
    if(node_array[parent(i)].freq>f)
    {
        swap(&node_array[parent(i)],&node_array[i]);
        minheap(parent(i));
    }
}

void insertminheap(struct node *x)
{
	node_array[size++] = *x;
	minheap(size-1);
}

void printnodes(int i)
{
	int j;
	for(j=0;j<i;j++)
	{
		printf("%c: %d \n", node_array[j].element,node_array[j].freq);
	}
}

void createnodes(char *A, int *freq, int i)
{
	int j;
	for(j=0;j<i;j++)
	{
		struct node *x  = (struct node *) malloc(sizeof(struct node));
		x->left = NULL;
		x->right = NULL;
		x->element = A[j];
		x->freq = freq[j];
		printf("%c: %d \n", x->element,x->freq);
		insertminheap(x);
	}
}

struct node * extractminheap()
{
    struct node *min = (struct node *)malloc(sizeof(struct node));
    *min = node_array[0];
    node_array[0] = node_array[size-1];
    sinkDown(0);
    size--;
    return min;
}

void sinkDown(int k)
{
    int smallest = k;
    int leftChildIdx = 2*k+1;
    int rightChildIdx = 2*k+2;
    if (leftChildIdx < size && node_array[smallest].freq >= node_array[leftChildIdx].freq)
    {
        smallest = leftChildIdx;
    }
    if (rightChildIdx < size && node_array[smallest].freq >= node_array[rightChildIdx].freq)
    {
        smallest = rightChildIdx;
    }
    if (smallest != k) {
        swap(&node_array[k], &node_array[smallest]);
        sinkDown(smallest);
    }
}


void setcodes(struct node *root, char *arr, int i)
{
    char c1, c2;
    if(root==NULL)
    {
        return;
    }
    if(root->left!=NULL || root->right!=NULL)
    {
        c1=root->left->element;
        c2=root->right->element;
    }
    if(root->left==NULL)
    {
        c1='0';
    }
    if(root->right==NULL)
    {
        c2='0';
    }
    FILE *file3 = fopen("tree.txt", "a");
    fprintf(file3,"%c %c %c %d\n", root->element,c1,c2, root->freq);
    fclose (file3);
    if(root->element == 'x')
    {
        arr[i]='0';
        setcodes(root->left,arr,i+1);
        arr[i]='1';
        setcodes(root->right,arr,i+1);
    }
    else {
        codes_array[k].element = root->element;
        codes_array[k].code = (char *)malloc(10*sizeof(char));
        arr[i]='\0';
        strcpy(codes_array[k].code, arr);
        k++;
    }
}

void printcodes(int i)
{
    int j;
	for(j=0;j<i;j++)
	{
		printf("%c: %s \n", codes_array[j].element,codes_array[j].code);
	}
}

void huffmantree()
{
    int i;
    char *arr = (char *)malloc(10*sizeof(char));
    while(size>1)
    {
        struct node *x = extractminheap();
        struct node *y = extractminheap();
        struct node *res = (struct node *)malloc(sizeof(struct node));
        res->freq = x->freq + y->freq;
        res->element = 'x';
        res->left = x;
        res->right = y;
        insertminheap(res);
    }
    printnodes(1);
    setcodes(&node_array[0], arr, 0);
    printcodes(8);
    FILE *file2 = fopen("code.txt", "w");
    for(i=0; i<8; i++)
        fprintf(file2,"%c %s\n", codes_array[i].element,codes_array[i].code);
}

int main()
{
	char n; int m, i=0; char A[100]; int freq[100];
    FILE *file_kl = NULL;
    file_kl=fopen("input.txt", "r");
    if(file_kl==NULL)
    {
        printf("Error Reading");
        return 0;
    }
    fscanf(file_kl, "%c %d\n", &n, &m);
    while(i<8)
    {
    	A[i] = n;
 		freq[i] = m;
 		i++;
 		fscanf(file_kl, "%c %d\n", &n, &m);
    }
    createnodes(A,freq,i);
    printnodes(i);
    huffmantree();
    /* printf("\n %c, %c, %c, %c, %c, %c, %c. %c, %c", node_array[0].element, node_array[0].left->element,node_array[0].right->element, node_array[0].left->left->element, node_array[0].left->right->element, node_array[0].right->right->element, node_array[0].right->left->element, node_array[0].right->left->right->element, node_array[0].right->left->left->element);
    FILE *file2 = fopen("output2.txt", "w");
    for(i=0; i<c; i++)
        fprintf(file2, "%d %d %d\n", result[i].u, result[i].v, result[i].weight);
    fprintf(file2, "%d", w); */
    return 0;
}
