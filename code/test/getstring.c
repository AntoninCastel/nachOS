#include "syscall.h"

int main(){
	char buffer[6];
	GetString(buffer, 6);
	PutString(buffer);
	Halt();
}