#include "syscall.h" 

int main() {
	Create("fichier_t",10);
	int fichier = Open("fichier_t");
	PutString("Premier id du fichier ouvert :\n");
	PutInt(fichier);
	PutChar('\n');

	int fichier2 = Open("fichier_t");
	PutString("Seconde id du fichier ouvert :\n");
	PutInt(fichier2);
	PutChar('\n');
	return 0;
}
