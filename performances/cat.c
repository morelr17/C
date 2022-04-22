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

    int sizetmp;
    sizetmp = atoi(argv[1]);

    int fd;
    if( (fd = open(argv[2], O_RDWR)) == -1){
        perror("open");
        exit(1);
    }

    char buffer[sizetmp];

    int readChar;
    while ( (readChar = read(fd,buffer,sizeof(buffer))) > 0) {
        write(0,buffer,readChar);
    }

    close(fd);
    exit(0);
}