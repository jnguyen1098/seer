#include "gryphsig.h"

int _pass = 0;
int _total = 0;

void _handle_segfault(int signo)
{
    if (signo) {}
#if _CATCH_CRASHES
    longjmp(env_buffer, 1);
#else
    fprintf(stderr, "Program crashed! Test harness exiting.\n");
    fprintf(stderr, "Score prior to exiting: %d\n", _pass);
    exit(-1);
#endif
}

void _initialize_signals(void)
{
    struct sigaction crash_handler;
    crash_handler.sa_handler = _handle_segfault;
    sigemptyset(&crash_handler.sa_mask);
    crash_handler.sa_flags = SA_NODEFER;

    // catch segmentation fault
    if (sigaction(SIGSEGV, &crash_handler, NULL) == -1) {
        puts("Test harness could not initialize SIGSEGV... fatal error");
        exit(-1);
    }

    // catch program abort handler
    // TODO: should I keep this in?
    if (sigaction(SIGABRT, &crash_handler, NULL) == -1) {
        puts("Test harness could not initialize SIGABRT...fatal error");
        exit(-1);
    }

    // catch floating point/arithmetic exception
    if (sigaction(SIGFPE, &crash_handler, NULL) == -1) {
        puts("Test harness could not initialize SIGFPE...fatal error");
        exit(-1);
    }

    // catch illegal instruction
    if (sigaction(SIGILL, &crash_handler, NULL) == -1) {
        puts("Test harness could not initialize SIGILL...fatal error");
        exit(-1);
    }
}

void initialize_test_harness(void)
{
    _initialize_signals();
}
