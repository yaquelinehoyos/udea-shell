#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[]){
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    printf("El directorio de trabajo actual es: %s \n", cwd);
}