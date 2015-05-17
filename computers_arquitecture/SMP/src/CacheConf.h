#pragma once
#include "afxwin.h"


// Cuadro de di�logo de CacheConf

class CacheConf : public CDialog
{
	DECLARE_DYNAMIC(CacheConf)

public:
	CacheConf(CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~CacheConf();

// Datos del cuadro de di�logo
	enum { IDD = IDD_CACHE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	// Bloques en cache
	int bCaches;
	// Funcion correspondencia
	CString funcion;
	// Numero de Conjuntos
	int conjuntos;
	// Algoritmo de remplazamiento
	CString algoritmo;
	// Control del combobox para los bloques de cache
	CComboBox CBCaches;
};
