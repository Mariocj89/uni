// SMPCacheDoc.h: interfaz de la clase CSMPCacheDoc
//


#pragma once


class CSMPCacheDoc : public CDocument
{
protected: // Crear s�lo a partir de serializaci�n
	CSMPCacheDoc();
	DECLARE_DYNCREATE(CSMPCacheDoc)

// Atributos
public:

// Operaciones
public:

// Reemplazos
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementaci�n
public:
	virtual ~CSMPCacheDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignaci�n de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()
};


