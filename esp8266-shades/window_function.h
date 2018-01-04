// Handling switches for window shades

void stopWindow(bool _window) {
  Serial.println("Stop window ");
  msg_err="";
  digitalWrite(RelayPin[_window*2], HIGH);
  digitalWrite(RelayPin[_window*2+1], HIGH); 
  
  if (_window) 
  {      
    taskManager.StopTask(&Windows2_Move_Up_Task);
    taskManager.StopTask(&Windows2_Move_Down_Task);
  }
  else {
    taskManager.StopTask(&Windows1_Move_Up_Task);
    taskManager.StopTask(&Windows1_Move_Down_Task);     
  }
  positionState[_window]=PS_STOPPED;
  targetPosition [_window]=currentPosition [_window];
}

void closeWindow(bool _window) {
  Serial.println("Closing window ");
  digitalWrite(RelayPin[_window*2], HIGH);// Relais schalten
  digitalWrite(RelayPin[_window*2+1], LOW); 
  
  if (_window) {
    taskManager.StartTask(&Windows2_Move_Down_Task);    // Task Starten zum runterfahren
  }
  else {
    taskManager.StartTask(&Windows1_Move_Down_Task);
  }
}

void openWindow(bool _window) {
  Serial.println("Opening window ");
  digitalWrite(RelayPin[_window*2], LOW );// Relais schalten
  digitalWrite(RelayPin[_window*2+1], HIGH); 

  if (_window) {       
    taskManager.StartTask(&Windows2_Move_Up_Task);     // Task Starten zum hochfahren
  }
  else {      
    taskManager.StartTask(&Windows1_Move_Up_Task);
  }
}
