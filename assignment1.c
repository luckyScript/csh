#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>


void ls(char args[10]);
void echo(char **args, int argscount);
char* getcwdname();

int main(int argc,char **argv) {
    char* user = "kay";
    char* cwd = getcwdname();
    char shell[100];
    sprintf(shell,"[%s]@myshell:%s>",user,cwd);
    printf("%s",shell);
    
    while(1) {
        char *line = malloc(128);
        char *originLine = line;
        fgets(line, 128, stdin);
        char command[25];       
        sscanf(line, "%20s ", command);
        char **arguments = malloc(sizeof(char *));
        unsigned int argscount = 0;
        line = strchr(line, ' ');
        if (strcmp(command, "exit") == 0) {
            break;
        }
        while(1) {
            char args[20];
            if(line &&(sscanf(++line, "%20s", args) == 1)) {
                arguments[argscount] = malloc(sizeof(char) * 20);
                strncpy(arguments[argscount], args, 20);
                argscount++;
                arguments = realloc(arguments, sizeof(char *) * argscount + 1);
                line = strchr(line, ' ');
            } else {
                break;
            }
        }

        if(strcmp(command, "ls") == 0) {
            printf("hello world");
            if(argscount == 0) {
                ls("ls");
            } else if(argscount == 1 && (strcmp(arguments[0], "-l") == 0)) {
                ls("ll");
            }else {
                ls(arguments[0]);
            }
        } else if(strcmp(command, "echo") == 0) {
            echo(arguments, argscount);
        } else {
            printf("command not found!")
        }
        /*for(int i = 0; i < argscount; i++) {
            printf("%s", arguments[i]);
        }*/
        for(int i = 0; i < argscount; i++) {
            free(arguments[i]);
        }
        free(arguments);
        free(originLine);
        printf("%s",shell);
    }
    printf("exit!");
    return 0;
}

void ls(char args[10]) {
    DIR *dp;
    struct dirent *dirp;
    char dirname[20] = "./";
    if(strcmp(args,"ls") == 0 || strcmp(args,"ll") == 0) {
        dp = opendir(dirname);
        while((dirp = readdir(dp)) != NULL) {
            if(strcmp(args,"ls") == 0) {
                if(dirp->d_name[0] != '.') {
                    printf("%s ", dirp->d_name);
                }
            } else if(strcmp(args,"ll") == 0) {
                printf("%s ", dirp->d_name);
            }
        }
    }else {
        strcat(dirname, args);
        dp = opendir(dirname);
        //printf("%s", dirname);

        while((dirp = readdir(dp)) != NULL) {
            printf("%s ", dirp->d_name);
        }
    }
    
    printf("\n");
    closedir(dp);
}

void echo(char **args, int argscount) {
    for(int i = 0; i < argscount; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}

char* getcwdname() {
    char buf[100];
    getcwd(buf, sizeof(buf));
    return buf;
}