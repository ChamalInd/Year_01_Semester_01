#include "types.h"

extern node *stack;

// Time complexity : O(1) 
// O(1) can be achieved by inserting to head
void push(int element)
{
    node *NewNode = malloc(sizeof(node));
    if (NewNode == NULL)
    {
        printf(RED "Failed to allocate memory.\n" RESET);
        return;
    }

    NewNode->element = element;
    NewNode->next = NULL;

    if (stack != NULL)
    {
        NewNode->next = stack;
        
    }

    stack = NewNode;
    printf(GREEN "%i pushed to Stack.\n" RESET, element);
}

// Time complexity : O(1) 
int peek()
{
    if (stack == NULL)
    {
        printf(RED "Stack is empty.\n" RESET);
        return 1;
    }
    
    printf(GREEN "Item at the top : %i\n" RESET, stack->element);
    return 0;
}

// Time complexity : O(1) 
// O(1) can be achieved by removing from head
void pop()
{
    if (!peek())
    {
        node *temp = stack;
        stack = stack->next;
        free(temp);
    }
}