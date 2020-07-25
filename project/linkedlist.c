/* linkedlist.c */
#include "linkedlist.h"

Node *create_node(int data)
{
    Node *to_return = NULL;
    if (!(to_return = malloc(sizeof(Node))))
        return NULL;

    to_return->data = data;
    to_return->next = NULL;

    return to_return;
}

// TODO: check memory leak of autograder

size_t list_length(Node *list)
{
    int size = 0;
    for (Node *tmp = list; tmp; tmp = tmp->next, size++)
        ;
    return size;
}

char *list_to_string(Node *list)
{
    if (list){}
    char *to_return = NULL;
    return to_return;
}
