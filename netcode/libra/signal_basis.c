#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>


void sigusr1_act(){
    printf("[pid](%d): [sig](SIGUSR1) is captured\n",getpid());
}

void sigusr2_act(){
    printf("[pid](%d): [sig](SIGUSR2) is captured\n",getpid());
}

void sigint_act(){
    printf("[pid](%d): [sig](SIGINT)  is captured\n",getpid());
    printf("[pid](%d) exit\n", getpid());
    exit(1);
}

int main(){
    printf("[pid](%d) start\n",getpid());
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    
    action.sa_handler=&sigusr1_act;
    action.sa_flags=0;
    sigemptyset(&action.sa_mask);
    
    sigaction(SIGUSR1,&action,NULL);
    action.sa_handler=&sigusr2_act;
    sigaction(SIGUSR2,&action,NULL);
    action.sa_handler=&sigint_act;
    sigaction(SIGINT,&action,NULL);
    while(1){
        pause();
    }
}


