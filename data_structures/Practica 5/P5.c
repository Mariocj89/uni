/*
 ============================================================================
 Name        : P5.c
 Author      : Mario
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "P5.h"


CABFILET Cabdat;
FILE *Fd;

FECHAT TraduceFecha (char *fuente)
{
 char *ptr;
 int offset = 0, i, size;
 char campo[2][3];
 int parte[2];
 FECHAT resul;

 for (i=0;i<2;i++){
        ptr = strchr(fuente+offset, '/');
        size = ptr - (fuente+offset);
        memmove(campo[i],fuente+offset,size);
        campo[i][size] = '\0';
        parte[i] = atoi(campo[i]);
        offset += size+1;
        };
 resul.dia = parte[0];
 resul.mes = parte[1];
 resul.anio = atoi(fuente+offset);
 return resul;
}

char ObtenSgteReg (FILE *fd, REGT *reg)
// Interpreta la siguiente l¡nea del fichero fd, almacenando el contenido
// en el par metro reg. La funci¢n retorna un valor positivo si se hizo
// correctamente y un valor 0 en caso en que no hubiera m s l¡neas por
// interpretar.
{
 char *ptr;
 int offset, size, i;
 char linea[255];
 char campo[80];

 if (!fgets(linea,255,fd)) return 0;
 offset = 0;
 for (i=0;i<6;i++){
         ptr = strchr(linea+offset, ';');
         if (ptr) size = ptr - (linea+offset);
         else size=strlen(linea+offset)-1;
         memmove(campo,linea+offset,size);
         campo[size] = '\0';
         offset += size + 1;
         switch (i){
                case 0 : strcpy(reg->codcli, campo);break;
                case 1 : reg->idpedido = atoi(campo);break;
                case 2 : strcpy(reg->nombre, campo);break;
                case 3 : strcpy (reg->ciudad, campo);break;
                case 4 : reg->fecha = TraduceFecha(campo);break;
                case 5 : reg->importe = atof (campo);break;
                }
         }
 return EXITO;
}

char ObtenSgteTr(FILE *fd, char *trcode, REGT *reg)
{
 char *ptr;
 int offset, size, i;
 char linea[255]; // Linea del fichero texto
 char campo[80];

 memset(reg,0x0,REGSZ);
 if (!fgets(linea,255,fd)) return FRACASO;
 sscanf(linea,"%c;",trcode);
 //En función del tipo de trans, actuamos
 switch(*trcode){
     case 'a':
        offset = 2;
                for (i=0;i<6;i++){
                ptr = strchr(linea+offset, ';');
                if (ptr) size = ptr - (linea+offset);
                else size=strlen(linea+offset)-1;
                memmove(campo,linea+offset,size);
                campo[size] = '\0';
                offset += size + 1;
                switch (i){
                case 0 : strcpy(reg->codcli, campo);break;
                case 1 : reg->idpedido = atoi(campo);break;
                case 2 : strcpy(reg->nombre, campo);break;
                case 3 : strcpy (reg->ciudad, campo);break;
                case 4 : reg->fecha = TraduceFecha(campo);break;
                case 5 : reg->importe = atof (campo);break;
                }
         }
        break;
     case 's':
     case 'b':
         sscanf(linea,"%c;%d",trcode,&(reg->idpedido));
         break;
     }
 return EXITO;
}

char EscribePagina (void *pag, long pgsz, unsigned pagid, FILE *fd){
 unsigned long byte_offset, byte_offset_eof;

 byte_offset  = pagid;
 byte_offset *= pgsz;
 fseek(fd,0L,SEEK_END);
 byte_offset_eof = ftell(fd);
 if (byte_offset>byte_offset_eof){
                printf("Byte_offset incorrecto\n");
                exit(1);
                }
 fseek (fd, byte_offset, SEEK_SET);
 fwrite(pag,pgsz,1,fd);
 return EXITO;
}

char LeePagina (void *pag, long pgsz, unsigned pagid, FILE *fd){

 unsigned long byte_offset, byte_offset_eof;

 byte_offset  = pagid;
 byte_offset *= pgsz;
 fseek(fd,0L,SEEK_END);
 byte_offset_eof = ftell(fd);
 if (byte_offset>=byte_offset_eof){
                printf("Byte_offset incorrecto\n");
                exit(1);
                }
 fseek (fd, byte_offset, SEEK_SET);
 fread(pag,pgsz,1,fd);
 return EXITO;
}

char CierreSistema(void){
        fseek(Fd,0L,SEEK_SET);
        fwrite(&Cabdat,PAGSZ,1,Fd);
        fclose(Fd);
        return EXITO;
}

void ActivaBit(unsigned char *bitv, unsigned numbits, unsigned bit)
{
        if (numbits <= bit) return; //bit fuera del rango
        bitv[EN_BYTE(bit)] |= MASCARA_BYTE(bit);
}

void DesactivaBit(unsigned char *bitv, unsigned numbits, unsigned bit)
// Desactiva el bit del bitvector. El parámetro bit es un contador
// basado en 0.
{
 unsigned char mask;;

        if (numbits <= bit) return; //bit fuera del rango
        mask = MASCARA_BYTE(bit);
        mask = ~mask;
        bitv[EN_BYTE(bit)] &= mask;
}

unsigned char ValorBit(unsigned char *bitv, unsigned numbits, unsigned bit)
//Retorna el valor del bit indicado
{
                if (numbits <= bit) return ERRFUERADERANGO; //bit fuera del rango
                if (bitv[EN_BYTE(bit)] & MASCARA_BYTE(bit)) return 1;
                return 0;
}

char EsBitActivo (unsigned char *bitv, unsigned numbits, unsigned bit)
{

        if (numbits <= bit) return ERRFUERADERANGO; //bit fuera del rango
        return (bitv[EN_BYTE(bit)] & MASCARA_BYTE(bit));
}

unsigned PrimerBitNoActivo (unsigned char *bitv, unsigned numbits)
// Retorna la posici¢n del primer bit en bitvector que se encuentre a 0.
{
 unsigned i;
 unsigned char b=0;

 //Buscamos el primer byte con algún bit a cero
 for(i=0;i<BYTES_BITVECTOR(numbits) && bitv[i]==UNOCHAR;i++);

 //Si todos estan a 1 retornamos numbits
 if(i==BYTES_BITVECTOR(numbits)) return numbits; //Todos activos

 //El byte en que nos encontramos tiene algún bit a cero, lo buscamos
//Si el bit más significativo está a cero, su complemento tiene dicho bit a 1
//por tanto su valor es mayor o igual a 128...
 b = ~bitv[i];
 if (b >= 128) return (i*BYTESZ);
 if (b >= 64) return (1 + i*BYTESZ);
 if (b >= 32) return (2 + i*BYTESZ);
 if (b >= 16) return (3 + i*BYTESZ);
 if (b >= 8) return (4 + i*BYTESZ);
 if (b >= 4) return (5 + i*BYTESZ);
 if (b >= 2) return (6 + i*BYTESZ);
 return (7 + i*BYTESZ);
}

unsigned PrimerBitActivo (unsigned char *bitv, unsigned numbits)
// Retorna la posici¢n del primer bit en bitvector que se encuentre a 1.
{
 unsigned i;

 for(i=0;i<BYTES_BITVECTOR(numbits) && bitv[i]==0;i++);
 if(i==BYTES_BITVECTOR(numbits)) return numbits; //Todos inactivos
 if (bitv[i]>= 128) return (i*BYTESZ);
 if (bitv[i]>= 64) return (1 + i*BYTESZ);
 if (bitv[i]>= 32) return (2 + i*BYTESZ);
 if (bitv[i]>= 16) return (3 + i*BYTESZ);
 if (bitv[i]>= 8) return (4 + i*BYTESZ);
 if (bitv[i]>= 4) return (5 + i*BYTESZ);
 if (bitv[i]>= 2) return (6 + i*BYTESZ);
 return (7 + i*BYTESZ);
}

unsigned NBAChar(unsigned char c)
//Cuenta el número de bits activos en un byte
{
        unsigned char B[3]={0x55,0x33,0x0F}; //Números mágicos
        unsigned char S[3] = {1,2,4};//Potencias de 2
        unsigned result = c;

        result = ((result >> S[0]) & B[0]) + (result & B[0]);
        result = ((result >> S[1]) & B[1]) + (result & B[1]);
        result = ((result >> S[2]) & B[2]) + (result & B[2]);
        return result;
}

unsigned NumeroBitsActivos (unsigned char *bitv, unsigned numbits)
// Retorna el número de bits activos en el bitvector.
{
 unsigned i,n = 0;

 for (i=0;i<BYTES_BITVECTOR(numbits);i++) //Para cada byte
    n += NBAChar(bitv[i]); //Cuenta los bits activos
 return n;
}

char EsPrimo(unsigned long val){
        unsigned long i;
        if( (val==1) | (val==2) | (val==3) ) return EXITO;
        for(i=2;i<sqrt(val);i++)
                if(!(val%i)) return FRACASO;
        return EXITO;
}

//******Cálculo del primo más cercano por exceso a un entero dado
unsigned long PrimoMasCercano(unsigned long val){
        unsigned long sgte=val;
        //Comenzamos siempre por un impar
        if (sgte % 2 == 0) sgte++;
        while (!EsPrimo(sgte)){
                sgte +=2; //Buscamos impares
                //Ciudado con sobrepasar el límite del tipo!
                if (sgte < val ) {
                        printf("El primo más cercano no cabe en un tipo unsigned long");
                        exit(1);
                }
        }
        return sgte;
}

unsigned long Hash(unsigned clave){
        return (clave % (Cabdat.ocupacion-1)) + 1;
}

char SlotBorrado(PAGT *pag, unsigned slot){
        return(EsBitActivo(pag->bitv,NRP,slot));
}

char *RegistroAString(REGT reg)
{
// Toma un registro y convierte sus datos a un formato visible
// incluyendolo en una cadena de caracteres
 char *linea;

 linea = (char *) malloc (255);
 sprintf(linea,"%.5s;%d;%s;%s;%d/%d/%d;%.4f",reg.codcli,\
        reg.idpedido,reg.nombre,reg.ciudad,reg.fecha.dia,\
        reg.fecha.mes,reg.fecha.anio,reg.importe);
 return linea;
}

/*************************************************/
/**             IMPLEMENTACION PROPIA           **/
/*************************************************/

