#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

#define PASS 1
#define FAIL 0

jmp_buf env_buffer;

void handle_segfault(int signo)
{
    longjmp(env_buffer, 1);
}

int test(void)
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

    return PASS;
}

int main(void)
{
    puts("Hello world");
    return 0;
}
