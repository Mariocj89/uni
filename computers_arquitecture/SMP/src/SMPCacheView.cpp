// SMPCacheView.cpp: implementación de la clase CSMPCacheView
//

#include "stdafx.h"
#include "SMPCache.h"

#include "SMPCacheDoc.h"
#include "SMPCacheView.h"

#include "ProcConf.h"
#include "MemConf.h"
#include "CacheConf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSMPCacheView

IMPLEMENT_DYNCREATE(CSMPCacheView, CFormView)

BEGIN_MESSAGE_MAP(CSMPCacheView, CFormView)
	ON_COMMAND(ID_FILE_OPEN, &CSMPCacheView::OnFileOpen)
	ON_COMMAND(ID_OPCIONES_CONFIGURARMULTIPROCESADOR, &CSMPCacheView::OnOpcionesConfigurarmultiprocesador)
	ON_COMMAND(ID_OPCIONES_MEMORIA, &CSMPCacheView::OnOpcionesMemoria)
	ON_COMMAND(ID_OPCIONES_CACHES, &CSMPCacheView::OnOpcionesCaches)
	ON_BN_CLICKED(IDC_BIniciar, &CSMPCacheView::OnBnClickedBiniciar)
	ON_BN_CLICKED(IDC_BPausa, &CSMPCacheView::OnBnClickedBpausa)
	ON_BN_CLICKED(IDC_BDetener, &CSMPCacheView::OnBnClickedBCompleta)
	ON_BN_CLICKED(IDC_BSalir, &CSMPCacheView::OnBnClickedBsalir)
	ON_EN_CHANGE(IDC_STEPS, &CSMPCacheView::OnEnChangeSteps)
END_MESSAGE_MAP()

// Construcción o destrucción de CSMPCacheView

CSMPCacheView::CSMPCacheView()
	: CFormView(CSMPCacheView::IDD)
	, steps(1)
{
	enEjecucion = false;
	enPausa = false;
	Bus::getInstancia()->fallos = 0;
	Bus::getInstancia()->aciertos = 0;
	Bus::getInstancia()->numTranEstado = 0;
	Bus::getInstancia()->numBloqTrans = 0;
	Bus::getInstancia()->numTransBus = 0;
	// TODO: agregar aquí el código de construcción
	procn = 8;
	for(int i = 0 ; i<8; i++)
	{
		fParriba[i] = false;
		fCIarriba[i] = false;
		fCDarriba[i] = false;
	}

}

CSMPCacheView::~CSMPCacheView()
{
}

void CSMPCacheView::iniciarSimulacion()
{
	for(int i =0 ;i <procn;i++)
	{
		Bus::getInstancia()->indicarProtocoloArbitracion(arbitracion);
		if(!fTrazas[i].IsEmpty()) 
		{
			new Cache(i,bloqCache,fcorrespondencia,nConjuntos,aremplazamiento,protocolo,bloqMemoria,palabrasBloque,fTrazas[i]);
		}
	}
	char cadena[10];
	_itoa_s(1,cadena,10);
	TSteps.SetWindowTextW((CString)cadena);
}

