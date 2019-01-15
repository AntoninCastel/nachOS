#include "syscall.h"

int main() {
    int i;
    ForkExec("./infiniteA");
    ForkExec("./infiniteB");
    for(i = 0; i < 100; ++i) {
        PutChar('c');
    }
    while(1) {}
    return 0;
}
