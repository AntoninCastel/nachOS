#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static Lock *LectureEnCours;
static Lock *EcritureEnCours;
static Lock *EcritureStringEnCours;


static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile, int callArg)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    LectureEnCours = new Lock("LectureEnCours");
    EcritureEnCours = new Lock("EcritureEnCours");
    EcritureStringEnCours = new Lock("EcritureStringEnCours");

    console = new Console(readFile,writeFile, ReadAvail, WriteDone, callArg);
}

SynchConsole::~SynchConsole()
{
    delete console;
    delete writeDone;
    delete readAvail;
    delete LectureEnCours;
    delete EcritureEnCours;
    delete EcritureStringEnCours;
}

void SynchConsole::SynchPutChar(const char ch)
{
    EcritureEnCours->Acquire ();
	if (ch == EOF)
	    return;		// if EOF, quit
	console->PutChar (ch);
	writeDone->P ();
    EcritureEnCours->Release ();
}

char SynchConsole::SynchGetChar()
{
    readAvail->P ();	
    char ch = console->GetChar ();
    return ch;
}

void SynchConsole::SynchPutString(const char s[])
{
    int taille = strlen(s);
    for (int i=0; i<taille && s[i]; i++){
        SynchPutChar(s[i]);
    }
}

void SynchConsole::SynchGetString(char *s, int n)
{
	int i;
    for(i=0; i<n; i++){
    	s[i]=SynchGetChar();
    	if(!s[i] || s[i] == '\n')
    		break;
    }
    s[i]='\0';
}


void copyStringFromMachine(int from, char *to, unsigned size){
    int c;
    unsigned i;
    for( i=0;i<size;i++) {
        machine->ReadMem(from,1,&c); 
        to[i]=(char)c; 
        from++;
        if(c == '\0')
            break;
    }
    to[i]='\0'; 
}


void copyStringToMachine(int to, char *from, unsigned size){
    int c;
    unsigned i;
    for( i=0;i<size && c!='\0';i++) {
        c = from[i];
        machine->WriteMem(to,1,c);
        to++;
    }
    machine->WriteMem(to,1,'\0');
}
