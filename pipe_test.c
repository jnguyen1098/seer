#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int     fd[2], nbytes;
    pid_t   childpid;
    char    string[] = "Hello, world!\n";
    char    readBuffer[80];

    pipe(fd);

    if ((childpid = fork()) == -1) {
        perror("fork fail: ");
        exit(1);
    }

    if (childpid == 0) {
        close(fd[0]);

        char *something = malloc(1);
        for (int i = 0; i < 100; i++)
            free(something);
        free((char *)0x324);
        __builtin_trap();
        raise(SIGSEGV);

        write(fd[1], string, strlen(string) + 1);
        exit(0);
    }

    else {
        close(fd[1]);

        int returnStatus = 0;
        waitpid(childpid, &returnStatus, 0);

        if (WIFSIGNALED(returnStatus)) {
            printf("first return status %ld\n", returnStatus);
            switch (WTERMSIG(returnStatus)) {
                case SIGSEGV:
                    puts("segfault");
                    break;

                case SIGBUS:
                    puts("bus error");
                    break;

                case SIGILL:
                    puts("illegal instruction");
                    break;

                case SIGTERM:
                    puts("termination");
                    break;

                case SIGINT:
                    puts("interruption");
                    break;

                case SIGSTOP:
                    puts("stop signal");
                    break;

                case SIGABRT:
                    puts("abort");
                    break;
            }
            return 0;
        }

        nbytes = read(fd[0], readBuffer, sizeof(readBuffer));
        if (nbytes == 0)
            puts("Got no string");
        else
            printf("Received (%d) string: %s", strlen(readBuffer), readBuffer);
    }

    return 0;
}