void CSMPCacheView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IMG_Proc1, proc[0]);
	DDX_Control(pDX, IMG_Proc2, proc[1]);
	DDX_Control(pDX, IMG_Proc3, proc[2]);
	DDX_Control(pDX, IMG_Proc4, proc[3]);
	DDX_Control(pDX, IMG_Proc5, proc[4]);
	DDX_Control(pDX, IMG_Proc6, proc[5]);
	DDX_Control(pDX, IMG_Proc7, proc[6]);
	DDX_Control(pDX, IMG_Proc8, proc[7]);
	DDX_Control(pDX, FLE_Proc1, flechasCI[0]);
	DDX_Control(pDX, FLE_Proc2, flechasCI[1]);
	DDX_Control(pDX, FLE_Proc3, flechasCI[2]);
	DDX_Control(pDX, FLE_Proc4, flechasCI[3]);
	DDX_Control(pDX, FLE_Proc5, flechasCI[4]);
	DDX_Control(pDX, FLE_Proc6, flechasCI[5]);
	DDX_Control(pDX, FLE_Proc7, flechasCI[6]);
	DDX_Control(pDX, FLE_Proc8, flechasCI[7]);
	DDX_Control(pDX, FLE_Proc9, flechasproc[0]);
	DDX_Control(pDX, FLE_Proc10, flechasproc[1]);
	DDX_Control(pDX, FLE_Proc11, flechasproc[2]);
	DDX_Control(pDX, FLE_Proc12, flechasproc[3]);
	DDX_Control(pDX, FLE_Proc13, flechasproc[4]);
	DDX_Control(pDX, FLE_Proc14, flechasproc[5]);
	DDX_Control(pDX, FLE_Proc15, flechasproc[6]);
	DDX_Control(pDX, FLE_Proc16, flechasproc[7]);
	DDX_Control(pDX, FLE_Mem, flechaMem);
	DDX_Control(pDX, FLE_Proc17, flechasCD[0]);
	DDX_Control(pDX, FLE_Proc18, flechasCD[1]);
	DDX_Control(pDX, FLE_Proc19, flechasCD[2]);
	DDX_Control(pDX, FLE_Proc20, flechasCD[3]);
	DDX_Control(pDX, FLE_Proc21, flechasCD[4]);
	DDX_Control(pDX, FLE_Proc22, flechasCD[5]);
	DDX_Control(pDX, FLE_Proc23, flechasCD[6]);
	DDX_Control(pDX, FLE_Proc24, flechasCD[7]);
	DDX_Control(pDX, TXT_Proc1, textoproc[0]);
	DDX_Control(pDX, TXT_Proc2, textoproc[1]);
	DDX_Control(pDX, TXT_Proc3, textoproc[2]);
	DDX_Control(pDX, TXT_Proc4, textoproc[3]);
	DDX_Control(pDX, TXT_Proc5, textoproc[4]);
	DDX_Control(pDX, TXT_Proc6, textoproc[5]);
	DDX_Control(pDX, TXT_Proc7, textoproc[6]);
	DDX_Control(pDX, TXT_Proc8, textoproc[7]);
	DDX_Control(pDX, TXT_Proc9, textoCI[0]);
	DDX_Control(pDX, TXT_Proc10, textoCI[1]);
	DDX_Control(pDX, TXT_Proc11, textoCI[2]);
	DDX_Control(pDX, TXT_Proc12, textoCI[3]);
	DDX_Control(pDX, TXT_Proc13, textoCI[4]);
	DDX_Control(pDX, TXT_Proc14, textoCI[5]);
	DDX_Control(pDX, TXT_Proc15, textoCI[6]);
	DDX_Control(pDX, TXT_Proc16, textoCI[7]);
	DDX_Control(pDX, TXT_Proc17, textoCD[0]);
	DDX_Control(pDX, TXT_Proc18, textoCD[1]);
	DDX_Control(pDX, TXT_Proc19, textoCD[2]);
	DDX_Control(pDX, TXT_Proc20, textoCD[3]);
	DDX_Control(pDX, TXT_Proc21, textoCD[4]);
	DDX_Control(pDX, TXT_Proc22, textoCD[5]);
	DDX_Control(pDX, TXT_Proc23, textoCD[6]);
	DDX_Control(pDX, TXT_Proc24, textoCD[7]);
	DDX_Control(pDX, IDC_BIniciar, bIniciar);
	DDX_Control(pDX, IDC_BPausa, bPausa);
	DDX_Control(pDX, IDC_BDetener, bCompleta);
	DDX_Control(pDX, IDC_BSalir, bSalir);
	DDX_Text(pDX, IDC_LTBus, Bus::getInstancia()->numTransBus);
	DDX_Text(pDX, IDC_LTBloques,Bus::getInstancia()->numBloqTrans);
	DDX_Text(pDX, IDC_LTestado,Bus::getInstancia()->numTranEstado);
	DDX_Control(pDX, IDC_STEPS, TSteps);
	DDX_Control(pDX, IDC_SAMemoria2, TotalAccesos);
	DDX_Control(pDX, IDC_SInstrucciones2, TotalInst);
	DDX_Control(pDX, IDC_SDLeidos2, TotalLeidas);
	DDX_Control(pDX, IDC_SDEscritos2, TotalEscritos);
	DDX_Control(pDX, IDC_SAMemoria, Caccesos);
	DDX_Control(pDX, IDC_SInstrucciones, Cinstrucciones);
	DDX_Control(pDX, IDC_SDLeidos, Cleidos);
	DDX_Control(pDX, IDC_SDEscritos, Cescritos);
	DDX_Control(pDX, IDC_LTBus, CtransBus);
	DDX_Control(pDX, IDC_LTBloques, Cbloqtrans);
	DDX_Control(pDX, IDC_LTestado, Ctransestado);
	DDX_Control(pDX, IDC_SNAciertos, Caciertos);
	DDX_Control(pDX, IDC_SPAciertos, CPorAciertos);
	DDX_Control(pDX, IDC_SNFallos, Cfallos);
	DDX_Control(pDX, IDC_SPFallos, CPorFallos);
	DDX_Control(pDX, IDC_Estados0, cambios[0][0]);
	DDX_Control(pDX, IDC_Estados1, cambios[0][1]);
	DDX_Control(pDX, IDC_Estados2, cambios[0][2]);
	DDX_Control(pDX, IDC_Estados3, cambios[0][3]);
	DDX_Control(pDX, IDC_Estados16, cambios[0][4]);
	DDX_Control(pDX, IDC_Estados4, cambios[1][0]);
	DDX_Control(pDX, IDC_Estados5, cambios[1][1]);
	DDX_Control(pDX, IDC_Estados6, cambios[1][2]);
	DDX_Control(pDX, IDC_Estados7, cambios[1][3]);
	DDX_Control(pDX, IDC_Estados17, cambios[1][4]);
	DDX_Control(pDX, IDC_Estados8, cambios[2][0]);
	DDX_Control(pDX, IDC_Estados9, cambios[2][1]);
	DDX_Control(pDX, IDC_Estados10, cambios[2][2]);
	DDX_Control(pDX, IDC_Estados11, cambios[2][3]);
	DDX_Control(pDX, IDC_Estados18, cambios[2][4]);
	DDX_Control(pDX, IDC_Estados12, cambios[3][0]);
	DDX_Control(pDX, IDC_Estados13, cambios[3][1]);
	DDX_Control(pDX, IDC_Estados14, cambios[3][2]);
	DDX_Control(pDX, IDC_Estados15, cambios[3][3]);
	DDX_Control(pDX, IDC_Estados19, cambios[3][4]);
	DDX_Control(pDX, IDC_Estados20, cambios[4][0]);
	DDX_Control(pDX, IDC_Estados21, cambios[4][1]);
	DDX_Control(pDX, IDC_Estados22, cambios[4][2]);
	DDX_Control(pDX, IDC_Estados23, cambios[4][3]);
	DDX_Control(pDX, IDC_Estados24, cambios[4][4]);
	DDX_Control(pDX, IDC_CEstadoL1A, labelCambios[0][0]);
	DDX_Control(pDX, IDC_CEstadoL2A, labelCambios[1][0]);
	DDX_Control(pDX, IDC_CEstadoL3A, labelCambios[2][0]);
	DDX_Control(pDX, IDC_CEstadoL4A, labelCambios[3][0]);
	DDX_Control(pDX, IDC_CEstadoL5A, labelCambios[4][0]);
	DDX_Control(pDX, IDC_CEstadoL1B, labelCambios[0][1]);
	DDX_Control(pDX, IDC_CEstadoL2B, labelCambios[1][1]);
	DDX_Control(pDX, IDC_CEstadoL3B, labelCambios[2][1]);
	DDX_Control(pDX, IDC_CEstadoL4B, labelCambios[3][1]);
	DDX_Control(pDX, IDC_CEstadoL5B, labelCambios[4][1]);
}

