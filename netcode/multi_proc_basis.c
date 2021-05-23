#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int fd1_td1,fd2_td1,fd1_td2;
    pid_t pid;
        
    //father output1
    printf("[pid](%d) [ppid](%d): start\n",getpid(),getppid());

    //father open td1.txt
    fd1_td1 = open("td1.txt",O_RDONLY);

    //father output2
    printf("[pid](%d) [ppid](%d): [fd1_td1](%d) is got\n",getpid(),getppid(),fd1_td1);

    //derive sons
    for(int i=0;i<argv[2][0]-49;i++){
        pid = fork();
        if(pid == 0){
            printf("[pid](%d) [ppid](%d): start\n",getpid(),getppid());
            break;
        }
       
    }

    //read 5 chars
    char buf[10];
    read(fd1_td1,buf,5);
    printf("[pid](%d) [ppid](%d): [read](%5s) by [fd1_td1](%d)\n",getpid(),getppid(),buf,fd1_td1);
    printf("%s\n",buf);
    //sons open file
    if(pid == 0){
        fd2_td1 = open("td1.txt",O_RDONLY);
        printf("[pid](%d) [ppid](%d): [fd2_td1](%d) is got\n",getpid(),getppid(),fd2_td1);

        //read 5 chars
        read(fd2_td1,buf,5);
        printf("%s\n",buf);
        printf("[pid](%d) [ppid](%d): [read](%5s) by [fd2_td1](%d)\n",getpid(),getppid(),buf,fd2_td1);
        
        //close fd2_td1
        close(fd2_td1);
        //close fd1_td1
        close(fd1_td1);
        printf("[pid](%d) [ppid](%d): exit\n",getpid(),getppid());
        exit(0);
    }
    else{
        //father close td1.txt
        close(fd1_td1);

        //father open td2.txt
        fd1_td2 = open("td2.txt",O_RDONLY);

        //father output3
        printf("[pid](%d) [ppid](%d): [fd1_td2](%d) is got\n",getpid(),getppid(),fd1_td2);

        //read 5 chars
        read(fd1_td2,buf,5);
	printf("%s\n",buf);
        //father output4
        printf("[pid](%d) [ppid](%d): [read](%5s) by [fd1_td2](%d)\n",getpid(),getppid(),buf,fd1_td2);

        //father output5
        printf("[pid](%d) [ppid](%d): exit\n",getpid(),getppid());
        sleep(5);
        exit(0);
    }

    return 0;
}
