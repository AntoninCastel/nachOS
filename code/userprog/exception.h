#include <cstdio>
#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "userthread.h"
#include "usersemaphore.h"

static void UpdatePC ();

void ExceptionHandler(ExceptionType which);

void Syscall_Exit();

void Syscall_Halt();

void Syscall_GetChar();
void Syscall_GetString();
void Syscall_PutChar();
void Syscall_PutString();
void Syscall_PutInt();
void Syscall_GetInt();

void Syscall_UserThreadCreate();
void Syscall_UserThreadExit();
void Syscall_UserThreadJoin();


void Syscall_Sem_Init();
void Syscall_Sem_P();
void Syscall_Sem_V();
void Syscall_Sem_GetValue();
void Syscall_Sem_Destroy();