BOOL CSMPCacheView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: modificar aquí la clase Window o los estilos cambiando
	// CREATESTRUCT cs
	return CFormView::PreCreateWindow(cs);
}

void CSMPCacheView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}

// Diagnósticos de CSMPCacheView

#ifdef _DEBUG
void CSMPCacheView::AssertValid() const
{
	CView::AssertValid();
}

void CSMPCacheView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSMPCacheDoc* CSMPCacheView::GetDocument() const // La versión de no depuración es en línea
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSMPCacheDoc)));
	return (CSMPCacheDoc*)m_pDocument;
}
#endif //_DEBUG


// Controladores de mensaje de CSMPCacheView

void CSMPCacheView::OnOpcionesConfigurarmultiprocesador()
{
	ProcConf formulario;
	formulario.DoModal();
}

void CSMPCacheView::OnOpcionesMemoria()
{
	MemConf formulario;
	formulario.DoModal();
}

void CSMPCacheView::OnOpcionesCaches()
{
	CacheConf formulario;
	formulario.DoModal();
}

void CSMPCacheView::mostrarFCache(int pos)
{
	flechasCD[pos].ShowWindow(true);
	flechasCI[pos].ShowWindow(true);
	textoCI[pos].ShowWindow(true);
	textoCD[pos].ShowWindow(true);	
}

void CSMPCacheView::ocultarFCache(int pos)
{
	flechasCD[pos].ShowWindow(false);
	flechasCI[pos].ShowWindow(false);
	textoCI[pos].ShowWindow(false);
	textoCD[pos].ShowWindow(false);	
}

