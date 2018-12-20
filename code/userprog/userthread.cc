#include "userthread.h"
#include "system.h"
#include "thread.h"
#include "synch.h"
#include <string>

static void StartUserThread(int f);

int do_UserThreadCreate(int f, int arg) {
    IntStatus oldLevel = interrupt->SetLevel (IntOff);

	param_t *p = new param_t;
	*p = {.fn = f, .param = arg, .SP = machine->ReadRegister(StackReg)};
	char* Nom = new char[10]; 
	sprintf(Nom, "%d\n",currentThread->space->nomThread );
	Thread *newthread = new Thread(Nom);
	currentThread->space->nomThread++;
	newthread->Fork(StartUserThread, (int)p);
	currentThread->space->threads_sharing_addrspace->V();

    (void) interrupt->SetLevel (oldLevel);

	return newthread->gettid();
}

static void StartUserThread(int f) {

	param_t* p = (param_t*)f;
	for(int i = 0; i < NumTotalRegs; i++){
		machine->WriteRegister(i, 0);
	}
	machine->WriteRegister(PCReg, p->fn);
	machine->WriteRegister(NextPCReg, p->fn+4);
	int prochainSP = ((currentThread->space->threads_sharing_addrspace->getValue()+1)* (3*PageSize))+(3*PageSize) ;
	machine->WriteRegister(StackReg, /*p->SP - 3*PageSize*/ prochainSP);
	machine->Run();
}

void do_UserThreadExit(){
	IntStatus oldLevel = interrupt->SetLevel (IntOff);
	fprintf(stderr, "le thread %d termine apres un super appel systeme\n",currentThread->gettid() );
	//currentThread->space->Ended->SortedInsert((void *)currentThread->gettid(),currentThread->gettid());
	if(!currentThread->space->BlockedMain->IsEmpty()){
		//fprintf(stderr, "Je remet le main en runnable\n" );
		scheduler->ReadyToRun ((Thread *)currentThread->space->BlockedMain->Remove());
	}
	currentThread->Finish();
	(void) interrupt->SetLevel (oldLevel);
}

void do_UserThreadJoin(int IdThreadAttendu) {
	IntStatus oldLevel = interrupt->SetLevel (IntOff);
	Thread *nextThread;
	//while(scheduler->ReadyListContains((void*)IdThreadAttendu) == 1){
	while(currentThread->space->TestId(IdThreadAttendu)){
		currentThread->space->BlockedMain->Append((void*)currentThread);
    	nextThread = scheduler->FindNextToRun ();
    	if (nextThread != NULL){
	  		scheduler->Run (nextThread);
      	}
	}
	fprintf(stderr, "Le thread %d s'est surement terminé\n",IdThreadAttendu );
	(void) interrupt->SetLevel (oldLevel);
}