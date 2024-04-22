#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int element;
    struct node * next;
}Node;

typedef struct list{
    int size;
    Node * head;
}*LIST;

struct heap {
    int *data;
    int size;
    int capacity;
    int depth;
};

typedef struct heap* Heap;

Heap heap_create()
{
	Heap h = malloc(sizeof(struct heap));
	h->data = malloc(sizeof(int));
	h->size = 0;
	h->capacity = 1;
	h->depth = 0;
	return h;
}

Heap add_to_tree(Heap h, int element){
	if(h->size == h->capacity)
	{
		h->capacity*=2;
		h->data = realloc(h->data, h->capacity*sizeof(int));
		h->depth++;
	}
	h->data[h->size++] = element;
	return h;
}

int parent(Heap h, int node){
	if(node == 0)return -1;
	else return node/2;
}
int left_child(Heap h, int node){
	if(node*2+1 >h->size)return -1;
	else return node*2+1;
}
int right_child(Heap h, int node){
	if(node*2+2 > h->size-1)return -1;
	else return node*2+2;
}

void min_heapify(Heap h, int index)
{
	int left = left_child(h, index);
	int right = right_child(h, index);
	int smallest = index;
	if (left < h->size && h->data[left] < h->data[smallest])
	{
		smallest = left;
	}
	if (right < h->size && h->data[right] < h->data[smallest])
	{
		smallest = right;
	}
	if (smallest != index)
	{
		int temp = h->data[index];
		h->data[index] = h->data[smallest];
		h->data[smallest] = temp;
		min_heapify(h, smallest);
	}
}

Heap build_min_heap(Heap heap){
    Heap h = heap_create();
    for(int i=0;i<heap->size;i++){
        add_to_tree(h,heap->data[i]);
    }
    for(int i=0;i<heap->size;i++){
        min_heapify(h,i);
    }
    return h;
}

void insert(Heap h, int value)
{
    add_to_tree(h, value);
    build_min_heap(h);
    return;
}

int minimum(Heap h)
{
    if (h->size == 0)
        return -1;    // -1 denotes that the heap is empty
    else
        return h->data[0];
}

int extract_minimum(Heap h)
{
    int min = minimum(h);
    h->data[0] = h->data[h->size];
    h->size--;
    build_min_heap(h);
    return min;
}

void increase_key(Heap h, int x, int k)
{
    h->data[x] = k;
    build_min_heap(h);
    return;
}

LIST merge_k_lists(Node **lists, int k) {

    Heap min_heap = heap_create();

    LIST merged_list = malloc(sizeof(struct list));
    merged_list->size = 0;
    merged_list->head = NULL;

    for (int i = 0; i < k; i++) {
        if (lists[i] != NULL) {
            insert(min_heap, lists[i]->element);
            lists[i] = lists[i]->next;
        }
    }

    while (min_heap->size > 0) {

        int min_value = extract_minimum(min_heap);

        Node *new_node = malloc(sizeof(Node));
        new_node->element = min_value;
        new_node->next = NULL;

        if (merged_list->head == NULL) {
            merged_list->head = new_node;
        } else {
            Node *temp = merged_list->head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
        }
        
        for (int i = 0; i < k; i++) {
            if (lists[i] != NULL && lists[i]->element == min_value) {
                lists[i] = lists[i]->next;
                if (lists[i] != NULL) {
                    insert(min_heap, lists[i]->element);
                }
                break;
            }
        }
    }

    return merged_list;
}