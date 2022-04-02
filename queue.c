#include <stdio.h>
#include <stdlib.h>

/* Strukturos aprasas */
struct node
{
    int data;
    struct node *link;
};

/* Funkcija tikrina ar eile tuscia, grazina true arba false */
int isEmpty(struct node **front, struct node **rear){
    return ((*front == *rear) && (*rear == NULL));
}

/* Funkcija iterpianti nauja elementa i eile */
void insert(struct node **front, struct node **rear, int value)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));

    if (temp == NULL)
    {
        printf("Memory can't be allocated. Value insertion failed!\n");
        exit(0);
    }

    temp->data = value;
    temp->link = NULL;

    if (*rear == NULL)
    {
        *rear = temp;
        *front = *rear;
    }
    else
    {
        (*rear)->link = temp;
        *rear = temp;
    }
}

/* Funkcija isimanti eiles elementa */
void pop(struct node **front, struct node **rear)
{
    struct node *temp;
    if(!isEmpty(front, rear)){
        temp = *front;
        *front = (*front)->link;
        if (*rear == temp)
            *rear = (*rear)->link;
        
    }else{
        printf("Queue is empty!\n");
    }
    free(temp);
}

/* Funkcija grazina eiles ilgi */
int queueLength(struct node **front, struct node **rear){
    struct node *temp;
    int i;
    if(!isEmpty(front, rear)){
        temp = *front;
        int i = 1;

        while(temp->link != NULL){
            i++;
            temp = temp->link;
        }
        return i;
    }else{
        return 0;
    }
    free(temp);
}

/* Funkcija istrinanti eile */
void deleteQueue(struct node **front, struct node **rear){
    struct node *temp;
    if(!isEmpty(front,rear)){
        while(*front != NULL){
            temp = (*front)->link;
            free(*front);
            *front = temp;
        }
    }
    *front = NULL;
    *rear = NULL;
}

int main()
{
    struct node *front = NULL, *rear = NULL;
    int n, value;
    /* Meniu */
    while(1){
        int choice, amount;

        printf("\n1. Check if queue is empty\n");
        printf("2. Insert element to queue\n");
        printf("3. Pop element from queue\n");
        printf("4. Print first member of queue\n");
        printf("5. Print size of queue\n");
        printf("6. Delete queue\n");
        printf("7. Quit\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Queue is %s", isEmpty(&front, &rear) ? "empty\n" : "not empty\n");
                break;
            case 2:
                printf("Enter value to insert\n");
                scanf("%d", &amount);
                insert(&front, &rear, amount);
                break;
            case 3:
                pop(&front,&rear);
                break;
            case 4:
                if(front != NULL && rear != NULL){
                    printf("First element of queue: %d\n", (*front).data);
                }
                break;
            case 5:
                printf("Elements in queue: %d\n", queueLength(&front, &rear));
                break;
            case 6:
                deleteQueue(&front, &rear);
                break;
            case 7:
                if(front != NULL){
                    deleteQueue(&front, &rear);
                }
                exit(1);
                break;
            default:
                printf("Wrong choice!\n");
                break;
        }
    }
}