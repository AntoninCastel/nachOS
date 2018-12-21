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
	sprintf(Nom, "t%d",currentThread->space->nomThread );
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
	int prochainSP = ((currentThread->space->threads_sharing_addrspace->getValue()+1)* (2*PageSize))+(2*PageSize) ;
	machine->WriteRegister(StackReg, /*p->SP - 3*PageSize*/ prochainSP);
	machine->Run();
}

void do_UserThreadExit(){
	fprintf(stderr, "le thread %d termine apres un super appel systeme\n",currentThread->gettid() );
	//currentThread->space->Ended->SortedInsert((void *)currentThread->gettid(),currentThread->gettid());
	if(!currentThread->space->BlockedMain->IsEmpty()){
		Thread *nextThread;
		nextThread = (Thread *)currentThread->space->BlockedMain->Remove();
		fprintf(stderr, "Je remet le %s en runnable\n", nextThread->getName());
		scheduler->ReadyToRun (nextThread);
	}
	currentThread->Finish();
}

void do_UserThreadJoin(int IdThreadAttendu) {
	//IntStatus oldLevel = interrupt->SetLevel (IntOff);
	//Thread *nextThread;
	while(currentThread->space->TestId(IdThreadAttendu) == 1){
    	/*nextThread = scheduler->FindNextToRun ();
     	interrupt->DumpState();
   	   	//interrupt->OneTick();
    	if (nextThread != NULL){
    		currentThread->space->BlockedMain->Append((void*)currentThread);
    		currentThread->setStatus (BLOCKED);
    		IntStatus oldLevel = interrupt->SetLevel (IntOff);
	  		scheduler->Run (nextThread);    
	  		(void) interrupt->SetLevel (oldLevel);
      	}*/
      	currentThread->space->BlockedMain->Append((void*)currentThread);
		IntStatus oldLevel = interrupt->SetLevel (IntOff);
      	currentThread->Sleep();
      	(void) interrupt->SetLevel (oldLevel);
	}
	fprintf(stderr, "Le thread %d s'est surement terminé\n",IdThreadAttendu );
	//(void) interrupt->SetLevel (oldLevel);
}