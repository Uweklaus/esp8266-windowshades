// HTTP requests are defined here


serverWS.on("/", handleRoot); //main page

serverWS.on("/setup/pin", handlePin);  //select pins for switches and relays

serverWS.on("/setup/timing", handleTiming); //adjust timing for Up and Down of shades

serverWS.on("/setup/WiFi", handleWiFi);  //set new SSID and password

serverWS.on("/inline", [](){
  serverWS.send(200, "text/plain", "this works as well");
});

serverWS.on("/window/0/currentPosition", HTTP_GET, [](){   
  serverWS.send(200, "application/json", String(currentPosition[0]) );
  Serial.println("get CP0 "+String(currentPosition[0]));
  handleNotFound();
});

serverWS.on("/window/1/currentPosition", HTTP_GET, [](){     //HM_GET
  serverWS.send(200, "application/json", String(currentPosition[1]) );
  Serial.println("get CP1 "+String(currentPosition[1]));
  });

serverWS.on("/window/0/positionState", HTTP_GET, [](){     //HM_GET
  serverWS.send(200, "application/json", String(positionState[0]) );
  Serial.println("get PS0 "+String(positionState[0]));
  });

serverWS.on("/window/1/positionState", HTTP_GET, [](){     //HM_GET
  serverWS.send(200, "application/json", String(positionState[1]) );
  Serial.println("get PS1 "+String(positionState[1]));
});

serverWS.on("/window/0/targetPosition", HTTP_GET, [](){     //HM_GET
  serverWS.send(200, "application/json", String(targetPosition[0]) );
    Serial.println("get TP0 "+String(targetPosition[0]));
});

serverWS.on("/window/1/targetPosition", HTTP_GET, [](){     //HM_GET
  serverWS.send(200, "application/json", String(targetPosition[1]) );
  Serial.println("get TP1 "+String(targetPosition[1]));
});
  
serverWS.on("/window/0/targetSetPosition", HTTP_GET, handleTargetPosition0);
  
serverWS.on("/window/1/targetSetPosition", HTTP_GET, handleTargetPosition1);


serverWS.onNotFound(handleNotFound);


