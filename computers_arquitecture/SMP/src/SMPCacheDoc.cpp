// SMPCacheDoc.cpp: implementación de la clase CSMPCacheDoc
//

#include "stdafx.h"
#include "SMPCache.h"

#include "SMPCacheDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSMPCacheDoc

IMPLEMENT_DYNCREATE(CSMPCacheDoc, CDocument)

BEGIN_MESSAGE_MAP(CSMPCacheDoc, CDocument)
END_MESSAGE_MAP()


// Construcción o destrucción de CSMPCacheDoc

CSMPCacheDoc::CSMPCacheDoc()
{
	// TODO: agregar aquí el código de construcción único

}

CSMPCacheDoc::~CSMPCacheDoc()
{
}

BOOL CSMPCacheDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: agregar aquí código de reinicio
	// (los documentos SDI volverán a utilizar este documento)

	return TRUE;
}




// Serialización de CSMPCacheDoc

void CSMPCacheDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: agregar aquí el código de almacenamiento
	}
	else
	{
		// TODO: agregar aquí el código de carga
	}
}


// Diagnósticos de CSMPCacheDoc

#ifdef _DEBUG
void CSMPCacheDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSMPCacheDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Comandos de CSMPCacheDoc
