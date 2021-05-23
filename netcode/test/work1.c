#include <stdio.h>

#define SIZE(x) printf(#x);  \
	printf("占%d个字节\n",(int)sizeof(struct x))

struct x1{
 int a;
 char* b;
 char c;
};

struct x2{
    char a;
    int b;
    char c;
};

struct x3{
    int a;
    char b;
};

struct x4{
    char a;
    short b;
};

struct x5{
    char a;
    short b;
    char c;
};

struct x6{
    char a;
    long b;
};

struct x7{
    char a;
    long b;
    char c;
};

struct x8{
    char a;
    long long b;
};

struct x9{
    char a;
    long long b;
    char c;
};

struct x10{
    char a;
    int b;
    short c;
};

struct x11{
    char a;
    short b;
    char c;
    int d;
};

int main(){
    SIZE(x1);
    SIZE(x2);
    SIZE(x3);
    SIZE(x4);
    SIZE(x5);
    SIZE(x6);
    SIZE(x7);
    SIZE(x8);
    SIZE(x9);
    SIZE(x10);
    SIZE(x11);

    return 0;
}

