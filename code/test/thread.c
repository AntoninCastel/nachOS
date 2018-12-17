#include "syscall.h" 

void antoestuncon() {
	PutString("Putain j'avoue !\n");
}

int main() {
	if(UserThreadCreate(antoestuncon, 0) == -1) {
		PutString("Erreur\n");
	}
	Halt();
}
