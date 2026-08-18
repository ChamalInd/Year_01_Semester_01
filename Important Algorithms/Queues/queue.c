#include "types.h"

extern node *queue;

void enqueue(int element)
{
    node *new_node;
    new_node = malloc(sizeof(node));
    new_node->element = element;
    new_node->next = NULL;

    if (new_node != NULL)
    {
        if (queue == NULL)
        {
            queue = new_node;
        }
        else 
        {
            node *temp = queue;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new_node;
        }
    }
}

void dequeue()
{
    node *temp = queue;
    if (temp == NULL) {
        printf("Nothing to delete.\n");
    }
    else
    {
        queue = temp->next;
        free(temp);
    }
}

void print()
{
    node *temp = queue;
    if (temp == NULL)
    {
        printf("Nothing to print.\n");
    }
    else {
        while (temp->next != NULL)
        {
            printf("%i ", temp->element);
            temp = temp->next;
        }
        printf("%i\n", temp->element);
    }
}