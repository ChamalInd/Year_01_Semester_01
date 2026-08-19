#include "types.h"

int head = -1;
int tail = -1;
int queue[LIMIT];
int count = 0;

int main()
{
    char input;
    int element;

    while (TRUE)
    {
        printf("---Implementation of Queues using Arrays---\n\n");
        printf("1 : to enqueue\n2 : to dequeue\n3 : to peek\n\n: ");
        scanf(" %c", &input);

        if (input == '1')
        {
            printf("Enter a number : ");

            if (!scanf("%i", &element))
            {
                printf("Invalid characters.\n: ");
                break;
            }

            enqueue(element);
        }
        else if (input == '2')
        {
            dequeue();
        }
        else if (input == '3')
        {
            peek();
        }
        else
        {
            break;
        }

        printf("\n");
    }

    return 0;
}