#include <stdio.h>
#include <stdlib.h>

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

void max_heapify(Heap h, int index)
{
	int left = left_child(h, index);
	int right = right_child(h, index);
	int largest = index;
	if (left < h->size && h->data[left] > h->data[largest])
	{
		largest = left;
	}
	if (right < h->size && h->data[right] > h->data[largest])
	{
		largest = right;
	}
	if (largest != index)
	{
		int temp = h->data[index];
		h->data[index] = h->data[largest];
		h->data[largest] = temp;
		max_heapify(h, largest);
	}
}

Heap build_max_heap(Heap heap){
    Heap h = heap_create();
    for(int i=0;i<heap->size;i++){
        add_to_tree(h,heap->data[i]);
    }
    for(int i=0;i<heap->size;i++){
        max_heapify(h,i);
    }
    return h;
}

void insert(Heap h, int value)
{
    add_to_tree(h, value);
    build_max_heap(h);
    return;
}

int maximum(Heap h)
{
    if (h->size == 0)
        return -1;    // -1 denotes that the heap is empty
    else
        return h->data[0];
}

int extract_maximum(Heap h)
{
    int max = maximum(h);
    h->data[0] = h->data[h->size];
    h->size--;
    build_max_heap(h);
    return max;
}

void increase_key(Heap h, int x, int k)
{
    h->data[x] = k;
    build_max_heap(h);
    return;
}

int pick_gifts(int *gifts, int k){
    int n = sizeof(gifts)/sizeof(int);
    int total = 0;
    Heap h = heap_create();
    for(int i=0;i<n;i++){
        insert(h,gifts[i]);
    }
    while(k--){
        total+=sqrt(maximum(h));
        increase_key(h,0,maximum(h)-sqrt(maximum(h)));
    }
    return total;
}