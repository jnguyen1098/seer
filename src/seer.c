/**
 * @private
 * @file seer.c
 * @author Jason Nguyen <jnguye21@uoguelph.ca>
 * @brief Test process isolation function
 */
#include "seer.h"
#include "text.h"

int fd[2];

const char _signalstr[32][16] = {
    "(none)",   // No signal
    "SIGHUP",   // Terminal hangup
    "SIGINT",   // Interrupt
    "SIGQUIT",  // Quit + core dump
    "SIGILL",   // "The notorious" Illegal instruction
    "SIGTRAP",  // Trace trap
    "SIGABRT",  // Aborted
    "SIGBUS",   // Bus error
    "SIGFPE",   // Floating point error
    "SIGKILL",  // Killed
    "SIGUSR1",  // User-defined signal 1
    "SIGSEGV",  // Segmentation fault
    "SIGUSR2",  // User-defined signal 2
    "SIGPIPE",  // Broken pipe
    "SIGALRM",  // Alarm clock
    "SIGTERM",  // Terminated
    "SIGSTKFLT",// Stack fault
    "SIGCHLD",  // Child status changed
    "SIGCONT",  // Continue
    "SIGSTOP",  // Stopped
    "SIGTSTP",  // Keyboard stop
    "SIGTTIN",  // Backround read (tty)
    "SIGTTOU",  // Background write (tty)
    "SIGURG",   // Urgent socket cond.
    "SIGXCPU",  // CPU limit reached
    "SIGXFSZ",  // File size limit
    "SIGVTALRM",// Virtual time alarm
    "SIGPROF",  // Profiling alarm clock
    "SIGWINCH", // Window size change
    "SIGIO",    // I/O now possible
    "SIGPWR",   // Power failure restart
    "SIGSYS",   // Bad system call
};

void description(char message[SEER_MAX_STR])
{
    if (strlen(message) >= SEER_MAX_STR) {
        char overflow_message[SEER_MAX_STR] = {0};
        strncpy(overflow_message, "Description too long. Fix.", SEER_MAX_STR);
        write(fd[1], overflow_message, SEER_MAX_STR);
    }

    char to_send[SEER_MAX_STR] = "";
    strncpy(to_send, message, SEER_MAX_STR);
    write(fd[1], message, SEER_MAX_STR);
}

TestResult run_test(int test_num)
{
    /* Create test result struct */
    TestResult test_result = TEST_RESULT_INIT;

    /* Create IPC */
    pid_t child_pid;

    /* Check pipe */
    if (pipe(fd) == -1) {
        RED_MSG("Fatal: pipe failed!\n");
        perror("pipe");
        abort();
    }

    /* Fork and check */
    fflush(stdout);
    if ((child_pid = fork()) == -1) {
        RED_MSG("Fatal: fork failed!\n");
        perror("fork");
        abort();
    }

    /* Child test runner */
    if (child_pid == 0) {
        /* Close read end */
        close(fd[0]);

        /* Make tmp test result to send back */
        TestResult tmp = _run_test(test_num);

        write(fd[1], &tmp, sizeof(TestResult));
        exit(0);
    }

    /* Parent interpreter */
    else {
        /* Close write end */
        close(fd[1]);

        /* Check child */
        int child_return = 0;
        waitpid(child_pid, &child_return, WUNTRACED);

        if (WIFEXITED(child_return)) {
            /* Prepare description */
            char description[SEER_MAX_STR] = {0};

            /* Read description */
            int desc_bytes = read(fd[0], description, SEER_MAX_STR);
            if (desc_bytes != SEER_MAX_STR) {
                RED_MSG("FATAL: Could not read description from pipe. "
                        "TestResult wasn't written. Aborting Seer...\n");
                abort();
            }

            /* Read in intermediate TestResult */
            int test_bytes = read(fd[0], &test_result, sizeof(TestResult));
            if (test_bytes != sizeof(TestResult)) {
                RED_MSG("ERROR: read() TestResult mismatch. "
                        "Did you forget a description()? Please fix.\n");
                test_result.result = FAIL;
                strcpy(test_result.comment, "Internal pipe read error.");
                strcpy(test_result.description, "(unknown test)");
            } else {
                /* Write description to intermediate TestResult if no error */
                strcpy(test_result.description, description);
            }
        } else {
            /* Derive crash reason */
            int signal_code = 
                WIFSTOPPED(child_return) ?
                WSTOPSIG(child_return) :
                WTERMSIG(child_return);

            /* Prepare to salvage description */
            char description[SEER_MAX_STR] = "(description lost due to crash)";

            /* Read description from pipe */
            int nbytes = read(fd[0], description, SEER_MAX_STR);

            /* Verify pipe read */
            if (nbytes != SEER_MAX_STR) {
                RED_MSG("FATAL: read() description salvage mismatch. "
                        "Do not trust tests after this line.\n");
            }

            /* Create diagnostic TestResult */
            strcpy(test_result.description, description);
            test_result.result = CRASH;
            sprintf(test_result.comment, "Killed by %s signal",
                    _signalstr[signal_code]);
        }

    }

    return test_result;
}
