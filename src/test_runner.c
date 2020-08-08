#include "seer.h"
#include "text.h"

const char _signalstr[32][16] = {
    "(none)",   // No signal
    "SIGHUP",   // Terminal hangup
    "SIGINT",   // Interrupt
    "SIGQUIT",  // Quit + core dump
    "SIGILL",   // Illegal instruction
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

TestResult run_test(int test_num)
{
    /* Create test result struct */
    TestResult test_result = TEST_RESULT_INIT;

    /* Create IPC */
    int fd[2];
    pid_t child_pid;

    /* Check pipe */
    if (pipe(fd) == -1) {
        RED_MSG("Fatal: pipe failed!\n");
        perror("pipe");
        abort();
    }

    /* Fork and check */
    fflush(_seer_output);
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
            int nbytes = read(fd[0], &test_result, sizeof(TestResult));
            if (nbytes != sizeof(TestResult)) {
                RED_MSG("FATAL: read() TestResult mismatch. "
                        "Do not trust tests after this line.\n");
                test_result.result = FAIL;
                strcpy(test_result.comment, "Internal system error.");
            }
        }

        else {
            int signal_code = 
                WIFSTOPPED(child_return) ?
                WSTOPSIG(child_return) :
                WTERMSIG(child_return);

            test_result.result = CRASH;
            sprintf(
                    test_result.comment,
                    "Killed by %s signal",
                    _signalstr[signal_code]
                   );
        }

    }

    return test_result;
}



















