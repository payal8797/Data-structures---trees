#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right; 
}node;

int static count=0; 
int flag=0;
int flag1=-1;
int static sizeHalf=0;
int static sizeFull= 0;
int static sizeLeaf= 0;
int static sizeLevel= 0;


void printArrayLevel(int arrayLevelValues[], int count){
    int i;
    for (i=0;i<count;i++){
        printf("%d->",arrayLevelValues[i]);
    }
}

void printArrayLevelAlpa(int arrayLevelValues[], int count){
    int i;
    for (i=0;i<count;i++){
        if(arrayLevelValues[i]==0){
            printf("L->");
        }
        else{
            printf("I->");
        }
    }
}

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

int* HalfNodes(node* root, int arrayNodes[]){
    if (root==NULL){
        return NULL;
    }
    else{
        if ((root->left==NULL && root->right!=NULL) || (root->left!=NULL && root->right==NULL)){
            arrayNodes[sizeHalf++]=root->data;
        }
        HalfNodes(root->left, arrayNodes);
        HalfNodes(root->right,arrayNodes);
    }
    return arrayNodes;
}

int* FullNodes(node* root, int arrayNodes[]){
    int static i=0;
    if (root==NULL){
        return NULL;
    }
    else{
        if (root->left!=NULL && root->right!=NULL){
            arrayNodes[sizeFull++]=root->data;
        }
        FullNodes(root->left, arrayNodes);
        FullNodes(root->right,arrayNodes);
    }
    return arrayNodes;
}

int* LeafNodes(node* root, int arrayNodes[]){
    int static i=0;
    if (root==NULL){
        return NULL;
    }
    else{
        if (root->left==NULL && root->right==NULL){
            arrayNodes[sizeLeaf++]=root->data;
        }
        LeafNodes(root->left, arrayNodes);
        LeafNodes(root->right,arrayNodes);
    }
    return arrayNodes;
}

int* inorderTraverse(node* root, int arrayLevel[]){ 
    int static i=0;
    if (root==NULL){
        return NULL;
    }
    else{
        inorderTraverse(root->left, arrayLevel);
        arrayLevel[i++]=root->data;
        inorderTraverse(root->right,arrayLevel);
    }
    return arrayLevel;
}

int* preorderTraverse(node* root, int arrayLevel[]){ 
    int static i;
    if (root==NULL){
        return NULL;
    }
    else{
        arrayLevel[i++]=root->data;
        preorderTraverse(root->left, arrayLevel);
        preorderTraverse(root->right,arrayLevel);
    }
    return arrayLevel;
}

int* postorderTraverse(node* root, int arrayLevel[]){ 
    int static i;
    if (root==NULL){
        return NULL;
    }
    else{
        postorderTraverse(root->left, arrayLevel);
        postorderTraverse(root->right,arrayLevel);
        arrayLevel[i++]=root->data;
    }
    return arrayLevel;
}

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


node* spiralTraverse(node* root,int level,int arrayLevel[], int flag1){
    int static i=0;
    if(root==NULL){
        return NULL;
    }
    else{
        if(level==1){
            //arrayLevel[i++]=root->data;
            //sizeLevel+=1;
            printf("%d->", root->data);
        }
        else{
            if(flag1==1){
                spiralTraverse(root->left, level-1,arrayLevel, flag1 );
                spiralTraverse(root->right, level-1,arrayLevel, flag1);
            }
            else{
                spiralTraverse(root->right, level-1,arrayLevel, flag1 );
                spiralTraverse(root->left, level-1,arrayLevel, flag1);
            }
        }
    }
}

void inorder(node* root){
    if(root==NULL){
        return ;
    }
    inorder(root->left);
    printf("%d->",root->data);
    inorder(root->right);
}

node* mirrorTree(node* root){
    node* temp1;
    if(root==NULL){
        return NULL;
    }
    mirrorTree(root->left);
    mirrorTree(root->right);
    temp1=root->left;
    root->left =root->right; 
    root->right= temp1;

}

