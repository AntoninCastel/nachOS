
#include "syscall.h" 

void fonction() {
	PutString("désolé j'avais\n");
	int i = 100000;
  	while (i != 0){i--;}
  	UserThreadExit();
}
void fonction2() {
	PutString("pas pensé\n");
	int i = 100000;
  	while (i != 0){i--;}
  	UserThreadExit();
}
void fonction3() {
	PutString("au git\n");
	int i = 100000;
  	while (i != 0){i--;}
  	UserThreadExit();
}
int main() {
	int a = UserThreadCreate(fonction, 0);	
  	UserThreadJoin(a);

	int b = UserThreadCreate(fonction2, 0);	
  	

	int c = UserThreadCreate(fonction3, 0);	
  	UserThreadJoin(c);
	UserThreadJoin(b);
  	
	return 0;
}
