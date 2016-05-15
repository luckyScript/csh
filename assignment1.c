#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

void getFileName();
char* getcwdname();

int main(int argc,char **argv) {
    char command[20];
    char* user = "kay";
    char* cwd = getcwdname();
    char shell[100];
    sprintf(shell,"[%s]@myshell:[%s]>",user,cwd);
    printf("%s",shell);
    gets(command);
    while(strcmp(command,"exit") != 0) {
        if(strcmp(command,"ls") == 0) {
            getFileName(cwd);
        }
        printf("[USER]@myshell:[CWD]>");
        gets(command);
    }
    printf("exit!");
    return 0;
}

void getFileName(dir) {
    DIR *dp;
    struct dirent *dirp;
    char* dirname = dir;
    dp = opendir(dirname);
    while((dirp = readdir(dp)) != NULL) {
        printf("%s ", dirp->d_name);
    }
    printf("\n");
    closedir(dp);
}

char* getcwdname() {
    char buf[100];
    getcwd(buf, sizeof(buf));
    return buf;
}