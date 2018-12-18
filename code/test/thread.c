#include "syscall.h" 

void fonction() {
	PutString("montagne\n");
  UserThreadExit();
}

int main() {
  PutString("salut marianne !\n");

	UserThreadCreate(fonction, 0);
  PutString("COUCOUCOUCOUCOUCOUCOUCOUCOU \n");
  int i = 10000;
  while (i != 0){i--;}
	Halt();
}
