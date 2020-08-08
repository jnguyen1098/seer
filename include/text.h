#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>

/* Basic text test */
void _seer_test_ansi(void);

/* Coloured printf */
#define GREEN_MSG(x, y) (fprintf(x, "%s%s%s", ANSI_GREEN, y, ANSI_RESET))
#define RED_MSG(x, y)   (fprintf(x, "%s%s%s", ANSI_RED, y, ANSI_RESET))
#define YELLOW_MSG(x, y)(fprintf(x, "%s%s%s", ANSI_YELLOW, y, ANSI_RESET))

/* Reset */
#define ANSI_RESET      "\x1B[0m"

/* Basic colours */
#define ANSI_BLACK      "\x1B[30m"      /* Black */
#define ANSI_RED        "\x1B[31m"      /* Red */
#define ANSI_GREEN      "\x1B[32m"      /* Green */
#define ANSI_YELLOW     "\x1B[33m"      /* Yellow */
#define ANSI_BLUE       "\x1B[34m"      /* Blue */
#define ANSI_MAGENTA    "\x1B[35m"      /* Magenta */
#define ANSI_CYAN       "\x1B[36m"      /* Cyan */
#define ANSI_WHITE      "\x1B[37m"      /* White */

/* Bright colours */
#define ANSI_B_BLACK    "\x1B[30;1m"    /* Bright black */
#define ANSI_B_RED      "\x1B[31;1m"    /* Bright red */
#define ANSI_B_GREEN    "\x1B[32;1m"    /* Bright green */
#define ANSI_B_YELLOW   "\x1B[33;1m"    /* Bright yellow */
#define ANSI_B_BLUE     "\x1B[34;1m"    /* Bright blue */
#define ANSI_B_MAGENTA  "\x1B[35;1m"    /* Bright magenta */
#define ANSI_B_CYAN     "\x1B[36;1m"    /* Bright cyan */
#define ANSI_B_WHITE    "\x1B[37;1m"    /* Bright white */

/* Basic highlight */
#define ANSI_H_BLACK    "\x1B[40m"      /* Black */
#define ANSI_H_RED      "\x1B[41m"      /* Red */
#define ANSI_H_GREEN    "\x1B[42m"      /* Green */
#define ANSI_H_YELLOW   "\x1B[43m"      /* Yellow */
#define ANSI_H_BLUE     "\x1B[44m"      /* Blue */
#define ANSI_H_MAGENTA  "\x1B[45m"      /* Magenta */
#define ANSI_H_CYAN     "\x1B[46m"      /* Cyan */
#define ANSI_H_WHITE    "\x1B[47m"      /* White */

/* Bright highlight */
#define ANSI_HB_BLACK   "\x1B[40;1m"    /* Bright black */
#define ANSI_HB_RED     "\x1B[41;1m"    /* Bright red */
#define ANSI_HB_GREEN   "\x1B[42;1m"    /* Bright green */
#define ANSI_HB_YELLOW  "\x1B[43;1m"    /* Bright yellow */
#define ANSI_HB_BLUE    "\x1B[44;1m"    /* Bright blue */
#define ANSI_HB_MAGENTA "\x1B[45;1m"    /* Bright magenta */
#define ANSI_HB_CYAN    "\x1B[46;1m"    /* Bright cyan */
#define ANSI_HB_WHITE   "\x1B[47;1m"    /* Bright white */

/* Modifications */
#define BOLD            "\x1B[1m"       /* Bold */
#define UNDERLINE       "\x1B[4m"       /* Underline */
#define REVERSE         "\x1B[7m"       /* Reverse */

#endif
