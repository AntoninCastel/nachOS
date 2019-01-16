#include "syscall.h" 

semaphore_t sem;

void fonction3() {
	Sem_P(sem);
	PutString("Troisieme\n");
	Sem_V(sem);

  	UserThreadExit();
}
void fonction2() {
	UserThreadCreate(fonction3, 0);	
	UserThreadCreate(fonction3, 0);	

	Sem_P(sem);
	PutString("Deuxième\n");
	Sem_V(sem);

  	UserThreadExit();
}
void fonction() {
	UserThreadCreate(fonction2, 0);	
	UserThreadCreate(fonction2, 0);	

	Sem_P(sem);
	PutString("Premier\n");
	Sem_V(sem);

  	UserThreadExit();
}

int main() {
	sem=Sem_Init(1);
	UserThreadCreate(fonction, 0);		

	return 0;
}
