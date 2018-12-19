
#include "syscall.h" 

void fonction() {
	PutString("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  	UserThreadExit();
}

int main() {
	UserThreadCreate(fonction, 0);
	UserThreadCreate(fonction2, 0);
	UserThreadCreate(fonction, 0);

  	int i = 1000000;
  	
  	while (i != 0){i--;}
	return 0;
}
