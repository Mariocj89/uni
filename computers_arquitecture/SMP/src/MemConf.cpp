// MemConf.cpp: archivo de implementación
//

#include "stdafx.h"
#include "SMPCache.h"
#include "MemConf.h"


// Cuadro de diálogo de MemConf

IMPLEMENT_DYNAMIC(MemConf, CDialog)

MemConf::MemConf(CWnd* pParent /*=NULL*/)
	: CDialog(MemConf::IDD, pParent)
	, ancho(0)
	, palabras(0)
	, bloques(0)
{

}

MemConf::~MemConf()
{
}

void MemConf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_Ancho, ancho);
	DDV_MinMaxInt(pDX, ancho, 8, 64);
	DDX_CBIndex(pDX, IDC_Palabras, palabras);
	DDV_MinMaxInt(pDX, palabras, 1, 1024);
	DDX_CBIndex(pDX, IDC_Bloques, bloques);
	DDV_MinMaxInt(pDX, bloques, 1, 32768);
}


BEGIN_MESSAGE_MAP(MemConf, CDialog)
END_MESSAGE_MAP()


// Controladores de mensajes de MemConf
