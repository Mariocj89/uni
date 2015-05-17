// SMPCache.h: archivo de encabezado principal para la aplicación SMPCache
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"       // Símbolos principales


// CSMPCacheApp:
// Consulte la sección SMPCache.cpp para obtener información sobre la implementación de esta clase
//

class CSMPCacheApp : public CWinApp
{
public:
	CSMPCacheApp();


// Reemplazos
public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);

// Implementación
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSMPCacheApp theApp;