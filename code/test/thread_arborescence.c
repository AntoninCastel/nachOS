/* Test créant des threads qui créent eux meme plusieurs threads
 * Tous les threads lancés sont attendus dans le main.
 */

#include "syscall.h" 

semaphore_t sem;
int t1,t2,t3,t4,t5;

void fonction3() {
	Sem_P(sem);
	PutString("Troisieme\n");
	Sem_V(sem);

  	UserThreadExit();
}
void fonction2() {
	t3=UserThreadCreate(fonction3, 0);	
	t4=UserThreadCreate(fonction3, 0);	

	Sem_P(sem);
	PutString("Deuxième\n");
	Sem_V(sem);
  	UserThreadExit();
}
void fonction() {
	t2=UserThreadCreate(fonction2, 0);
	t5=UserThreadCreate(fonction2,0);	

	Sem_P(sem);
	PutString("Premier\n");
	Sem_V(sem);
  	UserThreadExit();
}

int main() {
	sem=Sem_Init(1);
	t1=UserThreadCreate(fonction, 0);		

    UserThreadJoin(t1);
	UserThreadJoin(t2);
	UserThreadJoin(t3);
	UserThreadJoin(t4);
	UserThreadJoin(t5);
	return 0;
}
