#include "types.h"

extern node *head;
extern node *tail;

void enqueue(int element)
{
    node *NewNode = malloc(sizeof(node));

    if (NewNode == NULL)
    {
        printf(RED "Memory allocation failed.\n" RESET);
        return;
    }

    NewNode->element = element;
    NewNode->next = NULL;

    if (head == NULL)
    {
        head = NewNode;
        tail = NewNode;
    }
    else
    {
        tail->next = NewNode;
        tail = NewNode;
    }

    printf(GREEN "%i enqueued to the queue.\n" RESET, element);
}

int peek()
{
    if (head == NULL)
    {
        printf(RED "Queue is empty.\n" RESET);
        return 1;
    }
    printf(GREEN "Item at the head : %i\n" RESET, head->element);
    return 0;
}

void dequeue()
{
    if (!peek())
    {
        node *temp = head;
        head = head->next;
        free(temp);
    }
}

