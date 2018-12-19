
#include "syscall.h" 

void fonction() {
  	PutString("MERDE\n");
  	UserThreadExit();
}

int main() {
	int a = UserThreadCreate(fonction, 0);
	int i = 1;
	while(i!=0){i--;}
  	//UserThreadJoin(a);
	return a;
}
