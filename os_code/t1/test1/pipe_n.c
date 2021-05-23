#include <stdio.h>
#include <unistd.h>
#define READ 0
#define WRITE 1


int main(){
	int pid;
	int pipefds_f[2],pipefds_s[2];
	int n=0;

	if(pipe(pipefds_f)==-1||pipe(pipefds_s)==-1){
		printf("pipe failed");
		return 0;
	}

	pid=fork();
	while(1){
		if(pid==0){
			close(pipefds_f[WRITE]);
			close(pipefds_s[READ]);
			read(pipefds_f[READ],&n,sizeof(int));
			n++;
			printf("i am son\n");
			write(pipefds_s[WRITE],&n,sizeof(int));				
		}else{
			close(pipefds_f[READ]);
                        close(pipefds_s[WRITE]);
                        read(pipefds_s[READ],&n,sizeof(int));
			printf("i am father\n");
		      	printf("%d",n);
			n=0;
			write(pipefds_f[WRITE],&n,sizeof(int));
		}
	}




}
