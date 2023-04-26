# WINAPI Mutex Demo App
This is an application to demonstrate the usage of a mutex in a multithreaded environment
## General Info
This program creates a user-specified number of threads. Each thread iterated a user-specified number of times and adds its
thread ID to a global total each iteration. If the user selects the mutex option, the calculation is protected with a mutex. 
Otherwise, the calculation is unprotected and subject to race events. The program also calculated a theoretical count that
is not affected by race events. When the program is finished, the global count and the theoretical count are displayed side 
by side.
## Languages
Written in C++ 14 Standard using WINAPI functions for thread manipulation
## Launch
Run from the command line using compiler of your choice. Takes three parameters:
1. How many threads should be created (max 100)
2. How many times should each thread iterate (max 100,000,000)
3. Enable mutex? (1 for yes, 0 for no)

Example:
```
start OpProj.exe 56 1032 1
```
This will create 56 threads that iterate 1032 times each, and the mutex option is enabled.