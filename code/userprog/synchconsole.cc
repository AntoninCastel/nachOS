#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile, int callArg)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console = new Console(readFile,writeFile, ReadAvail, WriteDone, callArg);
    buffer = new char[MAX_STRING_SIZE];
}

SynchConsole::~SynchConsole()
{
    delete console;
    delete writeDone;
    delete readAvail;
    delete[] buffer; 
}

void SynchConsole::SynchPutChar(const char ch)
{
	if (ch == EOF)
	    return;		// if EOF, quit
	console->PutChar (ch);	
	writeDone->P ();
}

char SynchConsole::SynchGetChar()
{
    readAvail->P ();	
    char ch = console->GetChar ();
    return ch;
}

void SynchConsole::SynchPutString(const char s[])
{	
    
    
}

void SynchConsole::SynchGetString(char *s, int n)
{
	int i;
    for(i=0; i<n ; i++){
    	s[i]=SynchGetChar();
    }
    s[i]='\0';
}


void copyStringFromMachine(int from, char *to, unsigned size){
    int c;
    unsigned i;
    for( i=0;i<size || c=='\0';i++) {
        machine->ReadMem(from,1,&c); 
        to[i]=(char)c; 
        from++;
    }
    to[i]='\0'; 
}
