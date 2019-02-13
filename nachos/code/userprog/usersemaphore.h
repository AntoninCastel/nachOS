#ifndef __USERSEMAPHORE_H__
#define __USERSEMAPHORE_H__
#include "synch.h"
#include "system.h"

class Semaphore;

extern int 	do_Sem_Init(int n);
extern int do_Sem_P(int sem);
extern int do_Sem_V(int sem);
extern int do_Sem_GetValue(int sem);
extern int do_Sem_Destroy(int sem);


#endif