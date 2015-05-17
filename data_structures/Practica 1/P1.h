/*
 * P1.h
 *
 *  Created on: 19/10/2009
 *      Author: Mario
 */

#ifndef P1_H_
#define P1_H_

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
// Algunas constantes útiles
#define UINTSZ 4 //Tamaño del unsigned int
#define EXITO 1
#define FRACASO 0
#define BLSZ 1024
#define MAXBLNUM 4096 //Número máximo de bloques del fichero

typedef struct {
   unsigned int blid;
   char datos_bl[BLSZ - UINTSZ];
} BLTIPO;

typedef struct {
   unsigned int blid;
   unsigned int ocupacion;
   char extra_info[BLSZ - 2*UINTSZ];
} CABFTIPO;

char EjercicioP1_1(void);
char EjercicioP1_2(void);
char EjercicioP1_3(char *filename, unsigned numbytes, char valorbyte);
char CreaFichero(char *filename, void *bloque, unsigned blsz);
char EjercicioP1_5(char *filename);
char EscrituraSecuencial(unsigned int numbl);
char LecturaSecuencial(void);
char AccesoDirecto(void);
char LeeBloque(void *bl, unsigned blsz, unsigned long blid, FILE *fp);

#endif /* P1_H_ */
