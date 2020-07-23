#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

#define PASS 1
#define FAIL 0

jmp_buf env_buffer;

void handle_segfault(int signo)
{
    if (signo) {}
    longjmp(env_buffer, 1);
}

int test(int test_num)
{
    if (setjmp(env_buffer))
        return FAIL;

    struct sigaction crash_handler;
    crash_handler.sa_handler = handle_segfault;
    sigemptyset(&crash_handler.sa_mask);
    crash_handler.sa_flags = SA_NODEFER;

    if (sigaction(SIGSEGV, &crash_handler, NULL) == -1) {
        puts("Test harness could not initialize... fatal error");
        exit(-1);
    }

    switch (test_num) {

        case 1:
            raise(SIGSEGV);
            break;

        case 2:
            free((char *)1);
            break;

        case 3:

            break;

        default:
            return -1;

    }

    return PASS;
}

#define NUM_TESTS 1

int main(void)
{
    int total = 0;

    for (int i = 1 ;; i++) {
        int result = test(i);
        if (result == -1) {
            puts("\nTests finished\n");
            break;
        } else {
            printf("Test %4d    %s\n", i, result == FAIL ? "PASS" : "FAIL");
            total += result;
        }
    }

    puts(total ? "Fail" : "Success");

    return 0;
}
