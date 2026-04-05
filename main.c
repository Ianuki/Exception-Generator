#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>
#include <stdlib.h>

sigjmp_buf checkpoint;

void handler(int signal) {
    printf("%s\n", strsignal(signal));
    siglongjmp(checkpoint, 1);
}

void stackfuckerflow() {
    char buffer[1024];
    stackfuckerflow();
}

int main() {
    signal(SIGSEGV, handler);
    signal(SIGFPE,  handler);
    signal(SIGILL,  handler);
    signal(SIGTRAP, handler);
    signal(SIGABRT, handler);

    if (sigsetjmp(checkpoint, 1) == 0) {
        volatile int zero = 0;
        int crash = 5 / zero;
    }

    if (sigsetjmp(checkpoint, 1) == 0) {
        volatile int *pointer = NULL;
        int crash = *pointer;
    }

    if (sigsetjmp(checkpoint, 1) == 0) {
        asm(
            "\n\tud2"
        );
    }

    if (sigsetjmp(checkpoint, 1) == 0) {
        asm(
            "\n\tint3"
        );
    }

    if (sigsetjmp(checkpoint, 1) == 0) {
        abort();
    }

    if (sigsetjmp(checkpoint, 1) == 0) {
        stackfuckerflow();
    }

    return 0;
}
