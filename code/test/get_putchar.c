#include "syscall.h"

int main(){
	PutChar(GetChar());
	Halt();
}
