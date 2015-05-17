/*
 ============================================================================
 Name        : P22.c
 Author      : Mario
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "P22.h"

unsigned BytesLibresPag(PAGT * pag){
	DIRPAGT *dir;
	dir = (DIRPAGT*) pag;
	if(pag->cabp.ocupacion) return ZDPAGSZ - dir->entrada[-(pag->cabp.ocupacion)]
	                                                 - (pag->cabp.ocupacion) * UINTSZ;
	else return ZDPAGSZ;

}

unsigned PrimerByteLibre(PAGT *pag){
	DIRPAGT *dir;
	dir = (DIRPAGT*) pag;
	if(pag->cabp.ocupacion) return dir->entrada[-(pag->cabp.ocupacion)];
	else return 0;
}

char AddRegAPag(PAGT *pag, char *reg, unsigned regsz){
	int pbl = PrimerByteLibre(pag);
	//comprobamos si hay espacio libre
	if(regsz + UINTSZ > BytesLibresPag(pag)) return FRACASO;

	//insertamos el registro.
	void *destino = pag->datos + PrimerByteLibre(pag);
	memcpy(destino, reg, regsz);

	//Añadimos el fin de esa tupla
	DIRPAGT *dir = (DIRPAGT*) pag;
	dir->entrada[-(pag->cabp.ocupacion+1)] = pbl + regsz;

	//actualizamos cabecera
	pag->cabp.ocupacion++;

	return EXITO;
}

//devuelve el inicio de una tupla. Si la tupla es la "siguiente" a la ultima,
//devuelve el primer byte libre.
unsigned ObtenerInicioDeTupla(PAGT *pag, unsigned pos){
	DIRPAGT *dir = (DIRPAGT*) pag;
	if(pos <= 0) return 0;
	if(pos > pag->cabp.ocupacion) return -1; //no existe
	return dir->entrada[-pos];
}

char ObtenRegDePag(PAGT *pag, char *reg, unsigned *regsz, unsigned pos){
	int origen = ObtenerInicioDeTupla(pag,pos);
	if(pos >= pag->cabp.ocupacion) return FRACASO;
	*regsz = ObtenerInicioDeTupla(pag,pos+1) - ObtenerInicioDeTupla(pag,pos);
	memcpy(reg, &(pag->datos[origen]), *regsz);
	return EXITO;
}

char CreaFichero(char *filename,void *cabecera, unsigned cabsz)
{
FILE  *fp;

fp = fopen(filename,"wb");
if (fp == NULL) return FRACASO;
fwrite (cabecera,cabsz,1,fp);
fclose (fp);
return EXITO;
}

char ObtenSgteRegLongVar(FILE *fd, char *reg, unsigned *regsz)
{
 unsigned clave;
 char linea[255]; // Linea del fichero texto
 char campo[80];


 if (!fgets(linea,255,fd)) return 0;
 sscanf(linea,"%d,%d,%s",regsz,&clave,campo);
 memmove(reg,&clave,sizeof(unsigned));
 memmove(reg + sizeof(unsigned),campo, *regsz);
 *regsz += sizeof(unsigned);
 return 1;
}



char ConstruyeLvregDat (void){
	int focupacion = 0;
	char nomfich[20] = "lvreg.dat";
	CABFILET filecab;
	filecab.pagid = focupacion;
	focupacion++;
	strcpy(filecab.nomfich, nomfich);
	filecab.ocupacion = focupacion;
	filecab.pagsz = PAGSZ;
	CreaFichero(nomfich,&filecab,PAGSZ);
	FILE  *fp;
	fp = fopen(nomfich,"r+b");
	fseek(fp,PAGSZ,SEEK_SET);
	if (fp == NULL) return FRACASO;


	PAGT pagina;
	CABPAGT *cabpag;

	cabpag = &(pagina.cabp);
	cabpag->ocupacion = 0;
	cabpag->pagid = focupacion;

	char memoria_aux[255];//memoria donde almacenar los registros(desconocemos su tamaño)
	void *reg = memoria_aux;
	unsigned int regsz;


	FILE * ftext = fopen("lvreg.txt","rt");
	while(ObtenSgteRegLongVar(ftext,reg, &regsz)){
		printf("%d\n",regsz);
		if(!AddRegAPag(&pagina,reg,regsz)){//si cabe se almacena, sino escribe la pag y almacena en una nueva pag
			fwrite(&pagina,PAGSZ,1,fp);
			//reseteamos los valores de la nueva pagina.
			memset(&pagina, 0x00, PAGSZ);
			focupacion++;
			cabpag->ocupacion = 0;
			cabpag->pagid = focupacion;
			AddRegAPag(&pagina, reg, regsz);
		}
	}
	fwrite(&pagina,PAGSZ,1,fp);
	focupacion++;
	fseek(fp,0,SEEK_SET);
	filecab.ocupacion = focupacion;
	fwrite(&filecab,PAGSZ,1,fp);

	printf("Construidas %d paginas.\n",focupacion);

	fclose(fp);
	fclose(ftext);
	return EXITO;
}

void ImprimeReg(char *reg, unsigned regsz, FILE *fd)
{
  unsigned clave;

  fprintf(fd,"%d,",regsz - UINTSZ);
  memmove(&clave,reg,sizeof(unsigned));
  fprintf(fd,"%d,",clave);
  reg[regsz] = '\0'; //Fin de cadena
  fprintf(fd,"%s\n",reg + sizeof(unsigned));
}

char VolcadoPedidosDatARespedTxt(void){
	FILE *fdat = fopen("lvreg.dat","rb");
	FILE *ftxt = fopen("lvreg2.txt","wb");
	if(fdat == NULL || ftxt == NULL) return FRACASO;
	CABFILET cabecera;
	PAGT pagina;
	char mem_aux[255];
	void *reg = mem_aux;
	unsigned int regsz;

	fread(&cabecera,PAGSZ,1,fdat);
	int i, j;
	for(i=1;i<cabecera.ocupacion;i++){
		fseek(fdat, i*PAGSZ,SEEK_SET);
		fread(&pagina,PAGSZ,1,fdat);
		for(j = 0; j < pagina.cabp.ocupacion; j++) {
			ObtenRegDePag(&pagina, reg, &regsz, j);
			ImprimeReg(reg,regsz,ftxt);
		}
	}
	fclose(ftxt);
	fclose(fdat);
	return EXITO;
}

int main(void) {
	printf("Comenzando juegos de prueba:\n");
	PAGT pag;
	pag.cabp.ocupacion = 0;
	pag.cabp.pagid = 1;
	char cadena[20] = " Yo Bien :D\n";
	AddRegAPag(&pag,cadena,13);
	strcpy(cadena,"Que tal?\n");
	AddRegAPag(&pag,cadena,10);
	strcpy(cadena,"Hola!\n");
	AddRegAPag(&pag,cadena,7);

	char salida[10];
	int tamreg = 0;
	ObtenRegDePag(&pag,salida,&tamreg,2);
	printf(salida);
	ObtenRegDePag(&pag,salida,&tamreg,1);
	printf(salida);
	ObtenRegDePag(&pag,salida,&tamreg,0);
	printf(salida);

	ConstruyeLvregDat();
	VolcadoPedidosDatARespedTxt();


	return EXIT_SUCCESS;
}
