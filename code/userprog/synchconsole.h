#ifndef SYNCHCONSOLE_H
#define SYNCHCONSOLE_H
#include "copyright.h"
#include "utility.h"
#include "console.h"

/** 
 * \brief Copie une chaine de caractère du monde MIPS vers le monde Linux.
 * \param from adresse virtuelle du début de la chaine à lire.
 * \param to adresse du début de buffer de destination
 * \param size nombre d'octets à lire.
 */
void copyStringFromMachine(int from, char *to, unsigned size);
void copyStringToMachine(int to, char *from, unsigned size);

class SynchConsole {
public:
    SynchConsole(char *readFile, char *writeFile, int callArg);
    // initialize the hardware console device
    ~SynchConsole();                    // clean up console emulation
    char* getBuffer();

    void SynchPutChar(const char ch);   // Unix putchar(3S)
    char SynchGetChar();                // Unix getchar(3S)
    void SynchPutString(const char *s); // Unix puts(3S)
    void SynchGetString(char *s, int n);       // Unix fgets(3S)

private:
    Console *console;
    char* buffer;
};
#endif // SYNCHCONSOLE_H
