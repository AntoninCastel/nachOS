#include "syscall.h" 

char a[100];

void fonctionA() {
	GetString(a, 100);
  	UserThreadExit();
}

void fonctionB() {
    PutString(a);
  	UserThreadExit();
}

int main() {
    int tidA = UserThreadCreate(fonctionA, 0),
        tidB = UserThreadCreate(fonctionB, 0);

    UserThreadJoin(tidA);
    UserThreadJoin(tidB);
	return 0;
}
