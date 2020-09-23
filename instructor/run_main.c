/**
 * @file run_main.c
 * @author Jason Nguyen <jnguye21@uoguelph.ca>
 * @brief This is the overarching main() that facilitates the test
 *        record-keeping. Here you may modify the grading calculation
 *        as well as the final report that is outputted.
 */
#include "seer.h"
#include "text.h"

/* Make sure to edit config.h to include student files */
#include "config.h"

/* Re-define main */
#ifdef main
#undef main
#endif

int main(int argc, char *argv[])
{
    /* Change output if valgrind */
    int valgrind_run = 0;
    if (argc == 2) {
        if (!strcmp(argv[1], "--valgrind")) {
            valgrind_run = 1;
        }
    }

    /* Initialize test results */
    TestResult test_results[SEER_MAX_TESTS] = {0};

    int num_test = 0;
    int num_pass = 0;
    int num_fail = 0;
    int num_crash = 0;

    /* Run tests and record results */
    for (;;) {
        if (valgrind_run) {
            printf("\nValgrind output for test %d\n", num_test);
        }
        TestResult tmp_result = run_test(num_test);
        if (tmp_result.result == FINISH) {
            break;
        }
        test_results[num_test++] = tmp_result;
    }
   
    /* Print border */
    printf("%s%s\n", valgrind_run ? "\n" : "",
        "- - - - - - TEST RESULTS - - - - - -");

    /* Print test results */
    for (int i = 0; i < num_test; i++) {

        /* Print test and description */
        printf("Test %04d - %s - ", i, test_results[i].description);

        /* Print result and instructor comment */
        switch (test_results[i].result) {
            case PASS:
                num_pass++;
                GREEN_MSG("Passed! (");
                GREEN_MSG(test_results[i].comment);
                GREEN_MSG(")\n");
                break;

            case FAIL:
                num_fail++;
                RED_MSG("Failed! (");
                RED_MSG(test_results[i].comment);
                RED_MSG(")\n");
                break;

            case CRASH:
                num_crash++;
                YELLOW_MSG("Crashed! (");
                YELLOW_MSG(test_results[i].comment);
                YELLOW_MSG(")\n");
                break;

            case INIT:
                YELLOW_MSG("Uninitialized test. Please fix.\n");
        }
    }

    puts("");

    /* Final report */
    GREEN_MSG("Tests passed: ");
    printf("%d/%d\n", num_pass, num_test);

    RED_MSG("Tests failed: ");
    printf("%d/%d\n", num_fail, num_test);

    YELLOW_MSG("Crashes: ");
    printf("%d/%d\n", num_crash, num_test);

    /* Final grade calculation */
    printf("\nFinal score: %.2f%%\n", 100.00 * ((float)num_pass/(float)num_test));


    return 0;
}
