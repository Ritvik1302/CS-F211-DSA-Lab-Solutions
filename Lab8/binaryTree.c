#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int element;
	struct node * left;
	struct node * right;
} Node;

typedef struct binaryTree{
	Node * root;
	int size;
} binaryTree;

binaryTree* createBT(){
	binaryTree *bt = malloc(sizeof(binaryTree));
	bt->root==NULL;
	bt->size=0;
	return bt;
}

Node * createNode(int e){
	Node * n = malloc(sizeof(Node));
	n->element = e;
	n->left = NULL;
	n->right = NULL;
	return n;
}
struct Queue
{
	int front, rear;
	int size;
	Node ** array;
};

struct Queue* createQueue(int size)
{
	struct Queue* queue = (struct Queue*) malloc(sizeof( struct Queue ));

	queue->front = queue->rear = -1;
	queue->size = size;

	queue->array = (struct node**) malloc
	(queue->size * sizeof( struct node* ));

	int i;
	for (i = 0; i < size; ++i)
		queue->array[i] = NULL;

	return queue;
}

int isEmpty(struct Queue* queue)
{
	return queue->front == -1;
}

int isFull(struct Queue* queue)
{  return queue->rear == queue->size - 1; }

int hasOnlyOneItem(struct Queue* queue)
{  return queue->front == queue->rear;  }

void Enqueue(Node *root, struct Queue* queue)
{
	if (isFull(queue))
		return;

	queue->array[++queue->rear] = root;

	if (isEmpty(queue))
		++queue->front;
}

struct node* Dequeue(struct Queue* queue)
{
	if (isEmpty(queue))
		return NULL;

	Node* temp = queue->array[queue->front];

	if (hasOnlyOneItem(queue))
		queue->front = queue->rear = -1;
	else
		++queue->front;

	return temp;
}

struct node* getFront(struct Queue* queue)
{  return queue->array[queue->front]; }

int hasBothChild(struct node* temp)
{
	return temp && temp->left && temp->right;
}

binaryTree * add_to_Btree(binaryTree* bt, int element, struct Queue* queue)
{
	Node *temp = createNode(element);
	Node * root = bt->root;
	if (root==NULL)
		root = temp;

	else
	{
		Node* front = getFront(queue);

		if (!front->left)
			front->left = temp;

		else if (!front->right)
			front->right = temp;

		if (hasBothChild(front))
			Dequeue(queue);
	}
	Enqueue(temp, queue);
	bt->size++;
	return bt;
}

int sizeOfBT(binaryTree* bt){
	return sizeof(binaryTree)+sizeof(struct node)*bt->size;
}

int main(){
	struct Queue* queue = createQueue(10);
	binaryTree* bt = createBT();
	int element[10]={1,2,3,4,5,6,7,8,9,10};
	for(int i=0;i<10;i++){
		add_to_Btree(bt,element[i],queue);
	}
	printf("(%d)\n",sizeOfBT(bt) );
}