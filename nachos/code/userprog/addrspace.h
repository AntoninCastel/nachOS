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
#include "frameprovider.h"
#include "bitmap.h"

/// increase this as necessary !

#define UserStackSize		4096

#define MAX_THREADS 50

#define NB_MAX_THREADS 50
#define NB_MAX_USER_SEMAPHORES 20

class Semaphore;

/**
 * \class AddrSpace addrspace.h
 */
class AddrSpace {
  public:  
  	//Sera traduit en string pour donner un nom aux futurs threads 
    int nomThread = 0 ;
    //Semaphore qui represente le nombre de threads total qui ont été lancés 
    //depuis le début dans cet address space
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

    /// Save address space-specific info on a context switch 
    void SaveState ();

    /// Restore address space-specific info on a context switch 
    void RestoreState (); 

    /// Getter pour la BitMap ThreadsPosition
    BitMap* getBitMap();
    
    int getSpMaxMain();

    void setSpMaxMain(int SpMain);

    void InitUserSemaphores();

    bool IsMainExiting();

    void SetExitingMain();

    Semaphore* WaitingMain;

    //Tableau de semaphores (une par Thread) pour que threadjoin puisse attendre 
    //la terminaison du thread qu'il attend
    //Tableau indexé par l'ID des threads
    Semaphore **TabThreads;
	
    //Tableau contenant les semaphores utilisées au niveau utilisateur
    Semaphore** UserSemaphores;
    int UserSemaphoresCounter;
    
    //Sémaphore pour la synchronisation des fonctions UserSemaphore
    Semaphore* UserSemaphoreSynch;

    //BitMap permettant de connaitre les sémaphores utilisateurs actifs 
    BitMap* UserActiveSemaphores;

	private:
	//SP Max du main, défini apès la création du premier thread.
    int SpMaxMain;
	
    //Booleen permettant de savoir si le main veut faire un Exit()
    bool ExitingMain;

    //Bitmap permettant de placer le SP des nouveaux threads dans la pile
	BitMap* ThreadsPosition;

    /// Assume linear page table translation for now !
    TranslationEntry * pageTable; 

    /// Number of pages in the virtual address space
    unsigned int numPages; 
};

#endif // ADDRSPACE_H