void CSMPCacheView::OnFileOpen()
{
	// TODO: Agregue aquí su código de controlador de comandos
	CString sFiltro;
	sFiltro="Ficheros configuracion (*.cfg)|*.cfg|Fichers traza (*.prg)|*.prg||";

	CFileDialog Dialogoabrir(TRUE,NULL,NULL,4|2,sFiltro);

	if(Dialogoabrir.DoModal() != IDOK)
		return;

	ErrorConfig varControl;

	CStdioFile file;
	CString str;
	int i = 0;
	file.Open(Dialogoabrir.GetPathName(), CFile::modeRead);
	file.ReadString(str);
	file.ReadString(str);
	procn = _wtoi(str);
	if(procn < 1 || procn > 8)
		varControl.add(_T("Error en la configuracion del numero de procesadores!"));
	file.ReadString(str);
	file.ReadString(str);
	protocolo = int2Protocolo(_wtoi(str),varControl);
	file.ReadString(str);
	file.ReadString(str);
	arbitracion = int2Arbitracion(_wtoi(str),varControl);
	file.ReadString(str);
	file.ReadString(str);
	anchoPalabra = _wtoi(str);
	if(anchoPalabra != 8 && anchoPalabra != 16 && anchoPalabra != 32 && anchoPalabra != 64 )
		varControl.add(_T("Error en la configuracion del ancho de palabra!"));
	file.ReadString(str);
	file.ReadString(str);
	palabrasBloque = _wtoi(str);
	if(palabrasBloque < 1 || ((int) log2(palabrasBloque)) != log2(palabrasBloque) || log2(palabrasBloque) > 10 )
		varControl.add(_T("Error en la configuracion de palabras por bloque!"));
	file.ReadString(str);
	file.ReadString(str);
	bloqMemoria = _wtoi(str);
	if(bloqMemoria < 1 || ((int) log2(bloqMemoria)) != log2(bloqMemoria) || log2(bloqMemoria) > 15 )
		varControl.add(_T("Error en la configuracion del numero de bloques en memoria!"));
	file.ReadString(str);
	file.ReadString(str);
	bloqCache = _wtoi(str);
	if(bloqCache < 1 || ((int) log2(bloqCache)) != log2(bloqCache) || log2(bloqCache) > 9 )
		varControl.add(_T("Error en la configuracion del numero de bloques en cache!"));
	file.ReadString(str);
	file.ReadString(str);
	fcorrespondencia = int2Correspondencia(_wtoi(str),varControl);
	file.ReadString(str);
	file.ReadString(str);
	nConjuntos = _wtoi(str);
	if(nConjuntos < 0 || ((int) log2(nConjuntos)) != log2(nConjuntos) || log2(nConjuntos) > 9 )
		varControl.add(_T("Error en la configuracion del numero de conjuntos en cache!"));
	file.ReadString(str);
	file.ReadString(str);
	aremplazamiento = int2ARemplazamiento(_wtoi(str),varControl);
	file.ReadString(str);
	file.ReadString(str);
	nCache = _wtoi(str);
	if(nCache != 1)
		varControl.add(_T("Error en la configuracion del numero de niveles de cache!"));
	file.ReadString(str);
	file.ReadString(str);
	pescritura = _wtoi(str);
	if(pescritura != 2)
		varControl.add(_T("Error en la configuracion del protocolo de escritura!"));
	file.ReadString(str);
	//ficheros de traza
	for(int i = 0; i < 8;i++)
	{
		file.ReadString(str);
		fTrazas[i] = str.Right(str.GetLength()-3);
	}

	//obtencion de las estadisticas totales
	int TAccesos = 0, TInst = 0, TLec = 0, TEsc = 0;
	CStdioFile file2;
	CString str2;
	for(int i = 0; i<procn;i++)
	{
		if(!fTrazas[i].IsEmpty())
		{
				if(!file2.Open(fTrazas[i], CFile::modeRead))
				{
					varControl.add(_T("Error: archivo de traza inexistente"));
				}
				while(file2.ReadString(str2))
				{
					TAccesos++;
					int i = 0;

					switch((TINSTRUCCION)_wtoi(str2.Left(1)))
					{
						case 0: TInst++;break;
						case 2: TLec++;break;
						case 3: TEsc++;break;
					}
				}
				file2.Close();
		}
	}

	bIniciar.EnableWindow(true);

		char cadena[20];
		_itoa_s(TInst,cadena,10);
		TotalInst.SetWindowTextW((CString)cadena);
		_itoa_s(TAccesos,cadena,10);
		TotalAccesos.SetWindowTextW((CString)cadena);
		_itoa_s(TLec,cadena,10);
		TotalLeidas.SetWindowTextW((CString)cadena);
		_itoa_s(TEsc,cadena,10);
		TotalEscritos.SetWindowTextW((CString)cadena);

	bool alguna = false;
	for(int i =0; i< 8; i++)
	{
		if(!fTrazas[i].IsEmpty()) alguna = true;
	}
	if(!alguna)
		varControl.add(_T("Error en la configuracion de los ficheros de traza, no se ha indicado ninguno!"));


	if(fcorrespondencia == F_DIRECTA && (nConjuntos != 0 || aremplazamiento != R_NO))
		varControl.add(_T("Error, falta de coherencia en los datos"));
	if(fcorrespondencia == F_ACONJUNTOS && nConjuntos == 0)
		varControl.add(_T("Error, falta de coherencia en los datos"));
	if(fcorrespondencia == F_TASOCIATIVA && nConjuntos != 0)
		varControl.add(_T("Error, falta de coherencia en los datos"));

	try{
		varControl.check();
		actualizarVista();
	}catch (ErrorConfig *ex)
	{
		ex->what();
	}
}

