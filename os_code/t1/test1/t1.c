#include <stdio.h>
#include <unistd.h>

int
main(){
    int i=10;
    int j= fork();
    while(i<10){
        if(j==0) {
            printf("son\n");
        }else{
            printf("father\n");
        }
	i--;
    }
}
