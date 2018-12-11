/**
 * \file addrspace.h
 * \brief Data structures to keep track of executing user programs 
 * (address spaces).
 *
 * Data structures to keep track of executing user programs 
 * (address spaces).
 * For now, we don't keep any information about address spaces.
 * The user level CPU state is saved and restored in the thread
 * executing the user program (see thread.h).
 * 
 * \copyright Copyright (c) 1992-1993 The Regents of the University of California. 
 * All rights reserved.  See copyright.h for copyright notice and limitation 
 * of liability and disclaimer of warranty provisions.
 */

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"

/// increase this as necessary !
#define UserStackSize		1024

/**
 * \class AddrSpace addrspace.h
 */
class AddrSpace
{
  public:
    /**
    * \brief Create an address space, initializing it with the program 
    * stored in the file "executable"
    */
    AddrSpace (OpenFile * executable); 

    /// De-allocate an address space
    ~AddrSpace ();

    /**
     * \brief Initialize user-level CPU registers,
     * before jumping to user code
     */
    void InitRegisters ();

    /// Save address space-specific info on a context switch 
    void SaveState ();
    
    /// Restore address space-specific info on a context switch 
    void RestoreState (); 

  private:
    /// Assume linear page table translation for now !
    TranslationEntry * pageTable; 

    /// Number of pages in the virtual address space
    unsigned int numPages; 
};

#endif // ADDRSPACE_H
