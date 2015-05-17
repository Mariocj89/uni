// SMPCacheDoc.h: interfaz de la clase CSMPCacheDoc
//


#pragma once


class CSMPCacheDoc : public CDocument
{
protected: // Crear sólo a partir de serialización
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

// Implementación
public:
	virtual ~CSMPCacheDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignación de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()
};


