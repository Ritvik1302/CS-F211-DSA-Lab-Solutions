#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct song
{
    char *name;
    char *artist;
    int priority;
} song;

struct heap
{
    song *data;
    int size;
    int capacity;
    int depth;
};

typedef struct heap *Heap;

Heap heap_create()
{
    Heap h = malloc(sizeof(struct heap));
    h->data = malloc(sizeof(int));
    h->size = 0;
    h->capacity = 1;
    h->depth = 0;
    return h;
}

Heap add_to_tree(Heap h, song element)
{
    if (h->size == h->capacity)
    {
        h->capacity *= 2;
        h->data = realloc(h->data, h->capacity * sizeof(song));
        h->depth++;
    }
    h->data[h->size++] = element;
    return h;
}

int parent(Heap h, int node)
{
    if (node == 0)
        return -1;
    else
        return node / 2;
}
int left_child(Heap h, int node)
{
    if (node * 2 + 1 > h->size)
        return -1;
    else
        return node * 2 + 1;
}
int right_child(Heap h, int node)
{
    if (node * 2 + 2 > h->size - 1)
        return -1;
    else
        return node * 2 + 2;
}

void max_heapify(Heap h, int index)
{
    int left = left_child(h, index);
    int right = right_child(h, index);
    int largest = index;
    if (left < h->size && h->data[left].priority > h->data[largest].priority)
    {
        largest = left;
    }
    if (right < h->size && h->data[right].priority > h->data[largest].priority)
    {
        largest = right;
    }
    if (largest != index)
    {
        song temp = h->data[index];
        h->data[index] = h->data[largest];
        h->data[largest] = temp;
        max_heapify(h, largest);
    }
}

Heap build_max_heap(Heap heap)
{
    Heap h = heap_create();
    for (int i = 0; i < heap->size; i++)
    {
        add_to_tree(h, heap->data[i]);
    }
    for (int i = 0; i < heap->size; i++)
    {
        max_heapify(h, i);
    }
    return h;
}

void insert(Heap h, song song)
{
    add_to_tree(h, song);
    build_max_heap(h);
    return;
}

int maximum(Heap h)
{
    if (h->size == 0)
        return NULL; // -1 denotes that the heap is empty
    else
        return h->data[0].priority;
}

int extract_maximum(Heap h)
{
    int max = maximum(h);
    h->data[0] = h->data[h->size];
    h->size--;
    build_max_heap(h);
    return max;
}

int main()
{
    FILE *fp = fopen("playlist.txt", "r");
    int lines = 0;
    char artist[50];
    char songname[50];
    int priority;
    while (fscanf(fp, "%[^;];%[^;];%d", artist, songname, &priority) == 3)
    {
        lines++;
    }
    printf("%d", lines);
    int size = lines;
    fclose(fp);
    int i=0;
    song arr[lines];
    fp = fopen("playlist.txt", "r");
    while (fscanf(fp, "%[^;];%[^;];%d", artist, songname, &priority) == 3)
    {
        arr[i].artist = malloc(50);
        arr[i].name = malloc(50);
        strcpy(arr[i].artist,artist);
        strcpy(arr[i].name,songname);
        arr[i].priority = priority;
        i++;
    }
    Heap playlist;
    for(int i=0;i<lines;i++){
        insert(playlist,arr[i]);
    }
}