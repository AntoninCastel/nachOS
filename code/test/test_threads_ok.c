#include "syscall.h" 

void fonction() {
	PutString("Premier");
  	UserThreadExit();
}

void fonction2() {
	PutString("Deuxieme");
  	UserThreadExit();
}

void fonction3() {
 	PutString("Troisieme\n");
  	UserThreadExit();
}

int main() {
	int a = UserThreadCreate(fonction, 0);	
	int b = UserThreadCreate(fonction2, 0);	
	int c = UserThreadCreate(fonction3, 0);	

	int i = 100;
  	while (i != 0){i--;}	

  	UserThreadJoin(a);
	UserThreadJoin(b);
  	UserThreadJoin(c);
	return 0;
}
