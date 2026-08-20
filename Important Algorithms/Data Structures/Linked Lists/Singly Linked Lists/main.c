#include "types.h"

node *list = NULL;

int main()
{
    char input;
    int element;

    printf("---Singly Linked List---\n");

    while (TRUE)
    {
        printf("1 : Add to Head\n2 : Add to Tail\n3 : Remove from Head\n4 : Remove from Tail\n5 : Search the list\n\n: ");
        scanf(" %c", &input);
        
        if (input == '3')
        {
            remove_from_head();
        }
        else if (input == '4')
        {
            remove_from_tail();
        }
        else if (input == '1' || input == '2' || input == '5')
        {
            printf("Enter a number : ");
            
            if (!scanf("%i", &element))
            {
                printf(RED "Invalid Input.\n" RESET);
                break;
            }

            if (input == '1' )
            {
                add_to_head(element);
            }
            else if (input == '2')
            {
                add_to_tail(element);
            }
            else 
            {
                search(element);
            }
        }
        else 
        {
            break;
        }

        printf("\n");
    }

    return 0;
}