/**
 * @file seer.h
 * @author Jason Nguyen <jnguye21@uoguelph.ca>
 * @brief Seer structs, functions, and constants
 */
#ifndef SEER_H
#define SEER_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Maximum amount of tests
 * @internal
 **/
#define SEER_MAX_TESTS 1000

/**
 * Maximum length of string
 * @internal
 **/
#define SEER_MAX_STR 128

/**
 * Default initializer for a test result
 * @internal
 **/
#define TEST_RESULT_INIT {INIT, "No description", "No comment"}

/**
 * File descriptors for IPC
 **/
extern int fd[2];

/**
 * Enum used to portably keep track of test results.
 * I will likely expand upon this in the future, so do not
 * use straight integers as this will ruin results.
 **/
typedef enum _seer_result_code {
    INIT,   // Uninitialized
    PASS,   // Test passed
    FAIL,   // Test failed
    CRASH,  // Test crashed
    FINISH, // Finished tests
} ResultCode;

/**
 * Struct used to encapsulate a test result. It currently uses:
 * 
 *    result - result code (ResultCode)
 *    description - description of the code independent of results
 *    comment - description of the particular result that happened
 **/
typedef struct _seer_test_result {
    int result;
    char description[SEER_MAX_STR];
    char comment[SEER_MAX_STR];
} TestResult;

/**
 * Function to pipe description to parent process via pipe
 * 
 * @param message message to send
 **/
void description(char message[SEER_MAX_STR]);

/**
 * External test runner, called in `run_main.c`.
 * 
 * @param test_number - test number
 * @return TestResult struct
 **/
TestResult run_test(int test_number);

/**
 * Internal test runner, called by `run_test()`.
 * 
 * @param test_number - test number
 * @return TestResult struct
 **/
TestResult _run_test(int test_number);

#endif
