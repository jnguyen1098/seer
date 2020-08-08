#include "seer.h"
#include "text.h"
#define MAX_TESTS 1000

/* TODO: edit config.h to include student .h files */
#include "config.h"

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
    TestResult test_results[MAX_TESTS] = {0};

    /* TODO: create new grading variables if needed */
    int num_test = 0;
    int num_pass = 0;
    int num_fail = 0;
    int num_crash = 0;

    /* Run tests and record results. Shouldn't change
     * unless absolutely necessary. */
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

    /* TODO: Print test results. Change as you place. */
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

    /* TODO: Final report. Change as you please. */
    GREEN_MSG("Tests passed: ");
    printf("%d/%d\n", num_pass, num_test);

    RED_MSG("Tests failed: ");
    printf("%d/%d\n", num_fail, num_test);

    YELLOW_MSG("Crashes: ");
    printf("%d/%d\n", num_crash, num_test);

    /* TODO: Final grade calculation. Change as you please. */
    printf("\nFinal score: %.2f%%\n", 100.00 * ((float)num_pass/(float)num_test));


    return 0;
}
