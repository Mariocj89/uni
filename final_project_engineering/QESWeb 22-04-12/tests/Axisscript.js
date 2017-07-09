var remaining_audio_init_timeout;
var Player;

function DrawTB(UseAudio, ImagePath, CamNbr, MediaRecording, HideMicSettings, ptz) // NOTE: HideMicSettings = "yes" for 207, otherwise it should be "no" (or undefined)
{
  var useMpeg = ImagePath.indexOf("h264") != -1 || ImagePath.indexOf("mpeg4") != -1;
  var useMjpeg = ImagePath.indexOf("mjpg") != -1;

  if (Player && typeof(Player.Play) != "undefined") {
    var config = "+play,+snapshot,+fullscreen";

    if ((useMjpeg || useMpeg) && MediaRecording != 0) {
      Player.EnableRecording = MediaRecording;
    }

    if (ptz == "yes") {
      config+= ",+ptz";
    } else {
      config+= ",-ptz";
    }
    if ((useMjpeg || useMpeg) && MediaRecording != 0) {
      config+= ",+rec";
    } else {
      config+= ",-rec";
    }
    if (UseAudio == "yes") {
      if (HideMicSettings == "yes") {
        config+= ",+mute,+volume,-audiocontrol";
      } else {
        config+= ",+audiocontrol";
      }
    } else {
      config+= ",-audiocontrol";
    }

    Player.ToolbarConfiguration = config;

    if (UseAudio == "yes" && (!(useMpeg && MediaRecording != 0) || (HideMicSettings != "yes" || useMpeg))) {
      remaining_audio_init_timeout = 5000;
      doAudioCheck(ImagePath, CamNbr, MediaRecording, ptz);
    }

    if (UseAudio == "yes") {
      try {
        Player.Play();
      } catch(e) {}
    }
  }
}

function doAudioCheck(ImagePath, CamNbr, MediaRecording, ptz)
{
  var audioComp = document.getElementById("AudioComponent");
  var aacDec = document.getElementById("AAC Decoder");
  if (!audioComp && !aacDec) {
    if (remaining_audio_init_timeout > 0) {
      setTimeout('doAudioCheck("' + ImagePath + '","' + CamNbr + '","' + MediaRecording + '","' + ptz + '"")', 250);
      remaining_audio_init_timeout -= 250;
    } else if (MediaRecording != 0) {
      Player.EnableRecording = MediaRecording;
    }
  } else {
    initAudio(ImagePath, CamNbr, MediaRecording, ptz);
  }
}

function activateContextMenu()
{
  if (Player && typeof(Player.Play) != "undefined") {
    Player.EnableContextMenu = "1";
    return;
  } else {
    setTimeout('activateContextMenu()', 250);
  }
}

function initAudio(ImagePath, CamNbr, MediaRecording, ptz)
{
  var confHost = getCurrentHostAndProt();
  Player.AudioConfigURL = confHost + "/axis-cgi/view/param.cgi?camera=" + CamNbr +  "&usergroup=anonymous&action=list&group=Audio,AudioSource.A0";

  Player.AudioTransmitURL = "/axis-cgi/audio/transmit.cgi";

  if (ImagePath.indexOf("mjpg") != -1) {
    var recieveURL = "/axis-cgi/audio/receive.cgi?audio=1&camera=" + CamNbr;
    Player.AudioReceiveURL = confHost + recieveURL;
  }

  if (MediaRecording != 0)
    Player.EnableRecording = MediaRecording;
}

function InstallFilter(prodName, ID, CLSID_filter, ver_filter, cab, installText1, text, installText2, installText3, installText4)
{
  var createdElement = document.createElement('<object ID="'+ ID + '" height="0" width="0" CLASSID="CLSID:' + CLSID_filter + '" CODEBASE="/activex/' + cab + '#Version=' + ver_filter + '"><br><b>' + ID + '</b>&nbsp;' + installText1 + '&nbsp;' + text + '&nbsp;' + installText2 + '&nbsp;' + installText3 + '<br>' +ID + '&nbsp;' + installText4 + '<br></OBJECT>');
  filterinstallocation.appendChild(createdElement);
}

