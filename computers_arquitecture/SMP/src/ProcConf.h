#pragma once


// Cuadro de di�logo de ProcConf

class ProcConf : public CDialog
{
	DECLARE_DYNAMIC(ProcConf)

public:
	ProcConf(CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~ProcConf();

// Datos del cuadro de di�logo
	enum { IDD = IDD_PROCCONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeNumproc();
	// Numero de procesadores
	int NumProc;
	// Protocolo de coherencia cache
	CString ProtCache;
	CString ArbBus;
};
