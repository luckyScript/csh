#include <stdio.h>
#include <stdlib.h>
int main(void) {
    char* user = "ab";
    char shell[100];
    sprintf(shell,"%s",user);
    printf(shell);
}