void setInt(CStatic &control, int &i)
{
	char cadena[20];
	_itoa_s(i,cadena,10);
	control.SetWindowTextW((CString)cadena);
}

void CSMPCacheView::actualizarControles()
{
	char cadena[20];
	_itoa_s(Bus::getInstancia()->memAccesos,cadena,10);
	Caccesos.SetWindowTextW((CString)cadena);
	_itoa_s(Bus::getInstancia()->instLeidas,cadena,10);
	Cinstrucciones.SetWindowTextW((CString)cadena);
	_itoa_s(Bus::getInstancia()->lecturas,cadena,10);
	Cleidos.SetWindowTextW((CString)cadena);
	_itoa_s(Bus::getInstancia()->escrituras,cadena,10);
	Cescritos.SetWindowTextW((CString)cadena);
	_itoa_s(Bus::getInstancia()->numTransBus,cadena,10);
	CtransBus.SetWindowTextW((CString)cadena);
	sprintf_s(cadena,"%f",Bus::getInstancia()->numBloqTrans);
	Cbloqtrans.SetWindowTextW((CString)cadena);
	_itoa_s(Bus::getInstancia()->numTranEstado,cadena,10);
	Ctransestado.SetWindowTextW((CString)cadena);
	_itoa_s(Bus::getInstancia()->aciertos,cadena,10);
	Caciertos.SetWindowTextW((CString)cadena);
	_itoa_s(Bus::getInstancia()->fallos,cadena,10);
	Cfallos.SetWindowTextW((CString)cadena);
	_itoa_s(Bus::getInstancia()->aciertos*100/(Bus::getInstancia()->fallos+Bus::getInstancia()->aciertos),cadena,10);
	CPorAciertos.SetWindowTextW((CString)cadena);
	_itoa_s(Bus::getInstancia()->fallos*100/(Bus::getInstancia()->fallos+Bus::getInstancia()->aciertos),cadena,10);
	CPorFallos.SetWindowTextW((CString)cadena);
	if(!enPausa&&enEjecucion) return;
	int o = 0;
	for(int i = 0; i< procn;i++)
	{
		if(!fTrazas[i].IsEmpty())
		{
			CString ccadena(Bus::getInstancia()->caches[o++]->textoCache);
			cambiarTextoProc(i,ccadena);
		}
	}
	ocultarInteraccionesCache();
	if(Bus::getInstancia()->flechaMensajeCache.id != -1)
	{
		flechasCI[Bus::getInstancia()->flechaMensajeCache.id].ShowWindow(true);
		flechasCD[Bus::getInstancia()->flechaMensajeCache.id].ShowWindow(true);
		flechasCD[Bus::getInstancia()->flechaMensajeCache.id].SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_FArriba)));	
		textoCI[Bus::getInstancia()->flechaMensajeCache.id].ShowWindow(true);
		textoCD[Bus::getInstancia()->flechaMensajeCache.id].ShowWindow(true);
		switch(Bus::getInstancia()->flechaMensajeCache.mensaje.tipo)
		{
		case M_BUSRD: strcpy_s(cadena,"BUSRD");break;
		case M_BUSRDX: strcpy_s(cadena,"BUSRDX");break;
		case M_BUSUPD: strcpy_s(cadena,"BUSUPD");break;
		case M_BUSRDUPD: strcpy_s(cadena,"RD/UPD");break;
		default:  strcpy_s(cadena,"ERROR");break;
		}
		textoCI[Bus::getInstancia()->flechaMensajeCache.id].SetWindowTextW((CString)cadena);
		_itoa_s(dirMemToBloq(Bus::getInstancia()->flechaMensajeCache.mensaje.dirmem,palabrasBloque,bloqMemoria),cadena,10);
		textoCD[Bus::getInstancia()->flechaMensajeCache.id].SetWindowTextW((CString)cadena);
		if(Bus::getInstancia()->origDat == -1)
		{
			flechaMem.ShowWindow(true);
		}
		else
		{
			flechasCI[Bus::getInstancia()->origDat].ShowWindow(true);
		}
	}
	//actualizacion de los estados
	switch(protocolo)
	{	
	case P_MSI:
		setInt(cambios[0][0],Bus::getInstancia()->cambios_estado[C_M][C_M]);
		setInt(cambios[0][1],Bus::getInstancia()->cambios_estado[C_M][C_S]);
		setInt(cambios[0][2],Bus::getInstancia()->cambios_estado[C_M][C_I]);
		setInt(cambios[1][0],Bus::getInstancia()->cambios_estado[C_S][C_M]);
		setInt(cambios[1][1],Bus::getInstancia()->cambios_estado[C_S][C_S]);
		setInt(cambios[1][2],Bus::getInstancia()->cambios_estado[C_S][C_I]);
		setInt(cambios[2][0],Bus::getInstancia()->cambios_estado[C_I][C_M]);
		setInt(cambios[2][1],Bus::getInstancia()->cambios_estado[C_I][C_S]);
		setInt(cambios[2][2],Bus::getInstancia()->cambios_estado[C_I][C_I]);
		break;
	case P_MESI:
		setInt(cambios[0][0],Bus::getInstancia()->cambios_estado[C_M][C_M]);
		setInt(cambios[0][1],Bus::getInstancia()->cambios_estado[C_M][C_E]);
		setInt(cambios[0][2],Bus::getInstancia()->cambios_estado[C_M][C_S]);
		setInt(cambios[0][3],Bus::getInstancia()->cambios_estado[C_M][C_I]);
		setInt(cambios[1][0],Bus::getInstancia()->cambios_estado[C_E][C_M]);
		setInt(cambios[1][1],Bus::getInstancia()->cambios_estado[C_E][C_E]);
		setInt(cambios[1][2],Bus::getInstancia()->cambios_estado[C_E][C_S]);
		setInt(cambios[1][3],Bus::getInstancia()->cambios_estado[C_E][C_I]);
		setInt(cambios[2][0],Bus::getInstancia()->cambios_estado[C_S][C_M]);
		setInt(cambios[2][1],Bus::getInstancia()->cambios_estado[C_S][C_E]);
		setInt(cambios[2][2],Bus::getInstancia()->cambios_estado[C_S][C_S]);
		setInt(cambios[2][3],Bus::getInstancia()->cambios_estado[C_S][C_I]);
		setInt(cambios[3][0],Bus::getInstancia()->cambios_estado[C_I][C_M]);
		setInt(cambios[3][1],Bus::getInstancia()->cambios_estado[C_I][C_E]);
		setInt(cambios[3][2],Bus::getInstancia()->cambios_estado[C_I][C_S]);
		setInt(cambios[3][3],Bus::getInstancia()->cambios_estado[C_I][C_I]);
		break;
	case P_DRAGON:
		setInt(cambios[0][0],Bus::getInstancia()->cambios_estado[C_E][C_E]);
		setInt(cambios[0][1],Bus::getInstancia()->cambios_estado[C_E][C_SC]);
		setInt(cambios[0][2],Bus::getInstancia()->cambios_estado[C_E][C_SM]);
		setInt(cambios[0][3],Bus::getInstancia()->cambios_estado[C_E][C_M]);
		setInt(cambios[0][4],Bus::getInstancia()->cambios_estado[C_E][C_I]);
		setInt(cambios[1][0],Bus::getInstancia()->cambios_estado[C_SC][C_E]);
		setInt(cambios[1][1],Bus::getInstancia()->cambios_estado[C_SC][C_SC]);
		setInt(cambios[1][2],Bus::getInstancia()->cambios_estado[C_SC][C_SM]);
		setInt(cambios[1][3],Bus::getInstancia()->cambios_estado[C_SC][C_M]);
		setInt(cambios[1][4],Bus::getInstancia()->cambios_estado[C_SC][C_I]);
		setInt(cambios[2][0],Bus::getInstancia()->cambios_estado[C_SM][C_E]);
		setInt(cambios[2][1],Bus::getInstancia()->cambios_estado[C_SM][C_SC]);
		setInt(cambios[2][2],Bus::getInstancia()->cambios_estado[C_SM][C_SM]);
		setInt(cambios[2][3],Bus::getInstancia()->cambios_estado[C_SM][C_M]);
		setInt(cambios[2][4],Bus::getInstancia()->cambios_estado[C_SM][C_I]);
		setInt(cambios[3][0],Bus::getInstancia()->cambios_estado[C_M][C_E]);
		setInt(cambios[3][1],Bus::getInstancia()->cambios_estado[C_M][C_SC]);
		setInt(cambios[3][2],Bus::getInstancia()->cambios_estado[C_M][C_SM]);
		setInt(cambios[3][3],Bus::getInstancia()->cambios_estado[C_M][C_M]);
		setInt(cambios[3][4],Bus::getInstancia()->cambios_estado[C_M][C_I]);
		setInt(cambios[4][0],Bus::getInstancia()->cambios_estado[C_I][C_E]);
		setInt(cambios[4][1],Bus::getInstancia()->cambios_estado[C_I][C_SC]);
		setInt(cambios[4][2],Bus::getInstancia()->cambios_estado[C_I][C_SM]);
		setInt(cambios[4][3],Bus::getInstancia()->cambios_estado[C_I][C_M]);
		setInt(cambios[4][4],Bus::getInstancia()->cambios_estado[C_I][C_I]);
		break;
	}
}

