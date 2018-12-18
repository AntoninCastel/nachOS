#include "syscall.h" 

void fonction() {
	PutString("Vive NachOS !\n");
  UserThreadExit();
}

int main() {
	/*
	if(UserThreadCreate(fonction, 0) == -1) {
		PutString("Erreur\n");
	}*/
	UserThreadCreate(fonction, 0);
  int i = 10000;
  while (i != 0){i--;}
	Halt();
}
