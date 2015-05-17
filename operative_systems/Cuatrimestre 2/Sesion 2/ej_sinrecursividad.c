//Ejemplo: Programa para recorrer un directorio
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main(int argc, char *argv[]){
  DIR *directorio;
  char camino[100];
  struct dirent *entrada;
  struct stat buffer;
  int pid, estado, padrepid;
  if (argc!=2)
        { printf("Hay que poner un unico parametro\n"); exit(1); }
  else
        {
               directorio=opendir(argv[1]);
               if (directorio==NULL)
                         {printf("Error al abrir el directorio\n"); exit(1); }
               entrada=readdir(directorio);
               while (entrada!=NULL)
                {        /* formamos el path del fichero a partir de sus componentes */
                  strcpy(camino,"/0");
                  strcpy(camino,argv[1]);
                  strcat(camino,"/");
                  strcat(camino,entrada->d_name);
                  printf("Nombre: %s ",camino);
                  if (stat(camino,&buffer)<0)
                          { printf("Error en el stat: %s\n",strerror(errno));
                            exit(1); }
                  else {
                  if(S_ISBLK(buffer.st_mode)) printf("fichero de bloques \n");
                  if(S_ISCHR(buffer.st_mode)) printf("fichero de caracteres \n");
                  if(S_ISDIR(buffer.st_mode)) printf("es un directorio \n ");
                  if(S_ISREG(buffer.st_mode)) printf("es un fichero normal \n");
                  if(S_ISLNK(buffer.st_mode)) printf("es un enlace \n");
                          }
		  printf("El tamaño en bytes es: %i\n", (int) buffer.st_size);
                  entrada=readdir(directorio); /* else */
               } /* while */
        } /*else */
} /*main*/


//Compilar con la consola: gcc ej.c -o ejecutable
//Para ejecutar pasarle por parámetros el nombre de los archivos