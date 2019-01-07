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
	if(currentThread->space->nomThread==1){ //Lors de la création du premier Thread, on place le SP max du main.
		currentThread->space->SetSpMaxMain(machine->ReadRegister(29));
	}
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
	machine->WriteRegister(StackReg, currentThread->space->prochainSP);
	machine->Run();
}

void do_UserThreadExit(){
	//fprintf(stderr, "le thread %d termine apres un super appel systeme\n",currentThread->gettid() );
	//currentThread->space->PrintTabThread();
	//fprintf(stderr, "nombre de thread a 0 : %d\n",currentThread->space->CheckNbThreadEnCours() );
	if(currentThread->space->CheckNbThreadEnCours() == 1){
		currentThread->space->TabThreads[currentThread->gettid()]->V();
	}
	currentThread->Finish();
	
}

void do_UserThreadJoin(int IdThreadAttendu) {
	//fprintf(stderr, "Le main attend le thread %d\n",IdThreadAttendu );
	currentThread->space->TabThreads[IdThreadAttendu]->P();	
	currentThread->space->TabThreads[IdThreadAttendu]->V();	
	//fprintf(stderr, "Le thread %d s'est surement terminé\n",IdThreadAttendu );
}