function InstallDecoder(prodName, ID, CLSID_AMC, cab, ver_AMC, authorized, notAuthorizedText, authorizedText, installDecoderText1, installDecoderText2)
{
  var installedVersion = "0,0,0,0";
  try {
    installedVersion = document.Player.GetVersionPart(CLSID_AMC,0);
    installedVersion += ',' + document.Player.GetVersionPart(CLSID_AMC,1);
    installedVersion += ',' + document.Player.GetVersionPart(CLSID_AMC,2);
    installedVersion += ',' + document.Player.GetVersionPart(CLSID_AMC,3);
  }
  catch(e) {}

  ver_AMC = ver_AMC.replace(/&#44;/g, ",");
  var newerVersion = false;
  instVerArray = installedVersion.split(",");
  verAMCArray  = ver_AMC.split(",");

  for (i=0; i<instVerArray.length; i++) {
    if (parseInt(verAMCArray[i]) > parseInt(instVerArray[i])) {
      newerVersion = true;
      break;
    } else if (parseInt(verAMCArray[i]) < parseInt(instVerArray[i])) {
      break;
    }
  }

  var o = '<OBJECT ID="'+ ID + '" height="0" width="0" CLASSID="CLSID:' + CLSID_AMC + '" CODEBASE="' + cab + '#version=' + ver_AMC + '" STANDBY="Loading Axis Media Control components...">';
  if (newerVersion) {
    if (authorized != "yes") {
      o += '<br><p><b>' + notAuthorizedText + '</b><br>';
    } else {
      o += '<br><p><a href="javascript:launch(\'';
      if (ID == "AAC Decoder") {
        o += '/incl/aac_license.shtml\')">';
      } else if (ID == "H.264 Decoder") {
        o += '/incl/license_h264.shtml\')">';
      } else {
        o += '/incl/license.shtml\')">';
      }
      o += authorizedText + '</a><br>';
    }
    if (installedVersion == "0,0,0,0") {
      o += '<br>' + installDecoderText1;
      if (authorized == "yes") {
        o += '<br>' + installDecoderText2;
      }
    } else {
      o += '<br>' + installDecoderText2;
    }
  }
  document.write(o + '<br></OBJECT>');
}

function drawMpeg4Dec(height, width, ImagePath, CLSID_AMC, cab, ver_AMC)
{
  document.write('<OBJECT ID="Decoder" height="' + height + '" width="' + width + '" border="0" CLASSID="CLSID:' + CLSID_AMC + '" CODEBASE="/activex/decoder/' + cab + '#version=' + ver_AMC + '" STANDBY="Loading Axis Media Control components..."><br></OBJECT>');
}

function drawAacDec(height, width, ImagePath, CLSID_AAC_dec, cab, ver_AAC_dec)
{
  document.write('<OBJECT ID="aac" height="' + height + '" width="' + width + '" border="0" CLASSID="CLSID:' + CLSID_AAC_dec + '" CODEBASE="/activex/decoder/' + cab + '#version=' + ver_AAC_dec + '" STANDBY="Loading Axis Media Control components..."></OBJECT>');
}

function DrawAMC(prodName, ID, height, width, ImagePath, CLSID_AMC, cab, ver_AMC, ShowAMCToolbar, ptzgui, useWithCam, CamNbr, UseRel, ShowRelCross, ShowSVG, UseMotion, UseAudio, rtspPort, external, installText1, text, installText2, installText3, installText4, mediaRecording, extra, enableAreaZoom, maintainAspectRatio ) // NOTE: extra = "yes" -> 207, extra = "9999" means centermode (zoom=9999) is activated in 212PTZ, extra = "recording" -> recording playback, otherwise extra should be "no" or undefined.
{
  var host = getHost(ImagePath);
  var confHost = getCurrentHostAndProt();

  var mpeg4 = ImagePath.indexOf("mpeg4") != -1;
  var h264 = ImagePath.indexOf("h264") != -1;
  var mjpg = ImagePath.indexOf("mjpg") != -1;
  var mpeg2 = ImagePath.indexOf("mpeg2") != -1;
  var multicast = ImagePath.indexOf("sdp") != -1;

  var o = '<OBJECT ID="Player" height="' + height + '" width="' + width + '" border="0" CLASSID="CLSID:' + CLSID_AMC + '" CODEBASE="/activex/' + cab + '#version=' + ver_AMC + '" STANDBY="Loading Axis Media Control components...">';
  if ((mpeg4 || h264) && external == "no") {
    o += '<param name="MediaURL" value="' + host + ':' + rtspPort + '' + ImagePath + '">';
  } else if (ImagePath.indexOf("://") > 0 || external == "yes") {
    o += '<param name="MediaURL" value="' + ImagePath + '">';
  } else {
    o += '<param name="MediaURL" value="' + host + ImagePath + '">';
  }
  var MediaType;
  if (mpeg4) {
    MediaType = "mpeg4"
  } else if (h264) {
    MediaType = "h264"
  } else if (mpeg2) {
    if (multicast)
      MediaType = "mpeg2-multicast"
    else
      MediaType = "mpeg2-unicast"
  } else {
    MediaType = "mjpeg"
  }

  o += '<param name="MediaType" value="' + MediaType + '">';
  o += '<param name="Volume" value="' + (extra == "yes"?'70':'1') + '">'; // 207
  o += '<param name="ShowStatusBar" value="' + (ShowAMCToolbar == "yes"?'1':'0') + '">';
  o += '<param name="ShowToolbar" value="' + (ShowAMCToolbar == "yes"?'1':'0') + '">';
  o += '<param name="AutoStart" value="' + (UseAudio == "yes"?'0':'1') + '">';
  o += '<param name="StretchToFit" value="' + (((UseMotion == "yes") || (external == "yes"))?'0':'1') + '">';

  if ((ptzgui == "yes") && (useWithCam == "yes")) {
    extra += ""
    o += '<param name="PTZControlURL" value="' + confHost + '/axis-cgi/com/ptz.cgi?camera=' + CamNbr + (extra == "9999"?'&zoom=9999':'') + '">';
  }

  o += '<br><b>' + ID + '</b>&nbsp;' + installText1 + '&nbsp;' + text + '&nbsp;' + installText2 + '&nbsp;' + installText3 + '<br>' + ID + '&nbsp;' + installText4;
  document.write(o + '<br><br></OBJECT>');

  Player = document.getElementById("Player");
  if (Player.ShowToolbar) { // This line is essential when installing AMC or else volume and mute buttons will show until reload
    if (ShowAMCToolbar == "yes") {
      if (extra == "yes") { // = 207
        Player.ToolbarConfiguration = "+play,+snapshot,+fullscreen,+mute,+volume";
      }
    }
  }
  var installedVersion = "0,0,0,0";
  var requiredVersion = "5,5,5,0";
  var tooOldVersion = false;
  try {
    installedVersion = Player.GetVersionPart(CLSID_AMC,0);
    installedVersion += ',' + Player.GetVersionPart(CLSID_AMC,1);
    installedVersion += ',' + Player.GetVersionPart(CLSID_AMC,2);
    installedVersion += ',' + Player.GetVersionPart(CLSID_AMC,3);
  }
  catch(e) {}
  instVerArray = installedVersion.split(",");
  verReqArray  = requiredVersion.split(",");
  for (i=0; i<instVerArray.length; i++) {
    if (parseInt(verReqArray[i]) > parseInt(instVerArray[i])) {
      tooOldVersion = true;
      break;
    } else if (parseInt(verReqArray[i]) < parseInt(instVerArray[i])) {
      break;
    }
  }
  if (!tooOldVersion) {
    Player.MaintainAspectRatio = ( maintainAspectRatio && maintainAspectRatio != "")?((maintainAspectRatio == "yes")?"true":"false"):"true";
  }
  if (UseMotion == "yes") {
    Player.UIMode = "MDConfig";
    Player.MotionConfigURL = confHost + "/axis-cgi/operator/param.cgi?ImageSource=" + [CamNbr - 1]
    Player.MotionDataURL = confHost + "/axis-cgi/motion/motiondata.cgi";
  }

  if (ShowSVG == "yes") {
    Player.SvgDataURL = confHost + "/axis-cgi/iv/stream.cgi?channel=9";
  }

  activateContextMenu()

  if ((enableAreaZoom == "yes") && (useWithCam == "yes")) {
    Player.EnableJoystick = "True";
    Player.EnableAreaZoom = "True";
  }

  if (extra == "recording") {
    Player.EnableReconnect = "false"; // Don't start playback again when the recording has reached the end.
    // Don't display "Video lost" popup baloon when the recording has reached the end.
    // Display login dialog when necessary
    Player.Popups = 1;
  }
}

function getHost(ImagePath)
{
  var host;
  var indexOfAddr;

  indexOfAddr = ImagePath.indexOf("://");
  if (indexOfAddr > 0) {
    host = ImagePath.substring(0,indexOfAddr + 3);
  } else {
    if (ImagePath.indexOf("mpeg4") >= 0 || ImagePath.indexOf("h264") >= 0) {
      host = "rtsp://" + getIPv6HostName(location.hostname);
    } else {
      host = getCurrentHostAndProt();
    }
  }
  return host;
}

function getCurrentHostAndProt()
{
  return location.protocol + "//" + getIPv6HostName(location.hostname) + (location.port > 0 ?':' + location.port : "");
}

function getIPv6HostName(hostname)
{
  if (hostname.split(":").length > 1)
    hostname = "[" + hostname + "]"
  return hostname;
}
