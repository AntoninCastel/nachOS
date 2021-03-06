/**
 * \file    syscall.h 
 * \brief Nachos system call interface.
 *
 * 	Nachos system call interface.  These are Nachos kernel operations
 * 	that can be invoked from user programs, by trapping to the kernel
 *	via the "syscall" instruction.
 *
 *	This file is included by user programs and by the Nachos kernel. 
 *
 * \copyright Copyright (c) 1992-1993 The Regents of the University of California.
 * All rights reserved.  See copyright.h for copyright notice and limitation 
 * of liability and disclaimer of warranty provisions.
 */

#ifndef SYSCALLS_H
#define SYSCALLS_H

#include "copyright.h"

/* system call codes -- used by the stubs to tell the kernel which system call
 * is being asked for
 */

#define SC_Halt		0
#define SC_Exit		1
#define SC_Exec		2
#define SC_Join		3
#define SC_Create	4
#define SC_Open		5
#define SC_Read		6
#define SC_Write	7
#define SC_Close	8
#define SC_Fork		9
#define SC_Yield	10
#define SC_PutChar	11
#define SC_PutString 12
#define SC_GetChar 13
#define SC_GetString 14
#define SC_PutInt 15
#define SC_GetInt 16
#define SC_UserThreadCreate 17
#define SC_UserThreadExit 18
#define SC_UserThreadJoin 19
#define SC_Sem_Init 20
#define SC_Sem_P 21
#define SC_Sem_V 22
#define SC_Sem_GetValue 23
#define SC_Sem_Destroy 24
#define SC_ForkExec 25
#define SC_waitpid 26
#define SC_Proc_Exit 27


#ifdef IN_USER_MODE

// LB: This part is read only on compiling the test/*.c files.
// It is *not* read on compiling test/start.S


/* The system call interface.  These are the operations the Nachos
 * kernel needs to support, to be able to run user programs.
 *
 * Each of these is invoked by a user program by simply calling the 
 * procedure; an assembly language stub stuffs the system call code
 * into a register, and traps to the kernel.  The kernel procedures
 * are then invoked in the Nachos kernel, after appropriate error checking, 
 * from the system call entry point in exception.cc.
 */

typedef int pid_t;
typedef int semaphore_t;

/**
 * \brief Stops Nachos, and print out performance stats
 */
void Halt () __attribute__((noreturn));


/* Address space control operations: Exit, Exec, and Join */

/// This user program is done (status = 0 means exited normally).
void Exit (int status) __attribute__((noreturn));

/// A unique identifier for an executing user program (address space)
typedef int SpaceId;

/**
 * Run the executable, stored in the Nachos file "name", and return the 
 * address space identifier
 */
SpaceId Exec (char *name);

/**
 * \brief Only return once the the user program "id" has finished.  
 * \return Returns the exit status.
 */
int Join (SpaceId id);


/**
 * File system operations: Create, Open, Read, Write, Close
 * These functions are patterned after UNIX -- files represent
 * both files *and* hardware I/O devices.
 *
 * If this assignment is done before doing the file system assignment,
 * note that the Nachos file system has a stub implementation, which
 * will work for the purposes of testing out these routines.
 */

/// A unique identifier for an open Nachos file.
typedef int OpenFileId;

/* when an address space starts up, it has two open files, representing 
 * keyboard input and display output (in UNIX terms, stdin and stdout).
 * Read and Write can be used directly on these, without first opening
 * the console device.
 */

#define ConsoleInput	0
#define ConsoleOutput	1

/// Create a Nachos file, with "name"
int Create (char *name, int size);

/**
 * Open the Nachos file "name", and return an "OpenFileId" that can 
 * be used to read and write to the file.
 */
OpenFileId Open (char *name);

/// Write "size" bytes from "buffer" to the open file.
int Write (char *buffer, int size, OpenFileId id);

/** 
 * Read "size" bytes from the open file into "buffer".  
 * Return the number of bytes actually read -- if the open file isn't
 * long enough, or if it is an I/O device, and there aren't enough 
 * characters to read, return whatever is available (for I/O devices, 
 * you should always wait until you can return at least one character).
 */
int Read (char *buffer, int size, OpenFileId id);

/// Close the file, we're done reading and writing to it.
void Close (OpenFileId id);



/* User-level thread operations: Fork and Yield.  To allow multiple
 * threads to run within a user program. 
 */

/**
 * \param func Fucntion to fork
 * \brief Fork a thread to run a procedure ("func") in the *same* address space 
 * as the current thread.
 */
void Fork (void (*func) ());

/**
 * Yield the CPU to another runnable thread, whether in this address space 
 * or not. 
 */
void Yield ();


/**
 *  Takes as an argument a character c in user mode, and then sets
 *  SyscallException interrupt. This causes a switch to kernel mode and the
 *  execution of the standard handle.
 */
void PutChar(char c);


/**
 *  Takes as an argument a string s in user mode, and then sets
 *  SyscallException interrupt. This causes a switch to kernel mode and the
 *  execution of the standard handle.
 */
void PutString(char *s);

/**
 *  
 *  
 *  
 */
char GetChar();

/**
 *  
 *  
 *  
 */

void GetString(char *s, int n);
void PutInt(int n);
void GetInt(int *n);

int UserThreadCreate(void f(void *arg), void *arg);
void UserThreadExit();
void UserThreadJoin(int tid);

semaphore_t Sem_Init(int nbJetons);
int Sem_P(semaphore_t s);
int Sem_V(semaphore_t s);
int Sem_GetValue(semaphore_t s);
int Sem_Destroy(semaphore_t s);

pid_t ForkExec(char* file);
void waitpid(pid_t pid);
void Proc_Exit();

#endif // IN_USER_MODE

#endif /* SYSCALL_H */
