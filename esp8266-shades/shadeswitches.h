// Handling switches for window shades
void openWindow(bool window);
void closeWindow(bool window);
void stopWindow(bool window);

void Call_SWITCH (bool _window, Direction _dir)
{
  switch (positionState[_window])
  {
  case PS_INCREASING:
    stopWindow(_window); // Rollo 1 anhalten
    break;
  case PS_DECREASING:
    stopWindow(_window);
    break;
  case PS_STOPPED:
    if (_dir == UP)
    {
 //     currentPosition [_window]=0; // Volle Zeit hochfahren
      targetPosition [_window]=100;
      openWindow(_window);
    }
    else
    {
 //     currentPosition [_window]=100; // Volle Zeit hochfahren
      targetPosition [_window]=0;
      closeWindow(_window);
    } 
    break;
  }
}

void Handle_SWITCH1_UP(ButtonState _state)
{   
  if (_state == ButtonState_Pressed) { 
    Serial.println ("Switch 1 Up pressed" );
    Call_SWITCH (0, UP); 
  } // apply on press
}

void Handle_SWITCH1_DOWN(ButtonState _state)
{
  if (_state == ButtonState_Pressed) { 
    Serial.println ("Switch 1 Down pressed" );
    Call_SWITCH (0, DOWN); 
  }
}

void Handle_SWITCH2_UP(ButtonState _state)
{
  if (_state == ButtonState_Pressed) { 
    Serial.println ("Switch 2 Up pressed" );
    Call_SWITCH (1, UP); 
    }
}

void Handle_SWITCH2_DOWN(ButtonState _state)
{
  if (_state == ButtonState_Pressed) { 
    Serial.println ("Switch 2 Down pressed" );
    Call_SWITCH (1, DOWN); 
  }
}

