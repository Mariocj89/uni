#fichero Makefile

mozart : mozart.o lexico.o sonido.o
	g++ -omozart mozart.o lexico.o
	rm  -f  *.o lexico.c mozart.tab.c mozart.c mozart.h

lexico.o : lexico.c mozart.h
	g++ -olexico.o lexico.c -c

lexico.c : lexico.l
	flex -olexico.c lexico.l

mozart.o : mozart.c
	g++ -omozart.o mozart.c -c

mozart.c : mozart.y
	bison -d -omozart.c mozart.y

mozart.h : mozart.y
	bison -d -omozart.c mozart.y

clean : 
	rm  -f  *.o
