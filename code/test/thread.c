#include "syscall.h" 

void fonction() {
	while(1){}
  UserThreadExit();
}


int main() {
	UserThreadCreate(fonction, 0);
  	int i = 1000000;
  	while (i != 0){i--;}
	Halt();
}
