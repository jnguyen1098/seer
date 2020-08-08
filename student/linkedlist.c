#include "linkedlist.h"

Node *create_node(int data)
{
    Node *to_return = malloc(sizeof(Node));
    if (!to_return)
        return NULL;

    to_return->data = data;
    to_return->next = NULL;

    return to_return;
}

Node *insert_node(Node *list, int data)
{
    if (!list)
        return NULL;

    Node *new_node = create_node(data);
    if (!new_node)
        return NULL;

    Node *tmp = list;
    while (tmp->next)
        tmp = tmp->next;

    tmp->next = new_node;

    return list;
}

void destroy_list(Node *list)
{
    if (!list)
        return;

    while (list) {
        Node *tmp = list;
        list = list->next;
        free(tmp);
    }
}

int search(Node *list, int data)
{
    for (Node *tmp = list; tmp; tmp = tmp->next)
        if (tmp->data == data)
            return 1;
    return 0;
}
