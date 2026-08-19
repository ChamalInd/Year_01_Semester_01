#include "types.h"

extern node *queue;

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

    if (queue == NULL)
    {
        queue = NewNode;
    }
    else
    {
        node *temp = queue;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = NewNode;
    }

    printf(GREEN "%i enqueued to the queue.\n" RESET, element);
}

int peek()
{
    if (queue == NULL)
    {
        printf(RED "Queue is empty.\n" RESET);
        return 1;
    }
    printf(GREEN "Item at the head : %i\n" RESET, queue->element);
    return 0;
}

void dequeue()
{
    if (!peek())
    {
        node *temp = queue;
        queue = queue->next;
        free(temp);
    }
}

