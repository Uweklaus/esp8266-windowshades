// Handling WiFi and HTTP for window shades

// functions to handle http requests

void handleSave (){
  char temp[256];  
    saveConfig();
    Serial.println("Config saved");
    snprintf ( temp, 256,
"<html><head><title>ESP8266 Timing Setup</title>\
<meta http-equiv='refresh' content='3; URL=/'></head>\
<body>Config saved to EEPROM</body></html>");
  serverWS.send ( 200, "text/html", temp );
}

void handleTPost() {
  char temp[256];  

  for ( uint8_t i = 0; i < serverWS.args(); i++ ) {
    windowTime[i] = serverWS.arg(i).toInt();
  }
  snprintf ( temp, 256,

"<html><head><title>ESP8266 Timing Setup</title>\
<meta http-equiv='refresh' content='3; URL=/'></head>\
<body><b>Do NOT forget to SAVE the values!</b></body></html>");
  serverWS.send ( 200, "text/html", temp );
}

void handleTiming() {
  char temp[1000]; 
  snprintf ( temp, 1000,
"<html><head><title>ESP8266 Timing Setup</title>\
<style> body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088;}</style></head>\
<body><h1>Timing Shades Master ESP8266</h1>\
<form><table style='width:50%' border='1' cellpadding='1' cellspacing='1' summary=''>\
<tr><th></th><th>UP</th><th>DOWN</th></tr>\
<tr><td>Window 1</td>\
<td><input type='number' name='W1tu' value=%00d></td>\
<td><input type='number' name='W1td' value=%00d></td></tr>\
<tr><td>Window 2</td>\
<td><input type='number' name='W2tu' value=%00d></td>\
<td><input type='number' name='W2td' value=%00d></td></tr></table>\
<button type='submit' formmethod='post' formaction='/Tpost' formtarget='_self'>Save</button>\
</form></body> </html>",

    windowTime[0], windowTime[1],windowTime[2], windowTime[3]
  );
  serverWS.send ( 200, "text/html", temp );
}

void handlePPost() {
  char temp[500];
  bool flag=true;
  int help=0,checksum1=0,checksum2=0; 
  for ( uint8_t i = 0; i < serverWS.args(); i++ ) {
    help = serverWS.arg(i).toInt();
    if (i==0|i==1|i==4|i==5){
      if (help==0|help==2|help==4|help==5){checksum1+=help;}
    }
    else {
      if (help==12|help==13|help==14|help==16){checksum2+=help;}      
    }
  }
  if (checksum1!=11|checksum2!=55) {flag=false;}
  if (flag) {
   SwitchPin[0]=byte(serverWS.arg(0).toInt());
   SwitchPin[1]=byte(serverWS.arg(1).toInt());
   RelayPin[0]=byte(serverWS.arg(2).toInt());
   RelayPin[1]=byte(serverWS.arg(3).toInt());   
   SwitchPin[2]=byte(serverWS.arg(4).toInt());
   SwitchPin[3]=byte(serverWS.arg(5).toInt());
   RelayPin[2]=byte(serverWS.arg(6).toInt());
   RelayPin[3]=byte(serverWS.arg(7).toInt());

  snprintf ( temp, 500,
  "<html><head><title>ESP8266 Pin Setup</title>\
  <meta http-equiv='refresh' content='3; URL=/'></head>\
  <body><b>Do NOT forget to SAVE the values!</b></body></html>");
  serverWS.send ( 200, "text/html", temp );
  }
  else {
  snprintf ( temp, 500,
  "<html><head><title>ESP8266 Pin Setup</title>\
  <meta http-equiv='refresh' content='5; URL=/setupPin'></head>\
  <body>Wrong Pin Assingment - Please correct.</body></html>");
  serverWS.send ( 200, "text/html", temp );
  }
}

void handlePin() {
  char temp[2000]; 
   
  snprintf ( temp, 2000,

"<html><head><title>ESP8266 Pin Setup</title>\
<style> body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head>\
<body><h1>Pin Setup Shades Master ESP8266</h1> <form action='/pin' method='post'>\
<table style='width:75%' border='1' cellpadding='1' cellspacing='1' summary=''>\
<tr><th></th><th>UP</th><th>DOWN</th></tr>\
<tr><td colspan='3'><b>Window 1</b></td></tr>\
<tr><td>Switches</td><td>\
<input type='number' size='2' maxlength='1' value=%00d name='W1su'/> 0,2,5,4</td>\
<td><input type='number' size='2' maxlength='1' value=%00d name='W1sd'/> 2,0,5,4</td></tr>\
<tr><td>Relays</td><td>\
<input type='number' size='2' maxlength='2' value=%00d name='W1ru'/> 12,13,14,16</td>\
<td><input type='number' size='2' maxlength='2' value=%00d name='W1rd'/> 13,12,14,16</td></tr>\
<tr><td colspan='3'><b>Window 2</b></td></tr>\
<tr><td>Switches</td><td>\
<input type='number' size='2' maxlength='1' value=%00d name='W2su'/> 5,4,0,2</td>\
<td><input type='number' size='2' maxlength='1' value=%00d name='W2sd'/> 4,5,0,2</td></tr>\
<tr><td>Relays</td>\
<td><input type='number' size='2' maxlength='2' value=%00d name='W2ru'/> 14,16,12,13</td>\
<td><input type='number' size='2' maxlength='2' value=%00d name='W2rd'/> 16,14,12,13</td></tr>\
</table>\
<input type='submit' value='Save' formmethod='post' formaction='/Ppost' formtarget='_self'/></form></body> </html>",

    SwitchPin[0], SwitchPin[1], RelayPin[0], RelayPin[1],
    SwitchPin[2], SwitchPin[3], RelayPin[2], RelayPin[3]
  );
  serverWS.send ( 200, "text/html", temp );

}
 

