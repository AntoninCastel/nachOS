#include "userfile.h"
#include "system.h"
#include "filesys.h"
#include "utility.h"

int do_UserCreate(char* name, int size){
	/*bool result = fileSystem->Create(name,size);
	if(result)
		return 1;
	else */
		return 0;
}

int do_UserOpen(char* name){
	int index = -1;
	/*for(int i = 0;i < NbOpenFile+2;i++){
		if(!strcmp(fileSystem->openFileName[i],name)){
			return i;
		}
	}

	do{
		index = fileSystem->openFileMap->Find();
	}while(index == 0 || index == 1);

	if(index >= 0){
		OpenFile * newFile = fileSystem->Open(name);
		strcpy(fileSystem->openFileName[index],name);
		fileSystem->openFileTab[index] = newFile;
	}*/
	return index;
}

