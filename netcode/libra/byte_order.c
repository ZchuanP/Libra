#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define uchar unsigned char


void myprint(void* num,int size,char type){
    uchar* pt= (uchar *)num;
    if(size==4 && type=='n') {
        printf("[ipv4_n_cbc_d]");
        for(int i=0;i<size;i++){
            if(i<size-1){
                printf("%d.",pt[i]);
            }else{
                printf("%d\n",pt[i]);
            }
        }
    }
    if(size==4 && type=='h') {
        printf("[ipv4_h_cbc_d]");
        for(int i=0;i<size;i++){
            if(i<size-1){
                printf("%d.",pt[i]);
            }else{
                printf("%d\n",pt[i]);
            }
        }
    }

    if(size==4 && type=='n'){
        printf("[ipv4_n_cbc_x]");
    }
    if(size==4 && type=='h'){
        printf("[ipv4_h_cbc_x]");
    }
    if(size==2 && type=='n'){
        printf("[port_n_cbc_x]");
    }
    if(size==2 && type=='h'){
        printf("[port_h_cbc_x]");
    }
    for(int i=0;i<size;i++){
        printf("%02X",pt[i]);
    }
    printf("\n");


    if(size==4 && type=='n'){
        printf("[ipv4_n_asw_x]");
        printf("%08X\n",(*(u_int32_t *)num));
    }
    if(size==4 && type=='h'){
        printf("[ipv4_h_asw_x]");
        printf("%08X\n",(*(u_int32_t *)num));
    }
    if(size==2 && type=='n'){
        printf("[port_n_asw_x]");
        printf("%04X\n",(*(u_int16_t *)num));
    }
    if(size==2 && type=='h'){
        printf("[port_h_asw_x]");
        printf("%04X\n",(*(u_int16_t *)num));
    }


    if(size==2 && type=='n'){
        printf("[port_n_asw_d]");
        printf("%u\n",(*(u_int16_t *)num));
    }
    if(size==2 && type=='h'){
        printf("[port_h_asw_d]");
        printf("%u\n",(*(u_int16_t *)num));
    }
}


int main(int argc,char* argv[]){
    u_int32_t ipv4_h, ipv4_n;
    u_int16_t port_h, port_n;
    ipv4_n=inet_addr(argv[1]);
    ipv4_h=ntohl(ipv4_n);
    port_n=htons((u_int16_t)strtol(argv[2],NULL,10));
    port_h=ntohs(port_n);
    myprint(&ipv4_n,sizeof(ipv4_n),'n');
    myprint(&port_n,sizeof(port_n),'n');
    myprint(&ipv4_h,sizeof(ipv4_h),'h');
    myprint(&port_h,sizeof(port_h),'h');
    return 0;
}


