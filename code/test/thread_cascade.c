#include "syscall.h" 

semaphore_t sem;
int a,b,c,d;

void fonction4() {
	Sem_P(sem);
	PutString("Quatrieme\n");
	Sem_V(sem);
  	UserThreadExit();
}

void fonction3() {
	d = UserThreadCreate(fonction4, 0);
	Sem_P(sem);
 	PutString("Troisieme\n");
	Sem_V(sem);
  	UserThreadExit();
}

void fonction2() {
	c = UserThreadCreate(fonction3, 0);	
	Sem_P(sem);
	PutString("Deuxieme");
	Sem_V(sem);
  	UserThreadExit();
}

void fonction() {
	b = UserThreadCreate(fonction2, 0);	
	Sem_P(sem);
	PutString("Premier");
	Sem_V(sem);
  	UserThreadExit();
}
int main() {
	sem=Sem_Init(1);
	a = UserThreadCreate(fonction, 0);		

  	UserThreadJoin(a);
	UserThreadJoin(b);
	UserThreadJoin(c);
  	UserThreadJoin(d);
	return 0;
}
