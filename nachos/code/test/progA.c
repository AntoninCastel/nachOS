#include "syscall.h"

int main() {
    PutString("Le processus fils se lance...");
    int i;
    for(i = 0; i < 1000; ++i) {}
    PutString("Puis se termine");
    Proc_Exit();
    return 0;
}
