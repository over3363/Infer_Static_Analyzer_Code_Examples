#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int lineAmount(char *arr, int fd, int size);
int openFile(char *arr);
void getSize(char *arr, struct stat *info);

const int BUFFSIZE = 256; 

int main(int argc, char *argv[])
{
    int dispAmount = 10;
    int dispFrom = -1;
    int iFd = -1;
    struct stat info;
    if(argc == 4){
        int fileFound=0;
        for(int i = 1; i < argc; i++){
            if(strncmp(argv[i],"-n",2) == 0){
                if(argv[i+1][0] == '+'){
                    char *arr = argv[i+1];
                    dispFrom = atoi(++arr);
                    dispAmount = -1;
                }else{
                    dispAmount = atoi(argv[i+1]);
                }
                i++;
            }else if(!fileFound){
                if(i == 1){
                    iFd = openFile(argv[1]);
                    getSize(argv[1], &info);
                    fileFound=1; 
                }else{
                    iFd = openFile(argv[argc-1]);
                    getSize(argv[argc-1], &info);
                    fileFound=1;
                }  
            }
        }
    }else if(argc < 2 || argc > 4){
        if(write(2,"invalid arguments\n",18) == -1){
            perror("Writing standard error");
        }
        return 0;
    }else{
        iFd = openFile(argv[1]);
        getSize(argv[1], &info);
    }
    //create a buffer to match file size
    int fSize = info.st_size;
    char buf[fSize];
    int lineCount = lineAmount(buf, iFd, fSize);
    
    //adjust for files with no new line at the end
    if(buf[fSize-1] != '\n'){
        lineCount++;
    }
    
    if(dispAmount != -1){
        for(int i = 0; i < fSize; i++){
            if(lineCount <= dispAmount){
                if(write(1, buf+i, fSize - i) == -1){
                    perror("Writing standard input");
                }
                break;
            }
            if(buf[i] == '\n'){
                lineCount--;
            }
        }
    }else{
        int lineIndex = 1;
        for(int i = 0; i < fSize; i++){
            if(lineIndex >= dispFrom){
                if(write(1, buf+i, fSize - i) == -1){
                    perror("Writing standard input");
                }
                break;
            }
            if(buf[i] == '\n'){
                lineIndex++;
            }
        }
    }
    return 0;
}

int lineAmount(char *arr, int fd, int size)
{
    int count = 0;
    if(read(fd,arr,size) == -1){
        perror("Reading File");
    }
    for(int i = 0; i < strlen(arr); i++){
        if(arr[i] == '\n'){
            count++;
        }
    }
    return count;
}

int openFile(char *arr)
{
    int fd = -1;
        fd = open(arr,O_RDONLY);
        if(fd == -1){
            perror("Opening file");
            exit(1);
        } 
    return fd;
}

void getSize(char *arr, struct stat *info)
{
    if(stat(arr,info)){
        perror(arr);
    }
}
