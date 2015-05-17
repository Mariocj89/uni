#ifndef AREAMAN_H
#define AREAMAN_H

#include "area.h"

class AreaMan: public Area{
public:
	AreaMan(Posicion inicio, int largo, int alto, char titulo[]);
	AreaMan(int iniciox,int inicioy, int largo, int alto, char titulo[]);

protected:
	void SaltoDeLinea();

};


#endif //areaman_h