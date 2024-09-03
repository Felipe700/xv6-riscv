#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{
    int pid = getpid();
    int ppid = getppid();
    printf("Corriendo yosoytupadre... \n");
    printf("Pid: %d\n", pid);
    printf("PPid: %d\n", ppid);
    exit(1);
}
