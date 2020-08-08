#include "seer.h"
#include "text.h"

TestResult _run_test(int test_num)
{
    TestResult to_return = TEST_RESULT_INIT;

    switch (test_num) {
        default:;
            TestResult result = {
                .passed = test_num,
                .feedback = "lmao",
            };
            to_return = result;
            break;
    }

    return to_return;
}
