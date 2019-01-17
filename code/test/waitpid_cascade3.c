#include "syscall.h"

int main() {
    PutChar('d');
    Proc_Exit();
    return 0;
}
