#ifndef SEER_H
#define SEER_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_STR 128

#define TEST_RESULT_INIT {-1, "Uninitialized"}

typedef struct _seer_test_case {
    char description[MAX_STR];
} TestCase;

typedef struct _seer_test_result {
    int passed;
    char feedback[MAX_STR];
} TestResult;

/* External test runner */
TestResult run_test(int test_number);

/* Internal test runner */
TestResult _run_test(int test_number);

#endif
