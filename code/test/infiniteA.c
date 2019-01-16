#include "syscall.h"

int main() {
    int i;
    for(i = 0; i < 1000; ++i) {
        PutChar('a');
    }
    Proc_Exit();
    return 0;
}
