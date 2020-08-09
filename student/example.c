#include "example.h"

char *string_to_upper(char *string)
{
    if (!string)
        return NULL;

    for (char *p = string; *p; p++)
        *p = toupper(*p);

    return string;
}

char *string_to_lower(char *string)
{
    if (!string)
        return NULL;

    for (char *p = string; *p; p++)
        *p = tolower(*p);

    // Intentionally incorrect
    *string = '.';

    return string;
}
