#include "seer.h"
#include "text.h"

// TODO: this is where you include the student's headers
#include "student.h"

int main(void)
{
    for (int i = 0; i < 32; i++) {
        TestResult lmao = run_test(i);
        printf("passed: %d\n", lmao.passed);
        printf("feedback: %s\n", lmao.feedback);
        puts("");
    }
    malloc(1);
    return 0;
}
