/* sample_project.h */
#include <stdio.h>
#define MAX_STR 1000

typedef struct random_struct {
    char data[MAX_STR];
    int len;
} SampleStruct;

int add_two_numbers_good(int x, int y);
int add_two_numbers_bad(int x, int y);
void print_string_good(char *string);
void print_string_bad(char *string);
