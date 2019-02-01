/*
    ejemplo.c

    Ejemplo de uso de la funcion separaItems
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "parser.h"

#define TAM 100

int main ()
{
  char ** items;
  int num, background, aux;
  char expresion[TAM];
  int condicion = 1;

  while(condicion == 1){ //Se crea un ciclo infinito para el envío de los comandos
    printf ("\033[01;33m\nTeclea una orden para el \033[01;35mudea-shell\033[01;37m$ ");
    printf("\033[01;36m");
    fgets (expresion, TAM, stdin);

    num = separaItems (expresion, &items, &background);

    if (num > 0){
      if(strcmp(items[0],"udea-pwd") == 0 || strcmp(items[0],"udea-cd") == 0 || strcmp(items[0],"udea-echo") == 0 || strcmp(items[0],"udea-clr") == 0 || 
        strcmp(items[0],"udea-time") == 0 || strcmp(items[0],"udea-exit") == 0){ //En caso de ser algún comando que se debía implementar manualmente
          identificarDirectorio(items, background); 
      }else{
        pid_t pid = fork();
        if(pid < 0){
          printf("Fork falló \n");
        }else if (pid == 0){
          aux = execlp(items[0], items[0], items[1], "/", NULL); //En caso de ser de la biblioteca del bin
          if(aux == -1){
            printf("\033[01;31mOrden no encontrada \n"); //En caso de ser un comando no existente
            exit(0);
          }
        }else{
          if(background == 0){ //Cuando no se pide ejecución en segundo plano
            wait(NULL);
          }
        }
      }
      liberaItems (items);
    }
  }
  return 0;
}
