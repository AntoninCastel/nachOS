
#include "syscall.h" 

void fonction() {
	PutString("J'AIMERAIS\n");
	int i = 1;
  	while (i != 0){i--;}
  	UserThreadExit();
}
void fonction2() {
	PutString("RESOUDRE\n");
	int i = 100000;
  	while (i != 0){i--;}
  	UserThreadExit();
}
void fonction3() {
	PutString("CE BUG\n");
	int i = 100000;
  	while (i != 0){i--;}
  	UserThreadExit();
}
int main() {
	int a = UserThreadCreate(fonction, 0);	
  	UserThreadJoin(a);
	int b = UserThreadCreate(fonction2, 0);	
	UserThreadJoin(b);
	/*int c = UserThreadCreate(fonction3, 0);	
  	UserThreadJoin(c);*/
  	
	return 0;
}
