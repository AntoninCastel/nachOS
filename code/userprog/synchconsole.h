#ifndef SYNCHCONSOLE_H
#define SYNCHCONSOLE_H
#include "copyright.h"
#include "utility.h"
#include "console.h"

class SynchConsole {
public:
    SynchConsole(char *readFile, char *writeFile, int callArg);
    // initialize the hardware console device
    ~SynchConsole();                    // clean up console emulation
    void SynchPutChar(const char ch);   // Unix putchar(3S)
    char SynchGetChar();                // Unix getchar(3S)
    void SynchPutString(const char *s); // Unix puts(3S)
    void SynchGetString(char *s, int n);       // Unix fgets(3S)
private:
    Console *console;
    char* buffer;
};
#endif // SYNCHCONSOLE_H
