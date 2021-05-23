#include <stdio.h>

struct test{
   char x1;
   short x2;
};

struct an{
char fox;
int cat;
short pig;
char dog;
};

struct an_s{
	char dog;
//	u8 __pad0[3];
	int cat;
	short pig;
	char fox;
//	u8 __pad1;
};

int main(){
   char* a;
   printf("%d",(int)sizeof(a));
   return 0;
}



