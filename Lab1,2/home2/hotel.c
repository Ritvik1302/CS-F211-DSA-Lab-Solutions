#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct room* ROOM;
struct room
{
    char name[100];
    int age;
    char add[100];
    ROOM next;
};

typedef struct hotel* HOTEL;
struct hotel
{
    ROOM head;
    char name[100];
    char add[100];
    int count;
};

HOTEL createNewHotel(char *name, char *add)
{
    HOTEL myList;
    myList = (HOTEL) malloc(sizeof(struct hotel));
    myList->count = 0;
    strcpy(myList->name, name);
    strcpy(myList->add, add);
    myList->head = NULL;
    return myList;
}
ROOM createNewRoom(char *name, char *add, int age)
{
    ROOM myNode;
    myNode = (ROOM)malloc(sizeof(struct room));
    myNode->age = age;
    strcpy(myNode->name, name);
    strcpy(myNode->add, add);
    myNode->next = NULL;
    return myNode;
}

int main()
{
    int n = 0;
    HOTEL arr = createNewHotel("The Grand Hotel", "Block 89");
    char name[100], add[100];
    int age;
    while (1)
    {
        printf("\n(1) Add visitor to first unoccupied room,\n(2) Add visitor to first room,\n(3) Empty a Room,\n(4) Display the info of a visitor,\n(5) Exit Menu\n");

        int menu;
        scanf("%d", &menu);
        if (menu == 5)
            break;
        switch (menu)
        {
        case 1:
            printf("\nEnter Name: ");
            scanf(" %s", name);
            printf("\nEnter Add: ");
            scanf(" %s", add);
            printf("\nEnter Age: ");
            scanf(" %d", &age);
            arr = realloc(arr, (n + 1) * sizeof(HOTEL *));
            n += 1;
            ROOM room = createNewRoom(name, add, age);
            if (arr->head == NULL)
                arr->head = room;
            else
            {
                ROOM curr = arr->head;
                while (curr->next != NULL)
                {
                    curr = curr->next;
                }
                curr->next = room;
            }
            break;
        case 2:
            arr = realloc(arr, (n + 1) * sizeof(HOTEL *));
            n += 1;
            printf("\nEnter Name: ");
            scanf(" %s", name);
            printf("\nEnter Add: ");
            scanf(" %s", add);
            printf("\nEnter Age: ");
            scanf(" %d", &age);
            room = createNewRoom(name, add, age);
            
            if (arr->head == NULL)
                arr->head = room;
            else
            {
                ROOM curr = arr->head;
                ROOM temp = arr->head;
                arr->head= createNewRoom(name,add,age);
                arr->head->next = temp;
            }
            break;
        case 3:
            printf("\nEnter Name");
            printf("\nIndex: ");
            scanf("%s", name);
            if(arr->head==NULL)break;
            ROOM curr = arr->head;
            ROOM prev = NULL;
            while(curr!=NULL){
                if(!strcmp(curr->name,name)){
                    {
                        prev = curr->next;
                    }
                    break;
                }
                prev = curr;
                curr=curr->next;
            }

        case 4:
            printf("Enter Room No.: ");
            int index;
            scanf(" %d",&index);
            int i=1;
            curr = arr->head;
            while(curr!=NULL){
                if(i==index){
                    printf("\nName: %s, Age: %d, Address: %s",curr->name,curr->age,curr->add);
                    break;
                }
                curr=curr->next;
                i++;
            }
            if(i!=index){printf("\nRoom Unoccupied");};
            break;
        }
    }
    return 0;
}