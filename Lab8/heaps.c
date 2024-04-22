#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int sizeOfHeap(Heap h){
	return (sizeof(struct heap)+h->capacity*sizeof(int));
}

int nodes_at_level(Heap h, int level){
	int * arr = h->data;
	if(pow(2,level)>h->size)return h->size-level+1;
	else return pow(2,level);
}

void heap_sort(Heap h)
{
	h = build_max_heap(h);
	for (int i = h->size - 1; i >= 1; i--)
	{
		int temp = h->data[0];
		h->data[0] = h->data[i];
		h->data[i] = temp;
		h->size = h->size - 1;
		max_heapify(h, 0);
	}
}


int main(){
	int element[10]={1,2,3,4,5,6,7,8,9,10};
	Heap heap = heap_create();

	for(int i=0;i<10;i++){
		add_to_tree(heap,element[i]);
	}
	printf("(%ld)\n",sizeof(int) );
	printf("(%d)\n",left_child(heap,2) );
	printf("(%d)\n",sizeOfHeap(heap) );
	printf("(%d)\n",nodes_at_level(heap,2) );
}