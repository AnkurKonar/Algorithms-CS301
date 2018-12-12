 #include<stdlib.h>
 #include<stdio.h>
 #include<malloc.h>
 #define HEIGHT 1

 struct node
 {
   int data;
   struct node* left;
   struct node* right;
   int height;
 };

 struct node* get_node(int val){
   struct node* new_node = (struct node*)malloc(sizeof(struct node));
   new_node->left = NULL;
   new_node->right = NULL;
   new_node->data = val;
   new_node->height = HEIGHT;
   return new_node;
 }
 int get_height(struct node* root){
   if(!root)
     return 0;
   else
     return root->height;
 }
 int get_balance(struct node* root){
   if(!root)
     return 0;
   return (get_height(root->left) - get_height(root->right));
 }
 int max(int a, int b){
   return (a > b) ? a : b;
 }

 struct node* left_rotate(struct node* root){
   struct node* right = root->right;
   struct node* left = right->left;

   right->left = root;
   root->right = left;

   root->height = max(get_height(root->left), get_height(root->right)) + 1;
   right->height = max(get_height(right->left), get_height(right->right)) + 1;

   return right;
 }

 struct node* right_rotate(struct node* root){
   struct node* left = root->left;
   struct node* right = left->right;

   left->right = root;
   root->left = right;

   root->height = max(get_height(root->left), get_height(root->right)) + 1;
   left->height = max(get_height(left->left), get_height(left->right)) + 1;

   return left;
 }
 struct node* insert(struct node* root, int val){

   if(!root){
     struct node* new_node = get_node(val);
     return new_node;
   }
   if(root->data > val)
     root->left = insert(root->left, val);
   else
     root->right = insert(root->right, val);

   root->height = max(get_height(root->left), get_height(root->right)) + 1;

   int balance = get_balance(root);

   if(balance > 1 && root->left->data > val){
     root = right_rotate(root);
   }

   else if(balance < -1 && root->right->data < val){
     root = left_rotate(root);
   }

   else if(balance > 1 && root->left->data < val){
     root->left = left_rotate(root->left);
     root = right_rotate(root);
   }

   else if(balance < -1 && root->right->data > val){
     root->right = right_rotate(root->right);
     root = left_rotate(root);
   }
   return root;
 }

 struct node* balance_tree(struct node* root){
   struct node* x, *y;
   int lheight,rheight;
   lheight = get_height(root->left);
   rheight = get_height(root->right);
   if(lheight >= rheight)
     x = root->left;
   else
     x = root->right;
   lheight = get_height(x->left);
   rheight = get_height(x->right);
   if(x == root->left){
     if(lheight >= rheight){
       y = x->left;
     }
     else
       y = x->right;
   }
   if(x == root->right){
     if(lheight > rheight){
       y = x->left;
     }
     else
       y = x->right;
   }
   //left-left case
   if(root->left == x && x->left == y){
     root = right_rotate(root);
   }
   //right-right case
   else if(x == root->right && x->right == y){
     root = left_rotate(root);
   }
   //left-right case
   else if(x == root->left && y == x->right){
     root->left = left_rotate(root->left);
     root = right_rotate(root);
   }
   //right-left case
   else if(x == root->right && y == x->left){
     root->right = right_rotate(root->right);
     root = left_rotate(root);
   }
   return root;
 }
 struct node* inorder_succ_right_tree(struct node* root){
   struct node* temp = root->right;
   while(temp->left){
     temp = temp->left;
   }
   return temp;
 }
 struct node* rightmost_elem(struct node* root){
   struct node* temp = root->right;
   while(temp->right){
     temp = temp->right;
   }
   return temp;
 }
 struct node* deletion(struct node* root, int val){

   if(!root)
     return NULL;
   if(root->data > val){
     root->left = deletion(root->left, val);
   }
   else if(root->data < val){
     root->right = deletion(root->right, val);
   }
   else{
     struct node* temp;
     if(root->left == NULL || root->right == NULL){
       if(root->left)
         temp = root->left;
       else if(root->right)
         temp = root->right;
       else
         temp = NULL;
       root = NULL;
       free(root);
       return temp;
     }
     else{
       temp = inorder_succ_right_tree(root);
       root->data = temp->data;
       root->right = deletion(root->right,temp->data);
     }
   }
   if(root){
     root->height = max(get_height(root->left), get_height(root->right)) + 1;
     int balance = get_balance(root);
     if(balance > 1 || balance < -1)
       root = balance_tree(root);
   }
   return root;
 }

 struct node * join_trees(struct node *root1, struct node *root2)
 {
  struct node *temp = rightmost_elem(root1);
  int value = temp->data;
  struct node *root3 = deletion(root1, temp->data);
  struct node *newnode = get_node(value);
  newnode->left = root3;
  newnode->right = root2;
  newnode->height = max(get_height(newnode->left), get_height(newnode->right)) + 1;
  struct node * root = balance_tree(newnode);
  return root;
 }
 void preorder(struct node* root){
   if(!root)
     return;
   printf("%d\t",root->data);
   preorder(root->left);
   preorder(root->right);
 }

 void inorder(struct node* root){
   if(!root)
     return;
   inorder(root->left);
   printf("%d\t",root->data);
   inorder(root->right);
 }
 void traverse(struct node *root,int *arr, int *n)
 {
     if(root==NULL)
     {
         return;
     }
        arr[*n]=root->data;
        *n = *n + 1;
        traverse(root->left,arr,n);
        traverse(root->right,arr,n);
 }
 void printarray(int *arr, int n)
 {
     int i=0;
     for(i=0;i<n;i++)
     {
         printf("\n %d",arr[i]);
     }
 }
  int main(){
   struct node* root1 = NULL;
   root1 = insert(root1, 5);
   root1 = insert(root1, 9);
   root1 = insert(root1, 10);
   root1 = insert(root1, 11);
   root1 = insert(root1, 17);
   root1 = insert(root1, 23);
   root1 = insert(root1, 31);
   root1 = insert(root1, 1);
   root1 = insert(root1, 2);
   struct node* root2 = NULL;
   root2 = insert(root2, 21);
   root2 = insert(root2, 7);
   root2 = insert(root2, 8);
   root2 = insert(root2, 4);
   root2 = insert(root2, 15);
   root2 = insert(root2, 20);
   root2 = insert(root2, 18);
   root2 = insert(root2, 6);
   root2 = insert(root2, 3);
   printf("Preorder1\n");
   preorder(root1);
   printf("\nInorder1\n");
   inorder(root1);
   printf("\nPreorder2\n");
   preorder(root2);
   printf("\nInorder2\n");
   inorder(root2);
   struct node* root = NULL;
   int arr[100];
   int n=0,i=0;
   traverse(root1,arr,&n);
   traverse(root2,arr,&n);
   for(i=0;i<n-1;i++)
   {
       root = insert(root,arr[i]);
   }
   printf("\nAfter joining\n");
   printf("\nPreorder\n");
   preorder(root);
   printf("\nInorder\n");
   inorder(root);
   return 0;
 }
