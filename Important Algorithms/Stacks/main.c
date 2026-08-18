#include "types.h"

node *stack;

int main() 
{
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    print();
    pop();
    push(60);
    print();
}