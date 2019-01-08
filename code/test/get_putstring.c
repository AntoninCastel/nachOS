#include "syscall.h"

int main(){
	char buffer[500];
	GetString(buffer, 500);
	PutString(buffer);
	Halt();
}
