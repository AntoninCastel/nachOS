// exception.cc 
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.  
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "userthread.h"
#include "userfile.h"
#include "userprocess.h"
#include "exception.h"
//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
	int pc = machine->ReadRegister (PCReg);
	machine->WriteRegister (PrevPCReg, pc);
	pc = machine->ReadRegister (NextPCReg);
	machine->WriteRegister (PCReg, pc);
	pc += 4;
	machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions 
//      are in machine.h.
//----------------------------------------------------------------------

void ExceptionHandler(ExceptionType which) { 
  int type = machine->ReadRegister(2);
  if (which == SyscallException) {
	switch (type) {
	case SC_Exit: 
		Syscall_Exit();
		break;
	case SC_Halt: 
		Syscall_Halt();
		break;
	case SC_GetChar:
		Syscall_GetChar();
		break;
	case SC_GetString:
		Syscall_GetString();
		break;
	case SC_PutChar:
		Syscall_PutChar();
		break;
	case SC_PutString:
		Syscall_PutString();
		break;
	case SC_PutInt:
		Syscall_PutInt();
		break;
	case SC_GetInt:
		Syscall_GetInt();
		break;
	case SC_UserThreadCreate:
		Syscall_UserThreadCreate();
		break;
	case SC_UserThreadExit:
		Syscall_UserThreadExit();
		break;
	case SC_UserThreadJoin:
		Syscall_UserThreadJoin();
		break;
	  case SC_Sem_Init:
		Syscall_Sem_Init();
		break;
	  case SC_Sem_P:
		Syscall_Sem_P();
		break;
	  case SC_Sem_V:
		Syscall_Sem_V();
		break;
	  case SC_Sem_GetValue:
		Syscall_Sem_GetValue();
		break;
	  case SC_Sem_Destroy:
		Syscall_Sem_Destroy();
		break;
	case SC_ForkExec:
		Syscall_ForkExec();
		break;
	 case SC_Create:
		Syscall_Create();
		break;  
	 case SC_Open:
		Syscall_Open();
		break; 		     
	default: 
		printf("Unexpected user mode exception %d %d\n", which, type);
		ASSERT(FALSE);
	}
  UpdatePC();
  } 
}

void Syscall_Exit(){
    machine->WriteRegister(2,machine->ReadRegister(4));
    if(currentThread->isPrimaryThread) {
        interrupt->Halt();
    } else {
        currentThread->Finish();
    }
}

void Syscall_Halt(){
  DEBUG('a', "Shutdown, initiated by user program.\n");
  interrupt->Halt(); 
}

void Syscall_GetChar(){
  machine->WriteRegister(2,synchconsole->SynchGetChar());
}

void Syscall_GetString(){
  int adr = machine->ReadRegister(4); 
  char buffer[MAX_STRING_SIZE];
  int taille = machine->ReadRegister(5) > MAX_STRING_SIZE ? MAX_STRING_SIZE : machine->ReadRegister(5);
  synchconsole->SynchGetString(buffer,taille);
  copyStringToMachine(adr,buffer,MAX_STRING_SIZE); 
}

void Syscall_PutChar(){
  char c= (char)machine->ReadRegister(4); //on recupere le char
  synchconsole->SynchPutChar(c);
}

void Syscall_PutString(){
  int adr = machine->ReadRegister(4);
  char buffer[MAX_STRING_SIZE];
  copyStringFromMachine(adr,buffer,MAX_STRING_SIZE);
  synchconsole->SynchPutString(buffer);
  
}

void Syscall_PutInt(){
  char buffer[MAX_STRING_SIZE];
  int val  = machine->ReadRegister(4);
  snprintf(buffer, MAX_STRING_SIZE, "%d", val);
  synchconsole->SynchPutString(buffer);
}

void Syscall_GetInt(){
  int adr = machine->ReadRegister(4), val;
  char buffer[MAX_STRING_SIZE];
  synchconsole->SynchGetString(buffer, MAX_STRING_SIZE);
  sscanf(buffer, "%d", &val);
  copyStringToMachine(adr,(char*)&val,sizeof(int));
}

void Syscall_UserThreadCreate(){
	int fn_adr = machine->ReadRegister(4);
	int arg_adr = machine->ReadRegister(5);
	int ret = do_UserThreadCreate(fn_adr, arg_adr);
	machine->WriteRegister(2, ret);
}

void Syscall_UserThreadExit(){
	do_UserThreadExit();
}

void Syscall_UserThreadJoin() {
	int param = machine->ReadRegister(4);
	do_UserThreadJoin(param);
}

void Syscall_Sem_Init(){
	 int param = machine->ReadRegister(4);
	machine->WriteRegister(2, do_Sem_Init(param));
}

void Syscall_Sem_P(){
  int param = machine->ReadRegister(4);
  machine->WriteRegister(2,do_Sem_P(param));
}

void Syscall_Sem_V(){
  int param=machine->ReadRegister(4);
  machine->WriteRegister(2,do_Sem_V(param));
}
void Syscall_Sem_GetValue(){
  int param=machine->ReadRegister(4);
  machine->WriteRegister(2,do_Sem_GetValue(param));
}

void Syscall_Sem_Destroy(){
  int param=machine->ReadRegister(4);
  machine->WriteRegister(2,do_Sem_Destroy(param));
}
void Syscall_ForkExec() {
    int adr = machine->ReadRegister(4);
    char buffer[MAX_STRING_SIZE];
    copyStringFromMachine(adr, buffer, MAX_STRING_SIZE);
    do_UserForkExec(buffer);
}

void Syscall_Create() {
	int adr = machine->ReadRegister(4);
	int size  = machine->ReadRegister(5);
	char buffer[MAX_STRING_SIZE];
	copyStringFromMachine(adr, buffer, MAX_STRING_SIZE);
	machine->WriteRegister(2,do_UserCreate(buffer,size));
}
void Syscall_Open() {
	int adr = machine->ReadRegister(4);
	char name[MAX_STRING_SIZE];
	copyStringFromMachine(adr, name, MAX_STRING_SIZE);
	machine->WriteRegister(2,do_UserOpen(name));
}
