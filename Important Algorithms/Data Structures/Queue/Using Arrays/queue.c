#include "types.h"

extern int head;
extern int tail;
extern int count;
extern int queue[];

void enqueue(int element)
{
    if (count >= LIMIT)
    {
        printf(RED "Queue is full.\n" RESET);
        return;
    }

    if (head == -1)
    {
        head++;
    }

    tail = (tail + 1) % LIMIT;
    queue[tail] = element;
    count++;
    printf(GREEN "%i enqueued to the queue.\n" RESET, element);
}

int peek()
{
    if (head == -1)
    {
        printf(RED "Queue is empty.\n" RESET);
        return 1;
    }

    printf(GREEN "Item at the head : %i\n" RESET, queue[head]);
    return 0;
}

void dequeue()
{
    if (!peek())
    {
        head = (head + 1) % LIMIT;
        count--;

        if (count == 0)
        {
            head = -1;
            tail = -1;
        }
    }
}

