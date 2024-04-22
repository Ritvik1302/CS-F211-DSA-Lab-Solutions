#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct person{
    char * name;
    int user_id;
    int salary;
    int age;
}person;

typedef struct user_id_pointer
{
    int user_id;
    int index;
}user_id_pointer;

typedef struct user_id_node
{
    int num_keys;
    struct user_id_pointer keys[3];
    struct user_id_node * children[4];
    int isLeaf;

}user_id_node;

typedef struct salary_pointer
{
    int salary;
    int index;
}salary_pointer;

typedef struct salary_node
{
    int num_keys;
    struct salary_pointer keys[3];
    struct salary_node* children[4];
    int isLeaf;
}salary_node ;

typedef struct user_id_tree
{
    user_id_node *root;
} user_id_tree;

typedef struct salary_tree
{
    salary_node *root;
} salary_tree;

user_id_node *new_node()
{
    user_id_node *temp = malloc(sizeof(user_id_node));
    user_id_pointer p1 = {-1,-1};
    for (int i = 0; i < 3; i++)
    {
        temp->keys[i]= p1;
        temp->children[i] = NULL;
    }
    temp->children[3] = NULL;
    temp->isLeaf = 0;
    temp->num_keys = 0;
    return temp;
}

salary_node *new_node()
{
    user_id_node *temp = malloc(sizeof(salary_node));
    user_id_pointer p1 = {-1,-1};
    for (int i = 0; i < 3; i++)
    {
        temp->keys[i]= p1;
        temp->children[i] = NULL;
    }
    temp->children[3] = NULL;
    temp->isLeaf = 0;
    temp->num_keys = 0;
    return temp;
}

void user_id_insert_24(user_id_tree *tree, person val, int index)
{
    user_id_node *temp = tree->root;
    user_id_pointer p1 = {val.user_id,index};
    if (temp == NULL)
    {
        user_id_node *myNode = new_node();
        myNode->isLeaf = 1;
        myNode->keys[0] = p1;
        myNode->num_keys = 1;
        tree->root = myNode;
        return;
    }

    // traverse to leaf, splitting 4-nodes as we go
    // A 4-node is a node with 3 keys and 4 children
    user_id_node *parent = NULL;
    while (temp)
    {
        if (temp->num_keys == 3)
        {
            // split 4-node
            user_id_node *newNode = new_node();
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
                    if (parent->keys[0].user_id > temp->keys[1].user_id)
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
                    if (parent->keys[0].user_id > temp->keys[1].user_id)
                    {
                        parent->children[3] = parent->children[2];
                        parent->children[2] = parent->children[1];
                        parent->children[1] = newNode;
                        parent->keys[2] = parent->keys[1];
                        parent->keys[1] = parent->keys[0];
                        parent->keys[0] = temp->keys[1];
                    }
                    else if (parent->keys[1].user_id > temp->keys[1].user_id)
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
                if (val.user_id < parent->keys[i].user_id)
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
                if (val.user_id < parent->keys[i].user_id)
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
                if (val.user_id < parent->keys[i].user_id)
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
        if (val.user_id < parent->keys[i].user_id)
        {
            parent->keys[i + 1] = parent->keys[i];
        }
        else
        {
            parent->keys[i + 1] = p1;
            break;
        }
        if (i == 0)
        {
            parent->keys[i] = p1;
        }
    }
    parent->num_keys++;
}

void construct_user_id_two_four(user_id_tree* tree, person *arr, int size){
    for(int i=0; i<size; i++){
        user_id_insert_24(tree,arr[i],i);
    }
    return;
}

void salary_insert_24(salary_tree *tree, person val, int index)
{
    salary_node *temp = tree->root;
    salary_pointer p1 = {val.salary,index};
    if (temp == NULL)
    {
        salary_node *myNode = new_node();
        myNode->isLeaf = 1;
        myNode->keys[0] = p1;
        myNode->num_keys = 1;
        tree->root = myNode;
        return;
    }

    // traverse to leaf, splitting 4-nodes as we go
    // A 4-node is a node with 3 keys and 4 children
    salary_node *parent = NULL;
    while (temp)
    {
        if (temp->num_keys == 3)
        {
            // split 4-node
            salary_node *newNode = new_node();
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
                    if (parent->keys[0].salary > temp->keys[1].salary)
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
                    if (parent->keys[0].salary > temp->keys[1].salary)
                    {
                        parent->children[3] = parent->children[2];
                        parent->children[2] = parent->children[1];
                        parent->children[1] = newNode;
                        parent->keys[2] = parent->keys[1];
                        parent->keys[1] = parent->keys[0];
                        parent->keys[0] = temp->keys[1];
                    }
                    else if (parent->keys[1].salary > temp->keys[1].salary)
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
                if (val.salary < parent->keys[i].salary)
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
                if (val.salary < parent->keys[i].salary)
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
                if (val.salary < parent->keys[i].salary)
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
        if (val.salary < parent->keys[i].salary)
        {
            parent->keys[i + 1] = parent->keys[i];
        }
        else
        {
            parent->keys[i + 1] = p1;
            break;
        }
        if (i == 0)
        {
            parent->keys[i] = p1;
        }
    }
    parent->num_keys++;
}

void construct_salary_two_four(salary_tree* tree, person *arr, int size){
    for(int i=0; i<size; i++){
        salary_insert_24(tree,arr[i],i);
    }
    return;
}

int main()
{
    FILE * fp = fopen("people.csv","r");
    person * arr = malloc(sizeof(person));
    int n = 0;
    char name[50];
    int age;
    int salary;
    int id;
    while(fscanf(fp,"%[^,], %d, %d, %d\n",name,&age,&salary,&id)==4){
        arr = realloc(arr, (++n)*sizeof(person));
        arr[n-1].age =age;
        arr[n-1].user_id =id;
        arr[n-1].salary =salary;
        arr[n-1].name = malloc(sizeof(char)*50);
        strcpy(arr[n-1].name, name);
    }
    user_id_tree * id_tree;
    construct_user_id_two_four(id_tree,arr, n);
}