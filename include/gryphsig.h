#ifndef GRYPHSIG_H
#define GRYPHSIG_H

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <assert.h>

#define PASS 1
#define FAIL 0

#define PRINT_TEST(x) printf("%-50s", x)

jmp_buf env_buffer;

extern int pass;
extern int total;

void initialize_test_harness(void);

void _handle_segfault(int signo);
void _initialize_signals(void);
int _internal_test_case(int test_num);
int _run_all_tests(void);

#endif
