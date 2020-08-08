#include "seer.h"
#include "text.h"

// TODO: this is where you include the student's headers
#include "student.h"

int main(void)
{
    call_seer();
    GREEN_MSG("hello world\n");
    YELLOW_MSG("hello world\n");
    RED_MSG("hello world\n");
//    _seer_test_ansi();
    printf("5 + 6 is %d\n", add_two_numbers(5, 6));
    return 0;
}
