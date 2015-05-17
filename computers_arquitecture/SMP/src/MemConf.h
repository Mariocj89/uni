#pragma once


// Cuadro de di�logo de MemConf

class MemConf : public CDialog
{
	DECLARE_DYNAMIC(MemConf)

public:
	MemConf(CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~MemConf();

// Datos del cuadro de di�logo
	enum { IDD = IDD_MEMCONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	// Ancho de palabra en bits
	int ancho;
	//Palabras en un bloque
	int palabras;
	// Bloques de memoria
	int bloques;
};
