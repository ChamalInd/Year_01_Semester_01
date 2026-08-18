#include "types.h"

node *queue;

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    print();
    dequeue();
    dequeue();
    enqueue(60);
    print();
}