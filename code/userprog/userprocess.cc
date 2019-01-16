#include "thread.h"
#include "system.h"
#include "userprocess.h"
#include "synch.h"

typedef int pid_t;

void StartForkProcess(int arg) {
    currentThread->space->InitRegisters();	// set the initial register values
    currentThread->space->RestoreState();	// load page table register
    machine->Run();		// jump to the user progam
    ASSERT(FALSE);		// machine->Run never returns;
}

pid_t do_UserForkExec(char *buff) {
    IntStatus oldlevel = interrupt->SetLevel(IntOff);

    Thread* newThread = new Thread(buff);
    OpenFile *executable = fileSystem->Open (buff);
    AddrSpace *space;

    if (executable == NULL) {
	    printf ("Unable to open file %s\n", buff);
	    return -1;
    }

    space = new AddrSpace (executable);
    newThread->space = space;
    delete executable;		// close file

    newThread->Fork((VoidFunctionPtr)StartForkProcess, 0);

    currentThread->edit_semaphores->P();
    pid_t pid = currentThread->sem_children.size();
    currentThread->sem_children[pid] = new Semaphore(buff, 0);
    newThread->pid = pid;
    newThread->self_sem_for_parent = currentThread->sem_children[pid];
    newThread->edit_semaphores->V();
    interrupt->SetLevel(oldlevel);
    return pid;
}

void do_process_exit() {
    currentThread->edit_semaphores->P();
    for(std::map<pid_t,Semaphore*>::iterator it = currentThread->sem_children.begin(); it != currentThread->sem_children.end(); ++it) {
        currentThread->edit_semaphores->V();
        do_waitpid(it->first);
        currentThread->edit_semaphores->P();
    }
    currentThread->self_sem_for_parent->V();
    currentThread->edit_semaphores->V();
}

void do_waitpid(pid_t pid) {
    currentThread->edit_semaphores->P();
    if(currentThread->sem_children.count(pid)) {
        currentThread->sem_children[pid]->P();
        currentThread->sem_children[pid]->V();
    }
    currentThread->edit_semaphores->V();
}
