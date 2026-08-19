#include "types.h"

extern int head;
extern int tail;
extern int queue[];

void enqueue(int element)
{
    if (head == -1 && tail == -1)
    {
        head++;
    }

    if (tail + 1 >= LIMIT)
    {
        printf(RED "Queue is full.\n" RESET);
        return;
    }

    tail++;
    queue[tail] = element;
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
        for (int i = head; i < tail; i++)
        {
            queue[i] = queue[i+1];
        }
        tail--;

        if (tail == -1)
        {
            head--;
        }
    }
}

