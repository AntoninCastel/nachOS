#include "syscall.h"

int main() {
    pid_t pid = ForkExec("./waitpid_multiple2");
    waitpid(pid);
    PutString("Fin du premier processus\n");
    return 0;
}
