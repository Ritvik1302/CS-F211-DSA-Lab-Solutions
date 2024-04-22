#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int value;
    struct node *left;
    struct node *right;
    int height;
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
    node->height = 0;
    return node;
}
void traverse_bfs(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    Node *queue[100];
    int front = 0;
    int back = 0;
    queue[back++] = node;
    while (front != back)
    {
        Node *current = queue[front++];
        printf("%d ", current->value);
        if (current->left != NULL)
        {
            queue[back++] = current->left;
        }
        if (current->right != NULL)
        {
            queue[back++] = current->right;
        }
    }
}

int search(int arr[], int strt, int end, int value)
{
    int i;
    for (i = strt; i <= end; i++) {
        if (arr[i] == value)
            break;
    }
    return i;
}
Node *buildUtil(int in[], int post[], int inStart, int inEnd, int *pIndex) {
    if (inStart > inEnd) {
        return NULL;
    }
    Node *node = new_node(post[(*pIndex)--]);
    if (inStart == inEnd) {
        return node;
    }
    int index = search(in, inStart, inEnd, node->value);
    node->right = buildUtil(in, post, index + 1, inEnd, pIndex);
    node->left = buildUtil(in, post, inStart, index - 1, pIndex);
    return node;
}


Node *build_tree(int *in_order, int *post_order, int n) {
    int pIndex = n - 1;
    return buildUtil(in_order, post_order, 0, n - 1, &pIndex);
}

int main() 
{
    int n;
    scanf("%d", &n);
    int in_order[n];
    int post_order[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &in_order[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &post_order[i]);
    }
    BST *bst = new_bst();
    bst->root = build_tree(in_order, post_order, n);
    traverse_bfs(bst->root);
    printf("\n");
    return 0;
}