#include "syscall.h"

int main() {
    ForkExec("./waitpid_cascade3");
    PutChar('c');
    ForkExec("./waitpid_cascade3");
    PutChar('c');
    Proc_Exit();
    return 0;
}