char CreaFicheroHash(void)
{
    CABFILET cab;
    PAGT pag;
    memset(&pag,0x0,PAGSZ);
    memset(&cab,0x0,PAGSZ);
    strcpy(cab.filename,NOMFICH_DAT);
    //cab.nregactivos = 0
    unsigned long nh =(unsigned long) ceil(MAXNUMREG/FACTORCARGA);//Hayamos el numero de huecos a priori
    unsigned int np =(unsigned int) ceil(nh/(double)NRP);//Hayamos el numero de paginas a priori
    cab.ocupacion = PrimoMasCercano(np)+1;//el numero de pagina realmente es el proximo primo
    //cab.pagid = 0;
    cab.pagsz = PAGSZ;
    cab.regsz = REGSZ;
    FILE *fd = fopen(NOMFICH_DAT,"wb");
    if(fd == NULL) return FRACASO;
    EscribePagina(&cab,PAGSZ,0,fd);
    int i;
    for(i = 1;i<cab.ocupacion;i++){
      pag.pagid = i;
      EscribePagina(&pag,PAGSZ,i,fd);
    }
    fclose(fd);
    return EXITO;
}

char AperturaSistema(void)
{
     Fd = fopen(NOMFICH_DAT,"r+b");
     if(Fd == NULL){
       if(CreaFicheroHash() == FRACASO) return FRACASO;
       Fd = fopen(NOMFICH_DAT,"r+b");
       if(Fd == NULL) return FRACASO;
     }
     LeePagina(&Cabdat, PAGSZ,0,Fd);
     return EXITO;
}

