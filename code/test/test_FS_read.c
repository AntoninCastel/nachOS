#include "syscall.h" 

int main() {
	int too = Open("repet");
	char buffer[12]; 
	Read(buffer, 12, too);
	PutString(buffer);PutChar('\n');

	int too2 = Open("repet");
	char buffer2[12]; 
	Read(buffer2, 12, too2);
	PutString(buffer2);PutChar('\n');
	return 0;
}