#include "types.h"

extern int top;
extern int stack[];

void push(int element)
{
    top++;

    if (top < LIMIT)
    {
        stack[top] = element;
        printf(GREEN "%i pushed into the Stack.\n" RESET, element);
    }
    else 
    {
        top--;
        printf(RED "Stack is already Full.\n" RESET);
    }
}

void peek()
{
    if (top == -1)
    {
        printf(RED "Stack is empty.\n" RESET);
        return;
    }
    else
    {
        printf(GREEN "Item at top : %i\n" RESET, stack[top]);
    }
}

void pop()
{
    if (top == -1)
    {
        printf(RED "Stack is already empty.\n" RESET);
        return;
    }
    else
    {
        printf(GREEN "Item popped : %i\n" RESET, stack[top]);
        top--;
    }
}