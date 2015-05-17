#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
	int x,i;
	int res;
	char aux[50];

	if(argc<4){
		printf("Error, debe introducir 3 directorios\n");
		exit(-1);
	}

      for(i=1;i<4;i++){
	x=fork();
	if(x==0){//Ejecutado por el hijo
		sprintf(aux, "%s/salida%d.txt",argv[i],i);
		int fd = creat(aux,0777);
		int copia = dup(1);
		dup2(fd,1);
		printf("Mostrando directorio: %s\n",argv[i]);
		execl("/bin/ls","ls",argv[i],NULL);
		dup2(copia,fd);
		close(fd);
		exit(0);
	}
      }



}
