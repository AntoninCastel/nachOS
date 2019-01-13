#include "thread.h"
#include "userprocess.h"

void do_UserForkExec(char *buff) {
    Thread* newThread = new Thread(buff);
    newThread->Fork((VoidFunctionPtr)StartProcess, (int)buff);
}