char BuscaRegEnPag(unsigned idpedido, PAGT *pag, unsigned *pos,char *lapida)
{
     unsigned i;
     for(i = 0;i<pag->ocupacion;i++){
       if(SlotBorrado(pag,i)){
         *lapida = EXITO;
       }
       else if(pag->reg[i].idpedido == idpedido){
         *pos = i;
         return EXITO;
       }
     }
     return FRACASO;
}

char BuscaRegistro(unsigned idpedido, REGT *reg, unsigned *pagid,
          char *lapida, unsigned *intentos)
{
     int condicion = 1, pos;
     *intentos = 0;
     char sublapida = *lapida = FRACASO;
     PAGT pag;
     long i,inicio = i = Hash(idpedido);
     do{
       LeePagina(&pag,PAGSZ,i,Fd);
       (*intentos)++;
       if(BuscaRegEnPag(idpedido,&pag,&pos,&sublapida) == EXITO){//Encontramos el registro
         *reg = pag.reg[pos];
         *pagid = i;
         return EXITO;
       }
       if(*lapida == FRACASO && sublapida == EXITO){//Encontramos una lapida
         *lapida = sublapida;
         *pagid = pag.pagid;
       }
       condicion = condicion && (pag.ocupacion == NRP);//Si una pagina no esta llena, termnamos
       i = (i%(Cabdat.ocupacion-1))+1;//vamos a la siguiente pagina
       condicion = condicion && (i != inicio);//si hemos dado una vuelva terminamos
     }while(condicion);
     if(*lapida == FRACASO) *pagid = i-1;//Guardamos la pagina donde hemos encontrado el primer hueco
     if(*pagid == 0) *pagid = Cabdat.ocupacion-1; //Tenemos que controlar que pagid no sea 0(al haberle restado 1 antes.
     return FRACASO;
}

