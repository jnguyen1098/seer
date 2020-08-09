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
         * TODO: make test cases here
         *
         * Create each new test case as a "case" in the switch statement.
         * You must use the proper ordering or the testing will suddenly end.
         * 
         * You will be responsible for filling out the description() and
         * result. These two fields are not optional.
         * 
         * What is optional, though, is the 'comment' member.
         **/

        case 0: {
            description("Assert openFileForReading(NULL) == NULL");
            if (openFileForReading("invalidfile")) {
                test_result.result = FAIL;
                strcpy(test_result.comment, "Should have returned NULL");
            } else {
                test_result.result = PASS;
            }
            break;
        }

        /* This is used to signal that the 
         * testing is finished. Do not change.*/
        default: {
            description("Testing finished");
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
