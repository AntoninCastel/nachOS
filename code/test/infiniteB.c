#include "syscall.h"

int main() {
    int i;
    for(i = 0; i < 10; ++i) {
        PutChar('b');
    }
    Proc_Exit();
    return 0;
}
