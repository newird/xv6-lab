#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void prime(int i);
int
main(int argc,char * argv[]){
    int pip[2];
    pipe(pip);
    if(fork()){
        close(pip[0]);
        int i;
        for(i = 2;i<= 35 ;++i){
            write(pip[1],&i,sizeof(i));
        }
        close(pip[1]);
        }else{
        close(pip[1]);
        prime(pip[0]);
        }
        wait(0);
        exit(0);
}  // end main

void prime(int i){
   int base;
   if(read(i,&base,sizeof(base))<=0){
       exit(0);
   }
    printf("prime %d\n",base);
    int p[2];
    pipe(p);
    if(fork()==0){
        close(p[1]);
        prime(p[0]);
    }else{
        close(p[0]);
        int j;
        while(read(i,&j,sizeof(j))){
            if(j%base!=0){
                 write(p[1],&j,sizeof(j));
            }
        }
        close(p[1]);
        wait(0);
        exit(0);
    }
}