char InsertaRegistro(REGT reg)
{
     unsigned long nh =(unsigned long) ceil(MAXNUMREG/FACTORCARGA);//Hayamos el numero de huecos a priori
     unsigned pagid, intentos, primlapida;
     char lapida = FRACASO;
     PAGT pag;
     if(Cabdat.nregactivos == nh) return FICHEROLLENO;
     if(BuscaRegistro(reg.idpedido,&reg,&pagid,&lapida,&intentos) == EXITO) return FRACASO;//Uso aqui reg, puesto que solo se va a modificar en caso de que el registro se encuentro, caso en el cual dejaria de ser util su anterior valor
     if(lapida == EXITO){//Hemos encontrado una lapida donde insertar
       LeePagina(&pag, PAGSZ, pagid,Fd);
       primlapida = PrimerBitActivo(pag.bitv,NRP);//Obtenemos la primera lapida
       pag.reg[primlapida] = reg;
       DesactivaBit(pag.bitv,NRP,primlapida);//Desmarcamos como lapida
       EscribePagina(&pag,PAGSZ,pagid,Fd);
       Cabdat.nregactivos++;
       return EXITO;
     }
     //Si no hay lapidas donde insertar, insertamos en la ultima pagina de desbordamiento
     LeePagina(&pag, PAGSZ, pagid,Fd);
     pag.reg[pag.ocupacion] = reg;
     pag.ocupacion++;
     EscribePagina(&pag,PAGSZ,pagid,Fd);
     Cabdat.nregactivos++;
     return EXITO;
}

char BorraRegistro(unsigned idpedido)
{
     unsigned intentos, pagid,pos;
     REGT reg;
     PAGT pag;
     char lapida;//no lo vamos a usar, es auxiliar para la sig funcion
     if(BuscaRegistro(idpedido,&reg,&pagid,&lapida,&intentos) != EXITO) return FRACASO;
     LeePagina(&pag,PAGSZ,pagid,Fd);
     BuscaRegEnPag(idpedido,&pag,&pos,&lapida);
     ActivaBit(pag.bitv,NRP,pos);
     Cabdat.nregactivos--;
     EscribePagina(&pag,PAGSZ,pagid,Fd);
     return EXITO;
}

