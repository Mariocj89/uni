//requires JQUERY & Jquery UI
//Variables para la comunicacion con el servidor
var server = "https://localhost/WS/";

//Configuracion para Pusher
var pusherKey = '9a3fe2f64106d87e0291';
var pusherChannel = 'QESTest';
var soundFile = "beep.wav";

//refreshca la sesion cada "min" minutos con el token "token"
function autoRefresh(min,token)
{
	var action = "$.post('"+server+"'+'Refresh?token="+token+"');";
	eval(action);
	self.setInterval(action,min * 60 *1000);
}


//FUNCIONES AUXILIARES
function updateTips( t,tips ) {
	tips
		.text( t )
		.addClass( "ui-state-highlight" );
	setTimeout(function() {
		tips.removeClass( "ui-state-highlight", 1500 );
	}, 500 );
}

function checkLength( o, n, min, max ,tips) {
	if ( o.val().length > max || o.val().length < min ) {
		o.addClass( "ui-state-error" );
		updateTips( "La longitud de " + n + " debe estar entre " +
			min + " y " + max + ".",tips );
		return false;
	} else {
		return true;
	}
}

function checkRegexp( o, regexp, n ,tips) {
	if ( !( regexp.test( o.val() ) ) ) {
		o.addClass( "ui-state-error" );
		updateTips( n ,tips);
		return false;
	} else {
		return true;
	}
}

function iguales( a, b, n ,tips) {
	if ( a.val() != b.val() ) {
		a.addClass( "ui-state-error" );
		b.addClass( "ui-state-error" );
		updateTips( n ,tips);
		return false;
	} else {
		return true;
	}
}

//Muestra un dialogo con un mensaje de informacion
//Requiere Jquery UI
function mensaje(mensaje)
{
var $dialog = $('<div class="dialogo"></div>')
		.html(mensaje)
		.dialog({
			width:350,
			height:160,
			hide: 'fold',
			show: 'blind',
			modal: true,			
			buttons: {
				"Aceptar":function() {
					$( this ).dialog( "close" );
				}
			}
		});
}


//mostrar una camara
function displayCamera(url, port, user, password,DisplayWidth,DisplayHeight)
{

	// Ancho y alto de la imagen
	var DisplayWidth = DisplayWidth || "320";
	var DisplayHeight = DisplayHeight || "300";

	// ruta de la camara que genera las imagenes
	var File = "axis-cgi/mjpg/video.cgi?resolution=640x480";
	// No changes required below this point

	var output = "";
	if ((navigator.appName == "Microsoft Internet Explorer") &&
	(navigator.platform != "MacPPC") && (navigator.platform != "Mac68k"))
	{
		// If Internet Explorer under Windows then use ActiveX
		// Url de la camara
		var BaseURL = "http://"+url+":"+port+"/";		
		
		output = '<div class="dragContainer" style="border:5px solid #ebebeb;">';		
		
		output += '<OBJECT ID="Player" width=';
		output += DisplayWidth;
		output += ' height=';
		output += DisplayHeight;
		output += ' CLASSID="CLSID:DE625294-70E6-45ED-B895-CFFA13AEB044" ';
		output += 'CODEBASE="';
		output += BaseURL;
		output += 'activex/AMC.cab#version=3,20,18,0">';
		output += '<PARAM NAME="MediaURL" VALUE="';
		output += BaseURL;
		output += File + '">';
		output += '<param name="MediaUsername" value="root">';
		output += '<param name="MediaPassword" value="domouex">';
		output += '<param name="MediaType" value="mjpeg-unicast">';
		output += '<param name="ShowStatusBar" value="1">';
		output += '<param name="ShowToolbar" value="1">';
		output += '<param name="AutoStart" value="1">';
		output +='<param name="MediaUsername" value="'+user+'">'
		output +='<param name="MediaPassword" value="'+password+'">'		
		output += '<param name="StretchToFit" value="1">';
		output += '<BR><B>Axis Media Control</B><BR>';
		output += 'The AXIS Media Control, which enables you ';
		output += 'to view live image streams in Microsoft Internet';
		output += ' Explorer, could not be registered on your computer.';
		output += '<BR></OBJECT>';
		output+= '</div>';
	} else {
	// If not IE for Windows use the browser itself to display
		// Url de la camara
		var BaseURL = "http://"+user+":"+password+"@"+url+":"+port+"/";
		theDate = new Date();
		output = '<IMG class="stream" SRC="';
		output += BaseURL;
		output += File;
		output += '&dummy=' + theDate.getTime().toString(10);
		output += '" HEIGHT="';
		output += DisplayHeight;
		output += '" WIDTH="';
		output += DisplayWidth;
		output += '" ALT="Video">';
	}
	return  output;
	
	//document.Player.ToolbarConfiguration = "play,+snapshot,+fullscreen"
	// document.Player.UIMode = "MDConfig";
	// document.Player.MotionConfigURL = "/axis-cgi/operator/param.cgi?ImageSource=0"
	// document.Player.MotionDataURL = "/axis-cgi/motion/motiondata.cgi";
}

//cookies
function createCookie(name,value,days) {
	if (days) {
		var date = new Date();
		date.setTime(date.getTime()+(days*24*60*60*1000));
		var expires = "; expires="+date.toGMTString();
	}
	else var expires = "";
	document.cookie = name+"="+value+expires+"; path=/";
}

function readCookie(name) {
	var nameEQ = name + "=";
	var ca = document.cookie.split(';');
	for(var i=0;i < ca.length;i++) {
		var c = ca[i];
		while (c.charAt(0)==' ') c = c.substring(1,c.length);
		if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
	}
	return null;
}

function eraseCookie(name) {
	createCookie(name,"",-1);
}

