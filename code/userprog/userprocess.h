#ifndef __USERPROCESS_H__
#define __USERPROCESS_H__

extern void StartProcess (char *file), ConsoleTest (char *in, char *out), SynchConsoleTest (char *in, char *out);

void do_UserForkExec(char *buff);

#endif