void CSMPCacheView::ocultarInteraccionesCache()
{
	for(int i = 0;i<procn; i++)
	{
		flechasCI[i].ShowWindow(false);
		flechasCD[i].ShowWindow(false);
		textoCI[i].ShowWindow(false);
		flechaMem.ShowWindow(false);
		textoCD[i].ShowWindow(false);
	}
}

void CSMPCacheView::actualizarVista()
{
	for (int i =0;i < 8 ; i++)
	{
		if(i<procn)
		{
			proc[i].ShowWindow(true);
			flechasproc[i].ShowWindow(true);
			flechasCI[i].ShowWindow(false);
			flechaMem.ShowWindow(false);
			flechasCD[i].ShowWindow(false);
			textoCI[i].ShowWindow(false);
			textoCD[i].ShowWindow(false);
			textoproc[i].ShowWindow(true);
			if(fTrazas[i].IsEmpty())
				proc[i].SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_PsinT)));
			else
				proc[i].SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_PconT)));
		}else
		{
			proc[i].ShowWindow(false);
			flechasproc[i].ShowWindow(false);
			flechasCD[i].ShowWindow(false);
			flechasCI[i].ShowWindow(false);
			textoproc[i].ShowWindow(false);
			textoCI[i].ShowWindow(false);
			textoCD[i].ShowWindow(false);
		}
	}
	switch(protocolo)
	{		
	case P_MSI:
		for(int i = 0; i < 5;i++)
		{
			cambios[i][3].ShowWindow(false);
			cambios[3][i].ShowWindow(false);
			cambios[i][4].ShowWindow(false);
			cambios[4][i].ShowWindow(false);
		}
		labelCambios[3][0].ShowWindow(false);
		labelCambios[4][0].ShowWindow(false);
		labelCambios[3][1].ShowWindow(false);
		labelCambios[4][1].ShowWindow(false);
		labelCambios[0][0].SetWindowTextW(_T("M"));
		labelCambios[1][0].SetWindowTextW(_T("S"));
		labelCambios[2][0].SetWindowTextW(_T("I"));
		labelCambios[0][1].SetWindowTextW(_T("M"));
		labelCambios[1][1].SetWindowTextW(_T("S"));
		labelCambios[2][1].SetWindowTextW(_T("I"));

		break;
	case P_MESI:
		for(int i = 0; i < 5;i++)
		{
			if(i<=3)
			{
				cambios[i][3].ShowWindow(true);
				cambios[3][i].ShowWindow(true);
			}
			else
			{
				cambios[i][3].ShowWindow(false);
				cambios[3][i].ShowWindow(false);
			}
			cambios[i][4].ShowWindow(false);
			cambios[4][i].ShowWindow(false);
		}
		labelCambios[3][0].ShowWindow(true);
		labelCambios[4][0].ShowWindow(false);
		labelCambios[3][1].ShowWindow(true);
		labelCambios[4][1].ShowWindow(false);
		labelCambios[0][0].SetWindowTextW(_T("M"));
		labelCambios[1][0].SetWindowTextW(_T("E"));
		labelCambios[2][0].SetWindowTextW(_T("S"));
		labelCambios[3][0].SetWindowTextW(_T("I"));
		labelCambios[0][1].SetWindowTextW(_T("M"));
		labelCambios[1][1].SetWindowTextW(_T("E"));
		labelCambios[2][1].SetWindowTextW(_T("S"));
		labelCambios[3][1].SetWindowTextW(_T("I"));

		break;
	case P_DRAGON:
		for(int i = 0; i < 5;i++)
		{
			cambios[i][3].ShowWindow(true);
			cambios[3][i].ShowWindow(true);
			cambios[i][4].ShowWindow(true);
			cambios[4][i].ShowWindow(true);
		}
		labelCambios[3][0].ShowWindow(true);
		labelCambios[4][0].ShowWindow(true);
		labelCambios[3][1].ShowWindow(true);
		labelCambios[4][1].ShowWindow(true);

		labelCambios[0][0].SetWindowTextW(_T("E"));
		labelCambios[1][0].SetWindowTextW(_T("SC"));
		labelCambios[2][0].SetWindowTextW(_T("SM"));
		labelCambios[3][0].SetWindowTextW(_T("M"));
		labelCambios[4][0].SetWindowTextW(_T("F"));
		labelCambios[0][1].SetWindowTextW(_T("E"));
		labelCambios[1][1].SetWindowTextW(_T("SC"));
		labelCambios[2][1].SetWindowTextW(_T("SM"));
		labelCambios[3][1].SetWindowTextW(_T("M"));
		labelCambios[4][1].SetWindowTextW(_T("F"));
		break;

	}
}

