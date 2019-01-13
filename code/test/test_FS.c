#include "syscall.h" 

int main() {
	int a = Create("repet");
	PutInt(a);
	OpenFileId id = Open("repet");
	PutInt((int)id);
	return 0;
}
