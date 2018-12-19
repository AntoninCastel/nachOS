#include "userthread.h"
#include "system.h"
#include "thread.h"
#include "synch.h"

static void StartUserThread(int f);

int do_UserThreadCreate(int f, int arg) {
	param_t *p = new param_t;
	*p = {.fn = f, .param = arg, .SP = machine->ReadRegister(StackReg)};
	Thread *newthread = new Thread("new Thread");
	newthread->Fork(StartUserThread, (int)p);
	currentThread->space->threads_sharing_addrspace->V();
	return newthread->gettid(); // non definitif
}

static void StartUserThread(int f) {
	param_t* p = (param_t*)f;
	for(int i = 0; i < NumTotalRegs; i++){
		machine->WriteRegister(i, 0);
	}
	machine->WriteRegister(PCReg, p->fn);
	machine->WriteRegister(NextPCReg, p->fn+4);
	machine->WriteRegister(StackReg, p->SP - 3*PageSize );
	machine->Run();
}
void do_UserThreadExit(){
	currentThread->space->Ended->SortedInsert((void *)currentThread->gettid(),currentThread->gettid());
	currentThread->Finish();
}

void do_UserThreadJoin(int arg) {
	while(!currentThread->space->Ended->Contains(arg)){
		//scheduler->Print();
		currentThread->Yield();
	}
	fprintf(stderr, "Le thread %d s'est surement terminé\n",arg );
}