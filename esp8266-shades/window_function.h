// Handling switches for window shades

void stopWindow(bool _which) {
  Serial.println("Stop window ");
  msg_err="";
  if (_which) 
  {
    digitalWrite(WINDOW2_UP_PIN, HIGH);
    digitalWrite(WINDOW2_DOWN_PIN, HIGH);       
    taskManager.StopTask(&Windows2_Move_Task);
  }
  else {
    digitalWrite(WINDOW1_UP_PIN, HIGH);
    digitalWrite(WINDOW1_DOWN_PIN, HIGH);
    taskManager.StopTask(&Windows1_Move_Task);       
  }
  positionState[_which]=PS_STOPPED;
}

void closeWindow(bool _which) {
  Serial.println("Closing window ");
  if (_which) {
    // Relais schalten
    digitalWrite(WINDOW2_UP_PIN, HIGH);
    digitalWrite(WINDOW2_DOWN_PIN, LOW);       
    taskManager.StartTask(&Windows2_Move_Task);
    // Zeit festlegen
    // Task Starten zum runterfahren
  }
  else {
    // Relais schalten
    digitalWrite(WINDOW1_UP_PIN, HIGH);
    digitalWrite(WINDOW1_DOWN_PIN, LOW);       
    taskManager.StartTask(&Windows1_Move_Task);
  }
}

void openWindow(bool _which) {
  Serial.println("Opening window ");
  if (_which) {
    // Relais schalten
    digitalWrite(WINDOW2_UP_PIN, LOW);
    digitalWrite(WINDOW2_DOWN_PIN, HIGH);       
    taskManager.StartTask(&Windows2_Move_Task);
    // Zeit festlegen
    // Task Starten zum runterfahren
  }
  else {
    // Relais schalten
    digitalWrite(WINDOW1_UP_PIN, LOW);
    digitalWrite(WINDOW1_DOWN_PIN, HIGH);       
    taskManager.StartTask(&Windows1_Move_Task);
  }
}
