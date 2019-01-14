#include "syscall.h" 

int main() {
	Create("repet",8);
	int to = Open("repet");
	Write("BONJOUR",7,to);
	Close(to);
	
	int too = Open("repet");
	char buffer[8]; 
	Read(buffer, 7, too);
	PutString(buffer);
	return 0;
}
