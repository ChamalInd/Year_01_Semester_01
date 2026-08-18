#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int element;
    struct Node *next;
};
typedef struct Node node;

void enqueue(int element);
void dequeue();
void print();

#endif