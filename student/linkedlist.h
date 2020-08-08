#include <stdlib.h>

typedef struct node_struct {
    int data;
    struct node_struct *next;
} Node;

Node *create_node(int data);

Node *insert_node(Node *list, int data);

int search(Node *list, int data);

void destroy_list(Node *list);