char CargaFicheroHash(void)
{
     if(AperturaSistema() == FRACASO) return FRACASO;
     FILE * ftext = fopen(NOMFICH_FTE,"rt");
     FILE * flog = fopen(NOMFICH_LOG,"wt");
     if(ftext == NULL) return FRACASO;
     REGT reg;
     int exitos = 0, fracasos = 0;
     while(ObtenSgteReg(ftext,&reg))
       {
         if(InsertaRegistro(reg) == EXITO){
           exitos++;
          // fprintf(flog,"Se ha insertado correctamente el registro con clave %d\n", reg.idpedido);
         }
         else {
           fracasos++;
           fprintf(flog,"Error al insertar el registro con clave %d\n", reg.idpedido);
         }
       }
     fprintf(flog, "Se insertaron un total de %d nuevos registros\n",exitos);
     printf("Se han insertado correctamente %d registro y han fracasado %d\n",exitos,fracasos);
     fclose(ftext);
     fclose(flog);
     CierreSistema();
     return EXITO;
}

void ProcesaTrans(void)
{
    FILE *ftr, *fl;
    char trcode=0x0;
    REGT reg;
    char res;
    unsigned aux1, aux2;
    char aux3;
    unsigned count[3]={0,0,0}; //Contador transacciones

        fl = fopen(NOMFICH_LOG,"at");
        if(fl == NULL){
          printf("Imposible acceder al fichero log.");
          exit(-1);
        }

        AperturaSistema();

    ftr = fopen(NOMFICH_TRA,"rt");
    if(ftr == NULL){
      printf("Imposible acceder al fichero de transacciones.");
      exit(-1);
    }
    printf("\nProcesando transacciones");
    fprintf(fl,"------------------INICIO PROCESO TRANSACCIONES--------------\n");
    while (ObtenSgteTr(ftr, &trcode,&reg)){
        printf(".");
        switch(trcode){
            case 'a':
                res =  InsertaRegistro(reg);
                if (res == EXITO){
                                        fprintf(fl,"Se insertó el registro con clave %d\n",reg.idpedido);
                                        count[0]++;
                }
                else
                  fprintf(fl,"Clave duplicada %d\n",reg.idpedido);
                break;
            case 's':
                res = BuscaRegistro(reg.idpedido,&reg,&aux1,&aux3,&aux2);
                if (res == FRACASO)
                                                fprintf(fl,"Clave inexistente, búsqueda fallida %d\n",reg.idpedido);
                                else {
                                                fprintf(fl,"Se localizó el registro con clave %d: %s\n",reg.idpedido,RegistroAString(reg));
                                                count[1]++;
                                }
                break;
            case 'b':
                res = BorraRegistro(reg.idpedido);
                if(res == FRACASO)
                  fprintf(fl,"Clave inexistente, borrado fallido %d\n",reg.idpedido);
                else {
                  fprintf(fl,"Se borró el registro con clave %d\n",reg.idpedido);
                  count[2]++;
                }
        }
    }//Fin while
    printf("\nFin de proceso.");
    fprintf(fl,"\nSe han realizado un total de %d transacciones con éxito:\n",count[0]+count[1]+count[2]);
    fprintf(fl,"\n%d inserciones, %d borrados y %d búsquedas\n",count[0],count[2],count[1]);
    fprintf(fl,"------------------ FIN PROCESO TRANSACCIONES --------------\n");
    fclose(ftr);
    printf("La longitud media de busqueda es: %f\n", LongitudMediaBusqueda());
    CierreSistema();
        fprintf(fl,"Sistema cerrado\n");
        fclose(fl);
}

float LongitudMediaBusqueda()
{
    REGT regaux;
    PAGT pag;
    int i, j,numreg = 0, intentos, sumintentos = 0, aux;
    char caux;
    for( i = 1; i < Cabdat.ocupacion; i++){
      LeePagina(&pag, PAGSZ, i, Fd);
      for(j = 0; j < pag.ocupacion; j++){
        if(!SlotBorrado(&pag,j)){//cogemos un registro
          BuscaRegistro(pag.reg[j].idpedido,&regaux,&aux,&caux, &intentos);
          sumintentos += intentos;
          numreg++;
        }
      }
    }
    return (double)sumintentos/(double) numreg;
}

int main(void) {
	CargaFicheroHash();
	ProcesaTrans();
	return EXIT_SUCCESS;
}
