#include "text.h"

#define TEST_STRING "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijlkmnopqrstuvwxyz\n"

void _seer_test_ansi(void)
{
    char *_seer_bright_colours[] = {
        ANSI_B_BLACK,
        ANSI_B_RED,
        ANSI_B_GREEN,
        ANSI_B_YELLOW,
        ANSI_B_BLUE,
        ANSI_B_MAGENTA,
        ANSI_B_CYAN,
        ANSI_B_WHITE,
        NULL,
    };

    char *_seer_basic_colours[] = {
        ANSI_BLACK,
        ANSI_RED,
        ANSI_GREEN,
        ANSI_YELLOW,
        ANSI_BLUE,
        ANSI_MAGENTA,
        ANSI_CYAN,
        ANSI_WHITE,
        NULL,
    };

    char *_seer_basic_highlights[] = {
        ANSI_H_BLACK,
        ANSI_H_RED,
        ANSI_H_GREEN,
        ANSI_H_YELLOW,
        ANSI_H_BLUE,
        ANSI_H_MAGENTA,
        ANSI_H_CYAN,
        ANSI_H_WHITE,
        NULL,
    };

    char *_seer_bright_highlights[] = {
        ANSI_HB_BLACK,
        ANSI_HB_RED,
        ANSI_HB_GREEN,
        ANSI_HB_YELLOW,
        ANSI_HB_BLUE,
        ANSI_HB_MAGENTA,
        ANSI_HB_CYAN,
        ANSI_HB_WHITE,
        NULL,
    };

    char *_seer_modifications[] = {
        BOLD,
        UNDERLINE,
        REVERSE,
        NULL,
    };

    puts("Basic 8 colours");
    for (int i = 0; _seer_basic_colours[i]; i++) {
        printf("%s%s%s", _seer_basic_colours[i], TEST_STRING, ANSI_RESET);
    }
    puts("");

    puts("Bright 8 colours");
    for (int i = 0; _seer_bright_colours[i]; i++) {
        printf("%s%s%s", _seer_bright_colours[i], TEST_STRING, ANSI_RESET);
    }
    puts("");

    puts("Basic 8 highlights on default text");
    for (int i = 0; _seer_basic_highlights[i]; i++) {
        printf("%s%s%s", _seer_basic_highlights[i], TEST_STRING, ANSI_RESET);
    }
    puts("");

    puts("Bright 8 highlights on default text");
    for (int i = 0; _seer_bright_highlights[i]; i++) {
        printf("%s%s%s", _seer_bright_highlights[i], TEST_STRING, ANSI_RESET);
    }
    puts("");

    puts("Modifications on default text");
    for (int i = 0; _seer_modifications[i]; i++) {
        printf("%s%s%s", _seer_modifications[i], TEST_STRING, ANSI_RESET);
    }
    puts("");
}
