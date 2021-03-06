# Seer

Generalized test harness for small-to-medium-sized C projects.

The frontend of Seer is a simple `makefile` interface that can be brought up using the command `make` or `make help`.

In order to make the `valgrind` report more accurate and reduce the potential margin of error, nothing in this test harness is heap/dynamically-allocated. `TestResults` contain no pointers and are passed by value. Delegating memory management (outside of calling `close()`) makes Seer considerably more reliable. Surprisingly, no pointers were used.

## Features

- Seamless test case creation -- all cases are routed through a single function with a switch statement that takes in a test number.

- Crash handling -- Seer catches as many crash signals as possible and records them into the test results

## Typical Workflow

1. Edit `config.h` and add any needed `#include` statements

2. (Optional) Format test report using `make plan`

2. Create test cases and fixtures using `make edit`

3. Move `.c` and `.h` files to the `student` folder

4. Use `make grade` or `make valgrade` to grade a submission

## FAQ

- Why not use `signal`/`sigaction`/`sigsetaction`?

It's not really possible to tell which parts of memory are safe within a given process during a `SIGSEGV` (segmentation fault) or `SIGABRT` (usually fired by `free()` during double-free or corruption). Using the current process after such an event is essentially UB.

- Why not use `setjmp`/`longjmp`?

This was actually my original intent, but this only reduces the inherent risk. If the offending event somehow hits the stack, then this method is just as useless.

- Why not use `pthread`s?

The default (`SIG_DFL`) action for a segmentation fault is to terminate the current process, not the current thread. The only thing that threads don't have in common is the call stack -- everything else is shared. This means one thread could potentially ruin the memory being touched by other threads. As such, the only solution I can use is to `fork()` entire processes.

- What makes `fork()` so much safer? Isn't it a waste of memory?

Not entirely. Although child processes inherit an entire copy of the parent's address space, it is marked as "copy on write". This means if a child process is created and immediately crashes, the only memory copied to them is the memory immediately used/abused. Although spawning a process is inherently more taxing, period, I still think safety matters more here. This holds true especially in the case of more complex assignments.
