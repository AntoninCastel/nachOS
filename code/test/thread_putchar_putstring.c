#include "syscall.h" 

void fonctionA() {
	PutString("AAAAAAAAAA");
  	UserThreadExit();
}

void fonctionB() {
    PutChar('B');
  	UserThreadExit();
}

int main() {
    int tidA = UserThreadCreate(fonctionA, 0),
        tidB = UserThreadCreate(fonctionB, 0);
    UserThreadJoin(tidA);
    UserThreadJoin(tidB);
	return 0;
}
