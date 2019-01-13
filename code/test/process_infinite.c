#include "syscall.h"

int main() {
    ForkExec("./infiniteA");
    ForkExec("./infiniteB");
    while(1) {
        PutChar('C');
    };
    return 0;
}
