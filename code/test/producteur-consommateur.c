#include "syscall.h"

#define N 100                         /* nombre de places dans le tampon */

semaphore mutex;  /* contrôle d'accès au tampon */ 
semaphore vide;     /* nb de places libres */
semaphore plein;   /* nb de places occupées */
 
int buffer[100];


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
    PutString("\t**fin sc PRODUCTEUR**\n");
    Sem_V(mutex) ;                     /* sortie de section critique */ 
    Sem_V(plein) ;                     /* inc. nb place occupées */ 
  }
} 

void consommateur () 
{
  int objet,i=0; 

  while (1) {
    Sem_P(plein) ;                   	/* déc. nb emplacements occupés */ 
    Sem_P(mutex) ; 
    PutString("debut sc CONSOMMATEUR\n");	/* entrée section critique */ 
    while(i<N && buffer[i]){i++;}       /* retire un objet du tampon */ 
    objet=buffer[i];
    buffer[i]=0;
    PutString("\tfin sc CONSOMMATEUR\n");
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
	int a,b,c,d;
	a=UserThreadCreate(consommateur,0);
	b=UserThreadCreate(consommateur,0);
	c=UserThreadCreate(consommateur,0);
	d=UserThreadCreate(producteur,0);
	UserThreadJoin(a);
	UserThreadJoin(b);
	UserThreadJoin(c);
	UserThreadJoin(d);
	return 0;

}