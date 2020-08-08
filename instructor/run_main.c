#include "seer.h"
#include "text.h"
#include <assert.h>

// TODO: this is where you include the student's headers
#include "student.h"

#define MAX_TESTS 10000

int main(void)
{
    /* TODO: change output stream if writing to file */
    _seer_output = stdout;

    /* TODO: change error stream if writing to file */
    _seer_error = stderr;

    /* TODO: change MAX_TESTS if > 10000 tests */
    TestResult test_results[MAX_TESTS] = {{0}};


    /* TODO: create new grading variables if needed */
    int num_test = 0;
    int num_pass = 0;
    int num_fail = 0;
    int num_crash = 0;

    /* Run tests and record results */
    for (;;) {
        TestResult tmp_result = run_test(num_test);
        if (tmp_result.result == FINISH) {
            break;
        }
        test_results[num_test++] = tmp_result;
    }

    for (int i = 0; i < num_test; i++) {
        printf("Test %04d - %s - ", i, test_results[i].comment);
        switch (test_results[i].result) {
            case PASS:
                num_pass++;
                GREEN_MSG(_seer_output, "Passed!\n");
                break;

            case FAIL:
                num_fail++;
                RED_MSG(_seer_output, "Failed!\n");
                break;

            case CRASH:
                num_crash++;
                YELLOW_MSG(_seer_output, "Crashed!\n");
                break;
        }
    }

    puts("");

    GREEN_MSG(_seer_output, "Tests passed: ");
    printf("%d/%d\n", num_pass, num_test);

    RED_MSG(_seer_output, "Tests failed: ");
    printf("%d/%d\n", num_fail, num_test);

    YELLOW_MSG(_seer_output, "Crashes: ");
    printf("%d/%d\n", num_crash, num_test);

    return 0;
}
