#include "array_deque.h"

// Use these functions if you find them helpful or define other static helper functions that might assist you.
// One possible implementation:
// Assume that next_first decrements (or moves left) and rolls back from the other end of the array.
// Assume that next_last increments (or moves right).
// So at any instant, during add_first the element is added to next-first position and next_first is updated accordingly
// Or an element is added at next_last which is then updated accordingly


static unsigned int get_first_index(array_deque *ad);

static unsigned int get_last_index(array_deque *ad);

static unsigned int decrement_index(array_deque *d, size_t index);

static unsigned int increment_index(array_deque *d, size_t index);

static void resize_if_needed(array_deque *d);

static process *create_process(process p);

array_deque *create_empty_process_array_deque() {
    // COMPLETE
    array_deque* aq = calloc(1,sizeof(array_deque));
    aq->processes = calloc(INITIAL_SIZE_ARRAY_DEQUE,sizeof(process*));
    aq->next_first = 0;
    aq->next_last = 0;
    aq->capacity = INITIAL_SIZE_ARRAY_DEQUE;
    aq->size = 0;
    return aq;
}

static unsigned int decrement_index(array_deque *ad, size_t index) {
    index = index - 1;
    if (index == -1) {
        index = ad->capacity - 1;
    }
    return index;
}

static unsigned int increment_index(array_deque *d, size_t index) {
    return (index + 1) % d->capacity;
}

static unsigned int get_first_index(array_deque *ad) {
    return increment_index(ad, ad->next_first);
}

static unsigned int get_last_index(array_deque *ad) {
    return decrement_index(ad, ad->next_last);
}

bool add_first_array_deque(array_deque *ad, process p) {
    // COMPLETE
    resize_if_needed(ad);
    ad->next_first = (ad->next_first - 1 + ad->capacity) % ad->capacity;
    ad->processes[ad->next_first] = create_process(p);
    ad->size++;
    return true;
}

static process *create_process(process p) {
    process *pro = malloc(sizeof(process));
    if (!pro) return NULL;
    *pro = p;
    return pro;
}

bool add_last_array_deque(array_deque *ad, process p) {
    // COMPLETE
    resize_if_needed(ad);
    ad->processes[ad->next_last] = create_process(p);
    ad->next_last = (ad->next_last+1)%ad->capacity;
    ad->size++;
    return true;
}

bool remove_first_array_deque(array_deque *ad, process *p) {
    // COMPLETE
    if(ad->size == 0)return false;
    *p = *ad->processes[ad->next_first];
    ad->next_first = (ad->next_first+1)%ad->capacity;
    ad->size--;
    return true;
}

bool remove_last_array_deque(array_deque *ad, process *p) {
    // COMPLETE
    if(ad->size == 0)return false;
    if(ad->next_last == 0) ad->next_last =ad->capacity-1;
    else ad->next_last -= 1; 
    *p = *ad->processes[ad->next_last];
    ad->size--;
    return true;
}

size_t get_size_array_deque(array_deque *ad) {
    return ad->size;
}

static void resize_if_needed(array_deque *ad) {
    if (ad->size < ad->capacity) {
        return;
    }
    // COMPLETE
    process** processes = calloc(ad->capacity * 2,sizeof(process*));
    for(int i=0;i<ad->size;i++){
        processes[i] = ad->processes[i];
    }
    for (int i = 0; i < ad->size; i++) {
        processes[i] = ad->processes[(ad->next_first + i) % ad->capacity];
    }

    free(ad->processes);
    ad->capacity*=2;
    ad->processes = processes;
    ad->next_first = 0;
    ad->next_last = ad->size;
}

void print_array_deque(array_deque *ad) {
    int j = ad->size;
    for(int i=0;i<j;i++){
        printf("%d => " , ad->processes[(ad->next_first+i)%ad->capacity]->pid);
    }
    printf("\n");
}

bool is_empty_array_deque(array_deque* ad){
    return ad->size==0;
}