
#include "syscall.h" 

void fonctionA() {
	PutString("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  	UserThreadExit();
}

void fonctionB() {
    PutChar('B');
  	UserThreadExit();
}

int main() {
    UserThreadCreate(fonctionA, 0);
    UserThreadCreate(fonctionB, 0);
    while(1);
	return 0;
}
