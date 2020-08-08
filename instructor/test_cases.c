#include "seer.h"
#include "text.h"
#include "config.h"

/* Commpares if a list is equal to an array */
int instructor_list_equals(Node *list, int *nums, size_t size)
{
    size_t i = 0;
    for (Node *tmp = list; tmp; tmp = tmp->next) {
        if (!tmp || nums[i] != tmp->data)
            return 0;
        i++;
    }
    if (i != size)
        return 0;
    return 1;
}

/* Quickly creates a linked list for instructor testing */
Node *instructor_list_create(int *nums, size_t size)
{
    if (!nums || !size)
        return NULL;

    Node *list;
    if (!(list = create_node(nums[0])))
        return NULL;

    for (size_t i = 1; i < size; i++)
        if (!(insert_node(list, nums[i])))
            return NULL;

    if (!(instructor_list_equals(list, nums, size)))
        return NULL;

    return list;
}

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
         * must make test 1.
         * 
         * Every time a test runs, a new test result object is created.
         * This object has three members:
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
         **/

        case 0: {
            /* Description */
            strcpy(test_result.description, "Create node with value of 1");

            /* Perform testing and record results */
            Node *list = create_node(1);
            if (list && list->data == 1) {
                test_result.result = PASS;
                free(list);
            } else {
                test_result.result = FAIL;
                strcpy(test_result.comment, "Could not allocate list");
            }
            break;
        }
        
        case 1: {
            strcpy(test_result.description, "Insert 4 into list [1]");
            Node *list = create_node(1);
            if (!insert_node(list, 4)) {
                test_result.result = FAIL;
                strcpy(test_result.comment, "Could not insert 4");
            } else {
                if (list->data == 1 && list->next->data == 4) {
                    test_result.result = PASS;
                    destroy_list(list);
                }
                else {
                    test_result.result = FAIL;
                    strcpy(test_result.comment, "Second value not 4");
                    destroy_list(list);
                }
            }
            break;
        }

        case 2: {
            strcpy(test_result.description, "Create list [1, 2, 3]");

            int nums[] = {1, 2, 3};
            size_t size = sizeof(nums) / sizeof(nums[0]);
            Node *list = instructor_list_create(nums, size);

            if (list) {
                test_result.result = PASS;
                destroy_list(list);
            }
            else {
                test_result.result = FAIL;
                destroy_list(list);
                strcpy(test_result.comment, "Could not create [1, 2, 3]");
            }

            break;
        }

        case 3: {
            strcpy(test_result.description, "Create list [20, 19, ..., 1]");

            int nums[] = {
                20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6,
                5, 4, 3, 2, 1,
            };
            size_t size = sizeof(nums) / sizeof(nums[0]);
            Node *list = instructor_list_create(nums, size);

            if (list) {
                test_result.result = PASS;
                destroy_list(list);
            }
            else {
                test_result.result = FAIL;
                destroy_list(list);
                strcpy(test_result.comment, "Could not create list");
            }
                        
            break;
        }

        case 4: {
            strcpy(test_result.description, "Search for 10 in [5, 10, 15]");

            int nums[] = {
                5, 10, 15,
            };

            size_t size = sizeof(nums) / sizeof(nums[0]);
            Node *list = instructor_list_create(nums, size);

            if (!list) {
                test_result.result = FAIL;
                destroy_list(list);
                strcpy(test_result.comment, "Could not create list for search");
            }

            else if (!search(list, 10)) {
                test_result.result = FAIL;
                destroy_list(list);
                strcpy(test_result.comment, "Could not find known value 10 in list");
            }

            else {
                test_result.result = PASS;
                destroy_list(list);
            }

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
