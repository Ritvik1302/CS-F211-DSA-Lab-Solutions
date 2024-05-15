#include <stdio.h>
#include <stdlib.h>

typedef struct nodeLL* NODE;
struct nodeLL{
    int ele;
    NODE next;
};

typedef struct linked_list* LIST;
struct linked_list{
    int count;
    NODE head;
};

LIST createNewList()
{
    LIST myList;
    myList = (LIST) malloc(sizeof(struct linked_list));
    myList->count=0;
    myList->head=NULL;
    return myList;
}

NODE createNewNode(int value)
{
    NODE myNode;
    myNode = (NODE) malloc(sizeof(struct nodeLL));
    myNode->ele=value;
    myNode->next=NULL;
    return myNode;
}

void printList(LIST l1)
{
    NODE temp = l1->head;
    printf("[HEAD] ->");
    while(temp != NULL)
    {
        printf(" %d ->", temp->ele);
        temp = temp->next;
    }
    printf(" [NULL]\n");
}

void insertLL(int ele, LIST l1){
    if(l1->head==NULL){
        l1->head = createNewNode(ele);
        return;
    }
    NODE temp = l1->head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next = createNewNode(ele);
    return;
}

typedef struct node {
    LIST list;
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
} Node;

typedef struct bst {
    Node *root;
} BST;

BST *new_bst()
{
    BST *bst = malloc(sizeof(BST));
    bst->root = NULL;
    return bst;
}

Node *new_node(int key, LIST l1)
{
    Node *node = malloc(sizeof(Node));
    node->list = l1;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void insert(BST *bst, Node* node)
{
    if (bst->root == NULL)
    {
        bst->root = node;
        return;
    }
    Node *current = bst->root;
    while (current != NULL)
    {
        if (node->key < current->key)
        {
            if (current->left == NULL)
            {
                current->left = node;
                node->parent = current;
                return;
            }
            current = current->left;
        }
        else
        {
            if (current->right == NULL)
            {
                current->right = node;
                node->parent = current;
                return;
            }
            current = current->right;
        }
    }
}

void readData(BST* bst, FILE* fp){

    int n;
    int key;
    int num;
    char buffer[1024];
    fscanf(fp,"%d\n",&n);

    for(int j=0;j<n;j++){
        fgets(buffer, 1024 , fp);
        //printf("%s",buffer);
        int i=0;
        LIST l1 = createNewList();
        int key;
        int a,b;
        while(buffer[i]>='0' && buffer[i]<='9'){
            if(buffer[i+1]>='0' && buffer[i+1]<='9')
            {
                int a = buffer[i] - '0';
                int b = buffer[i+1] - '0';
                int num = a*10+b;
                //printf("%d ", num);
                insertLL(num, l1);
                i+=3;
            }
            else 
            {
                int a = buffer[i] - '0';
                int num = a;
                //printf("%d ", num);
                insertLL(num, l1);
                i+=2;
            }
        }
        insert(bst,new_node(l1->head->ele,l1));
        //printf("\n");
    }
}

void insertInOrder(int v, int A[], int last)
{
    int j = last - 1;
    while(j >= 0 && v < A[j])
    {
        A[j+1] = A[j];
        j--;
    }
    A[j+1] = v;
}

void insertionSort(int A[], int n)
{
    for(int j = 1; j < n; j++)
    {
        insertInOrder(A[j], A, j);
    }
}

void sortList(Node * n1){

    if(n1 == NULL)return; // Base Condition

    LIST l1 = n1->list;
    
    if(l1->head == NULL){
        sortList(n1->left);
        sortList(n1->right);
        return; 
    }

    NODE temp = l1->head->next;
    LIST l2 = createNewList();
    insertLL(l1->head->ele, l2);

    int nodes = 0;
    int * arr = malloc(sizeof(int));

    while(temp!=NULL){
        nodes++;
        arr = realloc(arr, sizeof(int)*nodes);
        arr[nodes-1] = temp->ele;
        temp = temp->next;
    }

    insertionSort(arr,nodes);
    
    for(int i=0;i<nodes;i++){
        insertLL(arr[i], l2);
    }

    free(l1);

    n1->list = l2;

    sortList(n1->left);
    sortList(n1->right);

    return; 
}

void sortLists(BST * bst){
    Node* temp = bst->root;
    if(temp == NULL)return;
    else sortList(temp);
}

void traverse(Node* node, FILE *fp2){ 

    if(node == NULL){
        return;
    }

    traverse(node->left,fp2);
    LIST l1 = node->list;

    NODE temp = l1->head;
    while(temp != NULL){
        printf("%d ", temp->ele);
        fprintf(fp2,"%d ", temp->ele);
        temp = temp->next;
    }
    
    printf("\n");
    fprintf(fp2,"\n");
    traverse(node->right, fp2);
    return;
}

int main(int argc, char* argv[]){

    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    BST * bst = new_bst();
    FILE * fp2 = fopen("file2.txt","w");
    readData(bst,fp);
    sortLists(bst);
    traverse(bst->root,fp2);
}