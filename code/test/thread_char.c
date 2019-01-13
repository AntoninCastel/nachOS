
#include "syscall.h" 

void fonction() {
    PutChar('a');
    PutChar('a');
    PutChar('a');
    PutChar('a');
    PutChar('a');
    PutChar('a');
    PutChar('a');
    PutChar('a');
    PutChar('a');
	int i = 1;
  	while (i != 0){i--;}
  	UserThreadExit();
}
void fonction2() {
    PutChar('b');
    PutChar('b');
    PutChar('b');
    PutChar('b');
    PutChar('b');
    PutChar('b');
    PutChar('b');
    PutChar('b');
    PutChar('b');
    PutChar('b');
    PutChar('b');
	int i = 100000;
  	while (i != 0){i--;}
  	UserThreadExit();
}
void fonction3() {
    PutChar('c');
    PutChar('c');
    PutChar('c');
    PutChar('c');
    PutChar('c');
    PutChar('c');
    PutChar('c');
    PutChar('c');
    PutChar('c');
    PutChar('c');
    PutChar('c');
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
