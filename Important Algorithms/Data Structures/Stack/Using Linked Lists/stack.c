#include "types.h"

extern node *stack;

void push(int element)
{
    node *NewNode = malloc(sizeof(node));
    NewNode->element = element;
    NewNode->next = NULL;

    if (NewNode == NULL)
    {
        printf(RED "Failed to allocate memory.\n" RESET);
        return;
    }

    if (stack != NULL)
    {
        NewNode->next = stack;
        
    }

    stack = NewNode;
    printf(GREEN "%i pushed to Stack.\n" RESET, element);
}

void peek()
{
    if (stack == NULL)
    {
        printf(RED "Stack is empty.\n" RESET);
    }
    else 
    {
        printf(GREEN "Item at the top : %i\n" RESET, stack->element);
    }
}

void pop()
{
    if (stack == NULL)
    {
        printf(RED "Stack is empty.\n" RESET);
        return;
    }
    
    node *temp = stack;
    stack = stack->next;
    printf(GREEN "Item popped : %i\n" RESET, temp->element);
    free(temp);
}