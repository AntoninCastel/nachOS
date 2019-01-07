#include "syscall.h" 

char a;

void fonctionA() {
	GetString(&a, 1);
  	UserThreadExit();
}

void fonctionB() {
    a = GetChar();
  	UserThreadExit();
}

int main() {
    UserThreadCreate(fonctionA, 0);
    UserThreadCreate(fonctionB, 0);
    while(1);
	return 0;
}
