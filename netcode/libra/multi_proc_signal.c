#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <wait.h>

int conc_amnt=0;

void pa_handle_sigint(){
    printf("[pid](%d): SIGINT is handled in pa_handle_sigint()\n",getpid());
    printf("[pid](%d): [func](exit)  with [conc_amnt](%d)\n",getpid(),conc_amnt);
    exit(0);
}

void pa_handle_sigchld(){
    printf("[pid](%d): SIGCHLD is handled in pa_handle_sigchld()\n",getpid());
    int status=0;
    pid_t pid;
    while((pid=waitpid(-1,&status,WNOHANG))>0){
        printf("[pid](%d): [cpid](%d) is waited in pa_handle_sigchld()\n",getpid(),pid);
        conc_amnt--;
    }
}

int main(int argc,char* argv[]) {
    if (argc < 3) {
        printf("need more arg\n");
        exit(1);
    } else {
        if (strcmp("-c", argv[1]) == 0) {
            printf("[pid](%d): start\n",getpid());
            conc_amnt=atoi(argv[2]);
            pid_t pides[conc_amnt-1];

            struct sigaction action;
            memset(&action, 0, sizeof(action));
            sigemptyset(&action.sa_mask);
            
            action.sa_handler=&pa_handle_sigint;
            sigaction(SIGINT,&action,NULL);
            action.sa_handler=&pa_handle_sigchld;
            sigaction(SIGCHLD,&action,NULL);
            
            for(int i=0;i<conc_amnt-1;i++){
                pides[i]=fork();
                if(pides[i]==0){
                    printf("[pid](%d): start\n",getpid());
                    pause();
                }
            }

            sleep(1);
            for(int i=0;i<conc_amnt-1;i++){
                kill(pides[i],SIGINT);
            }

            while(conc_amnt>1){
                printf("[pid](%d): [func](pause) with [conc_amnt](%d)\n",getpid(),conc_amnt);
                pause();
            }

            pause();

        }

    }
}



