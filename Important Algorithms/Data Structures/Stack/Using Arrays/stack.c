#include "types.h"

extern int top;
extern int stack[];

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

void pop()
{
    if (!peek())
    {
        top--;
    }
}