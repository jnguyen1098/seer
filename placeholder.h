#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#define MAX_STR 128

typedef struct test_struct {
    char comment[MAX_STR];
    int passed;
} Response;

const char _gs_signal_names[32][16] = {
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

#endif
