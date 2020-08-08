#include "seer.h"
#include "text.h"
#include "config.h"

TestResult _run_test(int test_num)
{
    /* Initialize result struct */
    TestResult test_result = TEST_RESULT_INIT;

    /* Choose test */
    switch (test_num) {

        /**
         * TODO: make test cases here.
         *
         * A test case is defined by its case number (switch case).
         * In creating a test case, you must use the proper ordering.
         * This means you can't make test 0, then skip to test 2. You
         * must make test 1, and THEN test 2.
         * 
         * Every time a test runs, a new test result object is created.
         * This object has three members that you fill out:
         *
         *    description - a descriptive summary of the test being done
         *
         *    result - either PASS or FAIL. Assign when a test finishes.
         *
         *    comment - descriptive summary of the test result (should
         *              be specific to the test result!)
         *
         * description and comment are optional, but result is not. If
         * you do not fill out the result, the harness will report the
         * test as uninitialized and advise you to fix it.
         *
         * There is a linked list example in a separate repo branch.
         **/

        /*

        case 0: {
            break;
        }

         */

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
