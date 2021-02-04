#include<stdio.h>
#include<stdlib.h>

int count = 0;

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}node;

void merge(int arr[], int l, int m , int h){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = h - m;
    int LA[n1], RA[n2];

    for (i = 0; i < n1; i++)
        LA[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        RA[j] = arr[m + 1 + j];
    
    i=j=0;
    k=l;
    while (i < n1 && j < n2) {
        if (LA[i] <= RA[j]) {
            arr[k] = LA[i];
            i++;
        }
        else {
            arr[k] = RA[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = LA[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = RA[j];
        j++;
        k++;
    }
}

//Merge sort
void mergeSort(int array[], int l, int h)
{
    if (l<h) {
        int m = (l+h-1)/2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, h);
        merge(array, l, m, h);
    }

}

//count number of nodes in tree
void countNode(node* root){
    if (root==NULL){
        return ;
    }
    countNode(root->left);
    count++;
    countNode(root->right );
}

//storing the values in order in array storeArray
int* storeInorder(node* root, int sortArray[]){
    if (root==NULL){
        return NULL;
    }
    int static i=0;
    storeInorder(root->left, sortArray);
    sortArray[i++] = root->data;
    storeInorder(root->right,sortArray);
    return sortArray;
}

//insertion of elements in BST In inorder
void insertToBSTinInorder(node* root, int finalArray[]){
    if (root==NULL){
        return;
    }
    int static i=0;
    insertToBSTinInorder(root->left, finalArray);
    root->data = finalArray[i++];
    //printf("%d ->", root->data);
    insertToBSTinInorder(root->right, finalArray);
}

//printing values from tree in inorder
void printInorder(node* root){
    if (root==NULL){
        return;
    }
    printInorder(root->left);
    printf("%d ->", root->data);
    printInorder(root->right);
}

node* createTree(){
    node *p;
	int x;
	printf("Enter data(-1 for no data):");
	scanf("%d",&x);
	if(x==-1)
		return NULL;
	p=(node*)malloc(sizeof(node));
	p->data=x;
	printf("Enter left child of %d:\n",x);
	p->left=createTree();
	printf("Enter right child of %d:\n",x);
	p->right=createTree();
	return p;
}

int main()
{
    node* root=createTree();
    int i, count=0;
    int sortArray[count];

    countNode(root);
    printf("count:%d\n", count);

    printInorder(root);
    printf("\n");

    int* a = storeInorder(root, sortArray);
    for(i=0;i<count;i++){
        printf("%d\t",a[i]);
    }
    printf("\n");

    mergeSort(a, 0 , count-1);
    for(i=0; i<count;i++){
        printf("%d -> ",a[i]);
    }
    printf("\n");

    insertToBSTinInorder(root, a);
    printInorder(root);
}