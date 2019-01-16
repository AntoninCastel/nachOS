#include "syscall.h"

int main() {
    int i;
    pid_t pid = ForkExec("./infiniteA");
    pid_t pid2 = ForkExec("./infiniteB");
    for(i = 0; i < 100; ++i) {
        PutChar('c');
    }
    waitpid(pid);
    waitpid(pid2);
    return 0;
}
