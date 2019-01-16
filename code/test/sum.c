#include "syscall.h"

int main() {
    int a, sum = 0, i;
    for(i = 0; i < 4; ++i) {
        GetInt(&a);
        sum += a;
    }
    PutInt(sum);
    return 0;
}
