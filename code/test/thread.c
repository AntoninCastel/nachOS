
#include "syscall.h" 

void fonction() {
	PutString("MERDE");
	int i = 100000;
  	while (i != 0){i--;}
  	UserThreadExit();
}
void fonction2() {
	PutString("VICENT");
	int i = 100000;
  	while (i != 0){i--;}
  	UserThreadExit();
}
void fonction3() {
	PutString("VANIO");
	int i = 100000;
  	while (i != 0){i--;}
  	UserThreadExit();
}
int main() {
	int a = UserThreadCreate(fonction, 0);
	int b = UserThreadCreate(fonction2, 0);	
	int c = UserThreadCreate(fonction3, 0);	

  	int i = 100;
  	while (i != 0){i--;}
  	UserThreadJoin(c);
  	UserThreadJoin(a);
  	UserThreadJoin(b);
  	
	return 0;
}
