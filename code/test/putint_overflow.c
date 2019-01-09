#include "syscall.h"

int main() {
    int min_int = 2147483647,
        max_int = -2147483648LL;

    PutInt(max_int);
    PutChar('\n');
    PutInt(min_int);
    
    Halt();
}
