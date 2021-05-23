//
// Created by zbc on 2021/5/14.
//
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unp.h>

#define MAXLEN 512

int main(){
    struct sockaddr_in sockaddrIn;
    short port=8845;
    int listenfd, connfd;
    char buff[MAXLEN];
    time_t ticks;


    listenfd=socket(AF_INET, SOCK_STREAM, 0);

    bzero(&sockaddrIn,sizeof(sockaddrIn));
    sockaddrIn.sin_family=AF_INET;
    sockaddrIn.sin_addr.s_addr=htonl(INADDR_ANY);
    sockaddrIn.sin_port=htons(port);

    if(bind(listenfd,(struct sockaddr *)&sockaddrIn,sizeof(sockaddrIn))==-1){
        printf("bind error\n");
        exit(1);
    }

    listen(listenfd,LISTENQ);


    for(;;){
        connfd = Accept(listenfd, (struct sockaddr *)NULL,NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff) ,"%.24S\r\n" ,ctime(&ticks));
        Write(connfd, buff, strlen(buff));

        close(connfd);
    }

}
