#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc,char *argv[])
{
    int pip[2];
    char buff[2];
    pipe(pip);
    //child
    if(fork() == 0){
       read(pip[0],buff,sizeof(buff));
       printf("%d: received ping\n",getpid());
       write(pip[1],"0",1);
    }
    //parent
    else{
        write(pip[1],"0",1);
        read(pip[0],buff,sizeof(buff));
        printf("%d: received pong\n",getpid());
        write(pip[1],"0",1);
        wait(0);
    }
    exit(0);

}

