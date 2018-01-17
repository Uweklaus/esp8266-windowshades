// HTTP requests are defined here

void loadStandardValuesAP() {
  char temp[512];

  Serial.println("standard config loaded");
  snprintf ( temp, 512,
"<html><head><title>ESP8266 load Standard</title>\
<meta http-equiv='refresh' content='3; URL=/'></head>\
<body>Standard Config loaded</body></html>");
  serverWS.send ( 200, "text/html", temp );
  loadStandardValues();
}

void handleAPSSID () {
  char temp[512];
  String help;
  
  help=serverWS.arg(0);
  Serial.println("APSSID"+help);
  if (help!="") {
    help.toCharArray(ssid,30);
  }
  help=serverWS.arg(1);
  Serial.println("pw"+help);
  if (help!=""){
    help.toCharArray(password,30);
  }
  help=serverWS.arg(2);
  Serial.println("192.168.2."+help);
  if (help!=""){
    IPStatic[3]=byte(help.toInt());
  }
  snprintf ( temp, 512,
"<html><head><title>ESP8266 SSID Setup</title>\
<meta http-equiv='refresh' content='10; URL=/'></head>\
<body>SSID Saved - waiting for Reset</body></html>");
  serverWS.send ( 200, "text/html", temp );
  saveConfig();
  delay(10);
    ESP.restart();
}

void handleAPRoot() {
  char temp[1000];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

 Serial.println("AProot");

  snprintf ( temp, 1000,
  "<html> \
  <head>\
<title>ESP8266 Window Shades AP</title>\
<style> body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head>\
  <body><h1>ESP8266 Window Shades Master AP</h1>\
<p>Uptime: %02d:%02d:%02d<br></p>\ 
<p>Please enter SSID and password</p>\
<form> SSID: <input type='text' name='SSID'><br>\
password: <input type='password' name='password'><br>\ 
IP_192.168.2.<input type='number' size='3' maxlength='3' name='IP_'/><br>\
<button type='submit' formmethod='post' formaction='/ssid' formtarget='_self'> Save </button>\
<button type='submit' formmethod='post' formaction='/standard' formtarget='_self'> load standard values </button>\
</form></body> </html>",

    hr, min % 60, sec % 60
  );
  serverWS.send ( 200, "text/html", temp );
}




