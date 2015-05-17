#include "StdAfx.h"
#include "Procesador.h"

Procesador::Procesador(CString ficheroTraza)
{
	CStdioFile file;
	CString str;
	int i = 0;
	if(!file.Open(ficheroTraza, CFile::modeRead))
	{
		AfxMessageBox(_T("Error: No se ha conseguido abrir un archivo"));
		throw ("Archivo no encontrado");
	}
	LINEATRAZA aux;
	while(file.ReadString(str))
	{
		aux.tIns= ((TINSTRUCCION)_wtoi(str.Left(1)));
		aux.dirMem=wcstoul(str.Right(6),0,16);
		lineas.push(aux);
	}
	file.Close();
	

	/*Comprobacion, buena carga
	while(!lineas.empty())
	{
		char aux2[100];
		_itoa_s(lineas.front().dirMem,aux2,10);
		CString pooo(aux2);
		AfxMessageBox(pooo);
		lineas.pop();
	}*/
}

LINEATRAZA Procesador::getLinea()
{
	LINEATRAZA aux;
	aux.tIns = IVACIO;
	if(!lineas.empty())
	{
		aux = lineas.front();
		lineas.pop();
	}
	return aux;
}