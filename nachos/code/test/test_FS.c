#include "syscall.h" 

int main() {
	Create("repet",8);
	int to = Open("repet");
	Write("BONJOUR",7,to);
	Close(to);
	return 0;
}