void handleRoot() {

  char temp[2000];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

 Serial.println("root");
  snprintf ( temp, 2000,
  "<html> \
  <head> <meta http-equiv='refresh' content='5'/>\
<title>ESP8266 Window Shades</title>\
<style> body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head>\
  <body><h1>ESP8266 Window Shades Master</h1>\
<p>Uptime: %02d:%02d:%02d</p>\
<p> SSID: %s</p><p>IP-Address:%00d.%00d.%00d.%00d</p>\
<table style='width:70%' border='1' cellpadding='1' cellspacing='1' summary=''>\
<tr><th>POSITION</th><th>Current</th><th>Target</th><th>State</th></tr>\
<tr><td><b>Window 1</b></td><td align='center'>%00d</td><td align='center'>%00d</td><td align='center'>%00d</td></tr>\
<tr><td><b>Window 2</b></td><td align='center'>%00d</td><td align='center'>%00d</td><td align='center'>%00d</td></tr>\
</table><br>\
<table style='width:50%' border='1' cellpadding='1' cellspacing='1' summary=''>\
<tr><th></th><th>UP</th><th>DOWN</th></tr>\
<tr><td colspan='3'><b>Window 1</b></td></tr>\
<tr><td>Switches</td><td align='center'>%00d</td>\
<td align='center'>%00d</td></tr>\
<tr><td>Relays</td><td align='center'>%00d</td>\
<td align='center'>%00d</td></tr>\
<tr><td>Timing</td><td align='center'>%00d</td>\
<td align='center'>%00d</td></tr>\
<tr><td colspan='3'><b>Window 2</b></td></tr>\
<tr><td>Switches</td><td align='center'>%00d</td>\
<td align='center'>%00d</td></tr>\
<tr><td>Relays</td><td align='center'>%00d</td>\
<td align='center'>%00d</td></tr>\
<tr><td>Timing</td><td align='center'>%00d</td>\
<td align='center'>%00d</td></tr>\
</table>\
<form> <button type='submit' formmethod='get' formaction='/setupPin' formtarget='_self'> Setup Pins </button> \
<button type='submit' formmethod='get' formaction='/setupTime' formtarget='_self'> Setup Timing </button> \
<button type='submit' formmethod='get' formaction='/save' formtarget='_self'> Save_Config </button><br>\
<button type='submit' formmethod='get' formaction='/root' formtarget='_self'> Set_SSID </button> \
<button type='submit' formmethod='get' formaction='/standard' formtarget='_self'> Set Standard Values </button>\
</form></body> </html>",

    hr, min % 60, sec % 60,
    ssid,IPStatic[0],IPStatic[1],IPStatic[2],IPStatic[3],
    currentPosition[0],targetPosition[0],positionState[0],
    currentPosition[1],targetPosition[1],positionState[1],
    SwitchPin[0], SwitchPin[1], RelayPin[0], RelayPin[1],
    windowTime[0], windowTime[1],
    SwitchPin[2], SwitchPin[3], RelayPin[2], RelayPin[3],
    windowTime[2], windowTime[3]
  );
  serverWS.send ( 200, "text/html", temp );
}

  void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += serverWS.uri();
  message += "\nMethod: ";
  message += (serverWS.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += serverWS.args();
  message += "\n";
  for (uint8_t i=0; i<serverWS.args(); i++){
    message += " " + serverWS.argName(i) + ": " + serverWS.arg(i) + "\n";
  }
  serverWS.send(404, "text/plain", message);
  Serial.println(message);
  }


void handleTargetPosition(bool _window) {
 
  Serial.println("set TP window " + String(_window)+"."+serverWS.args());
    serverWS.send ( 200, "text/html", "" );

  Serial.println(serverWS.uri());
  Serial.println(serverWS.arg(0));
  Serial.println(serverWS.argName(0));
  Serial.println();
  if (serverWS.args()!=0 ){ 
    int newTargetPosition = serverWS.arg(0).toInt();
    if (newTargetPosition == 0 && serverWS.arg(0) != "0") {
    Serial.println("hTP wrong argument"+String(serverWS.args())+"/"+String(serverWS.arg("value")));   
      handleNotFound();
      return;
    }

    if (newTargetPosition < 0 || newTargetPosition > 100
      || (targetPosition[_window] == -1 && newTargetPosition == currentPosition[_window])) {
      Serial.println("hTP out of range");         
      handleNotFound();
      return;
    }

    targetPosition[_window] = newTargetPosition;

    void closeWindow(bool _window);
    void openWindow(bool _window);
    
    Serial.println("Target position Window "+String(_window)+" :" + targetPosition[_window]);
    if (newTargetPosition < currentPosition[_window]) {
      closeWindow(_window);
    }
    if (newTargetPosition > currentPosition[_window]) {
      openWindow(_window);
    }
    serverWS.send(200, "text/plain", "OK");
  } 
  else {
    Serial.println("no arguments");
    handleNotFound();
  }
}

void handleTargetPosition0 () {handleTargetPosition(0);}
void handleTargetPosition1 () {handleTargetPosition(1);}

