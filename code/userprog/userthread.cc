#include "userthread.h"
#include "system.h"
#include "thread.h"

static void StartUserThread(int f);

int do_UserThreadCreate(int f, int arg) {
	param_t *p = new param_t;
	*p = {.fn = f, .param = arg};
	Thread *newthread = new Thread("new Thread");
	newthread->Fork(StartUserThread, (int)p);
	return -1; // non definitif
}

static void StartUserThread(int f) {
	//param_t* p = (param_t*)f;
	currentThread->space->InitRegisters();
	machine->Run();
}
