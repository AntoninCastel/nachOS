#ifndef __USERTHREAD_H__
#define __USERTHREAD_H__
#include "synch.h"

class Semaphore;

//Semaphore garantssant qu'un seul thread à la fois ne peut se trouver dans UserThreadCreate
static Semaphore* ThreadCreation = new Semaphore ("lock thread create", 1);
static Semaphore* ThreadEnding = new Semaphore ("lock thread exit",1);



typedef struct {
	int fn;
	int param;
	int SP;
} param_t;

extern int do_UserThreadCreate(int f, int arg);
extern void do_UserThreadExit();
extern void do_UserThreadJoin(int arg);


#endif
