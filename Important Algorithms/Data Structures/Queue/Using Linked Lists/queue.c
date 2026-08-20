#include "types.h"

extern node *head;
extern node *tail;

// Time complexity : O(1) 
// O(1) can be achieved using a pointer to tail 
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

// Time complexity : O(1) 
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

// Time complexity : O(1) 
// time complexity of O(1) can be achieved by removing from head
void dequeue()
{
    if (!peek())
    {
        node *temp = head;
        head = head->next;

        if (head == NULL)
        {
            tail = NULL;
        }

        free(temp);
    }
}

