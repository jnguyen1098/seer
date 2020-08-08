# Seer

Generalized test harness for small-to-medium-sized C projects.

The frontend of Seer is a simple `makefile` interface that can be brought up using the command `make` or `make help`.

## Features

- Seamless test case creation -- all test cases are routed through a single function with a switch statement that takes in a test number.

- Crash catching -- the harness catches as many signals (segmentation fault, abort, etc.) as possible and encapsulates such events in test results. Other solutions (`setjmp`/`longjmp`, `pthreads`, `signal`/`sigsetaction`/`sigaction`) were found to be unsafe, so test cases are isolated into separate processes

## Typical workflow

1. Use `make plan` to format your results report

2. Use `make edit` to edit the test cases and fixtures

3. Move a given student's `.c` and `.h` files to the `student` folder

4. Use `make grade` or `make valgrade` to grade a submission
