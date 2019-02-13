

extern int do_UserCreate(char *name,int size);
extern int do_UserOpen(char *name);
extern int do_UserWrite(int fileid, int size, char* from);
extern int do_UserRead(int fileid, int size, char* from);
extern void do_UserClose(int fileid);