#include "syscall.h"

int main() {
    int i;
    for(i = 0; i < 10; ++i) {
        PutChar('b');
    }
    return 0;
}
