#include "userthread.h"
#include "system.h"
#include "thread.h"

static void StartUserThread(int f);

int do_UserThreadCreate(int f, int arg) {
	param_t *p = new param_t;
	*p = {.fn = f, .param = arg, .SP = machine->ReadRegister(StackReg)};
	Thread *newthread = new Thread("new Thread");
	newthread->Fork(StartUserThread, (int)p);
	return 0; // non definitif
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
	currentThread->Finish();
}

void do_UserThreadJoin() {

}
