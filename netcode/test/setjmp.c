#include <setjmp.h>
#include <stdio.h>

int main(){
    jmp_buf env;
    int i;
    i=setjmp(env);
    
    if(i==0){
    	printf("first runing\n");
	longjmp(env,2);
    }else{
    	printf("second runing\n");
    }
    
    printf("end!\n");
    return 0;

}
