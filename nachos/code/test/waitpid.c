#include "syscall.h"

int main() {
    pid_t pid = ForkExec("./progA");
    waitpid(pid);
    PutString("Le programme principal termine\n");
    Proc_Exit();
    return 0;
}
