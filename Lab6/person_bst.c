#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};
typedef struct person Person;

typedef struct node {
    Person value;
    struct node *left;
    struct node *right;
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

Node *new_node(Person person) 
{
    Node *node = malloc(sizeof(Node));
    node->value = person;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void traverse_in_order(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    traverse_in_order(node->left);
    printf("%d ", node->value.height);
    traverse_in_order(node->right);
}

//Task 1 Start
void traverse_pre_order(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    printf("%d ", node->value.height);
    traverse_pre_order(node->left);
    traverse_pre_order(node->right);
}

void traverse_post_order(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    traverse_post_order(node->left);
    traverse_post_order(node->right);
    printf("%d ", node->value.height);
}

void insert(BST *bst, Person value)
{
    Node *node = new_node(value);
    if (bst->root == NULL) 
    {
        bst->root = node;
        return;
    }
    Node *current = bst->root;
    while (current != NULL) 
    {
        if (value.height < current->value.height) 
        {
            if (current->left == NULL) 
            {
                current->left = node;
                return;
            }
            current = current->left;
        } 
        else 
        {
            if (current->right == NULL) 
            {
                current->right = node;
                return;
            }
            current = current->right;
        }
    }
}

int search(BST *bst, int key)
{
    Node *current = bst->root;
    while (current != NULL) 
    {
        if (key == current->value.height) 
        {
            return 1;
        } 
        else if (key < current->value.height) 
        {
            current = current->left;
        } 
        else 
        {
            current = current->right;
        }
    }
    return 0;
}

int find_min(BST *bst)
{
    Node *current = bst->root;
    while (current->left != NULL) 
    {
        current = current->left;
    }
    return current->value.height;
}

int find_max(BST *bst)
{
    Node *current = bst->root;
    while (current->right != NULL) 
    {
        current = current->right;
    }
    return current->value.height;
}

Node *predecessor(Node *node)
{
    if (node->left == NULL)
    {
        return NULL;
    }
    Node *current = node->left;
    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

Node *successor(Node *node)
{
    if (node->right == NULL)
    {
        return NULL;
    }
    Node *current = node->right;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

void delete(BST *bst, Node *node)
{
    if (node == NULL)
        return;
    if (node->left == NULL && node->right == NULL)
    {
        // Node is a leaf
        Node* current = bst->root;
        while (current != NULL)
        {
            if (current->left == node)
            {
                current->left = NULL;
                break;
            }
            if (current->right == node)
            {
                current->right = NULL;
                break;
            }
            if (node->value.height < current->value.height)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }
    
    if (node->left == NULL)
    {
        // Node only has right child
        Node* current = bst->root;
        if (current == node)
        {
            bst->root = node->right;
            free(node);
            return;
        }
        while (current != NULL)
        {
            if (current->left == node)
            {
                current->left = node->right;
                break;
            }
            if (current->right == node)
            {
                current->right = node->right;
                break;
            }
            if (node->value.height < current->value.height)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }

    if (node->right == NULL)
    {
        // Node only has left child
        Node* current = bst->root;
        if (current == node)
        {
            bst->root = node->left;
            free(node);
            return;
        }
        while (current != NULL)
        {
            if (current->left == node)
            {
                current->left = node->left;
                break;
            }
            if (current->right == node)
            {
                current->right = node->left;
                break;
            }
            if (node->value.height < current->value.height)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }

    // Node has both children
    Node *temp = successor(node);
    node->value = temp->value;
    delete(bst, temp);
    return;
}

//Task 2
BST *constructBST(Person *a, int size) 
{
    BST *bst = new_bst();
    if(size == 0)
        bst->root = NULL;
    else {
        int i=0;
        while(size--){
            insert(bst, a[i]);
            i++;
        }
    }
    return bst;
}

//Task 3
int isValidBSTNode(Node * node, int min, int max){
    if(node==NULL)return 1;
    if(node->value.height<min||node->value.height>max)return 0;
    return isValidBSTNode(node->left,min,node->value.height) && isValidBSTNode(node->right,node->value.height,max);
}

int isValidBST(BST *bst){
    if(bst->root==NULL)return 1;
    return isValidBSTNode(bst->root, INT_MIN, INT_MAX);
}

int findHeight(Node * node){
    if(node == NULL)return 0;
    int a=0,b=0;
    a = findHeight(node->left)+1;
    b = findHeight(node->right)+1;
    if(a>b) return a;
    else return b;
}

void removeHalfNonRoot(Node * node, Node * prev){
    if(node == NULL)return;
    if(node->left==NULL && node->right!=NULL) {
        prev->left = node->left;
        free(node);
    }
    else if(
        node->right==NULL && node->left!=NULL) {
        prev->right = node->right;
        free(node);
        }
    if(node->left != NULL)
    removeHalfNonRoot(node -> left, node);
    if(node->right != NULL)
    removeHalfNonRoot(node -> right, node);
}

void removeHalfNodes(BST * bst){
    if(bst -> root == NULL)return;
    Node * node = bst->root;
    if(node->left==NULL && node->right!=NULL){
        bst->root = node->right;
        free(node);
    }
    if(node->right==NULL && node->left!=NULL){
        bst->root = node->left;
        free(node);
    }
    removeHalfNonRoot(node->left, node);
    removeHalfNonRoot(node->right, node);
}

int LCA(Node *root, Node * node1, Node * node2){
    if(root==NULL)return -1;
    if(root->value.height > node2->value.height && root->value.height > node1->value.height){
        return LCA(root->left,node1,node2);
    }
    else if(root->value.height < node2->value.height && root->value.height < node1->value.height){
        return LCA(root->right,node1,node2);
    }
    return root->value.height;
}

int main(int argc, char* argv[])
{
	FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }

    int id = 0;
    char name[50];
    int age = 0;
    int height = 0;
    int weight = 0;
    int ind = 0;

    char *line = malloc(1000);
    int lines = 0;

    while (fscanf(fp, "%d,%[^,],%d,%d,%d\n", &id, name, &age, &height, &weight) == 5) {
        lines++;
    }

    fclose(fp);
    printf("%d\n", lines);
    int len = lines;

    fp = fopen(argv[1], "r");
    Person *arr = malloc(lines * sizeof(Person));

    while (len--) {
    	fscanf(fp, "%d,%[^,],%d,%d,%d\n", &id, name, &age, &height, &weight);
    	
        arr[ind].id = id;
        arr[ind].name = malloc(50);
        strcpy(arr[ind].name,name);
        arr[ind].age = age;
        arr[ind].height = height;
        arr[ind].weight = weight;
        ind++;
        printf("%d %s %d\n",id,name,height);
    }
    fclose(fp);

    BST* newBST;
    
    newBST=constructBST(arr,lines);
    //printf("%d",LCA(newBST->root,newBST->root->left,newBST->root->left->left));
    
    return 0;
}