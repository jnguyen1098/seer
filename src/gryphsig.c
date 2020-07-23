#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>

#define PASS 1
#define FAIL 0

#define PRINT_TEST(x) printf("%-50s", x)

jmp_buf env_buffer;

void handle_segfault(int signo)
{
    if (signo) {}
    longjmp(env_buffer, 1);
}

void initialize_signals(void)
{
    struct sigaction crash_handler;
    crash_handler.sa_handler = handle_segfault;
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

int test(int test_num)
{
    if (setjmp(env_buffer))
        return FAIL;

    switch (test_num) {

        case 1:
            PRINT_TEST("Raise SIGSEGV signal");
            raise(SIGSEGV);
            break;

        case 2:
            PRINT_TEST("Free invalid, non-allocated address");
            free((char *)1);
            break;

        case 3:;
            PRINT_TEST("Free stack memory");
            int i;
            int *bad_ptr = &i;
            free(bad_ptr);
            break;

        // raise SIGABRT signal (used in invalid free())
        case 4:
            PRINT_TEST("Raise SIGABRT signal (used in invalid free())");
            raise(SIGABRT);
            break;

        case 5:;
            PRINT_TEST("Dereference and set bad address");
            char *bad_addr = (char *)0x3;
            *bad_addr = 3;
            break;

        case 6:;
            PRINT_TEST("Double-free heap-allocated address");
            char *double_free_ptr = calloc(1, 234);
            free(double_free_ptr);
            free(double_free_ptr);
            break;

        case 7:;
            PRINT_TEST("Buffer overflow on stack array");
            int stack_buffer_overflow[10];
            for (int i = 0; i < 5000; i++)
                stack_buffer_overflow[i] = 0xFF;
            int *stack_overflow_array = stack_buffer_overflow;
            free(stack_overflow_array);
            break;

        case 8:;
            PRINT_TEST("Buffer overflow on heap array");
            int heap_buffer_overflow[10];
            for (int i = 0; i < 5000; i++)
                heap_buffer_overflow[i] = 0xFF;
            int *heap_buffer_array = heap_buffer_overflow;
            free(heap_buffer_array);
            break;

        case 9:;
            PRINT_TEST("Misc. memory operations with double-free");
            unsigned char **little_addrs = malloc(sizeof(char *) * 1000);
            for (int i = 0; i < 1000; i++)
                little_addrs[i] = malloc(1000);
            for (int i = 0; i < 1000; i++)
                free(little_addrs[i]);
            unsigned char *large_alloc = malloc(5000000);
            for (int i = 0; i < 1000; i++)
                free(little_addrs[i]);
            for (int i = 0; i < 5000000; i++)
                large_alloc[i] = 0xFF;
            break;

        case 10:;
            PRINT_TEST("division by 0");
            int zero = 0; // silence warning
            int division_by_zero = 3 / zero;
            if (division_by_zero) {}
            break;

        case 11:
            PRINT_TEST("Force illegal instruction");
            __builtin_trap();
            break;

        default:
            PRINT_TEST("Finishing up");
            return -1;

    }

    return PASS;
}

int run_all_tests(void)
{
    int total = 0;

    initialize_signals();

    for (int i = 1 ;; i++) {
        printf("Test %2d - ", i);
        int result = test(i);
        if (result == -1) {
            puts("\nTests finished\n");
            break;
        } else {
            printf("%s\n", result == FAIL ? "PASS" : "FAIL");
            total += result;
        }
    }

    return total;
}

int main(void)
{
    puts(run_all_tests() ? "Fail" : "Success");
    return 0;
}
