#include <stdio.h>
#include <stdlib.h>

int pindex=0;

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node* newNode (int data)
{
    struct node* temp = (struct node *) malloc( sizeof(struct node) );

    temp->data = data;
    temp->left = temp->right = NULL;

    return temp;
}

struct node* constructTree(int *pre,int *post,int l,int h,int size)
{
	if (pindex >= size || l > h)
        return NULL;
	struct node *root = newNode(pre[pindex]);
	pindex++;

	if (l == h)
        return root;

	int i;
    for (i=l;i<=h;i++)
    	if (pre[pindex]==post[i])
    			break;

    if (i<=h)
    {
        root->left = constructTree(pre,post,l,i,size);
        root->right = constructTree(pre,post,i+1,h,size);
    }

    return root;
}

void inorder (struct node* node)
{
    if (node == NULL)
        return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

void postorder(struct node* node)
{
  if (node == NULL)
        return;
  postorder(node->left);
  postorder(node->right);
  printf("%d ", node->data);
}


void preorder(struct node* node)
{
  if (node == NULL)
        return;
  printf("%d ", node->data);
  postorder(node->left);
  postorder(node->right);
}

int main()
{
	int pre[] = {1,2,4,8,9,5,3,6,7};
    int post[] = {8,9,4,5,2,6,7,3,1};
    int size = sizeof(pre)/sizeof(pre[0]);

    struct node *root=constructTree(pre,post,0,size-1,size);
    inorder(root);
	return 0;
}
