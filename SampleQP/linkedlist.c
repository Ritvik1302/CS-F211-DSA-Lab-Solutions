#include "linkedlist.h"
#include <stdio.h>

static node *create_node_for_list(process p);
// Check header files for documentation/ function description
process_linked_list *create_empty_process_linked_list() {
    // COMPLETE
    process_linked_list * n1 = malloc(sizeof(process_linked_list));
    n1->size = 0;
    n1->head = NULL;
    return n1;
}

bool add_first_to_linked_list(process_linked_list *list, process p) {
    return add_at_index_linked_list(list, 0, p);
}

bool add_last_to_linked_list(process_linked_list *list, process p) {
    return add_at_index_linked_list(list, list->size, p);
}

bool add_at_index_linked_list(process_linked_list *list, size_t index, process p) {
    // Create a new node for the given process
    node* new_node = create_node_for_list(p);
    if (!new_node) {
        // Memory allocation failed
        return false;
    }

    if (index == 0) {
        // Insertion at the beginning of the list
        new_node->next = list->head;
        if (list->head != NULL) {
            list->head->previous = new_node;
        }
        list->head = new_node;
    } else {
        // Traverse to the node at the specified index
        node* current_node = list->head;
        size_t i = 0;
        while (current_node != NULL && i < index - 1) {
            current_node = current_node->next;
            i++;
        }
        if (current_node == NULL) {
            // Index out of bounds
            free(new_node);
            return false;
        }

        // Insert the new node after the current node
        new_node->next = current_node->next;
        if (current_node->next != NULL) {
            current_node->next->previous = new_node;
        }
        current_node->next = new_node;
        new_node->previous = current_node;
    }

    // Increment the size of the list
    list->size++;
    return true;
}


bool remove_first_linked_list(process_linked_list *list, process *p) {
    if (list->size == 0) {
        return false;
    }
    *p = *list->head->process;
    if(list->head->next == NULL){
        free(list->head);
        list->head = NULL;
        list->size--;
        return true;
    }
    node* temp = list->head;
    list->head = list->head->next;
    list->head->previous = NULL;
    list->size--;
    free(temp);
    return true;
   // COMPLETE
}

bool remove_last_linked_list(process_linked_list *list, process *p) {
    if (list->size == 0) {
        return false;
    }
    node* temp = list->head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    *p = *temp->process;
    temp->previous->next = NULL;
    free(temp);
    list->size--;
    return true;
   // COMPLETE
}

size_t get_size_linked_list(process_linked_list *list) {
    return list->size;
}

void print_linked_list(process_linked_list *list) {
    node *tracker = list->head;
    for (int i = 0; i < list->size; ++i) {
        printf("%d => ", tracker->process->pid);
        tracker = tracker->next;
    }
    printf("%s", "\n");
}

static node *create_node_for_list(process p) {
    process *to_add_process = malloc(sizeof(process));
    if (!to_add_process) {
        return NULL;
    }
    *to_add_process = p;
    node *new_node = malloc(sizeof(node));
    if (!new_node) {
        return NULL;
    }
    new_node->process = to_add_process;
    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node;
}


void destroy_linked_list(process_linked_list *list) {
    node *current = list->head->next;
    for (int i = 0; i < list->size; ++i) {
        node *next = current->next;
        free(current->process);
        current = next;
    }
    free(list->head);
    free(list);
}