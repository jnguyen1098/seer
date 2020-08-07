#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "placeholder.h"

void simulate(int signal_number);

int main(void)
{
    simulate(1);
    return 0;

    for (int i = 0; i < 32; i++) {
        simulate(i);
        puts("");
    }
    return 0;
}

void simulate(int signal_number)
{
    int     fd[2], nbytes;
    pid_t   childpid;

    pipe(fd);

    if ((childpid = fork()) == -1) {
        perror("fork fail: ");
        exit(1);
    }

    if (childpid == 0) {
        close(fd[0]);

        Response test_result = { "Hey dude", 1 };

        write(fd[1], &test_result, sizeof(test_result));
        exit(0);
    }

    else {
        close(fd[1]);

#if 0
        kill(childpid, signal_number);
#endif

        int returnStatus = 0;
        waitpid(childpid, &returnStatus, WUNTRACED);

        printf("Right after waitpid, returnStatus is %ld\n", returnStatus);

        if (WIFEXITED(returnStatus)) {
            printf("WIFEXITED: child exited normally: %s\n",
                    strsignal(WEXITSTATUS(returnStatus)));
        }

        else if (WIFSTOPPED(returnStatus)) {
            printf("WIFSTOPPPED: child got exited by stop: %s\n",
                    strsignal(WSTOPSIG(returnStatus)));
            return;
        }

        else if (WIFSIGNALED(returnStatus)) {
            printf("WIFSIGNALED: child exited by signal: %s\n",
                    strsignal(WTERMSIG(returnStatus)));
            return;
        }

        Response test_result = {{0}, 0};

        nbytes = read(fd[0], &test_result, sizeof(test_result));
        if (nbytes == 0) {
            puts("Got nothing");
        }
        else {
            printf("Received payload\n");
            printf("Feedback: %s\n", test_result.comment);
            printf("Passed: %d\n", test_result.passed);
        }
    }
}
