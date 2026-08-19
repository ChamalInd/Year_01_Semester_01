#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"

struct Node {
    int element;
    struct Node *next;
};
typedef struct Node node;

void push(int element);
void pop();
void peek();

#endif