void printPath(int arrayLevel[], int i){
    printf("\n");
    for(int j=0;j<i;j++){
        printf("%d->",arrayLevel[j]);
    }
}

node* rootToLeaf(node* root, int arrayLevel[],int i){
    if(root==NULL){
        return NULL;
    }
    else{
        arrayLevel[i]=root->data;
        i++;
        if(root->left==NULL && root->right==NULL){
            printPath(arrayLevel, i);
        }
        else{
            rootToLeaf(root->left,arrayLevel, i);
            rootToLeaf(root->right,arrayLevel, i);
        }
    }
}

void checkSum(int arrayLevel[],int i, int k){
    int sum=0;
    for(int j=0;j<i;j++){
        sum+=arrayLevel[j];
    }
    if(sum==k){
        printf("\nPath exists with given sum!!");
    }
    else{
        printf("\nPath does not exists with given sum!!");
    }
}

node* rootToLeafCheckSum(node* root, int arrayLevel[],int i, int k){
    if(root==NULL){
        return NULL;
    }
    else{
        arrayLevel[i]=root->data;
        i++;
        if(root->left==NULL && root->right==NULL){
            checkSum(arrayLevel, i, k);
        }
        else{
            rootToLeafCheckSum(root->left,arrayLevel, i, k);
            rootToLeafCheckSum(root->right,arrayLevel, i, k);
        }
    }
}

int maxElement(int arrayLevelValues[], int count){
    int i;
    int maxVal=arrayLevelValues[0];
    for(i=1;i<count;i++){
        if(arrayLevelValues[i]>maxVal){
            maxVal=arrayLevelValues[i];
        }
    }
    return maxVal;
}

int minElement(int arrayLevelValues[], int count){
    int i;
    int minVal=arrayLevelValues[0];
    for(i=1;i<count;i++){
        if(arrayLevelValues[i]<minVal){
            minVal=arrayLevelValues[i];
        }
    }
    return minVal;
}

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

int structurallySameTree(node* root1, node* root2, int flag){
    if(!root1 && !root2){
        flag=1;
    }
    else if(!root1 || !root2){
        flag=0;
    }
    else{
        if(root1->data==root2->data){
            flag=1;
        }
        else{
            flag=0;
        }
        structurallySameTree(root1->left, root2->left, flag);
        structurallySameTree(root1->right, root2->right, flag);
    }
    return flag;
}

void search(node* root, int key ){
    if(root==NULL){
        return;
    }
    else{
        if(root->data==key){
            flag=1;
        }
        search(root->left, key);
        search(root->right, key);
    }
}
int max(int a, int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}

int diameter(node* root){
    if(root==NULL){
        return 0;
    }
    int leftHt=height(root->left);
    //printf("\nleftHt: %d", leftHt);
    int rightHt=height(root->right);
    //printf("\nrightHt: %d", rightHt);
    int leftDia=diameter(root->left);
    //printf("\nleftDia: %d",leftDia);
    int rightDia= diameter(root->right);
    //printf("\nrightDia: %d", rightDia);

    return max((leftHt+rightHt+1),max(leftDia,rightDia));
}

