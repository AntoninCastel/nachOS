#include "syscall.h"

int main() {
    int i;
    ForkExec("./PutCharA");
    ForkExec("./PutCharB");
    for(i = 0; i < 100; ++i) {
        PutChar('c');
    }
    while(1) {}
    return 0;
}
