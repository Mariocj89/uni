// SMPCacheView.h: interfaz de la clase CSMPCacheView
//


#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Procesador.h"
#include "Cache.h"
#include "Bus.h"
#include "constantes.h"


class CSMPCacheView : public CFormView
{

	void actualizarControles();
protected: // Crear sólo a partir de serialización
	CSMPCacheView();
	DECLARE_DYNCREATE(CSMPCacheView)

public:
	enum{ IDD = IDD_Principal };

// Atributos
public:
	CSMPCacheDoc* GetDocument() const;
	// variable de control para las imagenes de los procesadores
	CStatic proc[8];
	// variable de control para las flechas a la izquierda de los procesadores
	CStatic flechasproc[8];
	// variable de control para las flechas a la izquierda de las caches
	CStatic flechasCI[8];
	// variable de control para las flechas a la derecha de las caches
	CStatic flechasCD[8];
	//variable de control de la flecha de la memoria
	CStatic flechaMem;
	// variable de control para el texo a la izquierda de los procesadores
	CStatic textoproc[8];
	// variable de control para el texo a la izquierda de los cache
	CStatic textoCI[8];
	// variable de control para el texo a la derecha de los cache
	CStatic textoCD[8];

	//boleanos para saber si la flecha apunta hacia arriba
	bool fParriba[8];
	bool fCIarriba[8];
	bool fCDarriba[8];

	//variables para mostrar los cambios de estado
	CStatic cambios[5][5];
	CStatic labelCambios[5][2];

	//opciones de configuracion
	int procn;
	PROTOCOLO protocolo;
	ARBITRACION arbitracion;
	int anchoPalabra;
	int palabrasBloque;
	int bloqMemoria;
	int bloqCache;
	FCORRESPONDENCIA fcorrespondencia;
	int nConjuntos;
	AREMPLAZAMIENTO aremplazamiento;
	int nCache;
	int pescritura;
	CString fTrazas[8];

// Operaciones
public:
	void ocultarInteraccionesCache();
	void mostrarProc();
	void ocultarProc();
	void mostrarFCache(int pos);
	void ocultarFCache(int pos);
	void actualizarVista();
	void cambiarFlechaProc(int pos);
	void cambiarTextoProc(int pos, CString texto);
	void cambiarFlechaCI(int pos);
	void cambiarTextoCI(int pos, CString texto);
	void cambiarFlechaCD(int pos);
	void iniciarSimulacion();

// Reemplazos
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV
protected:
	virtual void OnInitialUpdate(); // Se llama la primera vez después de la construcción

// Implementación
public:
	virtual ~CSMPCacheView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignación de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpcionesConfigurarmultiprocesador();
	afx_msg void OnOpcionesMemoria();
	afx_msg void OnOpcionesCaches();
	afx_msg void OnFileOpen();
	afx_msg void OnBnClickedBiniciar();
	//estao de la simulacion
	bool enEjecucion;
	// boton iniciar
	CButton bIniciar;
	//estado del boton de pausa
	bool enPausa;

	// boton de pausa o continuar
	CButton bPausa;
	// boton de ejec completa
	CButton bCompleta;
	// boton para salir
	CButton bSalir;
	// pasos de ejecucion
	int steps;

	

	afx_msg void OnBnClickedBpausa();
	afx_msg void OnBnClickedBCompleta();
	afx_msg void OnBnClickedBsalir();
	bool realizarIteracion();
	afx_msg void OnEnChangeSteps();
	// cuadro de texto de steps
	CEdit TSteps;
	CStatic TotalAccesos;
	CStatic TotalInst;
	// numero de datos leidos
	CStatic TotalLeidas;
	// numero de datos escritos
	CStatic TotalEscritos;
	// variable de control de accesos
	CStatic Caccesos;
	// variable de control de instrucciones
	CStatic Cinstrucciones;
	CStatic Cleidos;
	CStatic Cescritos;
	// Control para las transacciones del bus
	CStatic CtransBus;
	// Control de los bloques transferidos
	CStatic Cbloqtrans;
	// Control para las transacciones de estado
	CStatic Ctransestado;
	// Control del los aciertos en cache
	CStatic Caciertos;
	// Control del porcentaje de aciertos en cache
	CStatic CPorAciertos;
	// Control de los fallos en cache
	CStatic Cfallos;
	// Control del porcentaje de fallos en cache
	CStatic CPorFallos;
};

#ifndef _DEBUG  // Versión de depuración en SMPCacheView.cpp
inline CSMPCacheDoc* CSMPCacheView::GetDocument() const
   { return reinterpret_cast<CSMPCacheDoc*>(m_pDocument); }
#endif

