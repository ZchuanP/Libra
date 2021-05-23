//
// Created by zbc on 2021/5/14.
//

#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unp.h>

#define MAXLIEN 512

int main(int argc,char* argv[]){
    int sockfd, n;
    char recvline[MAXLIEN + 1];
    struct sockaddr_in sockaddrIn;

    if((sockfd = socket(AF_INET, SOCK_STREAM,0))<0){
        printf("isocket_erro\n");
   	exit(1);
    }

    bzero(&sockaddrIn,sizeof(sockaddrIn));
    sockaddrIn.sin_family=AF_INET;
    sockaddrIn.sin_port=htons(8845);

    if(inet_pton(AF_INET,argv[1],&sockaddrIn.sin_addr)<0){
        printf("inet_pton erro!\n");
   	exit(1);
   }

    if(connect(sockfd,(struct sockaddr*)&sockaddrIn,sizeof(sockaddrIn))<0){
        printf("connect erro!\n");
   	exit(1);
   }

        
    while((n=read(sockfd, recvline, MAXLIEN))>0){
        recvline[n]=0;

        if(fputs(recvline, stdout) == EOF){
        printf("fputs erro!\n");
   	exit(1);
   	}

    }
    if(n<0){
        printf("read error");
   	exit(1);
   }

    exit(0);
}
