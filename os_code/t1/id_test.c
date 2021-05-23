//
// Created by zbc on 2021/4/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <wait.h>


void *pt_entrance()
{
    printf("ChThrd: [PID]%d [PPID]%d [PGRP]%d [SPID]%lu  [PTID]%lu\n", getpid(), getppid(), getpgrp(), syscall(SYS_gettid), pthread_self());
    sleep(1);
}


int main(int argc, char *argv[]) {
    printf("PaPrTh: [PID]%d [PPID]%d [PGRP]%d [SPID]%lu  [PTID]%lu\n", getpid(), getppid(), getpgrp(), syscall(SYS_gettid),pthread_self());
    pthread_t ptid, ptidt;
    pthread_create(&ptid, NULL, pt_entrance, NULL);
    pthread_create(&ptidt, NULL, pt_entrance, NULL);
    pthread_join(ptid, NULL);
    pthread_join(ptidt, NULL);
    
    pid_t pid;
    for(int i=0;i<2;i++) {
        if(pid=fork()==0) {
            printf("ChProc: [PID]%d [PPID]%d [PGRP]%d [SPID]%lu  [PTID]%lu\n", getpid(), getppid(), getpgrp(), syscall(SYS_gettid),pthread_self());
            return 0;
        }
        waitpid(pid,NULL,0);
    }
    
    sleep(1);
    return 0;

}
