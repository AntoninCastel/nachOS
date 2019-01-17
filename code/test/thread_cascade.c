/* Creation de plusieurs threads en cascade, chaque thread qui lance d'autres
 * threads fait un join sur ceux-ci, sauf pour des threads crée en dernier
 *  qui est attendu pas le main. 
 * ATTENTION : Il y a un bug qui bloque l'execution quand on fait join dans 
 * un thread autre que main, pas eu le temps de debugger.
 */
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
	UserThreadJoin(d);
  	UserThreadExit();
}

void fonction2() {
	c = UserThreadCreate(fonction3, 0);	
	Sem_P(sem);
	PutString("Deuxieme");
	Sem_V(sem);
	UserThreadJoin(c);
  	UserThreadExit();
}

void fonction() {
	b = UserThreadCreate(fonction2, 0);	
	Sem_P(sem);
	PutString("Premier");
	Sem_V(sem);
	UserThreadJoin(b);
  	UserThreadExit();
}
int main() {
	sem=Sem_Init(1);
	a = UserThreadCreate(fonction, 0);		
  	UserThreadJoin(a);
	return 0;
}
