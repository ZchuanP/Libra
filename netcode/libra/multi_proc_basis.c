#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 5

int main(int argc,char* argv[]) {
    if(argc < 3){
        printf("need more arg\n");
        exit(1);
    }else{
        if(strcmp("-c",argv[1])==0){
            printf("[pid](%d) [ppid](%d): start\n",getpid(),getppid());
            int fd1_td1=open("td1.txt",O_RDONLY);
            if(fd1_td1 == -1){
                printf("open file error\n");
                exit(1);
            }
            printf("[pid](%d) [ppid](%d): [fd1_td1](%d) is got\n",getpid(),getppid(),fd1_td1);
            pid_t pid;
            for(int i=0;i<atoi(argv[2])-1;i++){
                if((pid=fork())==0){
                    printf("[pid](%d) [ppid](%d): start\n",getpid(),getppid());
                    char ctmp[SIZE];

                    read(fd1_td1,ctmp,5);
                    printf("[pid](%d) [ppid](%d): [read](%s) by [fd1_td1](%d)\n",getpid(),getppid(),ctmp,fd1_td1);

                    int fd2_td1=open("td1.txt",O_RDONLY);
                    if(fd2_td1 == -1){
                        printf("open file error\n");
                        exit(1);
                    }
                    printf("[pid](%d) [ppid](%d): [fd2_td1](%d) is got\n",getpid(),getppid(),fd2_td1);

                    read(fd2_td1,ctmp,5);
                    printf("[pid](%d) [ppid](%d): [read](%s) by [fd2_td1](%d)\n",getpid(),getppid(),ctmp,fd2_td1);

                    close(fd2_td1);
                    close(fd1_td1);
                    printf("[pid](%d) [ppid](%d): exit\n",getpid(),getppid());
                    exit(0);
                }
            }
            char ftmp[SIZE];
            read(fd1_td1,ftmp,5);
            printf("[pid](%d) [ppid](%d): [read](%s) by [fd1_td1](%d)\n",getpid(),getppid(),ftmp,fd1_td1);
            close(fd1_td1);

            int fd1_td2=open("td2.txt",O_RDONLY);
            if(fd1_td2 == -1){
                printf("open file error\n");
                exit(1);
            }
            printf("[pid](%d) [ppid](%d): [fd1_td2](%d) is got\n",getpid(),getppid(),fd1_td2);

            read(fd1_td2,ftmp,5);
            printf("[pid](%d) [ppid](%d): [read](%s) by [fd1_td2](%d)\n",getpid(),getppid(),ftmp,fd1_td2);

            close(fd1_td2);
            sleep(2);
            printf("[pid](%d) [ppid](%d): exit\n",getpid(),getppid());

        }
    }
}

