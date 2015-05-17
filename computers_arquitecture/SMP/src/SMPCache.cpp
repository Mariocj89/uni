// SMPCache.cpp : define los comportamientos de las clases para la aplicaci�n.
//

#include "stdafx.h"
#include "SMPCache.h"
#include "MainFrm.h"

#include "SMPCacheDoc.h"
#include "SMPCacheView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSMPCacheApp

BEGIN_MESSAGE_MAP(CSMPCacheApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CSMPCacheApp::OnAppAbout)
	// Comandos de documento est�ndar basados en archivo
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// Construcci�n de CSMPCacheApp

CSMPCacheApp::CSMPCacheApp()
{
	// TODO: agregar aqu� el c�digo de construcci�n,
	// Colocar toda la inicializaci�n importante en InitInstance
}


// El �nico objeto CSMPCacheApp

CSMPCacheApp theApp;


// Inicializaci�n de CSMPCacheApp

BOOL CSMPCacheApp::InitInstance()
{
	CWinApp::InitInstance();

	// Inicializaci�n est�ndar
	// Si no utiliza estas caracter�sticas y desea reducir el tama�o
	// del archivo ejecutable final, debe quitar
	// las rutinas de inicializaci�n espec�ficas que no necesite
	// Cambie la clave del Registro en la que se almacena la configuraci�n
	SetRegistryKey(_T("Practica SMPCache. Arquitectura de Computadores. Manuel y Mario."));
	LoadStdProfileSettings(4);  // Cargar opciones de archivo INI est�ndar (incluidas las de la lista MRU)
	// Registrar las plantillas de documento de la aplicaci�n. Las plantillas de documento
	//  sirven como conexi�n entre documentos, ventanas de marco y vistas
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSMPCacheDoc),
		RUNTIME_CLASS(CMainFrame),       // Ventana de marco SDI principal
		RUNTIME_CLASS(CSMPCacheView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Habilitar apertura de ejecuci�n DDE
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Analizar l�nea de comandos para comandos Shell est�ndar, DDE, Archivo Abrir
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Enviar comandos especificados en la l�nea de comandos. Devolver� FALSE si
	// la aplicaci�n se inici� con los modificadores /RegServer, /Register, /Unregserver o /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Se ha inicializado la �nica ventana; mostrarla y actualizarla
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// Llamar a DragAcceptFiles s�lo si existe un sufijo
	//  En una aplicaci�n SDI, esto debe ocurrir despu�s de ProcessShellCommand
	// Habilitar apertura de arrastrar y colocar
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// Cuadro de di�logo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Datos del cuadro de di�logo
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementaci�n
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// Comando de la aplicaci�n para ejecutar el cuadro de di�logo
void CSMPCacheApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


BOOL CSMPCacheApp::OnIdle(LONG lCount)
{
	CSMPCacheView* miVista = (CSMPCacheView *) m_pMainWnd->GetWindow(GW_CHILD);
	if(miVista->enEjecucion && !miVista->enPausa)
	{
		if(!miVista->realizarIteracion())delete Bus::getInstancia();
	}		
	return TRUE;
}