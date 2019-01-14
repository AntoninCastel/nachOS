#include "userfile.h"
#include "openfile.h"
#include "system.h"
#include "filesys.h"
#include "utility.h"

int do_UserCreate(char* name, int size){
	bool result = fileSystem->Create(name,size);
	if(result)
		return 1;
	else 
		return 0;
}

int do_UserOpen(char* name){
	int index = -1;
	for(int i = 0;i < NbOpenFile+2;i++){
		if(!strcmp(fileSystem->openFileName[i],name)){
			return i;
		}
	}

	do{
		index = fileSystem->openFileMap->Find();
	}while(index == 0 || index == 1);

	if(index >= 0){
		strcpy(fileSystem->openFileName[index],name);
		fileSystem->openFileTab[index] = fileSystem->Open(name);
	}
	return index;
}

int do_UserWrite(int fileid, int size, char *from){
	OpenFile *currentfile; 
	currentfile = fileSystem->openFileTab[fileid];
	return currentfile->Write(from,size);
}

int do_UserRead(int fileid, int size, char *to){ 
	OpenFile *currentfile = fileSystem->openFileTab[fileid];
	return currentfile->Read(to,size);
}

void do_UserClose(int fileid){ 
	strcpy(fileSystem->openFileName[fileid],"");
	fileSystem->openFileMap->Clear(fileid);
	fileSystem->openFileTab[fileid] = NULL;
}