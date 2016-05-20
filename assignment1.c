/**
* luckyscript
* a shell REPL
* cd/mkdir/touch/cat/ls/exit
*/
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>


void ls(char dirname[100], char args[10]);
void echo(char **args, int argscount);

int main(int argc,char **argv) {
    // get current username
    char* user = getenv("LOGNAME");
    
    // get current work dir
    char buf[100];
    char* cwd = strcat(getcwd(buf, sizeof(buf)),"/");
    
    // print shell prompt
    char shell[100];
    sprintf(shell,"[%s]@myshell:%s>",user,cwd);
    printf("%s",shell);
    
    //parser start
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
            if (line &&(sscanf(++line, "%20s", args) == 1)) {
                arguments[argscount] = malloc(sizeof(char) * 20);
                strncpy(arguments[argscount], args, 20);
                argscount++;
                arguments = realloc(arguments, sizeof(char *) * argscount + 1);
                line = strchr(line, ' ');
            } else {
                break;
            }
        }
        //parser end
        
        if (strcmp(command, "ls") == 0) {
            if (argscount == 0) {
                ls(cwd, "ls");
            } else if (argscount == 1 && (strcmp(arguments[0], "-l") == 0)) {
                ls(cwd, "ll");
            }else if (argscount == 1) {
                ls(cwd, arguments[0]);
            } else {
                printf("warning: too many argyments\n");
            }
        
        } else if (strcmp(command, "echo") == 0) {
            if (argscount == 1 && strcmp(arguments[0], "$HOME") == 0) {
                printf("%s\n", getenv("HOME"));
            }else {
                echo(arguments, argscount);
            }
        
        } else if (strcmp(command, "cd") == 0) {
            if (argscount == 2) {
                printf("warning: too many arguments\n");
            } else if (argscount == 0 || (strcmp(arguments[0], ".") == 0)) {
                // do nothing
            } else {
                int rs = chdir(arguments[0]);
                cwd = strcat(getcwd(buf, sizeof(buf)),"/");
                sprintf(shell,"[%s]@myshell:%s>",user,cwd);
            }
        
        } else if (strcmp(command, "mkdir") == 0) {
            if (argscount == 1) {
                mkdir(arguments[0],777);
            } else {
                printf("warning: too many or few arguments\n");
            }
            
        } else if (strcmp(command, "cat") == 0) {
            if (argscount == 1) {
                FILE *fp = NULL;
                char c;
                fp = fopen(arguments[0], "r");
                if (fp == NULL) {
                    printf("file not exits or other error");
                }
                while(fscanf(fp, "%c", &c) != EOF) {
                    printf("%c", c);
                }
                fclose(fp);
                fp = NULL;
                printf("\n");
            } else {
                printf("warning: too many or few arguments\n");
            }
        } else if (strcmp(command, "touch") == 0) {
            if (argscount == 1) {
                FILE *fp = NULL;
                fp = fopen(arguments[0], "a+");
                fclose(fp);
                fp = NULL;
            } else {
                printf("warning: too many or few arguments\n");
            }
        } else {
            printf("command not found!");
        }
        
        // free
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

void ls(char dirname[100], char args[10]) {
    DIR *dp;
    struct dirent *dirp;
    // char dirname[20] = "./";
    if (strcmp(args,"ls") == 0 || strcmp(args,"ll") == 0) {
        dp = opendir(dirname);
        while((dirp = readdir(dp)) != NULL) {
            if (strcmp(args,"ls") == 0) {
                if (dirp->d_name[0] != '.') {
                    printf("%s ", dirp->d_name);
                }
            } else if (strcmp(args,"ll") == 0) {
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
