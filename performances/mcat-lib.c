#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc,char *argv[]){

    if(argc != 3){
        printf("erreur d'argument");
        exit(1);
    }

    int fd;
    if( (fd = fopen(argv[2], O_RDWR)) == -1){
        perror("open");
        exit(1);
    }

    while (fputc(fgetc(fd,stdin),fd,stdout) != EOF || 0)  {
        exit (1);
    }
    

    close(fd);
    exit(0);
}