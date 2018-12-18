#include "syscall.h" 

void fonction() {
	PutString("montagne\n");
    UserThreadExit();
}

int main() {
    PutString("salut marianne !\n");

	UserThreadCreate(fonction, 0);
    PutString("COUCOUCOUCOUCOUCOUCOUCOUCOU \n");
    int i;
    for(i = 0; i < 1000000;++i);
	Halt();
}
