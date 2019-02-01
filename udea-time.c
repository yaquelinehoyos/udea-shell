#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main (int argc, char *argv[]){
    time_t tiempo = time(NULL);
    struct tm *loctime = localtime(&tiempo);
    char buffer[256];
    strftime(buffer, 256, "El tiempo es %I:%M %p. \n", loctime);
    fputs(buffer, stdout);
}