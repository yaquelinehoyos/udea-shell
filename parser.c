/*
    parser.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include "parser.h"

int separaItems (char * expresion,   // Palabras a separar
                 char *** items,     // Resultado
                 int * background)   // 1 si hay un & al final
{
  int i, j, num, ult;
  char ** pp;
                    // En principio:
  *items = NULL;    //   cero parametros
  *background = 0;  //   ejecucion en primer plano

  for (i=0; expresion[i]!='\0'; i++)  // Cambiar saltos de
    if (expresion[i]=='\n' ||         // linea y tabuladores
        expresion[i]=='\t')           // por espacios
      expresion[i] = ' ';

  while (*expresion==' ')   // Quitar espacios del principio
    expresion ++;

  if (*expresion=='\0')     // Si cadena vacia ...
    return 0;               // ... cero parametros

  for (i=1, num=1, ult=0; expresion[i]!='\0'; i++)
    if (expresion[i]!=' ' &&
        expresion[i-1]==' ')            // Contar palabras
    {                                   // (parametros)
      num ++;
      ult = i;     // Recordar posicion de la ultima palabra
    }

  i --;
  while (i>=0 && expresion[i]==' ')   // Quitar espacios
    expresion[i--] = '\0';            // del final

                                      // Mirar si la ultima
  if (strcmp(expresion+ult,"&")==0)   // palabra es un &
  {
    *background = 1;  // Marcar ejecucion en segundo plano

    expresion[ult] = ' ';               // Quitar &

    while (i>=0 && expresion[i]==' ')   // Quitar espacios
      expresion[i--] = '\0';            // del final
                                        // (otra vez)
    num --;           // Descontar &

    if (*expresion=='\0')  // Si solo estaba el & ...
      return 0;            // ... cero parametros
  }

  pp = malloc ((num+1)*sizeof(char*));  // Pedir array
  if (pp==NULL) return -1;              // de punteros

  pp[0] = expresion;  // El primer parametro es facil

  for (i=1, j=1; expresion[i]!='\0'; i++)  // Localizar los
    if (expresion[i]!=' ' &&             // demas parametros,
        expresion[i-1]==' ')           // apuntar a ellos con
    {                                // los punteros del
      expresion[i-1] = '\0';       // array, y poner \0 en
      pp[j++] = expresion + i;   // lugar de espacios
    }
                  // Anyadir un puntero a NULL al final del
  pp[j] = NULL;   // array de punteros (asi es mas facil
                  // trabajar con el)
  *items = pp;
  return num;     // Devolver array y numero de palabras
}

void liberaItems (char ** items)
{
  free (items);
}

void identificarDirectorio(char ** items, int background){ //Este es el método para 
                                                           //las ordenes que se debían 
                                                           //implementar manualmente
  char orden[100] = "./";     //Creamos el nombre del archivo
  strcat(orden, items[0]);
  strcat(orden, ".out");

  if(strcmp(items[0],"udea-echo") == 0){  //Esta condición es especial
    char mensaje[100];                    //ya que debemos construir 
    mensaje[0] = '\0';                    //el mensaje que se debe imprimir
    int i = 1;                            //para luego enviarlo como 
    while (items[i] != 0){                //argumento al programa nuevo
      strcat(mensaje, items[i]);
      strcat(mensaje, " ");
      i = i + 1;
    }
    pid_t pid = fork();
    if(pid < 0){
      printf("Fork falló \n");
    }else if (pid == 0){
      execlp("./udea-echo.out", "./udea-echo.out", mensaje, NULL);  //Aquí se crea el nuevo programa
    }else{
      if(background == 0){  //Cuando no se pide ejecución en segundo plano
        wait(NULL);
      }
    }
    strcpy(mensaje, "");  //limpiamos la variable mensaje

  }else if(strcmp(items[0],"udea-exit") == 0){  //Para terminar el programa
    exit(0);

  }else{
    pid_t pid = fork();
    if(pid < 0){
      printf("Fork falló \n");
    }else if (pid == 0){
      execlp(orden, orden, items[1], NULL); //Se crea el nuevo programa
    }else{
      if(background == 0){  //Cuando no se pide ejecución en segundo plano
        wait(NULL);
      }
    }
  }
}