void CSMPCacheView::mostrarProc()
{
	int i;
	for (i =0;i < procn ; i++)
	{
		proc[i].ShowWindow(true);
		flechasproc[i].ShowWindow(true);
		flechasCI[i].ShowWindow(true);
		flechasCD[i].ShowWindow(true);
		textoproc[i].ShowWindow(true);
	}
}

void CSMPCacheView::ocultarProc()
{
	int i;
	for (i =0;i < procn ; i++)
	{
		proc[i].ShowWindow(false);
		flechasproc[i].ShowWindow(false);
		flechasCD[i].ShowWindow(false);
		flechasCI[i].ShowWindow(false);
		textoproc[i].ShowWindow(false);
	}
}

void CSMPCacheView::cambiarFlechaProc(int pos)
{
	if(fParriba[pos])
		flechasproc[pos].SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_FAbajo)));
	else
		flechasproc[pos].SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_FArriba)));
	fParriba[pos] = !fParriba[pos];
}

void CSMPCacheView::cambiarTextoProc(int pos, CString texto)
{
	textoproc[pos].SetWindowTextW(texto);
}

void CSMPCacheView::cambiarFlechaCI(int pos)
{
	if(fCIarriba[pos])
		flechasCI[pos].SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_FAbajo)));
	else
		flechasCI[pos].SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_FArriba)));
	fCIarriba[pos] = !fCIarriba[pos];
}

