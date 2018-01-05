// Handling WiFi and HTTP for window shades

// functions to handle http requests
void handleRoot() {

  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

 Serial.println("root");
 
  snprintf ( temp, 400,
"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Rollo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from Shades Master ESP8266!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <hl>_______________</hl>\
  </body>\
</html>",

    hr, min % 60, sec % 60
  );
  serverWS.send ( 200, "text/html", temp );
}
//select pins for switches and relays
void handlePin() {
}    
//adjust timing for Up and Down of shades
void handleTiming() {
} 
//set new SSID and password
void handleWiFi() {
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
 
  Serial.println("post TP window " + String(_window)+"."+serverWS.args());
    serverWS.send ( 200, "text/html", "" );

  Serial.println(serverWS.uri());
  Serial.println();
  if (serverWS.hasArg("value") ){ 
    int newTargetPosition = serverWS.arg("value").toInt();
    if (newTargetPosition == 0 && serverWS.arg("value") != "0") {
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
    Serial.println("wrong argument");
    handleNotFound();
  }
}

void handleTargetPosition0 () {  handleNotFound(); handleTargetPosition(0);}
void handleTargetPosition1 () {handleTargetPosition(1);}

