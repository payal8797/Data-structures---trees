#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right; 
}node;

int static count=0;
int static sizeLevel=0;
int static sizeVertical=0;
int static sizeLevelLeft=0;
int static sizeLevelRight=0;

//count nodes in tree
int countNode(node* root){ 
    if (root==NULL){
        return -1 ;
    }
    else{
        countNode(root->left);
        count+=1;
        countNode(root->right);
    }
    return count;
}

//height of tree
int height(node* root){
    if (root==NULL){
        return 0;
    }
    else{
        int leftHeight= height(root->left);
        int rightHeight= height(root->right);
        if (leftHeight>rightHeight){
            return (leftHeight+1);
        }
        else{
            return (rightHeight+1);
        }
    }
}

//print array
void printArrayLevel(int arrayLevelValues[], int count){
    int i;
    for (i=0;i<count;i++){
        printf("%d->",arrayLevelValues[i]);
    }
}

//find extreme indices of the tree
void findMinMax(node* root, int *min,int *max,int hd){
    if (root==NULL){
        return;
    }
    if (hd<*min){
        *min=hd;
    }
    else if(hd>*max){
        *max=hd;
    }
    findMinMax(root->left, min, max, hd-1);
    findMinMax(root->right, min, max, hd+1);
}

//prints the values of tree in vertical traversal
node* printValuesVertical(node* root, int i, int hd){
    int static j=0;
    if (root==NULL){
        return NULL;
    }
    if(hd==i){
        printf("%d\t", root->data);
        //arrayVertical[j++]=root->data;
    }
    //j=j+1;
    printValuesVertical(root->left, i, hd-1 );
    printValuesVertical(root->right, i, hd+1);
    
}

//vertical order traversal
node* verticalOrderTraversal(node* root){
    int min=0, max=0, i;
    findMinMax(root, &min,&max,0);
    //printf("\nminmax: %d %d", min, max);
    int *arrayVertical=(int*)malloc(sizeof(int)*count);
    //for(i=0;i<y;i++){
        //arrayVertical[i]=(int*)malloc(sizeof(int)*sizeVertical);
    //}
    for(i=min;i<=max;i++){
        printf("\n");
        printValuesVertical(root, i, 0);
    }
    //printArrayLevel(arrayVertical, count);
}

//level order traverse
node* levelOrder(node* root, int level, int arrayLevel[]){
    int static i=0;
    if(root==NULL){
        return NULL;
    }
    else{
        if(level==1){
            arrayLevel[i++]=root->data;
            sizeLevel+=1;
        }
        else{
            levelOrder(root->left, level-1,arrayLevel );
            levelOrder(root->right, level-1,arrayLevel);
        }
    }
}

//left view of the tree
node* leftView(node* root, int level,int *maxLevelLeft, int arrayLevel[]){
    int static i=0;
    if(root==NULL){
        return NULL;
    }
    else{
        if(*maxLevelLeft < level){
            //printf("%d->",root->data); 
            arrayLevel[i++]=root->data;
            *maxLevelLeft=level;
            sizeLevelLeft++;
        }
        leftView(root->left, level+1,maxLevelLeft, arrayLevel );
        leftView(root->right, level+1,maxLevelLeft, arrayLevel);
    }
}

//right view of the tree
node* rightView(node* root, int level,int *maxLevelRight, int arrayLevel[]){
    int static i=0;
    if(root==NULL){
        return NULL;
    }
    else{
        if(*maxLevelRight < level){
            //printf("%d->",root->data); 
            arrayLevel[i++]=root->data;
            *maxLevelRight=level;
            sizeLevelRight++;
        }
        rightView(root->right, level+1,maxLevelRight, arrayLevel );
        rightView(root->left, level+1,maxLevelRight, arrayLevel);
    }
}

//create binary tree
node* createTree(){
    int data;
    printf("Enter data(-1 for leaf node): ");
    scanf("%d",&data);
    if(data==-1){
        return NULL;
    }
    node* root=(node*)malloc(sizeof(node));
    root->data=data;
    printf("Enter value for left node of %d\n",data);
    root->left=createTree();
    printf("Enter value for right node of %d\n",data);
    root->right=createTree();
    return root;
}

int main(){
    int i, maxLevelLeft=0, maxLevelRight=0;
    node* root=createTree();

    int count= countNode(root);
    printf("Number of nodes: %d",count);

    int heightOfTree= height(root);
    printf("\nHeight of Tree is: %d",heightOfTree);

    int arrayLevel[count];
    printf("\nLevel Order: ");
    for(i=1;i<=heightOfTree+1;i++){
        levelOrder(root, i, arrayLevel);
    }
    printArrayLevel(arrayLevel, count);
    
    printf("\nVertical Traversal");
    verticalOrderTraversal(root);

    printf("\nLeft View");
    leftView(root, 1, &maxLevelLeft, arrayLevel);
    printArrayLevel(arrayLevel, sizeLevelLeft);

    printf("\nRight View");
    rightView(root, 1, &maxLevelRight, arrayLevel);
    printArrayLevel(arrayLevel, sizeLevelRight);
}