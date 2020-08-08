#include "seer.h"
#include "text.h"

TestResult _run_test(int test_num)
{
    TestResult to_return = TEST_RESULT_INIT;

    switch (test_num) {

        case 0: {
            TestResult result = {
                .result = PASS,
                .comment = "Good test",
            };
            to_return = result;
            break;
        }

        case 1: {
            TestResult result = {
                .result = PASS,
                .comment = "Good boy",
            };
            to_return = result;
            break;
        }

        default: {
            TestResult result = {
                .result = FINISH,
                .comment = "Testing finished",
            };
            to_return = result;
            break;
        }
    }

    return to_return;
}
