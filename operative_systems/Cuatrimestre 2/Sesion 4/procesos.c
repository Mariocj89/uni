
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int x;
	int res;
	x=fork();

	//printf("Soy el proceso %d\n",x);
	//execl("/bin/ls","ls",NULL); //Ejecutar un comando en un proceso hijo.
	if(x==0){//Ejecutado por el hijo
		exit(15);
	}
	else{//Ejecutado por el padre
		wait(&res);
		printf("El hijo termino devolviendo el valor %d\n",res>>8);
	}


}
