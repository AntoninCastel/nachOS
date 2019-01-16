#include "userthread.h"
#include "system.h"
#include "thread.h"
#include <string>

static void StartUserThread(int f);
Semaphore* ThreadCreation = new Semaphore ("lock thread create", 1);
Semaphore* ThreadEnding = new Semaphore ("lock thread exit",1);

int do_UserThreadCreate(int f, int arg) {
    ThreadCreation->P();
    //IntStatus oldLevel = interrupt->SetLevel (IntOff);

	param_t *p = new param_t;
	*p = {.fn = f, .param = arg, .SP = machine->ReadRegister(StackReg)};
	char* Nom = new char[10]; 
	sprintf(Nom, "t%d",currentThread->space->nomThread );
	Thread *newthread = new Thread(Nom);
	if(currentThread->space->nomThread==0){ //Lors de la création du premier Thread, on place le SP max du main.
		currentThread->space->setSpMaxMain(machine->ReadRegister(29));
	}
	currentThread->space->nomThread++;
	newthread->Fork(StartUserThread, (int)p);
	currentThread->space->threads_sharing_addrspace->V();
    //(void) interrupt->SetLevel (oldLevel);
    ThreadCreation->V();
	return newthread->gettid();
}

static void StartUserThread(int f) {

	param_t* p = (param_t*)f;
	for(int i = 0; i < NumTotalRegs; i++){
		machine->WriteRegister(i, 0);
	}
	machine->WriteRegister(PCReg, p->fn);
	machine->WriteRegister(NextPCReg, p->fn+4);
	currentThread->position=currentThread->space ->getBitMap()-> Find();; //met à jour le numéro de bloc du thread (position)
	int ThreadSP = (currentThread->space->getSpMaxMain()-currentThread->position * (PAGES_PER_THREADS*PageSize) );
	machine->WriteRegister(StackReg,  ThreadSP);
	machine->Run();
}

void do_UserThreadExit(){
	//fprintf(stderr, "le thread %d termine apres un super appel systeme\n",currentThread->gettid() );
	//currentThread->space->PrintTabThread();
	//fprintf(stderr, "nombre de thread a 0 : %d\n",currentThread->space->CheckNbThreadEnCours() );
	ThreadEnding->P();
	if(currentThread->space->CheckNbThreadEnCours() == 1){
		currentThread->space->TabThreads[currentThread->gettid()]->V();
		if (currentThread->space->IsMainExiting()){
			currentThread->space->WaitingMain->V();
		}
	}
    currentThread->space->getBitMap()->Clear(currentThread->position);
	ThreadEnding->V();
	currentThread->Finish();
}

void do_UserThreadJoin(int IdThreadAttendu) {
	//fprintf(stderr, "Le main attend le thread %d\n",IdThreadAttendu );
    if(IdThreadAttendu < NB_MAX_THREADS) {
        currentThread->space->TabThreads[IdThreadAttendu]->P();	
        currentThread->space->TabThreads[IdThreadAttendu]->V();	
	    //fprintf(stderr, "Le thread %d s'est surement terminé\n",IdThreadAttendu );
    }
}

