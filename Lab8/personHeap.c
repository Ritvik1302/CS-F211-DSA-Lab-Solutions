#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

struct timeval t1, t2;
double time_taken;

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};
typedef struct person person;

struct heap {
    person *data;
    int size;
    int capacity;
    int depth;
};
typedef struct heap* Heap;

Heap heap_create()
{
    Heap h = malloc(sizeof(struct heap));
    h->data = malloc(sizeof(person));
    h->size = 0;
    h->capacity = 1;
    h->depth = 0;
    return h;
}

Heap add_to_tree(Heap h, person element){
    if(h->size == h->capacity)
    {
        h->capacity*=2;
        h->data = realloc(h->data, h->capacity*sizeof(person));
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
    if (left < h->size && h->data[left].height > h->data[largest].height)
    {
        largest = left;
    }
    if (right < h->size && h->data[right].height > h->data[largest].height)
    {
        largest = right;
    }
    if (largest != index)
    {
        person temp = h->data[index];
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
    return (sizeof(struct heap)+h->capacity*sizeof(person));
}

void heap_sort(Heap h)
{
    h = build_max_heap(h);
    for (int i = h->size - 1; i >= 1; i--)
    {
        person temp = h->data[0];
        h->data[0] = h->data[i];
        h->data[i] = temp;
        h->size = h->size - 1;
        max_heapify(h, 0);
    }
}
int main(){
    FILE *fp;
    fp = fopen("dat10000.csv", "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }

    long int id = 0;
    char name[50];
    int age = 0;
    int height = 0;
    int weight = 0;
    int ind = 0;

    char *line = malloc(1000);
    long int lines = 0;
    while (fscanf(fp, "%ld,%[^,],%d,%d,%d\n", &id, name, &age, &height, &weight) == 5) {
        lines++;
    }

    fclose(fp);

    fp = fopen("dat10000.csv", "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }
    printf("%ld\n", lines);
    long int len = lines;
    person *arr = malloc(lines * sizeof(person));

    while (len--) {
        fscanf(fp, "%ld,%[^,],%d,%d,%d\n", &id, name, &age, &height, &weight);
        
        arr[ind].id = id;
        arr[ind].age = age;
        arr[ind].height = height;
        arr[ind].weight = weight;
        ind++;
        //printf("%ld %s %d\n",id,name,height);
    }
    fclose(fp);
    gettimeofday(&t1, NULL);
    Heap h = heap_create();
    for (int i=0;i<lines;i++){
        add_to_tree(h,arr[i]);
    }
    h = build_max_heap(h);
    heap_sort(h);
    gettimeofday(&t2,NULL);

    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

    printf("Time to Sort %f seconds to execute\n", time_taken);
}