/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 */


//Definition für Sensoren und Aktoren
#define SWITCH1_UP_PIN 0  //D3
#define SWITCH1_DOWN_PIN 2 //D4
#define WINDOW1_UP_PIN 12 //D6
#define WINDOW1_DOWN_PIN 13 //D7

// 2.Rollo
#define SWITCH2_UP_PIN 4 //D2
#define SWITCH2_DOWN_PIN 5 //D1
#define WINDOW2_UP_PIN 14 //D5
#define WINDOW2_DOWN_PIN 16 //D0

#include <ESP8266WiFi.h>

const char* ssid = "klaushome";
const char* password = "Johann1965";

WiFiServer server(1337);  // 80

#include <Task.h> // für  Taskmanager Schaltertasks
// include sub files
#include "ButtonTask.h" // this implements the button task

enum PositionState { 
  PS_DECREASING = 0,
  PS_INCREASING = 1,
  PS_STOPPED = 2
};

enum Direction {
  UP = 0,
  DOWN = 1
};

enum HttpMethod {
  HM_NONE,
  HM_GET,
  HM_POST
};


// Zeit für hochfahren des Rollos
const int window_Up_Time [2] = {17400,17400}; //evtl. auch zweite Zeit für Down
String msg_err = "";
String old_msg = "";

// für initialisierung - Rollo(s) soll komplett hochgefahren werden bei Start
int currentPosition [2] = {100,100};
int targetPosition [2] = {100,100};
int previousPosition [2] = {100,100};
PositionState positionState [2] = {PS_STOPPED, PS_STOPPED};

TaskManager taskManager;
#include "ShadesTask.h"  // muss hier stehen, das taskManager verwendet wird


void Handle_SWITCH1_UP(ButtonState state);
void Handle_SWITCH1_DOWN(ButtonState state);
void Handle_SWITCH2_UP(ButtonState state);
void Handle_SWITCH2_DOWN(ButtonState state);

void Handle_Window1_Move(bool x){};
void Handle_Window2_Move(bool x){};

void Handle_Check_Client(uint32_t deltaTime);


// foreward delcare functions passed to task constructors now required
ButtonTask SWITCH1_UP_Task(Handle_SWITCH1_UP, SWITCH1_UP_PIN); 
ButtonTask SWITCH1_DOWN_Task(Handle_SWITCH1_DOWN, SWITCH1_DOWN_PIN); 
ButtonTask SWITCH2_UP_Task(Handle_SWITCH2_UP, SWITCH2_UP_PIN); 
ButtonTask SWITCH2_DOWN_Task(Handle_SWITCH2_DOWN, SWITCH2_DOWN_PIN);
MoveTask Windows1_Move_Task (Handle_Window1_Move,false);
MoveTask Windows2_Move_Task (Handle_Window2_Move,true);
FunctionTask Check_Client_Task(Handle_Check_Client, MsToTaskTime(20));


int wCounter = 0;
bool noWiFi = false;



/*
 * Setup
 */
void setup() {
  Serial.begin(115200);
  delay(10);  // überspielt Zeichen beim Reset

  // Definition Eingangs uns Ausgangs Pins
  pinMode(SWITCH1_UP_PIN, INPUT_PULLUP);
  pinMode(SWITCH1_DOWN_PIN, INPUT_PULLUP);
  pinMode(WINDOW1_UP_PIN, OUTPUT);
  pinMode(WINDOW1_DOWN_PIN, OUTPUT);
  pinMode(SWITCH2_UP_PIN, INPUT_PULLUP);
  pinMode(SWITCH2_DOWN_PIN, INPUT_PULLUP);
  pinMode(WINDOW2_UP_PIN, OUTPUT);
  pinMode(WINDOW2_DOWN_PIN, OUTPUT);

  digitalWrite(WINDOW1_UP_PIN, HIGH);
  digitalWrite(WINDOW1_DOWN_PIN, HIGH);
  digitalWrite(WINDOW2_UP_PIN, HIGH);
  digitalWrite(WINDOW2_DOWN_PIN, HIGH);

  Serial.println();
  Serial.println("Pin I/O state defined");
  Serial.println();

  // Calculate window opening / closing duration if necessary
  Serial.println("Shades should be initially open...");
  Serial.println();

  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    wCounter += 1;
    delay(500);
    Serial.print(".");
    if (wCounter > 30) 
    {
      wCounter=0;
      noWiFi=true;
      break;
    }
  }
  
  Serial.println("");
  if (noWiFi) { Serial.println("WiFi not connected"); }
  else { 
    Serial.println("WiFi connected"); 
    // Start the server
    server.begin();
    Serial.println("Server started");
    // Print the IP address, IP Adresse sollte fix sein.!!!
    Serial.println(WiFi.localIP());
  }



// Tasks definieren und starten
  taskManager.StartTask(&SWITCH1_UP_Task); 
  taskManager.StartTask(&SWITCH1_DOWN_Task); 
  taskManager.StartTask(&SWITCH2_UP_Task); 
  taskManager.StartTask(&SWITCH2_DOWN_Task); 
//  taskManager.StartTask(&checkPosition_Task);
  taskManager.StopTask(&Windows1_Move_Task);
  taskManager.StopTask(&Windows2_Move_Task);
  if (noWiFi)
  {
    taskManager.StopTask(&Check_Client_Task); // not listening to WiFi
  }
  else
  {
    taskManager.StartTask(&Check_Client_Task); //listening to WiFi
  }



  
  Serial.println("Running...");
}



/*
 * Loop
 */
void loop() {

  taskManager.Loop();

} 

#include "handleWiFi.h"
#include "WiFiTask.h"

#include "shadeswitches.h"; // includes switch_handling
#include "window_function.h"; // includes windowshade_handling





