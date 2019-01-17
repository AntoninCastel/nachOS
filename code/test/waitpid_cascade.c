#include "syscall.h"

int main() {
    pid_t pid = ForkExec("./waitpid_cascade1");
    PutChar('a');
    waitpid(pid);
    return 0;
}
