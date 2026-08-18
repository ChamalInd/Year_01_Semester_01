#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int element;
    struct Node *next;
};
typedef struct Node node;

void push(int element);
void pop();
// void pop_from_end();
// void pop_from_start();
void print();

#endif