#ifndef __USERTHREAD_H__
#define __USERTHREAD_H__

typedef struct {
	int fn;
	int param;
	int SP;
	int FPnext;
} param_t;

extern int do_UserThreadCreate(int f, int arg);
void do_UserThreadExit();

#endif