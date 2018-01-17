// HTTP requests are defined here


serverWS.on("/", handleRoot);

serverWS.on("/standard",loadStandardValues);

serverWS.on("/root",handleAPRoot);
serverWS.on("/ssid",handleAPSSID);


serverWS.on("/favicon.ico", HTTP_GET, [](){   
  Serial.println("get icon");
});

serverWS.on("/setupTime", handleTiming);
serverWS.on("/setupPin", handlePin);
serverWS.on("/Tpost", handleTPost);
serverWS.on("/Ppost", handlePPost);
serverWS.on("/save", handleSave);

serverWS.on("/window/0/currentPosition", HTTP_GET, [](){   
  serverWS.send(200, "application/json", String(currentPosition[0]) );
  Serial.println("get CP0 "+String(currentPosition[0]));
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
  
serverWS.on("/window/0/targetSetPosition", HTTP_POST, handleTargetPosition0);
  
serverWS.on("/window/1/targetSetPosition", HTTP_POST, handleTargetPosition1);


serverWS.onNotFound(handleNotFound);