void CSMPCacheView::cambiarTextoCI(int pos, CString texto)
{
	textoCI[pos].SetWindowTextW(texto);
}

void CSMPCacheView::cambiarFlechaCD(int pos)
{
	if(fCDarriba[pos])
		flechasCD[pos].SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_FAbajo)));
	else
		flechasCD[pos].SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_FArriba)));
	fCDarriba[pos] = !fCDarriba[pos];
}

void CSMPCacheView::OnBnClickedBiniciar()
{
	iniciarSimulacion();
	enEjecucion = true;
	bPausa.EnableWindow(true);
	bCompleta.EnableWindow(false);
	bIniciar.EnableWindow(false);
	enPausa = false;
}

void CSMPCacheView::OnBnClickedBpausa()
{
	CString texto;
	if(enPausa)
	{
		texto = "Pausar";
		bPausa.SetWindowTextW(texto);
		enPausa = false;	
	}
	else
	{
		texto = "Continuar";
		bPausa.SetWindowTextW(texto);
		bCompleta.EnableWindow(true);
		enPausa = true;
	}
}

void CSMPCacheView::OnBnClickedBCompleta()
{
	enEjecucion = true;
	bPausa.EnableWindow(true);
	bCompleta.EnableWindow(false);
	enPausa = false;
	CString aux;
	TotalAccesos.GetWindowTextW(aux);
	steps = _wtoi(aux)+1;
	char cadena[20];
	_itoa_s(steps,cadena,10);
	TSteps.SetWindowTextW((CString)cadena);
	CString texto;
	texto = "Pausar";
	bPausa.SetWindowTextW(texto);
}

void CSMPCacheView::OnBnClickedBsalir()
{
	this->CloseWindow();
	exit(0);
}

bool CSMPCacheView::realizarIteracion()
{
	if(steps == 0) {OnBnClickedBpausa(); return true;}
	bool res = true;
	if(steps > 0)
	{
		res = Bus::getInstancia()->realizarIteracion();
	}
	if(steps <= Bus::getInstancia()->memAccesos)
	{
		OnBnClickedBpausa();
		steps = 1;
		char cadena[20];
		_itoa_s(steps,cadena,10);
		TSteps.SetWindowTextW((CString)cadena);
	}
	if(!res)//fin ejecucion
	{
		bPausa.EnableWindow(false);
		bCompleta.EnableWindow(false);
		bIniciar.EnableWindow(true);
		enEjecucion = false;
		AfxMessageBox(_T("Simulacion terminada con exito!"));
	}
	actualizarControles();
	return res;
}
void CSMPCacheView::OnEnChangeSteps()
{
	CString texto;
	TSteps.GetWindowTextW(texto);
	steps = _wtoi(texto);
}
