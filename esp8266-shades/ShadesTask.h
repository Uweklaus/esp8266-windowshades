// Relays should be attached to any io pin, when low, the relay active
// This includes  x 2 relays for windows shades. each one up other down. never both relays active to avoid programming mode

void stopWindow(bool _which);


// Positionsüberwachung beim Fahren erfolgt 100 mal pro Zeit fürs hoch/runterfahren

class MoveTask : public Task
{
public:
    typedef void(*action)(bool window,int state);

    MoveTask(action function,bool window, int state) :
        Task(MsToTaskTime(window_Time[window+2*state]/100)), // check every 1% of total shades move time
        _window(window),
        _state(state),
        _callback(function)
    { 
    };

private:
    const bool _window;
    const action _callback;
    int _state;
    
    virtual bool OnStart()
    {
      if (currentPosition[_window]<targetPosition[_window])       { 
        positionState[_window]=PS_INCREASING; //1
        } 
      else if (currentPosition[_window]>targetPosition[_window])  { 
        positionState[_window]=PS_DECREASING; //0
        } 
      else                                                        { 
        positionState[_window]=PS_STOPPED;    //2
        } 
        
      Serial.println("start moving window "+String(_window)+" "+String(positionState[_window])); 
      return true;
    }

    virtual void OnUpdate(uint32_t deltaTime)
    {
              
        switch (positionState[_window])
        {
        case PS_DECREASING:
          currentPosition[_window]-=1;
          Serial.println(" decr C"+String(currentPosition[_window])+" T"+String(targetPosition[_window])+" "+String(deltaTime));
          if (currentPosition[_window]<=targetPosition[_window]) 
          { 
            positionState[_window]=PS_STOPPED;
            stopWindow(_window); 
            if (currentPosition[_window]<0) 
            {
              currentPosition[_window]=0;
            }
          }
          break;
        case PS_INCREASING:
          currentPosition[_window]+=1;
          Serial.println(" incr C"+String(currentPosition[_window])+" T"+String(targetPosition[_window])+" "+String(deltaTime));
          if (currentPosition[_window]>=targetPosition[_window]) 
          { 
            positionState[_window]=PS_STOPPED;
            stopWindow(_window);  
            if (currentPosition[_window]>100) 
            {
              currentPosition[_window]=100;
            }
          }
          break;
        case PS_STOPPED:
          Serial.println("Already in endposition C"+String(currentPosition[_window])+" T"+String(targetPosition[_window]));
            positionState[_window]=PS_STOPPED;
            stopWindow(_window);            
          break;
        }
    }
};
