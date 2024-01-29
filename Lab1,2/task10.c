#include <sys/time.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
struct timeval t1, t2;
double time_taken;

typedef struct node* NODE;
struct node{
	char ID[14];
	float cgpa;
	NODE next;
};

typedef struct linked_list* LIST;
struct linked_list{
	int count;
	NODE head;
};

struct student{
	char *ID;
	float *cgpa;
};

LIST createNewList()
{
	LIST myList;
	myList = (LIST) malloc(sizeof(struct linked_list));
	myList->count=0;
	myList->head=NULL;
	return myList;
}
NODE createNewNode(char * id,float cg)
{
	NODE myNode;
	myNode = (NODE) malloc(sizeof(struct node));
	myNode->cgpa=cg;
	strcpy(myNode->ID,id);
	myNode->next=NULL;
	return myNode;
}

void insertFirst(NODE first,LIST list)
{
	if(list->head == NULL){
        list->head=first;
    }
    else{
        NODE temp = list->head;
	    list->head=first;
	    first->next=temp;
    }
}
void insertEnd(NODE first,LIST list)
{
	if(list->head == NULL){
        list->head=first;
    }
    else{
        NODE temp = list->head;
        while(temp->next!=NULL)temp=temp->next;
	    temp->next = first;
    }
}
int main()
{
	FILE *fptr;
	char id1[14];
	char line[100];
	float cg;
	fptr = fopen("data.txt", "r");
	struct student* students = malloc(10000 * sizeof(struct student));
	int i=0;
	gettimeofday(&t1, NULL);
	while(i<10000)
	{
		students[i].ID = malloc(14*sizeof(char));
		students[i].cgpa = malloc(1*sizeof(float));
		fscanf(fptr, "%[^,],%f\n", students[i].ID, students[i].cgpa);
		i++;
	}
	printf("\n");
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

	printf("Time to Store in Dynamic Array took %f seconds to execute\n", time_taken);
	fclose(fptr);

	fptr = fopen("data.txt", "r");
	LIST l1 = createNewList(); 
	gettimeofday(&t1, NULL);
	NODE n1;
	i=0;
	while(i<10000)
	{
		fscanf(fptr, "%[^,],%f\n", id1, &cg);
		n1 = createNewNode(id1,cg);
		insertEnd(n1,l1);
		i++;
	}
	printf("\n");
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

	printf("Time to Store in Linked List took %f seconds to execute\n", time_taken);
	fclose(fptr);


	fptr = fopen("newentries.txt", "r");
	students = realloc(students, 10010*sizeof(struct student));
	i=1;
	gettimeofday(&t1, NULL);
	int index = 0;
	while(i<11)
	{
		fscanf(fptr, "%[^,],%f,%d\n", id1, &cg, &index);
		students[10000+i-1].ID = malloc(14*sizeof(char));
		students[10000+i-1].cgpa = malloc(1*sizeof(float));
		for(int j=index+1;j<10000+i;j++){
			students[j]=students[j-1];	
		}
		students[index].ID = malloc(14*sizeof(char));
		students[index].cgpa = malloc(1*sizeof(float));
		i++;
	}
	printf("\n");
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

	printf("Time to Store new Entries in Dynamic Array took %f seconds to execute\n", time_taken);
	fclose(fptr);

	i=1;
	fptr = fopen("newentries.txt", "r");
	gettimeofday(&t1, NULL);
	while(i<11)
	{
		fscanf(fptr, "%[^,],%f,%d\n", id1, &cg, &index);
		NODE curr = l1->head;
		NODE prev = NULL;
		n1 = createNewNode(id1,cg);

		for(int j=1;j<index;j++){
			prev=curr;
			curr=curr->next;
		}
		prev->next=n1;
		n1->next=curr;
		i++;
	}
	printf("\n");
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

	printf("Time to Store new Entries in Linked List took %f seconds to execute\n", time_taken);
	fclose(fptr);


	printf("\nEnter Position to retrieve data: ");
	scanf(" %d",&index);
	if(index>10000){
		printf("INDEX out of bounds\n");
		return 0;
	}
	gettimeofday(&t1, NULL);
	char newid[14];
	strcpy(newid,students[index+1].ID);
	float *newcg = students[index+1].cgpa;
	gettimeofday(&t2, NULL);
	printf("\n");

	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

	printf("Time to retrieve Entry from Dynamic Array took %f seconds to execute\n", time_taken);

	gettimeofday(&t1, NULL);
	NODE curr=l1->head;
	while(--index)
	{
		curr = curr->next;
	}
	printf("\nID: %s, CGPA: %f\n",curr->ID, curr->cgpa);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

	printf("\nTime to retrieve Entry from Linked List took %f seconds to execute\n", time_taken);

	gettimeofday(&t1, NULL);

	for (int i = 0; i < 10009; i++) {
		free(students[i].ID);
		free(students[i].cgpa);
	}

	free(students);

	gettimeofday(&t2, NULL);
	printf("Time to Delete All Entries from Dynamic Array took %f seconds to execute\n", time_taken);

	gettimeofday(&t1, NULL);
	curr=l1->head;
	index=10010-2;
	while(--index)
	{
		l1->head->next=l1->head->next->next;
	}
	l1->head->next=NULL;
	l1->head=NULL;
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;

	printf("Time to Delete All Entries from Linked List took %f seconds to execute\n", time_taken);

	return 0;
}
