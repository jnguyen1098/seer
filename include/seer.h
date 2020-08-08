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

#define TEST_RESULT_INIT {INIT, "No description", "No comment"}

FILE *_seer_output;
FILE *_seer_error;

typedef enum _seer_result_code {
    INIT,   // Uninitialized
    PASS,   // Test passed
    FAIL,   // Test failed
    CRASH,  // Test crashed
    FINISH, // Finished tests
} ResultCode;

typedef struct _seer_test_result {
    int result;
    char description[MAX_STR];
    char comment[MAX_STR];
} TestResult;

/* External test runner */
TestResult run_test(int test_number);

/* Internal test runner */
TestResult _run_test(int test_number);

#endif
