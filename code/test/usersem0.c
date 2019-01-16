#include "syscall.h"

semaphore_t s;

void f1(){
	int i;
	Sem_P(s);
	for(i=0;i<10;i++)
		PutChar('.');
	Sem_V(s);
	UserThreadExit();
}

void f2(){
	int i;
	Sem_P(s);
	for(i=0;i<10;i++)
		PutChar('/');
	Sem_V(s);
	UserThreadExit();
}

int main(){
	s=Sem_Init(1);
	int t1,t2;
	t1=UserThreadCreate(f1,0);
	t2=UserThreadCreate(f2,0);
	UserThreadJoin(t1);
	UserThreadJoin(t2);
	Sem_Destroy(s);
	return 0;
}