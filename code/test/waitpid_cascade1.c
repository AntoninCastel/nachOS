#include "syscall.h"

int main() {
    ForkExec("./waitpid_cascade2");
    PutChar('b');
    ForkExec("./waitpid_cascade2");
    PutChar('b');
    ForkExec("./waitpid_cascade2");
    PutChar('b');
    Proc_Exit();
    return 0;
}
