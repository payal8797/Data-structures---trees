#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
    int height;
}node;

int max(int a, int b){
    if (a>b){
        return a;
    }
    else{
        return b;
    }
}

int height(node* root){
    if(root==NULL){
        return 0;
    }
    else{
        return (root->height);
    }
}

int getBalanceFactor(node* root){
    if(root==NULL){
        return 0;
    }
    else{
        return (height(root->left)-height(root->right));
    }
}

node* createRoot(int data){
    node* newNode= (node*)malloc(sizeof(node));
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->height=1;
    return newNode;
}

node* rightRotate(node* root){
    node* temp1=root->left;
    node* temp2=temp1->right;

    temp1->right=root;
    root->left=temp2;

    root->height= max(height(root->left), height(root->right))+1; 
    temp1->height= max(height(temp1->left), height(temp1->right))+1;
    return temp1;
}

node* leftRotate(node* root){
    node* temp1=root->right;
    node* temp2=temp1->left;

    temp1->left=root;
    root->right=temp2;

    root->height= max(height(root->left), height(root->right))+1; 
    temp1->height= max(height(temp1->left), height(temp1->right))+1;
    return temp1;
}

node *insert(node* root, int data){
    if (root==NULL){
        return createRoot(data);
    }
    if(root->data > data){
        root->left=insert(root->left, data);
    }
    else if(root->data < data){
        root->right=insert(root->right, data);
    }
    else{
        return root;
    }
    root->height=1+max(height(root->left), height(root->right));

    int balanceFactor= getBalanceFactor(root);

    if( balanceFactor>1 && data >root->left->data){
        return rightRotate(root);
    }
    if( balanceFactor>1 && data <root->left->data){
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    if( balanceFactor<-1 && data >root->right->data){
        return leftRotate(root);
    }
    if( balanceFactor<-1 && data <root->right->data){
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void preOrder(node* root){
    if(root==NULL){
        return;
    }
    else{
        printf("%d ", root->data); 
        preOrder(root->left); 
        preOrder(root->right); 
    }
}

int main(){
    node* root=NULL;
    int i, n, data;
    printf("Enter number of nodes you want to insert:");
    scanf("%d",&n);
    if (n<0){
        printf("Invalid input!!!");
    }
    else{
        for(i=0;i<n;i++){
            printf("Enter data:");
            scanf("%d",&data);
            root=insert(root, data);
        }
        printf("AVL Tree in preorder: ");
        preOrder(root);
    }
    printf("\n");
}