#include "syscall.h" 

char a;

void fonctionA() {
	GetString(&a, 1);
    PutChar(a);
  	UserThreadExit();
}

void fonctionB() {
    a = GetChar();
    PutChar(a);
  	UserThreadExit();
}

int main() {
    int tidA = UserThreadCreate(fonctionA, 0),
        tidB = UserThreadCreate(fonctionB, 0);

    UserThreadJoin(tidA);
    UserThreadJoin(tidB);
	return 0;
}
