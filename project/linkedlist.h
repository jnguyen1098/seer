/* linkedlist.h */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node_struct {
    char data;
    struct node_struct *next;
} Node;

Node *create_node(int data);

size_t list_length(Node *list);

char *list_to_string(Node *list);

#endif
