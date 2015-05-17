// acheConf.cpp: archivo de implementación
//

#include "stdafx.h"
#include "SMPCache.h"
#include "CacheConf.h"


// Cuadro de diálogo de CacheConf

IMPLEMENT_DYNAMIC(CacheConf, CDialog)

CacheConf::CacheConf(CWnd* pParent /*=NULL*/)
	: CDialog(CacheConf::IDD, pParent)
	, bCaches(0)
	, funcion(_T(""))
	, conjuntos(0)
	, algoritmo(_T(""))
{

}

CacheConf::~CacheConf()
{
}

void CacheConf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_BCaches, bCaches);
	DDV_MinMaxInt(pDX, bCaches, 1, 512);
	DDX_CBString(pDX, IDC_Funcion, funcion);
	DDX_CBIndex(pDX, IDC_Conjuntos, conjuntos);
	DDV_MinMaxInt(pDX, conjuntos, 1, 512);
	DDX_CBString(pDX, IDC_Algoritmo, algoritmo);
	DDX_Control(pDX, IDC_BCaches, CBCaches);
}


BEGIN_MESSAGE_MAP(CacheConf, CDialog)
END_MESSAGE_MAP()


// Controladores de mensajes de CacheConf
