// WiFi wird hier abgefragt in der loop mit dem Taskmanager


void Handle_Check_Client(uint32_t deltaTime) 
{ 
// Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Check if a client has connected
  Serial.println("New client");
   while (!client.available()){
    if (!client.connected()) {
      Serial.println("Client disonnected available");
      client.stop();
   
      return;
    } 
    delay(1);  
  }
  // Read the first line of the request
  //String req = client.readStringUntil('\r');
  String req;
  while (client.available()) {
    char c = client.read();
    req += c;
  }
  Serial.println();
  Serial.println("* "+req);
  client.flush();
  
  // Match the request
  String res;

  handleRequest(req, res, "/window/0/currentPosition", HM_GET,
    handleCurrentPosition);

  handleRequest(req, res, "/window/0/positionState", HM_GET,
    handlePositionState);

  handleRequest(req, res, "/window/0/targetPosition", HM_POST,
    handleTargetPosition);

  handleRequest(req, res, "/window/1/currentPosition", HM_GET,
    handleCurrentPosition1);

  handleRequest(req, res, "/window/1/positionState", HM_GET,
    handlePositionState1);

  handleRequest(req, res, "/window/1/targetPosition", HM_POST,
    handleTargetPosition1);

  if (res.length() == 0) {
    Serial.println("Invalid request" + req + res);
    client.stop();
     
    return;
  }
  client.flush();

  // Send the response to the client
  client.print(res);
  Serial.println("Client disonnected send" + String(res));

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
        
}

