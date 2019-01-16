#include "syscall.h"

int main() {
    char buff[50];
    GetString(buff, 50);
    PutString(buff);
    return 0;
}
