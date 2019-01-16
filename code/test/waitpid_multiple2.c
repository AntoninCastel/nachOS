#include "syscall.h"

int main() {
    pid_t pid = ForkExec("./progA");
    waitpid(pid);
    PutString("Fin du second processus\n");
    int i;
    for(i = 0; i < 1000; ++i) {}
    Proc_Exit();
    return 0;
}
