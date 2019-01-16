#include "thread.h"
#include "system.h"
#include "userprocess.h"
#include "synch.h"

void StartForkProcess(int arg) {
    currentThread->space->InitRegisters();	// set the initial register values
    currentThread->space->RestoreState();	// load page table register
    machine->Run();		// jump to the user progam
    ASSERT(FALSE);		// machine->Run never returns;
}

void do_UserForkExec(char *buff) {
    IntStatus oldlevel = interrupt->SetLevel(IntOff);

    Thread* newThread = new Thread(buff);
    OpenFile *executable = fileSystem->Open (buff);
    AddrSpace *space;

    if (executable == NULL) {
	    printf ("Unable to open file %s\n", buff);
	    return;
    }

    space = new AddrSpace (executable);
    newThread->space = space;
    delete executable;		// close file

    interrupt->SetLevel(oldlevel);
    newThread->Fork((VoidFunctionPtr)StartForkProcess, 0);
}
