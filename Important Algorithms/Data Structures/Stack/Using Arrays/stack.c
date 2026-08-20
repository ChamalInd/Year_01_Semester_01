#include "types.h"

extern int top;
extern int stack[];

// Time complexity : O(1) 
// keep inserting to tail
void push(int element)
{
    if (top + 1 >= LIMIT)
    {
        printf(RED "Stack is already Full.\n" RESET);
        return;
    }
    
    top++;
    stack[top] = element;
    printf(GREEN "%i pushed into the Stack.\n" RESET, element);
}

// Time complexity : O(1) 
int peek()
{
    if (top == -1)
    {
        printf(RED "Stack is empty.\n" RESET);
        return 1;
    }
    
    printf(GREEN "Item at top : %i\n" RESET, stack[top]);
    return 0;
}

// Time complexity : O(1) 
// keep removing from tail
void pop()
{
    if (!peek())
    {
        top--;
    }
}