node* lca(node* root, node* p1, node* p2){
    if(root==NULL){
        return NULL;
    }
    if (root==p1 ||root==p2)
    {
        return root;
    }
    node* left=lca(root->left, p1, p2);
    node* right= lca(root->right, p1, p2);
    if(left && right){
        return root;
    }
    else{
        if(left){
            return left;
        }
        else{
            return right;
        }
    }
}

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
    int key, n, i, j, k;

    //Create tree
    node* root=createTree();

    //count nodes
    int count= countNode(root);
    printf("Number of nodes: %d\n",count);

    //inorder Traversal
    int arrayLevel[count];
    int *arrayLevelValues=(int*)malloc(sizeof(int)*count);
    arrayLevelValues= inorderTraverse(root,arrayLevel);
    printf("\nInorder Tranversal - ");
    printArrayLevel(arrayLevelValues,count);
    arrayLevelValues=NULL;

    //Preorder Traversal
    arrayLevelValues=preorderTraverse(root,arrayLevel);
    printf("\nPreorder Tranversal - ");
    printArrayLevel(arrayLevelValues,count);

    //PostOrder Traversal
    arrayLevelValues= postorderTraverse(root,arrayLevel);
    printf("\nPostorder Tranversal - ");
    printArrayLevel(arrayLevelValues,count);
    arrayLevelValues=NULL;

    //Maximum Element 
    int maxEl= maxElement(arrayLevelValues,count);
    printf("\nMax Value: %d",maxEl);

    //Minimum element
    int minEl= minElement(arrayLevelValues,count);
    printf("\nMin Value: %d",minEl);

    //Search Element
    printf("\nEnter element you want to find: ");
    scanf("%d",&key);
    search(root, key);
    if(flag){
        printf("Value is present in tree!!");
    }
    else{
        printf("Value is not present in tree!!");
    }
    arrayLevelValues=NULL;

    //Height of tree
    int heightOfTree= height(root);
    printf("\nHeight of Tree is: %d\n",heightOfTree);

    //Half Nodes
    int* arrayNodes=(int*)malloc(sizeof(int)*count);
    arrayNodes= HalfNodes(root,arrayNodes);
    arrayNodes=(int*)realloc(arrayNodes,sizeHalf);
    printf("\nHalf nodes:");
    printArrayLevel(arrayNodes,sizeHalf);
    printf("\n");
    arrayNodes=NULL;

    //Full nodes
    arrayNodes=(int*)realloc(arrayNodes,count);
    arrayNodes= FullNodes(root,arrayNodes);
    arrayNodes=(int*)realloc(arrayNodes,sizeFull);
    printf("\nFull nodes:");
    printArrayLevel(arrayNodes,sizeFull);
    arrayNodes=NULL;

    //Leaf nodes
    arrayNodes=(int*)realloc(arrayNodes,count);
    arrayNodes= LeafNodes(root,arrayNodes);
    arrayNodes=(int*)realloc(arrayNodes,sizeLeaf);
    printf("\nLeaf nodes:");
    printArrayLevel(arrayNodes,sizeLeaf);
    arrayNodes=NULL;

    //Level Order
    printf("\nLevel Order: ");
    for(i=1;i<=heightOfTree+1;i++){
        levelOrder(root, i, arrayLevel);
    }
    printArrayLevel(arrayLevel, count);

    //Reverse Level Order
    printf("\nReverse Level Order: ");
    for(i=heightOfTree+1;i>=0;i--){
        levelOrder(root, i, arrayLevel);
    }
    printArrayLevel(arrayLevel, count);
    int *arrayDeep=(int*)malloc(sizeof(int)*count);
    j= heightOfTree+1;
    levelOrder(root, j, arrayDeep);
    arrayDeep=(int*)realloc(arrayDeep, sizeLevel);

    //Deepest node
    printf("\nDeepest level: ");
    printArrayLevel(arrayDeep, sizeLevel);
    //printf("\nsizelevel: %d",sizeLevel);
    printf("\nDeepest node: %d",arrayDeep[sizeLevel-1]);
    
    //leaf to leaf maximum path
    int dia= diameter(root);
    printf("\nDiameter: %d",dia);
    rootToLeaf(root, arrayLevel,0);

    //given a sum, if any root to leaf path exists
    printf("Enter sum: ");
    scanf("%d",&k);
    rootToLeafCheckSum(root, arrayLevel,0, k);

    //Mirror image of tree
    printf("Mirror Tree: ");
    mirrorTree(root);
    inorder(root);

    //Zigzag traversal
    printf("\nSpiral Tree: ");
    for(i=1;i<=heightOfTree+1;i++){
        spiralTraverse(root, i, arrayLevel, flag1);
        flag1*=-1;
    }
    free(root);
    free(arrayLevelValues);
    return 0;
}