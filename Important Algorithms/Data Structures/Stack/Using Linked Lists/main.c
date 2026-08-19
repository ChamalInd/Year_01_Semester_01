#include "types.h"

node *stack = NULL;

int main()
{
    char input;
    int element;

    while (TRUE)
    {
        printf("---Implementation of Stacks using Linked Lists---\n\n");
        printf("1 : to push\n2 : to pop\n3 : to peek\n\n: ");
        scanf(" %c", &input);

        if (input == '1')
        {
            printf("Enter a number : ");

            if (!scanf("%i", &element))
            {
                printf("Invalid characters.\n: ");
                break;
            }

            push(element);
        }
        else if (input == '2')
        {
            pop();
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