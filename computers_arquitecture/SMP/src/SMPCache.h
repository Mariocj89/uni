// SMPCache.h: archivo de encabezado principal para la aplicaci�n SMPCache
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"       // S�mbolos principales


// CSMPCacheApp:
// Consulte la secci�n SMPCache.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CSMPCacheApp : public CWinApp
{
public:
	CSMPCacheApp();


// Reemplazos
public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);

// Implementaci�n
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSMPCacheApp theApp;