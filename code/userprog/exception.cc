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

#include <cstdio>
#include "copyright.h"
#include "system.h"
#include "syscall.h"

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

void
ExceptionHandler(ExceptionType which)
{
  int type = machine->ReadRegister(2);
  if (which == SyscallException) 
  {
    switch (type) 
    {
      case SC_Exit: 
      case SC_Halt: 
      {
        DEBUG('a', "Shutdown, initiated by user program.\n");
        interrupt->Halt();
        break;
      }
      case SC_GetChar: {
        machine->WriteRegister(2,synchconsole->SynchGetChar());
        break;
      }
      case SC_GetString: {
        int adr = machine->ReadRegister(4); 
        char* buffer = synchconsole->getBuffer();
        int taille = machine->ReadRegister(5);
        synchconsole->SynchGetString(buffer,taille);
        copyStringToMachine(adr,buffer,MAX_STRING_SIZE); 
        break;
      }
      case SC_PutChar: {
        char c= (char)machine->ReadRegister(4); //on recupere le char
        synchconsole->SynchPutChar(c);
        break;

      }
      case SC_PutString: {
        int adr;
        adr= machine->ReadRegister(4); 
        copyStringFromMachine(adr,synchconsole->getBuffer(),MAX_STRING_SIZE); 
        synchconsole->SynchPutString(synchconsole->getBuffer());
        break;
      }
      case SC_PutInt: {
        char buffer[MAX_STRING_SIZE];
        int val  = machine->ReadRegister(4);
        snprintf(buffer, MAX_STRING_SIZE, "%d", val);
        synchconsole->SynchPutString(buffer);
        break;
      } 
      case SC_GetInt: {
        int adr = machine->ReadRegister(4), val;
        char buffer[MAX_STRING_SIZE];
        synchconsole->SynchGetString(buffer, MAX_STRING_SIZE);
        sscanf(buffer, "%d", &val);
        copyStringToMachine(adr,(char*)&val,sizeof(int));
        break;
      }
      default: 
      {
        printf("Unexpected user mode exception %d %d\n", which, type);
        ASSERT(FALSE);
      }
    }
  UpdatePC();
  }
}
