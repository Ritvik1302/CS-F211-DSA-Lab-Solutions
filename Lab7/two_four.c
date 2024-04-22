#include <stdlib.h>
#include <stdio.h>
typedef struct node
{
    int keys[3];
    struct node *children[4];
    int num_keys;
    int isLeaf;
} Node;

typedef struct tree
{
    Node *root;
} Tree;
Node *new_node()
{
    Node *temp = malloc(sizeof(Node));
    for (int i = 0; i < 3; i++)
    {
        temp->keys[i] = 0;
        temp->children[i] = NULL;
    }
    temp->children[3]=NULL;
    temp->isLeaf = 0;
    temp->num_keys = 0;
    return temp;
}

void insert_24(Tree *tree, int val)
{
    Node *temp = tree->root;
    if (temp == NULL)
    {
        Node *myNode = new_node();
        myNode->isLeaf = 1;
        myNode->keys[0] = val;
        myNode->num_keys = 1;
        tree->root = myNode;
        return;
    }
    
    // traverse to leaf, splitting 4-nodes as we go
    // A 4-node is a node with 3 keys and 4 children
    Node *parent = NULL;
    while (temp)
    {
        if (temp->num_keys == 3)
        {
            // split 4-node
            Node *newNode = new_node();
            newNode->isLeaf = temp->isLeaf;
            newNode->children[0] = temp->children[2];
            newNode->children[1] = temp->children[3];
            newNode->keys[0] = temp->keys[2];
            newNode->num_keys = 1;
            temp->children[2] = NULL;
            temp->children[3] = NULL;
            temp->num_keys = 1;
            // insert new node into parent
            if (parent == NULL)
            {
                parent = new_node();
                parent->isLeaf = 0;
                parent->children[0] = temp;
                parent->children[1] = newNode;
                parent->keys[0] = temp->keys[1];
                parent->num_keys = 1;
                tree->root = parent;
                printf("Created new root node\n");
            }
            else
            // The parent must have 1 or 2 keys since all 3 nodes have been split
            {
                if (parent->num_keys == 1)
                {
                    if (parent->keys[0] > temp->keys[1])
                    {
                        parent->children[2] = parent->children[1];
                        parent->children[1] = newNode;
                        parent->keys[1] = parent->keys[0];
                        parent->keys[0] = temp->keys[1];
                    }
                    else
                    {
                        parent->children[2] = newNode;
                        parent->keys[1] = temp->keys[1];
                    }
                    parent->num_keys = 2;
                }
                // ... 
                // 2 keys in parent
                else
                // ...
                {
                    if (parent->keys[0] > temp->keys[1])
                    {
                        parent->children[3] = parent->children[2];
                        parent->children[2] = parent->children[1];
                        parent->children[1] = newNode;
                        parent->keys[2] = parent->keys[1];
                        parent->keys[1] = parent->keys[0];
                        parent->keys[0] = temp->keys[1];
                    }
                    else if (parent->keys[1] > temp->keys[1])
                    {
                        parent->children[3] = parent->children[2];
                        parent->children[2] = newNode;
                        parent->keys[2] = parent->keys[1];
                        parent->keys[1] = temp->keys[1];
                    }
                    else
                    {
                        parent->children[3] = newNode;
                        parent->keys[2] = temp->keys[1];
                    }
                    parent->num_keys = 3;
                }
                
            }
            // Find the correct parent and child for the next iteration
            for (int i = 0; i <= parent->num_keys; i++)
            {
                if (val < parent->keys[i])
                {
                    parent = parent->children[i];
                    break;
                }
                else if (i == parent->num_keys)
                {
                    parent = parent->children[i];
                    break;
                }
            }
            // Find the correct child for the next iteration
            for (int i = 0; i <= parent->num_keys; i++)
            { 
                if (val < parent->keys[i])
                {
                    temp = parent->children[i];
                    break;
                }
                else if (i == parent->num_keys)
                {
                    temp = parent->children[i];
                    break;
                }
            }
        }
        // If the node is not a 4-node, just traverse to the correct child
        else
        {
            parent = temp;
            // Find the correct child for the next iteration
            for (int i = 0; i < parent->num_keys; i++)
            {
                if (val < parent->keys[i])
                {
                    temp = parent->children[i];
                    break;
                }
            }
            if (parent == temp)
            {
                temp = parent->children[parent->num_keys];
            }
        }
    }
    // Insert the value into the leaf
    for (int i = parent->num_keys - 1; i >= 0; i--)
    {
        if (val < parent->keys[i])
        {
            parent->keys[i + 1] = parent->keys[i];
        }
        else
        {
            parent->keys[i + 1] = val;
            break;
        }
        if (i == 0)
        {
            parent->keys[i] = val;
        }
    }
    parent->num_keys++;
}

void print_tree(Node *node, int level)
{
    printf("%*s", level * 2, "");
    if (node == NULL)
    {
        return;
    }
    if (node->isLeaf == 1)
    {
        for (int i = 0; i < node->num_keys; i++)
        {
            printf("%d ", node->keys[i]);
        }
        printf("\n");
    }
    else
    {
        for (int i = 0; i < node->num_keys; i++)
        {
            printf("%d ", node->keys[i]);
        }
        printf("\n");
        for (int i = 0; i <= node->num_keys; i++)
        {
            print_tree(node->children[i], level + 1);
        }
    }
}

