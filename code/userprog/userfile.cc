#include "userfile.h"
#include "openfile.h"
#include "system.h"
#include "filesys.h"
#include "utility.h"
#include "filehdr.h"

int do_UserCreate(char* name, int size){
	if(!strcmp(name,"") || !strcmp(name,".")|| !strcmp(name,"..")|| !strcmp(name,"/")){
		fprintf(stderr, "Impossible de créer un fichier appelé %s\n",name );
		return 0;
	}
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
	}else{
		//verification si il y a de la place dans la table des fichiers ouverts
		fprintf(stderr, "Impossible, seuls 10 fichiers ouverts simultanement pour les programmes utilisateurs\n");
	}
	//verification si le fichier a ete trouve
	if(fileSystem->openFileTab[index] == NULL){
		strcpy(fileSystem->openFileName[index],"");
		fileSystem->openFileMap->Clear(index);	
		fprintf(stderr, "Fichier introuvable dans le répertoire courant\n");	
		return -1;
	}
	//verification pour ne pas ouvrir un repertoire
	FileHeader *tmpHeader = fileSystem->openFileTab[index]->getHeader();
	if(tmpHeader->IsDirectory){
		delete tmpHeader;
		fileSystem->openFileTab[index] = NULL;
		strcpy(fileSystem->openFileName[index],"");
		fileSystem->openFileMap->Clear(index);			
		fprintf(stderr, "Erreur, impossible d'ouvrir un répertoire\n" );
	}
	return index;
}

int do_UserWrite(int fileid, int size, char *from){
	OpenFile *currentfile; 
	currentfile = fileSystem->openFileTab[fileid];
	if(currentfile != NULL)
		return currentfile->Write(from,size);
	else
		return -1;
}

int do_UserRead(int fileid, int size, char *to){ 
	OpenFile *currentfile = fileSystem->openFileTab[fileid];
	if (currentfile != NULL)
		return currentfile->Read(to,size);
	else
		return -1;
}

void do_UserClose(int fileid){ 
	strcpy(fileSystem->openFileName[fileid],"");
	fileSystem->openFileMap->Clear(fileid);
	fileSystem->openFileTab[fileid] = NULL;
}