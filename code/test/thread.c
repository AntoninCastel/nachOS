#include "syscall.h" 

void fonction() {
	PutString("Premier");
	int i = 100000;
  	while (i != 0){i--;}
  	UserThreadExit();
}

void fonction2() {
	PutString("Deuxieme");
	int i = 100000;
  	while (i != 0){i--;}
  	UserThreadExit();
}

void fonction3() {
	PutString("Troisieme");
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
