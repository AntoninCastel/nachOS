#include "syscall.h"

void ecrire1(){
	PutChar('a');
	PutChar('b');
	UserThreadExit();
}

void ecrire2(){
	PutChar('c');
	PutChar('d');
	UserThreadExit();
}

int main(){
	int tidA = UserThreadCreate(ecrire1, 0),
	 	tidB = UserThreadCreate(ecrire2, 0);
	UserThreadJoin(tidA);
	UserThreadJoin(tidB);
	return 0;
}