#include "seer.h"
#include "text.h"
#include "config.h"

TestResult _run_test(int test_num)
{
    /* Initialize result struct */
    TestResult test_result = TEST_RESULT_INIT;

    /* Choose test */
    switch (test_num) {
        case 0: {
            /* Initialize results */
            char description[MAX_STR] = "Add 5 and 6 (11)";
            char comment[MAX_STR] = "";
            ResultCode result = INIT;

            /* Perform testing */
            int five_plus_six = add_two_numbers(5, 6);
            if (five_plus_six == 11) {
                result = PASS;
                strcpy(comment, "Correct!");
            } else {
                result = FAIL;
                strcpy(comment, "Incorrect!");
            }

            /* Write to test result */
            test_result.result = result;
            strncpy(test_result.description, description, MAX_STR - 1);
            strncpy(test_result.comment, comment, MAX_STR - 1);
            break;
        }

        /* This is used to signal that the 
         * testing is finished. Do not change.*/
        default: {
            TestResult result = {
                .result = FINISH,
                .description = "Testing finished",
                .comment = "Testing finished",
            };
            test_result = result;
            break;
        }
    }

    /* Return */
    return test_result;
}
