// SMPCacheDoc.cpp: implementaci�n de la clase CSMPCacheDoc
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


// Construcci�n o destrucci�n de CSMPCacheDoc

CSMPCacheDoc::CSMPCacheDoc()
{
	// TODO: agregar aqu� el c�digo de construcci�n �nico

}

CSMPCacheDoc::~CSMPCacheDoc()
{
}

BOOL CSMPCacheDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: agregar aqu� c�digo de reinicio
	// (los documentos SDI volver�n a utilizar este documento)

	return TRUE;
}




// Serializaci�n de CSMPCacheDoc

void CSMPCacheDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: agregar aqu� el c�digo de almacenamiento
	}
	else
	{
		// TODO: agregar aqu� el c�digo de carga
	}
}


// Diagn�sticos de CSMPCacheDoc

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
