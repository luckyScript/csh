#include "stdio.h"
#include "string.h"
int
main(void) {
	char dirname[20] = "./";
	char args[10] = ".git";
	strcat(dirname, args);
	printf("%s", dirname);
}