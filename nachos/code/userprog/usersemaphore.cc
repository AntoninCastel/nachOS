#include "usersemaphore.h"

int do_Sem_Init(int n){
	currentThread->space->UserSemaphoreSynch->P();
	int id_semaphore;
	if(currentThread->space->UserSemaphoresCounter==NB_MAX_USER_SEMAPHORES){
		return -1;
	}
	id_semaphore=currentThread->space->UserSemaphoresCounter;
	char* name=new char[30];
	sprintf(name, "semaphore utilisateur n°%d", id_semaphore);
	currentThread->space->UserSemaphores[id_semaphore]=new Semaphore(name, n);
	currentThread->space->UserActiveSemaphores->Mark(id_semaphore);
	currentThread->space->UserSemaphoresCounter++;
	currentThread->space->UserSemaphoreSynch->V();
	return id_semaphore;
}
int do_Sem_P(int sem){
	if(!currentThread->space->UserActiveSemaphores->Test(sem)){
		return -1;
	}
	currentThread->space->UserSemaphores[sem]->P();
	return 0;
}
int do_Sem_V(int sem){
	if(!currentThread->space->UserActiveSemaphores->Test(sem)){
		return -1;
	}
	currentThread->space->UserSemaphores[sem]->V();
	return 0;
}
int do_Sem_GetValue(int sem){
	if(!currentThread->space->UserActiveSemaphores->Test(sem)){
		return -1;
	}
	return currentThread->space->UserSemaphores[sem]->getValue();

}
int do_Sem_Destroy(int sem){
	currentThread->space->UserSemaphoreSynch->P();
	int retCode;
	if (currentThread->space->UserActiveSemaphores->Test(sem)){
		delete currentThread->space->UserSemaphores[sem];
		currentThread->space->UserActiveSemaphores->Clear(sem);
		retCode=0;
	}
	else 
		retCode=-1;
	currentThread->space->UserSemaphoreSynch->V();
	return retCode;
}
