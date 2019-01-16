#include "syscall.h"

#define N 100                         /* nombre de places dans le tampon */

semaphore mutex;  /* contrôle d'accès au tampon */ 
semaphore vide;     /* nb de places libres */
semaphore plein;   /* nb de places occupées */
 
int buffer[100];

typedef struct{
  int numThread;
}param;

void producteur ()
{
  int objet, i=0; 

  while (1) {
    objet=1;                          /* produire l'objet suivant */  
    Sem_P (vide) ;                    /* déc. nb places libres */ 
    Sem_P (mutex) ;                   /* entrée en section critique */ 
    PutString("**debut sc PRODUCTEUR**\n");
    while(i<N && buffer[i]){i++;}
    buffer[i]=objet;				   /* mettre l'objet dans le tampon */ 
    i=0;
    PutString("\t**fin sc PRODUCTEUR**\n");
    Sem_V(mutex) ;                     /* sortie de section critique */ 
    Sem_V(plein) ;                     /* inc. nb place occupées */ 
    
  }
} 

void consommateur (void* p) 
{
  int objet,i=0;
  param* par=(param*)p;
  while (1) {
    Sem_P(plein) ;                   	/* déc. nb emplacements occupés */ 
    Sem_P(mutex) ; 
    PutString("debut sc CONSOMMATEUR ");	/* entrée section critique */ 
    PutInt(par->numThread);
    PutChar('\n');
    while(i<N && !buffer[i]){i++;}       /* retire un objet du tampon */ 
    objet=buffer[i];
    buffer[i]=0;
    i=0;
    PutString("\tfin sc CONSOMMATEUR ");
    PutInt(par->numThread);
    PutChar('\n');
    Sem_V(mutex) ;                     /* sortie de la section critique */ 
    Sem_V(vide) ;                      /* inc. nb emplacements libres */ 
    objet=objet-1;        					/* utiliser l'objet */  
  }
}



int main(){
	int i=0;
	mutex=Sem_Init(1);
	vide=Sem_Init(N);
	plein=Sem_Init(0);

	while(i<N){
		buffer[i]=0;
		i++;
	}

  param p1,p2,p3;
  p1.numThread=1;
  p2.numThread=2;
  p3.numThread=3;
	//int a,b,c,d;
	UserThreadCreate(consommateur,&p1);
	UserThreadCreate(consommateur,&p2);
	UserThreadCreate(consommateur,&p3);
	UserThreadCreate(producteur,0);

	return 0;

}