Node *search_24(Node *node, int val) {
    if (node == NULL) {
        return NULL; 
    }

    int i;
    for (i = 0; i < node->num_keys; i++) {
        if (val == node->keys[i]) {
            return node;
        } else if (val < node->keys[i]) {
            return search_24(node->children[i], val);
        }
    }
    return search_24(node->children[i], val);
}

Node *delete_24(Node *node, int val) {
    if (node == NULL) {
        return NULL; 
    }

    int i;
    for (i = 0; i < node->num_keys; i++) {
        if (val == node->keys[i]) {
            break;
        }
    }

    if (i < node->num_keys && val == node->keys[i]) {

        if (node->isLeaf && node->num_keys > 1) {
            for (int j = i; j < node->num_keys - 1; j++) {
                node->keys[j] = node->keys[j + 1];
            }
            node->num_keys--;
            return node;
        } else if (!node->isLeaf) {
            // Case 2: Internal node
            if (node->children[i]->num_keys > 1) {
                // Sub-case a: Left child has at least 2 keys
                // Replace with predecessor and recursively delete
                Node *pred = predecessor(node->children[i]);
                node->keys[i] = pred->keys[pred->num_keys - 1];
                node->children[i] = delete_24(node->children[i], pred->keys[pred->num_keys - 1]);
                return node;
            } else if (node->children[i + 1]->num_keys > 1) {
                // Sub-case b: Right child has at least 2 keys
                // Replace with successor and recursively delete
                Node *succ = successor(node->children[i + 1]);
                node->keys[i] = succ->keys[0];
                node->children[i + 1] = delete_24(node->children[i + 1], succ->keys[0]);
                return node;
            } else {
                // Sub-case c: Both children have only 1 key each
                // Merge the right child into the left child
                Node *mergedNode = merge_nodes(node->children[i], node->keys[i], node->children[i + 1]);
                for (int j = i; j < node->num_keys - 1; j++) {
                    node->keys[j] = node->keys[j + 1];
                    node->children[j + 1] = node->children[j + 2];
                }
                node->num_keys--;
                node->children[i] = mergedNode;
                // Recursively delete the key from the merged node
                node->children[i] = delete_24(node->children[i], val);
                return node;
            }
        }
    } else {
        // Case 3: Key not found in the node
        int childIdx = 0;
        while (childIdx < node->num_keys && val > node->keys[childIdx]) {
            childIdx++;
        }
        Node *child = node->children[childIdx];
        if (child->num_keys == 1) {
            // Ensure that all nodes we travel through will have at least 2 keys
            if (childIdx > 0 && node->children[childIdx - 1]->num_keys > 1) {
                // Move an element down from the parent into the child
                // and move an element from the sibling into the parent
                child->keys[1] = node->keys[childIdx - 1];
                node->keys[childIdx - 1] = node->children[childIdx - 1]->keys[node->children[childIdx - 1]->num_keys - 1];
                node->children[childIdx - 1]->num_keys--;
                child->num_keys++;
                // Now, descend into the child node
                return delete_24(child, val);
            } else if (childIdx < node->num_keys && node->children[childIdx + 1]->num_keys > 1) {
                // Move an element down from the parent into the child
                // and move an element from the sibling into the parent
                child->keys[1] = node->keys[childIdx];
                node->keys[childIdx] = node->children[childIdx + 1]->keys[0];
                for (int j = 0; j < node->children[childIdx + 1]->num_keys - 1; j++) {
                    node->children[childIdx + 1]->keys[j] = node->children[childIdx + 1]->keys[j + 1];
                }
                node->children[childIdx + 1]->num_keys--;
                child->num_keys++;
                // Now, descend into the child node
                return delete_24(child, val);
            } else {
                // Merge the child node with one of the siblings
                // and move an element down from the parent into the merged node
                if (childIdx > 0) {
                    Node *mergedNode = merge_nodes(node->children[childIdx - 1], node->keys[childIdx - 1], child);
                    for (int j = childIdx - 1; j < node->num_keys - 1; j++) {
                        node->keys[j] = node->keys[j + 1];
                        node->children[j] = node->children[j + 1];
                    }
                    node->num_keys--;
                    node->children[childIdx - 1] = mergedNode;
                    // Now, descend into the merged node
                    return delete_24(mergedNode, val);
                } else {
                    Node *mergedNode = merge_nodes(child, node->keys[childIdx], node->children[childIdx + 1]);
                    for (int j = childIdx; j < node->num_keys - 1; j++) {
                        node->keys[j] = node->keys[j + 1];
                        node->children[j + 1] = node->children[j + 2];
                    }
                    node->num_keys--;
                    node->children[childIdx] = mergedNode;
                    // Now, descend into the merged node
                    return delete_24(mergedNode, val);
                }
            }
        } else {
            // Node has at least 2 keys, proceed to descend into the child node
            return delete_24(child, val);
        }
    }

    return node; // Return the updated node
}

int main()
{
    Tree *tree = malloc(sizeof(Tree));
    tree->root = NULL;
    int keys [] = {4, 6, 14, 20, 2, 5, 10, 8, 15, 12, 18, 25, 16};
    for (int i = 0; i <= 12; i++)
    {
        insert_24(tree, keys[i]);
        printf("Tree after inserting %d\n", keys[i]);
        print_tree(tree->root, 0);
    }
}