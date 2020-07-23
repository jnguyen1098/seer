#include "gryphsig.h"

extern int _pass;
extern int _total;

int _internal_test(int test_num)
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

        case 12: {
            PRINT_TEST("Force failed assertion");
            int x = 5;
            assert(x == 123);
            break;
        }

        default:
            PRINT_TEST("Finishing up\n");
            return -1;

    }

    return PASS;
}

void _run_all_internal_tests(void)
{
    _initialize_signals();

    for (int i = 1 ;; i++) {
        printf("Test %2d - ", i);
        int result = _internal_test(i);
        _total += 1;
        if (result == -1) {
            puts("\nTests finished\n");
            break;
        } else {
            printf("%s\n", result == FAIL ? "PASS" : "FAIL");
            _pass += result;
        }
    }
}

int main(void)
{
    puts("This program will test Gryphsig's crash handling.\n");
    _run_all_internal_tests();
    puts(_pass ? "Meta-test failed!" : "Meta-test passed!");
    return 0;
}
