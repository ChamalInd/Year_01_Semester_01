#include "types.h"

extern node *stack;

void push(int element) 
{
    node *new_node;
    new_node = malloc(sizeof(node));
    new_node->element = element;
    new_node->next = NULL;

    node *temp = stack;

    if (new_node != NULL) 
    {
        if (temp == NULL)
        {
            stack = new_node;
        }
        else 
        {
            while (temp->next != NULL) 
            {
                temp = temp->next;
            }
            temp->next = new_node;
        }
    }
}

// void pop_from_end() 
void pop()
{
    node *temp1 = stack;
    if (temp1 == NULL)
    {
        printf("Nothing to pop.\n");
    }
    else 
    {
        node *temp2 = temp1->next;
        while (temp2->next != NULL) 
        {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        temp1->next = NULL;
        free(temp2);
    }
}

// void pop_from_start()
// {
//     node *temp = stack;
//     stack = temp->next;
//     free(temp);
// }

void print() 
{
    node *temp = stack;
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