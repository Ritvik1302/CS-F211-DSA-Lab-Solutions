#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int pid;
    int arrival_time;
    int burst_time;
} Process;

typedef struct node {
    Process data;
    struct node *next;
} Node;

typedef struct queue {
    Node *front;
    Node *rear;
} Queue;

Queue *createQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *queue, Process process) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = process;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

void dequeue(Queue *queue) {
    if (queue->front == NULL) {
        return; 
    }

    Node *temp = queue->front;
    queue->front = temp->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
}

int main() {
    FILE *file = fopen("fcfs_input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    Queue *q = createQueue();
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        Process process;
        fscanf(file, "%d %d %d", &process.pid, &process.arrival_time, &process.burst_time);

        while (currentTime < process.arrival_time) {
            if (q->front == NULL) {
                currentTime++;
                continue;
            }
            printf("Process %d started at time %d\n", q->front->data.pid, currentTime);
            q->front->data.burst_time--;

            if (q->front->data.burst_time == 0) {
                printf("Process %d finished at time %d\n", q->front->data.pid, currentTime);
                dequeue(q);
            }

            currentTime++;
        }
        enqueue(q, process);
        printf("Process %d arrived at time %d\n", process.pid, currentTime);
        printf("Process %d started at time %d\n", q->front->data.pid, currentTime);
        q->front->data.burst_time--;

        if (q->front->data.burst_time == 0) {
            printf("Process %d finished at time %d\n", q->front->data.pid, currentTime);
            dequeue(q);
        }

        currentTime++;
    }

    fclose(file);
    return 0;
}
