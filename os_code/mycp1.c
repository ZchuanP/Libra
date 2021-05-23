#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<dirent.h>
#include<sys/stat.h>

#define BUFSIZE 512

int is_dir(char* path){
    struct stat st;
    stat(path,&st);
    if(S_ISDIR(st.st_mode))
        return 1;
    else
        return 0;
}


int endwith(char* s,char c){
    if(s[strlen(s)-1]==c){
        return 1;
    }else{
        return 0;
    }
}


void file_to_file(char* path_s,char* path_d){
    ssize_t nread;

    // 两种情况的处理
    char *tail_s=rindex(path_s,'/');

    // 文件到目录的情况下，转化为文件到文件
    if(is_dir(path_d)){
        path_d = strcat(path_d,tail_s);
    }

    int fd_s=open(path_s,O_RDONLY);
    int fd_d=open(path_d,O_WRONLY|O_CREAT|O_TRUNC, 0664);
    if(fd_d==-1){
        printf("open file %s error!\n",path_d);
        exit(1);
    }

    if(fd_s==-1){
        printf("open file %s error!\n",path_s);
        exit(1);
    }
    
    // 拷贝文件到新文件
    char buffer[BUFSIZE];
    while((nread=read(fd_s,buffer,BUFSIZE))>0){
        if(write(fd_d,buffer,nread)<nread){
            close(fd_s);
            close(fd_d);
            printf("copy failed！\n");
            exit(1);
        }
    }
    close(fd_s);
    close(fd_d);
    if (nread == -1)
        exit(-1);
    else
        printf("copy finished!\n");
}


void dir_to_dir(char* path_s,char* path_d){
    char newsrcPath[4096];
    char newdestPath[4096];

    if(!opendir(path_d)){
        //如果不存在就用mkdir函数来创建
        if (mkdir(path_d,0777))
        {
            printf("创建文件夹失败！");
        }
    }else{
    	printf("open dir %s ok\n",path_d);
    
    }

    DIR* srcDp = opendir(path_s);
    if(srcDp == NULL)
    {
        printf("打开文件夹[%s]失败！\n",path_s);
        exit(1);
    }else{
        printf("%s open\n",path_s);
    }
    struct dirent * srcDirent = NULL;
    int flag = 0;
    while(srcDirent = readdir(srcDp))
    {
        flag++;
        if(flag>2) //去除隐藏文件 . ..
        {
            bzero(newsrcPath,sizeof(newsrcPath)); //清空
            bzero(newdestPath,sizeof(newdestPath));

            sprintf(newsrcPath,"%s/%s",path_s,srcDirent->d_name);//保存新的文件路径
            sprintf(newdestPath,"%s/%s",path_d,srcDirent->d_name);

            if(srcDirent->d_type == DT_DIR){
                if(!endwith(newdestPath,'.'))
                    dir_to_dir(newsrcPath,newdestPath);
            }
            else {					     	 //普通文件
                file_to_file(newsrcPath,newdestPath);
            }
        }

    }

}

int main(int argc,char* argv[]){

    if(strcmp(argv[1],"-r")==0){
        char *path_s=argv[2];
        char *path_d=argv[3];
        dir_to_dir(path_s,path_d);
    }else{
        char *path_s=argv[1];
        char *path_d=argv[2];
        file_to_file(path_s,path_d);
    }

    return 0;
}
