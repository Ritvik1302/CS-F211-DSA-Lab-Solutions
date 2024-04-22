#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct node
{
    int value;
    int height;
    struct node *left;
    struct node *right;
} Node;

typedef struct bst
{
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
    node->height = 1;
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

struct nodeLL
{
    Node *data;
    struct nodeLL *next;
};
typedef struct nodeLL nodeLL;
typedef nodeLL *NODELL;

struct linked_list
{
    int count;
    NODELL head;
    NODELL tail;
};
typedef struct linked_list linked_list;
typedef linked_list *LIST;

LIST createNewList()
{
    LIST myList;
    myList = (LIST)malloc(sizeof(struct linked_list));
    myList->count = 0;
    myList->head = NULL;
    myList->tail = NULL;
    return myList;
}

NODELL createNewNode(Node *data)
{
    NODELL myNode;
    myNode = (NODELL)malloc(sizeof(struct nodeLL));
    myNode->data = data;
    myNode->next = NULL;
    return myNode;
}

struct Queue
{
    LIST data;
};

void removeFirstNode(LIST list)
{
    if (list->head == NULL)
    {
        printf("No Node Present");
        return;
    }
    else if (list->head->next == NULL)
    {
        NODELL temp = list->head;
        list->head = NULL;
        list->tail = NULL;
        // free(temp);
    }
    else
    {
        NODELL temp = list->head;
        list->head = list->head->next;
        // free(temp);
    }
}
void insertNodeAtEnd(NODELL node, LIST list)
{
    if (list->tail == NULL)
    {
        list->tail = node;
        list->head = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
}
void insertNodeIntoList(NODELL node, LIST list)
{
    if (list->head == NULL)
    {
        list->tail = node;
        list->head = node;
    }
    else
    {
        node->next = list->head;
        list->head = node;
    }
}
typedef struct Queue Queue;
Queue *createQueue()
{
    Queue *myQueue = malloc(sizeof(Queue));
    myQueue->data = createNewList();
    return myQueue;
}

int isEmpty(Queue *queue)
{
    if (queue->data->head == NULL)
        return 1;
    return 0;
}

void enqueue(Queue *queue, Node *element)
{
    NODELL new = createNewNode(element);
    if (new == NULL)
        return;
    insertNodeAtEnd(new, queue->data);
    return;
}
void dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        return;
    }
    removeFirstNode(queue->data);
    return;
}
Node *front(Queue *queue)
{
    if (queue->data->head == NULL)
    {
        return NULL;
    }
    return queue->data->head->data;
}
void traverse_level_order(Node *node)
{
    if (node == NULL)
        return;
    Queue *q = createQueue();
    enqueue(q, node);
    while (!isEmpty(q))
    {
        Node *current_node = front(q);
        dequeue(q);
        printf("%d\t", current_node->value);
        if (current_node->left != NULL)
            enqueue(q, current_node->left);
        if (current_node->right != NULL)
            enqueue(q, current_node->right);
    }
    return;
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
        Node *current = bst->root;
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
        Node *current = bst->root;
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
        Node *current = bst->root;
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
    delete (bst, temp);
    return;
}

BST *constructBST(int *a, int size)
{
    BST *bst = new_bst();
    if (size == 0)
        bst->root = NULL;
    else
    {
        int i = 0;
        while (size--)
        {
            insert(bst, a[i]);
            i++;
        }
    }
    return bst;
}

int isValidBSTNode(Node *node, int min, int max)
{
    if (node == NULL)
        return 1;
    if (node->value < min || node->value > max)
        return 0;
    return isValidBSTNode(node->left, min, node->value) && isValidBSTNode(node->right, node->value, max);
}

int isValidBST(BST *bst)
{
    if (bst->root == NULL)
        return 1;
    return isValidBSTNode(bst->root, INT_MIN, INT_MAX);
}

int findHeight(Node *node)
{
    if (node == NULL)
        return 0;
    int a = 0, b = 0;
    a = findHeight(node->left) + 1;
    b = findHeight(node->right) + 1;
    if (a > b)
        return a;
    else
        return b;
}

// Home Exercise 1
int is_height_balanced(Node *node)
{
    if (node == NULL)
        return 1;
    int left_height = is_height_balanced(node->left);
    int right_height = is_height_balanced(node->right);

    if (left_height == -1 || right_height == -1 || abs(left_height - right_height) > 1)
        return -1;

    if (left_height > right_height)
        return 1 + left_height;
    else
        return 1 + right_height;
}

int is_avl(BST *bst)
{
    return is_height_balanced(bst->root) && isValidBST(bst);
}

// Task 1 & 2

void update_height(struct node *node)
{
    int left_height = (node->left != NULL) ? node->left->height : 0;
    int right_height = (node->right != NULL) ? node->right->height : 0;
    node->height = 1 + ((left_height > right_height) ? left_height : right_height);
}

int balance_factor(struct node *node)
{
    int left_height = (node->left != NULL) ? node->left->height : 0;
    int right_height = (node->right != NULL) ? node->right->height : 0;
    return left_height - right_height;
}
struct node *rotate_left(struct node *x)
{
    struct node *y = x->right;
    x->right = y->left;
    y->left = x;
    update_height(x);
    update_height(y);
    return y;
}

struct node *rotate_right(struct node *y)
{
    struct node *x = y->left;
    y->left = x->right;
    x->right = y;
    update_height(x);
    update_height(y);
    return x;
}

