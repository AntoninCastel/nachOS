#ifndef __USERTHREAD_H__
#define __USERTHREAD_H__

typedef struct {
	int fn;
	int param;
	int SP;
} param_t;

extern int do_UserThreadCreate(int f, int arg);

#endif