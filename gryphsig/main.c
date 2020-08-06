#include "gryphsig.h"

extern int _pass;
extern int _total;

int run_test(int test_num)
{
    if (setjmp(env_buffer))
        return 0;

    switch (test_num) {

        case 1: {
            PRINT_TEST("Smoke test");
            assert(1 == 1);
            break;
        }
        break;

        case 2: {
            PRINT_TEST("Create node != NULL");
            Node *test_node = create_node('A');
            assert(test_node);
            break;
        }

        case 3: {
            PRINT_TEST("Create node returns the right value");
            Node *test_node = create_node('A');
            assert(test_node->data == 'A');
            break;
        }

        case 4: {
            PRINT_TEST("List of length 1 assert length");
            Node *test_list = create_node('A');
            assert(list_length(test_list) == 1);
            break;
        }

        case 5: {
            break;
        }

        case 6: {
            break;
        }

        case 7: {
            break;
        }

        case 8: {
            break;
        }
        case 9: {
            break;
        }

        default:
            PRINT_TEST("Finishing up");
            return -1;
        break;

    }

    return 1;
}

void run_all_tests(void)
{
    for (int i = 1;; i++) {
        printf("Test %2d - ", i);
        int result = run_test(i);
        _total += 1;
        if (result == -1) {
            puts("\nTests finished\n");
            _total -= 1;
            break;
        } else {
            printf("%s\n", result == PASS ? "PASS" : "FAIL");
            _pass += result;
        }
    }
}

int main(void)
{
    initialize_test_harness();
    run_all_tests();
    printf("Final score: %d/%d (%f)\n", _pass, _total, (float)_pass/(float)_total);
    return 0;
}
