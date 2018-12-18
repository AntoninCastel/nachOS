#include "syscall.h" 

void fonction() {
	PutString("Vive NachOS !\n");
  UserThreadExit();
}

int main() {
	UserThreadCreate(fonction, 0);
  int i = 10000;
  while (i != 0){i--;}
	Halt();
}
