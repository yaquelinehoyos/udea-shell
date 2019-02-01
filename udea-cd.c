#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[]){
    char newPath[] = "/home/yaque/Documentos/Sistemas operativos";
    int dir;
    dir = chdir(newPath);
    if(dir == -1){
      printf("Error en el cambio de directorio");
    }else{
      printf("La nueva ruta es: /home/yaque/Documentos/Sistemas operativos \n");
    }
}