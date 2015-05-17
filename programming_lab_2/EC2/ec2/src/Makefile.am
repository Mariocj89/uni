bin_PROGRAMS = ec2
ec2_SOURCES = cargador.cpp celda.cpp ec2.cpp errornumerollaves.cpp \
	errorpuerta.cpp errortamanio.cpp fichero.cpp genaleatorios.cpp grafo.cpp llave.cpp \
	planta.cpp prision.cpp puerta.cpp registro.cpp testarbol.cpp testcelda.cpp \
	testcolagen.cpp testgrafo.cpp testllave.cpp testplanta.cpp testprision.cpp \
	testpuerta.cpp

# set the include path found by configure
INCLUDES= $(all_includes)

# the library search path.
ec2_LDFLAGS = $(all_libraries) 
noinst_HEADERS = arbol.h celda.h colagen.h errornumerollaves.h errorpuerta.h \
	errortamanio.h genaleatorios.h grafo.h llave.h planta.h prision.h puerta.h registro.h
ec2_LDADD = /home/Mario/Escritorio/ec2/src/gtest.a
