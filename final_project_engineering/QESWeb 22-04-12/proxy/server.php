<?php 
	/** Proxy para permitir llamadas cross domain (diferente puerto = diferente dominio)*/
	/** Fichero con constantes */
	header('Content-Type: text/html; charset=utf-8');
	header("Cache-Control: no-cache, must-revalidate");//importante para IE

	$server = "http://localhost:8500/WS/";
?>