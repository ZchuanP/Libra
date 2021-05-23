#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/wait.h>  
#include <sys/types.h>  
#define READ    0  
#define WRITE   1  
int main(void)  
{  
    int x;  
    pid_t pid;  
    int pipe1[2],pipe2[2];  
    /*初始化管道*/  
    pipe(pipe1);  
    pipe(pipe2);  
    pid = fork();  
    if(pid < 0)  
    {  
        printf("create process error!/n");  
        exit(1);  
    }  
    if(pid == 0)        //子进程  
    {  
        close(pipe1[WRITE]);  
        close(pipe2[READ]);  
        do  
        {  
            read(pipe1[READ],&x,sizeof(int));  
            printf("child %d read: %d\n",getpid(),x++);  
            write(pipe2[WRITE],&x,sizeof(int));  
        }while(x<=9);  
        //读写完成后,关闭管道  
        close(pipe1[READ]);  
        close(pipe2[WRITE]);  
        exit(0);  
    }  
    else if(pid > 0) //父进程  
    {  
        close(pipe2[WRITE]);  
        close(pipe1[READ]);  
        x = 1;  
        //每次循环向管道1 的1 端写入变量X 的值,并从  
        //管道2 的0 端读一整数写入X 再对X 加1，直到X 大于10  
        do{  
            write(pipe1[WRITE],&x,sizeof(int));  
            read(pipe2[READ],&x,sizeof(int));  
            printf("parent %d read: %d\n",getpid(),x);
	    x=0;  
        }while(x<=9);  
        //读写完成后,关闭管道  
        close(pipe1[WRITE]);  
        close(pipe2[READ]);  
        waitpid(pid,NULL,0);  
        exit(0);  
    }  
}  

