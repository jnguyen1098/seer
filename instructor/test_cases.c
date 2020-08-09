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
            description("Test string_to_upper() on 'hello'");
            char test_string[] = "hello";
            char target_string[] = "HELLO";
            if (strcmp(string_to_upper(test_string), target_string)) {
                test_result.result = FAIL;
                strcpy(test_result.comment, "Strings unequal");
            } else {
                test_result.result = PASS;
            }
            break;
        }

        case 1: {
            description("Test string_to_upper() on long string");
            char test_string[] = "a sfg asfgFg ASfg fds gaFg AFSgfa sFga fs";
            char target_string[] = "A SFG ASFGFG ASFG FDS GAFG AFSGFA SFGA FS";
            if (strcmp(string_to_upper(test_string), target_string)) {
                test_result.result = FAIL;
                strcpy(test_result.comment, "Strings unequal");
            } else {
                test_result.result = PASS;
            }
            break;
        }

        case 2: {
            /* Intentionally forcing a crash */
            description("Force segmentation fault");
            char *bad_ptr = NULL;
            strcpy(bad_ptr, "safdgjjsalkdfajlksdfg");
            break;
        }

        case 3: {
            /* string_to_lower() was intentionally made to fail */
            description("Test string_to_lower on 'hElLo'");
            char test_string[] = "hElLo";
            char target_string[] = "hello";
            if (strcmp(string_to_lower(test_string), target_string)) {
                test_result.result = FAIL;
                strcpy(test_result.comment, "Strings unequal");
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
