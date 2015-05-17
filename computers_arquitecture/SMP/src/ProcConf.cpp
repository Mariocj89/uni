// ProcConf.cpp: archivo de implementación
//

#include "stdafx.h"
#include "SMPCache.h"
#include "ProcConf.h"


// Cuadro de diálogo de ProcConf

IMPLEMENT_DYNAMIC(ProcConf, CDialog)

ProcConf::ProcConf(CWnd* pParent /*=NULL*/)
	: CDialog(ProcConf::IDD, pParent)
	, NumProc(0)
	, ProtCache(_T(""))
{
}

ProcConf::~ProcConf()
{
}

void ProcConf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NumProc, NumProc);
	DDV_MinMaxInt(pDX, NumProc, 1, 8);
	DDX_CBString(pDX, IDC_PCache, ProtCache);
	DDV_MaxChars(pDX, ProtCache, 7);
}


BEGIN_MESSAGE_MAP(ProcConf, CDialog)
	ON_CBN_SELCHANGE(IDC_NumProc, &ProcConf::OnCbnSelchangeNumproc)
END_MESSAGE_MAP()


// Controladores de mensajes de ProcConf

void ProcConf::OnCbnSelchangeNumproc()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
}
