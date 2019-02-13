/* Création de plusieurs threads depuis le thread main, 
 * et join sur chaque thread juste après.
 */
#include "syscall.h" 

void fonction() {
	PutString("Premier");
	int i = 100000;
  	while (i > 0){i--;} // Ne termine pas, termine avec i > 0
  	UserThreadExit();
}

void fonction2() {
	PutString("Deuxieme");
	int i = 100000;
  	while (i > 0){i--;} // Ne termine pas, termine avec i > 0
  	UserThreadExit();
}

void fonction3() {
	PutString("Troisieme");
	int i = 100000;
  	while (i > 0){i--;} // Ne termine pas, termine avec i > 0
  	UserThreadExit();
}

int main() {
	int a = UserThreadCreate(fonction, 0);	
	int b = UserThreadCreate(fonction2, 0);	
	int c = UserThreadCreate(fonction3, 0);	
  	UserThreadJoin(a);
	UserThreadJoin(b);
  	UserThreadJoin(c);
	return 0;
}
