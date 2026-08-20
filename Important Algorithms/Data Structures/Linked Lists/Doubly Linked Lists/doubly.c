#include "types.h"

extern node *list;

// Time complexity : O(1) 
// list pointer is pointing towards the head
void add_to_head(int element)
{
    node *NewNode = malloc(sizeof(node));

    if (NewNode == NULL)
    {
        printf(RED "Failed to allocate memory.\n" RESET);
        return;
    }

    NewNode->element = element;
    NewNode->next = NULL;
    NewNode->prev = NULL;

    if (list != NULL)
    {
        NewNode->next = list;
        list->prev = NewNode;
    }

    list = NewNode;
    printf(GREEN "Element %i inserted at Head.\n" RESET, element);

    print();
}

// Time complexity : O(n) 
// loop through the entire linked list to insert elements
// can be reduced to O(1) by adding a tail pointer
void add_to_tail(int element)
{
    node *NewNode = malloc(sizeof(node));

    if (NewNode == NULL)
    {
        printf(RED "Failed to allocate memory.\n" RESET);
        return;
    }

    NewNode->element = element;
    NewNode->next = NULL;
    NewNode->prev = NULL;

    if (list == NULL)
    {
        list = NewNode;
    }
    else
    {
        node *temp = list;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        NewNode->prev = temp;
        temp->next = NewNode;
    }
    printf(GREEN "Element %i inserted at Tail.\n" RESET, element);

    print();
}

// Time complexity : O(1) 
// list pointer is pointing towards the head
void remove_from_head()
{
    node *temp = list;

    if (temp == NULL)
    {
        printf(RED "List is empty.\n" RESET);
        return;
    }
    else if (list->next == NULL)
    {
        printf(GREEN "Deleted %i from Head.\n" RESET, list->element);
        free(list);
        list = NULL;
    }
    else 
    {
        list = temp->next;
        list->prev = NULL;
        printf(GREEN "Deleted %i from Head.\n" RESET, temp->element);
        free(temp);
    }
    print();
}

// Time complexity : O(n) 
// loop through the entire linked list to remove elements
// can be reduced to O(1) by adding a tail pointer
void remove_from_tail()
{
    if (list == NULL)
    {
        printf(RED "List is empty.\n" RESET);
        return;
    }
    else if (list->next == NULL)
    {
        printf(GREEN "Deleted %i from Tail.\n" RESET, list->element);
        free(list);
        list = NULL;
    }
    else 
    {
        node *temp = list;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        printf(GREEN "Deleted %i from Tail.\n" RESET, temp->element);
        temp->prev->next = NULL;
        free(temp);
    }
    print();
}

// Time complexity : O(n) 
// loop through the entire linked list to search elements
void search(int key)
{
    node *temp = list;
    int place = 0;
    int found = 0;

    if (list == NULL)
    {
        printf(RED "List is empty.\n" RESET);
        return;
    }

    while (temp != NULL)
    {
        if (temp->element == key)
        {
            printf(GREEN "Found %i at : %i index.\n" RESET, key, place);
            found++;
        }
        temp = temp->next;
        place++;
    }

    if (found == 0)
    {
        printf(RED "%i is not in the linked list.\n" RESET, key);
    }
}

// Time complexity : O(n) 
// loop through the entire linked list to print elements
void print()
{
    node *temp = list;

    if (list == NULL)
    {
        printf(RED "List is empty.\n" RESET);
        return;
    }

    printf("List : ");
    while (temp != NULL)
    {
        printf("%i ", temp->element);
        temp = temp->next;
    }
    printf("\n");
}