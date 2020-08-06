#include "sample_project.h"

int add_two_numbers_good(int x, int y)
{
    return x + y;
}

int add_two_numbers_bad(int x, int y)
{
    return x + y + 1;
}

void print_string_good(char *string)
{
    puts(string);
}

void print_string_bad(char *string)
{
    *((char *)0x00) = 'A';
}
