#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static Semaphore *LectureEnCours;
static Semaphore *EcritureEnCours;

static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile, int callArg)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    LectureEnCours = new Semaphore("LectureEnCours", 1);
    EcritureEnCours = new Semaphore("EcritureEnCours", 1);
    console = new Console(readFile,writeFile, ReadAvail, WriteDone, callArg);
}

SynchConsole::~SynchConsole()
{
    delete console;
    delete writeDone;
    delete readAvail;
    delete LectureEnCours;
    delete EcritureEnCours;
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
    EcritureEnCours->P ();
    int taille = strlen(s);
    for (int i=0; i<taille && s[i]; i++){
        SynchPutChar(s[i]);
    }
    EcritureEnCours->V ();
}

void SynchConsole::SynchGetString(char *s, int n)
{
	int i;
	LectureEnCours->P ();
    for(i=0; i<n; i++){
    	s[i]=SynchGetChar();
    	if(!s[i])
    		break;
    }
    s[i]='\0';
	LectureEnCours->V ();

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