struct node *insertAVL(struct node *node, int value)
{
    if (node == NULL)
    {
        node = new_node(value);
    }
    else if (value < node->value)
    {
        node->left = insertAVL(node->left, value);
        update_height(node);
    }
    else
    {
        node->right = insertAVL(node->right, value);
        update_height(node);
    }
    int balance = balance_factor(node);
    if (balance < -1 || balance > 1)
    {
        if (value < node->value)
        {
            if (value < node->left->value)
            {
                // LL imbalance
                node = rotate_right(node);
            }
            else
            {
                // LR imbalance
                node->left = rotate_left(node->left);
                node = rotate_right(node);
            }
        }
        else
        {
            if (value > node->right->value)
            {
                // RR imbalance
                node = rotate_left(node);
            }
            else
            {
                // RL imbalance
                node->right = rotate_right(node->right);
                node = rotate_left(node);
            }
        }
    }
    return node;
}

Node *deleteAVL(Node *node, int value)
{
    if (node == NULL)
    {
        // value not found
        return NULL;
    }
    else if (value < node->value)
    {
        // value is in left subtree
        node->left = deleteAVL(node->left, value);
        node->height = 1 + height(node->left) > height(node->right) ? height(node->left) : height(node->right);
    }
    else if (value > node->value)
    {
        // value is in right subtree
        node->right = deleteAVL(node->right, value);
        node->height = 1 + height(node->left) > height(node->right) ? height(node->left) : height(node->right);
    }
    else
    {
        // value is at this node
        if (node->left == NULL && node->right == NULL)
        {
            // node is a leaf
            free(node);
            node = NULL;
        }
        else if (node->left == NULL)
        {
            // node has only right child
            struct node *temp = node;
            node = node->right;
            free(temp);
        }
        else if (node->right == NULL)
        {
            // node has only left child
            struct node *temp = node;
            node = node->left;
            free(temp);
        }
        else
        {
            // node has both children
            struct node *temp = predecessor(node);
            node->value = temp->value;
            node->left = deleteAVL(node->left, temp->value);
            node->height = 1 + height(node->left) > height(node->right) ? height(node->left) : height(node->right);
        }
    }
    int balance = balance_factor(node);
    // balance factor is left height - right height
    if (balance > 1)
    {
        // left subtree is longer
        if (balance_factor(node->left) >= 0)
        {
            // LL imbalance
            node = rotate_right(node);
            node->right->height = 1 + (height(node->right->left) >
                                               height(node->right->right)
                                           ? height(node->right->left)
                                           : height(node->right->right));
            node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
        }
        else
        {
            // LR imbalance
            node->left = rotate_left(node->left);
            node->left->left->height = 1 + (height(node->left->left->left) >
                                                    height(node->left->left->right)
                                                ? height(node->left->left->left)
                                                : height(node->left->left->right));
            node->left->height = 1 + (height(node->left->left) >
                                              height(node->left->right)
                                          ? height(node->left->left)
                                          : height(node->left->right));
            node = rotate_right(node);
            node->right->height = 1 + (height(node->right->left) >
                                               height(node->right->right)
                                           ? height(node->right->left)
                                           : height(node->right->right));
            node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
        }
    }
    else if (balance < -1)
    {
        // right subtree is longer
        if (balance_factor(node->right) <= 0)
        {
            // RR imbalance
            node = rotate_left(node);
            node->left->height = 1 + (height(node->left->left) >
                                              height(node->left->right)
                                          ? height(node->left->left)
                                          : height(node->left->right));
            node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
        }
        else
        {
            // RL imbalance
            node->right = rotate_right(node->right);
            node->right->right->height = 1 + (height(node->right->right->left) >
                                                      height(node->right->right->right)
                                                  ? height(node->right->right->left)
                                                  : height(node->right->right->right));
            node->right->height = 1 + (height(node->right->left) >
                                               height(node->right->right)
                                           ? height(node->right->left)
                                           : height(node->right->right));
            node = rotate_left(node);
            node->left->height = 1 + (height(node->left->left) >
                                              height(node->left->right)
                                          ? height(node->left->left)
                                          : height(node->left->right));
            node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
        }
    }
    return node;
}

int main()
{

    // FILE *fp = fopen("n_integers.txt", "r");
    // if (fp == NULL)
    // {
    //     printf("Error opening file\n");
    //     exit(1);
    // }
    // int *sizePer = NULL;
    // int **arr = NULL;
    // int n = 0;
    // int size_arr;
    // int i = 0;

    // while (fscanf(fp, "%d,[", &size_arr) == 1)
    // {
    //     sizePer = realloc(sizePer, (n + 1) * sizeof(int));
    //     arr = realloc(arr, (n + 1) * sizeof(int *));
    //     arr[n] = malloc(size_arr * sizeof(int));
    //     sizePer[n] = size_arr;
    //     for (int j = 0; j < size_arr; j++)
    //     {
    //         int val;
    //         fscanf(fp, "%d", &val);
    //         arr[n][j] = val;
    //     }

    //     fscanf(fp, "]");
    //     n++;
    // }
    // fclose(fp);

    // Task 1
    BST *bst = new_bst();
    bst->root = insertAVL(bst->root, 1);
    bst->root = insertAVL(bst->root, 2);
    bst->root = insertAVL(bst->root, 3);
    bst->root = insertAVL(bst->root, 4);
    bst->root = insertAVL(bst->root, 5);
    bst->root = insertAVL(bst->root, 6);
    bst->root = insertAVL(bst->root, 7);
    bst->root = insertAVL(bst->root, 8);
    bst->root = insertAVL(bst->root, 9);
    traverse_level_order(bst->root);
    return 0;
}