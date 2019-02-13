#include "syscall.h" 

int main() {
	Create("repet",12);
	int to = Open("repet");
	Write("Hello World",12,to);
	Close(to);
	return 0;
}
