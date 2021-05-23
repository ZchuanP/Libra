#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]){
    char *check =argv[1];
    int need_zero=4-(int)strlen(check)%4;
    for(int i=0;i<need_zero && need_zero!=4;i++){
        strcat(check,"0");
    }
    u_int32_t checksum=0x0;
    for(int i=0;i<strlen(check);i+=4){
        char tmp[4];
        int t=i;
        for(int j=0;j<4;j++,t++){
            tmp[j]=check[t];
        }
        checksum+=(u_int16_t)strtol(tmp,NULL,16);
    }
    checksum=(checksum >> 16) +(checksum & 0x0000ffffUL);
    if((checksum & 0xffff0000UL) !=0){
        checksum=(checksum >> 16) +(checksum & 0x0000ffffUL);
    }
    checksum=(u_int16_t)~checksum;
    printf("%04x",checksum);
}
