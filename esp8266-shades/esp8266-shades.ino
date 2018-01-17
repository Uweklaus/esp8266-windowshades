/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 */

char* ssid="1234567890123456789012345678901234567890";
char* password="A234567890123456789012345678901234567890";
byte IPStatic [4] = {192,168,2,10};
byte IPdns [4] = {192,168,2,1};
byte IPSub [4] = {255,255,255,0};
byte SwitchPin [4] = {5,4,0,2}; // UP_Window 1, DOWN, UP_Window 2, DOWN D1,D2,D3,D4
byte RelayPin [4] = {12,13,14,16}; //UP_Window 1, DOWN, UP_Window 2, DOWN D6,D7,D5,D0
long windowTime [4] = {1000,2000,3000,4000}; //Window 1Up, 2Up, 1Down, 2Down
const char* ssidAP = "ESPap";
const char* passwordAP = "YOURPASSWORD";

#include "settings.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// WiFiServer server(1337);  // 80
ESP8266WebServer serverWS(80);

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


String msg_err = "";
String old_msg = "";

// für initialisierung - Rollo(s) soll komplett hochgefahren werden bei Start
int currentPosition [2] = {100,100};
int targetPosition [2] = {100,100};
PositionState positionState [2] = {PS_STOPPED, PS_STOPPED};

TaskManager taskManager;
#include "ShadesTask.h"  // muss hier stehen, da taskManager verwendet wird


void Handle_SWITCH1_UP(ButtonState state);
void Handle_SWITCH1_DOWN(ButtonState state);
void Handle_SWITCH2_UP(ButtonState state);
void Handle_SWITCH2_DOWN(ButtonState state);

void Handle_Window1_Move(bool x, int state){};
void Handle_Window2_Move(bool x, int state){};

void Handle_Check_Client(uint32_t deltaTime);


// foreward delcare functions passed to task constructors now required
ButtonTask SWITCH1_UP_Task(Handle_SWITCH1_UP, SwitchPin[0]);
ButtonTask SWITCH1_DOWN_Task(Handle_SWITCH1_DOWN, SwitchPin[1]);
ButtonTask SWITCH2_UP_Task(Handle_SWITCH2_UP, SwitchPin[2]);
ButtonTask SWITCH2_DOWN_Task(Handle_SWITCH2_DOWN, SwitchPin[3]);
MoveTask Windows1_Move_Up_Task (Handle_Window1_Move,false,1);
MoveTask Windows1_Move_Down_Task (Handle_Window1_Move,false,0);
MoveTask Windows2_Move_Up_Task (Handle_Window2_Move,true,1);
MoveTask Windows2_Move_Down_Task (Handle_Window2_Move,true,0);
FunctionTask Check_Client_Task(Handle_Check_Client, MsToTaskTime(20));


int wCounter = 0;
bool noWiFi = false;

// functions to handle http requests
#include "handleWiFi.h"
#include "handleWiFiAP.h";
/*
 * Setup
 */
void setup() {
  Serial.begin(115200);
  delay(10);  // überspielt Zeichen beim Reset
  Serial.println();
  Serial.println("Starting...");

  EEPROM.begin(512);
  delay(10);
  //EEPROM.write(0,0);
  if (!loadConfig()) {
    Serial.println("Standard values will be loaded");
    loadStandardValues();
  } else {
    Serial.println("Config loaded");
  }

  // Definition Eingangs und Ausgangs Pins, HIGH = nicht aktiv
  for (int i=0;i<4;i++) {
    pinMode (SwitchPin[i], INPUT_PULLUP);
    pinMode (RelayPin[i], OUTPUT);
    digitalWrite(RelayPin[i], HIGH);
  }
  
  Serial.println("");  
  Serial.println("Firmware V 0.1.0");
  Serial.println("Pin I/O state defined");
  Serial.println("");
  Serial.println("Shades should be initially open...");
  Serial.println("");
  
  // config static IP
  IPAddress ip(IPStatic[0],IPStatic[1],IPStatic[2],IPStatic[3]); // where xx is the desired IP Address
  IPAddress gateway(IPdns[0],IPdns[1],IPdns[2],IPdns[3]); // set gateway to match your network
  IPAddress subnet(IPSub[0],IPSub[1],IPSub[2],IPSub[3]); // set subnet mask to match your network
  WiFi.config(ip, gateway, subnet);
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.println(WiFi.SSID());
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    wCounter += 1;
    delay(500);
    Serial.print(".");
    if (wCounter > 30) {
      wCounter=0;
      noWiFi=true;
      break;
    }
  }
  Serial.println("");
  if (noWiFi) { 
    Serial.println("WiFi not connected - Standalone"); 
    Serial.println("Configuring access point...");
    WiFi.softAP(ssidAP, passwordAP);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.print("AP SSID: ");
  Serial.println(ssidAP);
  Serial.print("AP password: ");
  Serial.println(passwordAP);
  
  serverWS.on("/", handleAPRoot);
  serverWS.on("/ssid",handleAPSSID);
  serverWS.on("/standard",loadStandardValuesAP);
  
  serverWS.begin();
  Serial.println("HTTP AP server started"); 
  }
  else { 
    Serial.println("WiFi connected");
    if (MDNS.begin("esp8266")) {
      Serial.println("MDNS responder started");
    }

// Server command definition
    #include "WiFiTask.h"

// Start the server
    //    server.begin();
    serverWS.begin();
    Serial.println("Server started");
    Serial.println(WiFi.localIP());
  }

// Tasks definieren und starten
  taskManager.StartTask(&SWITCH1_UP_Task);
  taskManager.StartTask(&SWITCH1_DOWN_Task);
  taskManager.StartTask(&SWITCH2_UP_Task);
  taskManager.StartTask(&SWITCH2_DOWN_Task);

  taskManager.StopTask(&Windows1_Move_Up_Task);
  taskManager.StopTask(&Windows1_Move_Down_Task);  
  taskManager.StopTask(&Windows2_Move_Up_Task);
  taskManager.StopTask(&Windows2_Move_Down_Task);
  taskManager.StartTask(&Check_Client_Task);  //listening to WiFi 

  Serial.println("Running...");
}

/*
 * Loop
 */
void loop() {

  taskManager.Loop();


}

// HTTP Client
void Handle_Check_Client(uint32_t deltaTime) { 
  serverWS.handleClient();
}



#include "shadeswitches.h"; // includes switch_handling
#include "window_function.h"; // includes windowshade_handling
