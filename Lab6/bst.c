#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int value;
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

Node *new_node(int value) 
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
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
    printf("%d ", node->value);
    traverse_in_order(node->right);
}

//Task 1 Start
void traverse_pre_order(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    printf("%d ", node->value);
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
    printf("%d ", node->value);
}

void alter_traverse_in_order(Node *node)
{
    if (node == NULL)
    {
        printf("NULL ");
        return;
    }
    traverse_in_order(node->left);
    printf("%d ", node->value);
    traverse_in_order(node->right);
}

void alter_traverse_pre_order(Node *node)
{
    if (node == NULL)
    {
        printf("NULL ");
        return;
    }
    printf("%d ", node->value);
    traverse_pre_order(node->left);
    traverse_pre_order(node->right);
}

void alter_traverse_post_order(Node *node)
{
    if (node == NULL)
    {
        printf("NULL ");
        return;
    }
    traverse_post_order(node->left);
    traverse_post_order(node->right);
    printf("%d ", node->value);
}

void insert(BST *bst, int value)
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
        if (value < current->value) 
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
        if (key == current->value) 
        {
            return 1;
        } 
        else if (key < current->value) 
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
    return current->value;
}

int find_max(BST *bst)
{
    Node *current = bst->root;
    while (current->right != NULL) 
    {
        current = current->right;
    }
    return current->value;
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
            if (node->value < current->value)
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
            if (node->value < current->value)
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
            if (node->value < current->value)
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
BST *constructBST(int *a, int size) 
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
    if(node->value<min||node->value>max)return 0;
    return isValidBSTNode(node->left,min,node->value) && isValidBSTNode(node->right,node->value,max);
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

//Task 7
void flattenWrapper(BST *bst, Node * node){
    
    if (node == NULL)
    {
        return;
    }
    flattenWrapper(bst, node->left);
    insert(bst, node->value);
    flattenWrapper(bst, node->right);
    return;
}

BST * flattenBST(BST *bst){
    
    BST * newBST = new_bst();
    if (bst->root == NULL)
    {
        return NULL;
    }
    flattenWrapper(newBST, bst->root);
    return newBST;
}


//Home Exercise 1
struct nodeLL
{
    Node* data;
    struct nodeLL *next;
};
typedef struct nodeLL nodeLL;
typedef nodeLL * NODELL;

struct linked_list
{
    int count;
    NODELL head;
    NODELL tail;
};
typedef struct linked_list linked_list;
typedef linked_list * LIST;

LIST createNewList(){
	LIST myList;
	myList = (LIST) malloc(sizeof(struct linked_list));
	myList->count=0;
	myList->head=NULL;
	myList->tail=NULL;
	return myList;
	}

NODELL createNewNode(Node* data)
{
	NODELL myNode;
	myNode = (NODELL) malloc(sizeof(struct nodeLL));
	myNode->data=data;
	myNode->next=NULL;
	return myNode;
}

struct Queue{
    LIST data;
};

void removeFirstNode(LIST list){
    if (list->head == NULL) {
        printf("No Node Present");
        return;
    } else if (list->head->next == NULL) {
        NODELL temp = list->head;
        list->head = NULL;
        list->tail = NULL;  
        //free(temp);       
    } else {
        NODELL temp = list->head;
        list->head = list->head->next;
        //free(temp);  
    }
}
void insertNodeAtEnd(NODELL node, LIST list){
    if (list->tail == NULL) {
        list->tail = node;
        list->head = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
}
void insertNodeIntoList(NODELL node, LIST list){
    if (list->head == NULL) {
        list->tail = node;
        list->head = node;
    } else {
        node->next = list->head;
        list->head = node;
    }
}
typedef struct Queue Queue;
Queue *createQueue(){
    Queue* myQueue = malloc(sizeof(Queue));
    myQueue->data=createNewList();
    return myQueue;
}

int isEmpty(Queue *queue){
    if(queue->data->head==NULL)return 1;
    return 0;
}

void enqueue(Queue *queue, Node* element){
    NODELL new = createNewNode(element);
    if(new==NULL)return;
    insertNodeAtEnd(new,queue->data);
    return;
}
void dequeue(Queue *queue){
    if (isEmpty(queue)) {
        return;
    }
    removeFirstNode(queue->data);
    return;
}
Node* front(Queue* queue){
    if (queue->data->head == NULL) {
        return NULL;
    }
    return queue->data->head->data;
}

void traverse_level_order(Node* node){
    if(node==NULL)return;
    Queue *q = createQueue();
    enqueue(q,node);
    while(!isEmpty(q)){
        Node* current_node = front(q);
        dequeue(q);
        printf("%d\t",current_node->value);
        if(current_node->left!=NULL)enqueue(q,current_node->left);
        if(current_node->right!=NULL)enqueue(q,current_node->right);
    }
    return;
}

//Home Exercise 2
struct Stack{
	int top;
	LIST data;
};
typedef struct Stack Stack;
Stack *newStack(){
	LIST myList = createNewList();
	Stack * stack = (Stack* )malloc(sizeof(struct Stack));
	stack->top = -1;
	stack->data = myList;
	return stack;
}

void push(Stack *stack, Node* element){
	NODELL newNode = createNewNode(element);
	if(newNode==NULL)return;
	insertNodeIntoList(newNode,stack->data);
	stack->top++;
	return;
}

Node *top(Stack *stack){
	if(stack->top==-1)return NULL;
	else {
		return stack->data->head->data;
	}
}

void pop(Stack *stack){
	if(stack->top==-1){
		return;
	}
	else{
		removeFirstNode(stack->data);
		stack->top--;
		return;
	}
} 

int isEmptyStack(Stack *stack){
	if(stack->top==-1)return 1;
	else return 0;
}

void traverse_reverselevel_order(Node* node){
    if(node==NULL)return;
    Queue *q = createQueue();
    Stack *s = newStack();
    enqueue(q,node);
    while(!isEmpty(q)){
        Node* current_node = front(q);
        push(s,current_node);
        dequeue(q);
        if(current_node->right!=NULL)enqueue(q,current_node->right);
        if(current_node->left!=NULL)enqueue(q,current_node->left);
    }
    while(!isEmptyStack(s)){
        printf("%d\t",top(s)->value);
        pop(s);
    }
    return;
}

//Home Exercise 4
int i=0;
Node* get_in_order(Node *node, int k)
{
    if (node == NULL)
    {
        return NULL;
    }
    Node* left = get_in_order(node->left,k);
    if(left!=NULL)return left;
    
    i++;
    if(i==k)return node;

    return get_in_order(node->right,k);
}

int kthsmallest(BST* bst, int k){
    i = 0;
    return get_in_order((bst->root),k)->value;
}

//Home Exercise 5
BST *constructOBST(int *a, int *freq, int size) 
{
    BST *bst = new_bst();
    if(size == 0)
        bst->root = NULL;
    else {
        int i=0;
        while(size--){
            insert(bst, freq[i]);
            i++;
        }
    }
    
    return bst;
}
int main()
{
    FILE *fp = fopen("n_integers.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    int *sizePer=NULL;
    int **arr = NULL;
    int n = 0;
    int size_arr;
    int i = 0;

    while (fscanf(fp, "%d,[", &size_arr) == 1) {
        sizePer = realloc(sizePer,(n+1)*sizeof(int));
        arr = realloc(arr, (n + 1) * sizeof(int *));
        arr[n] = malloc(size_arr * sizeof(int));
        sizePer[n] = size_arr;
        for (int j = 0; j < size_arr; j++) {
            int val;
            fscanf(fp, "%d", &val);
            arr[n][j] = val;
        }

        fscanf(fp, "]");
        n++;
    }
    fclose(fp);

    BST *newBST[n];
    for(int i=0;i<n;i++){
        newBST[i]=constructBST(arr[i],sizePer[i]);
       // printf("%d ",findHeight(newBST[i]->root));
       // removeHalfNodes(newBST[i]);
       // printf("%d ",findHeight(newBST[i]->root));
       // printf("%d ",isValidBST(newBST[i]));
    }
    //traverse_in_order(newBST[0]->root);
    // BST *flattened = flattenBST(newBST[0]);
    // printf("%d ",findHeight(newBST[0]->root));
    // printf("%d ",findHeight(flattened->root));
    //traverse_level_order(newBST[0]->root);
    // traverse_reverselevel_order(newBST[0]->root);
    printf("%d ",kthsmallest(newBST[0],9));
    return 0;
}