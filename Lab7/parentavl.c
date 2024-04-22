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
    struct node *parent;
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
    node->parent = NULL;
    return node;
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

struct node *insertAVL(struct node *root, int value) {
    struct node *newNode = new_node(value);
    struct node *parent = NULL;
    struct node *current = root;

    if (root == NULL) {
        return newNode;
    }

    while (current != NULL) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (value < parent->value) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    newNode->parent = parent;

    struct node *unbalancedNode = newNode->parent;
    while (unbalancedNode != NULL) {
        update_height(unbalancedNode);
        int balance = balance_factor(unbalancedNode);

        if (balance > 1) {
            if (value < unbalancedNode->left->value) {
                unbalancedNode = rotate_right(unbalancedNode);
            } else {
                unbalancedNode->left = rotate_left(unbalancedNode->left);
                unbalancedNode = rotate_right(unbalancedNode);
            }
        } else if (balance < -1) {
            if (value > unbalancedNode->right->value) {
                unbalancedNode = rotate_left(unbalancedNode);
            } else {
                unbalancedNode->right = rotate_right(unbalancedNode->right);
                unbalancedNode = rotate_left(unbalancedNode);
            }
        }

        unbalancedNode = unbalancedNode->parent;
    }

    return root;
}

struct node *deleteAVL(struct node *root, int value) {
    struct node *current = root;

    while (current != NULL && current->value != value) {
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        return root;
    }

    struct node *parent = current->parent;

    if (current->left == NULL && current->right == NULL) {
        // Case 1: Node is a leaf
        if (parent == NULL) {
            free(current);
            return NULL;
        }

        if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }

        free(current);
    } else if (current->left == NULL || current->right == NULL) {
        // Case 2: Node has one child
        struct node *child = (current->left != NULL) ? current->left : current->right;
        if (parent == NULL) {
            free(current);
            return child;
        }

        if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }

        free(current);
    } else {
        // Case 3: Node has both children
        struct node *successor = find_min(current->right);
        current->value = successor->value;
        root = deleteAVL(root, successor->value);
    }
    struct node *unbalancedNode = parent;
    while (unbalancedNode != NULL) {
        update_height(unbalancedNode);
        int balance = balance_factor(unbalancedNode);

        if (balance > 1) {
            if (balance_factor(unbalancedNode->left) >= 0) {
                unbalancedNode = rotate_right(unbalancedNode);
            } else {
                unbalancedNode->left = rotate_left(unbalancedNode->left);
                unbalancedNode = rotate_right(unbalancedNode);
            }
        } else if (balance < -1) {
            if (balance_factor(unbalancedNode->right) <= 0) {
                unbalancedNode = rotate_left(unbalancedNode);
            } else {
                unbalancedNode->right = rotate_right(unbalancedNode->right);
                unbalancedNode = rotate_left(unbalancedNode);
            }
        }

        unbalancedNode = unbalancedNode->parent;
    }

    return root;
}

