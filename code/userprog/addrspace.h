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
#include <string>

#include "copyright.h"
#include "filesys.h"
#include "list.h"
#include "bitmap.h"

/// increase this as necessary !
#define UserStackSize		4096
#define MAX_THREADS 50
#define PAGES_PER_THREAD 3
#define PAGE_SIZE 128

class Semaphore;

/**
 * \class AddrSpace addrspace.h
 */
class AddrSpace {
  public:  
  	//Sera traduit en string pour donner un nom aux futurs threads 
    int nomThread = 0 ;
    int prochainSP;
    //Semaphore qui represente le nombre de threads total qui ont été lancés 
    //depuis le début
    Semaphore *threads_sharing_addrspace;    

    //Alloue et initialise le tableau de semaphores.
    //Les semaphores sont initialisées à 1 jeton.
    void InitTabThread();

    //Prend un jeton sur la semaphore d'index ID
    void ThreadExist(int id);
    
    //Remet un jeton sur la semaphore d'index ID
    void ThreadNoLongerExist(int id);

    //Affiche les valeurs des des differentes semaphores 
    void PrintTabThread();

    //Retourne le nombre de semaphores à 0 (Threads en cours d'execution)
    int CheckNbThreadEnCours();

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
    int ThreadsCounter();

    int GetSpMaxMain();

    void SetSpMaxMain(int valSP);

    int numBloc();

    int NextThreadSP();

    /// Save address space-specific info on a context switch 
    void SaveState ();

    /// Restore address space-specific info on a context switch 
    void RestoreState (); 

    Semaphore **TabThreads;
    BitMap* ThreadsPosition;


    //Tableau de semaphores (une par Thread) pour que threadjoin puisse attendre 
    //la terminaison du thread qu'il attend
    //Tableau indexé par l'ID des threads

  private:      

    /// Assume linear page table translation for now !
    
    int SpMaxMain;
    TranslationEntry * pageTable; 

    /// Number of pages in the virtual address space
    unsigned int numPages; 
};

#endif // ADDRSPACE_H
