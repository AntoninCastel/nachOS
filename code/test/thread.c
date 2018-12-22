
#include "syscall.h" 

void fonction() {
	int i = 1000;
  	while (i != 0){i--;}
	PutString("J'AIMERAIS\n");
  	UserThreadExit();
}
void fonction2() {
	int i = 1000;
  	while (i != 0){i--;}
	PutString("RESOUDRE\n");
  	UserThreadExit();
}
void fonction3() {
	int i = 1000;
  	while (i != 0){i--;}
 	PutString("CE BUG\n");
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
