#ifndef __USERPROCESS_H__
#define __USERPROCESS_H__

int do_UserForkExec(char *buff);
void do_process_exit();
void do_waitpid(pid_t pid);

#endif
