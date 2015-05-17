// SMPCache.cpp : define los comportamientos de las clases para la aplicación.
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
	// Comandos de documento estándar basados en archivo
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// Construcción de CSMPCacheApp

CSMPCacheApp::CSMPCacheApp()
{
	// TODO: agregar aquí el código de construcción,
	// Colocar toda la inicialización importante en InitInstance
}


// El único objeto CSMPCacheApp

CSMPCacheApp theApp;


// Inicialización de CSMPCacheApp

BOOL CSMPCacheApp::InitInstance()
{
	CWinApp::InitInstance();

	// Inicialización estándar
	// Si no utiliza estas características y desea reducir el tamaño
	// del archivo ejecutable final, debe quitar
	// las rutinas de inicialización específicas que no necesite
	// Cambie la clave del Registro en la que se almacena la configuración
	SetRegistryKey(_T("Practica SMPCache. Arquitectura de Computadores. Manuel y Mario."));
	LoadStdProfileSettings(4);  // Cargar opciones de archivo INI estándar (incluidas las de la lista MRU)
	// Registrar las plantillas de documento de la aplicación. Las plantillas de documento
	//  sirven como conexión entre documentos, ventanas de marco y vistas
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSMPCacheDoc),
		RUNTIME_CLASS(CMainFrame),       // Ventana de marco SDI principal
		RUNTIME_CLASS(CSMPCacheView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Habilitar apertura de ejecución DDE
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Analizar línea de comandos para comandos Shell estándar, DDE, Archivo Abrir
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Enviar comandos especificados en la línea de comandos. Devolverá FALSE si
	// la aplicación se inició con los modificadores /RegServer, /Register, /Unregserver o /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Se ha inicializado la única ventana; mostrarla y actualizarla
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// Llamar a DragAcceptFiles sólo si existe un sufijo
	//  En una aplicación SDI, esto debe ocurrir después de ProcessShellCommand
	// Habilitar apertura de arrastrar y colocar
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
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

// Comando de la aplicación para ejecutar el cuadro de diálogo
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