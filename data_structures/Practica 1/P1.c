/*
 ============================================================================
 Name        : P1.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "P1.h"

char EjercicioP1_1(void)
{
	char c = 0x00;
	FILE *fp = fopen("uno.dat","wb");
	if(fp == NULL) return FRACASO;
	fwrite(&c,1,1,fp);
	fclose(fp);
	return EXITO;	
}

char EjercicioP1_2()
{
	char c[1024] = {0x00};
	memset(c,0x00,1024);
	int size = 0;
	
	FILE *fp2 = fopen("dos.dat","wb");
	if(fp2 == NULL) return FRACASO;
	fwrite(&size,sizeof(int),1,fp2);
	fwrite(c,1024,1,fp2);
	size+=1024;
	fseek(fp2,0L,SEEK_SET);
	fwrite(&size,sizeof(int),1,fp2);
	fclose(fp2);
	return EXITO;
}

char EjercicioP1_3(char *filename, unsigned numbytes, char valorbyte)
{
	FILE *fp = fopen(filename,"wb");
	if(fp == NULL) return FRACASO;
	char contenido[numbytes];
	memset(&contenido,valorbyte,numbytes);
	unsigned int ocupacion = UINTSZ + numbytes;
	fwrite(&ocupacion,UINTSZ,1,fp);
	fwrite(contenido,numbytes, 1, fp);
	fclose(fp);
	return EXITO;
}

char CreaFichero(char *filename, void *bloque, unsigned blsz)
{
	FILE *fp = fopen(filename, "wb");
	if(fp == NULL) return FRACASO;
	fwrite(bloque, blsz, 1, fp);
	fclose(fp);
	return EXITO;
}

char EjercicioP1_5(char *filename)
{
	FILE *fp = fopen(filename,"rb");
	if(fp == NULL)
	{
		printf("No se puede mostrar el archivo %s", filename);
		return FRACASO;
	}
	unsigned int ocupacion = 0;
	fread(&ocupacion, UINTSZ,1,fp);
	printf("El fichero ocupa: %d. Contenido:\n", ocupacion);
	char car[ocupacion-UINTSZ];
	fread(car,ocupacion-UINTSZ,1,fp);
	printf(car);
	fclose(fp);
	return EXITO;
}

char EscrituraSecuencial(unsigned int numbl)
{
	CABFTIPO cab;
	cab.blid = 0;
	cab.ocupacion = 1;
	CreaFichero("bloques.dat", &cab, BLSZ);
	FILE *fp = fopen("bloques.dat","wb");
	if(fp == NULL) return FRACASO;
	fseek(fp,BLSZ,SEEK_SET);
	BLTIPO bloque;
	unsigned int i;
	for(i = 1; i <= numbl ; i++)
	{
		bloque.blid = i;
		cab.ocupacion++;
		fwrite(&bloque,BLSZ,1,fp);
	}
	fseek(fp,0,SEEK_SET);
	fwrite(&cab,BLSZ,1,fp);
	fclose(fp);
	return EXITO;
}

char LecturaSecuencial(void)
{
	FILE *fp = fopen("bloques.dat", "rb");
	if(fp == NULL) return FRACASO;
	CABFTIPO cab;
	fread(&cab,BLSZ,1,fp);
	int i = 0;
	BLTIPO bloq;
	printf("Mosrando los identificadores(%d): ", cab.ocupacion-1);
	for(i=1;i<cab.ocupacion;i++)
	{
		fread(&bloq,BLSZ,1,fp);
		printf("%d - ", bloq.blid);
	}
	fclose(fp);
	return EXITO;
}

//Desordena el array Cards de enteros sin signo
//El segundo parámetro indica el número de elementos del array
void Permutacion (unsigned Cards[], unsigned Size) {
  unsigned int TopHalf, BottomHalf, NewIdx, i, NumToMove;
  unsigned int *NewDeck;
  NewDeck = (unsigned int *)malloc(Size * sizeof(unsigned int));
  NewIdx = 0;
  TopHalf = 0;
  BottomHalf = Size / 2;
  srand(time(0L)|getpid());
  while (TopHalf < Size / 2 || BottomHalf < Size) {
    if (rand() % 2) {
      NumToMove = (rand() % 3) + 1;
      for (i = 0; i < NumToMove && TopHalf < Size / 2; i++)
        NewDeck[NewIdx++] = Cards[TopHalf++];
      NumToMove = (rand() % 3) + 1;
      for (i = 0; i < NumToMove && BottomHalf < Size; i++)
        NewDeck[NewIdx++] = Cards[BottomHalf++];
    } else {
      NumToMove = (rand() % 3) + 1;
      for (i = 0; i < NumToMove && BottomHalf < Size; i++)
        NewDeck[NewIdx++] = Cards[BottomHalf++];
      NumToMove = (rand() % 3) + 1;
      for (i = 0; i < NumToMove && TopHalf < Size / 2; i++)
        NewDeck[NewIdx++] = Cards[TopHalf++];
    }
  }
  memcpy(Cards, NewDeck, sizeof(unsigned int) * Size);
  free(NewDeck);
}

char AccesoDirecto(void)
{
	FILE *fp = fopen("bloques.dat","rb");
	if(fp == NULL) return FRACASO;
	CABFTIPO cab;
	BLTIPO bloq;
	fread(&cab,BLSZ,1,fp);
	unsigned int ids[cab.ocupacion-1];
	int i;
	for(i = 0; i<=cab.ocupacion-1;i++) ids[i] = i+1;
	Permutacion(ids,cab.ocupacion-1);
	printf("\nLectura directa del fichero(%d): ",cab.ocupacion-1);
	for(i=1;i<=(cab.ocupacion-1)*0.8;i++)
	{
		fseek(fp,BLSZ*ids[i],SEEK_SET);
		fread(&bloq,BLSZ,1,fp);
		printf("%d - ", bloq.blid);
	}

	fclose(fp);
	return EXITO;
}

unsigned long FileSz(FILE *fp){
    fseek(fp,0L,SEEK_END);
    return (ftell(fp));
}

char LeeBloque(void *bl, unsigned blsz, unsigned long blid, FILE *fp)
{
	if(blid*blsz>=FileSz(fp)) return FRACASO;
	fseek(fp,blsz*blid,SEEK_SET);
	fread(bl,blsz,1,fp);
	return EXITO;
}

char EscribeBloque(void *bl, unsigned blsz, unsigned long blid, FILE *fp)
{
	if((blid)*blsz>FileSz(fp)) return FRACASO;
	fseek(fp,blsz*blid,SEEK_SET);
	fwrite(bl,blsz,1,fp);
	return EXITO;
}

char TestPrincipal(void){
    char sz;
    sz = sizeof(unsigned int);
    if (sz == UINTSZ) return EXITO;
    printf("\nError: declaración de UINTSZ");
    printf(" a %d modifíquela por %d", UINTSZ, sz);
    printf("Introduce un carácter para continuar...");
    scanf("%c",&sz);
    return FRACASO;
}

int main(void) {
	TestPrincipal();
	EjercicioP1_3("e1.dat",50,0x00);
	EjercicioP1_5("e1.dat");
	EscrituraSecuencial(5);
	LecturaSecuencial();
	AccesoDirecto();


	BLTIPO bloq;
	FILE *fp = fopen("bloques.dat","r+b");
	bloq.blid = 3;
	if(EscribeBloque(&bloq,BLSZ,3,fp)== FRACASO) printf("falló1");
	bloq.blid = 6;
	if(EscribeBloque(&bloq,BLSZ,6,fp)== FRACASO) printf("falló");
	if(EscribeBloque(&bloq,BLSZ,8,fp)== EXITO) printf("falló");
	if(LeeBloque(&bloq,BLSZ,5,fp) == FRACASO) printf("falló");
	if(LeeBloque(&bloq,BLSZ,0,fp) == FRACASO) printf("falló");
	if(LeeBloque(&bloq,BLSZ,6,fp) == FRACASO) printf("falló");
	if(LeeBloque(&bloq,BLSZ,7,fp) == EXITO) printf("falló");


	return 1;
}


