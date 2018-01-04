// settings for kitchen shades

//Definition für Sensoren und Aktoren 
#define Standard //Standard,Kueche,Durchgang,Wohnzimmer,Schlafzimmer

#ifdef Standard
  uint8_t SwitchPin [4] = {5,4,0,2}; // UP_Window 1, DOWN, UP_Window 2, DOWN D1,D2,D3,D4
  uint8_t RelayPin [4] = {12,13,14,16}; //UP_Window 1, DOWN, UP_Window 2, DOWN D6,D7,D5,D0
  const int window_Time [4] = {5000,5000,10000,10000}; //Window 1Up, 2Up, 1Down, 2Down
  uint8_t IPStatic [4] = {192,168,2,10};
#endif

#ifdef Kueche
  uint8_t SwitchPin [4] = {5,4,0,2}; // UP_Window 1, DOWN, UP_Window 2, DOWN D1,D2,D3,D4
  uint8_t RelayPin [4] = {12,13,14,16}; //UP_Window 1, DOWN, UP_Window 2, DOWN D6,D7,D5,D0
  const int window_Time [4] = {18800,19200,18500,18700}; //Window 1Up, 2Up, 1Down, 2Down
  uint32_t IPStatic [4] = {192,168,2,12};
#endif

#ifdef Durchgang
  uint8_t SwitchPin [4] = {0,2,5,4}; // UP_Window 1, DOWN, UP_Window 2, DOWN D3,D4,D1,D2
  uint8_t RelayPin [4] = {12,13,14,16}; //UP_Window 1, DOWN, UP_Window 2, DOWN D6,D7,D5,D0
  const int window_Time [4] = {19000,19000,19000,19000}; //Window 1Up, 2Up, 1Down, 2Down
  uint32_t IPStatic [4] = {192,168,2,11};    
#endif

#ifdef Wohnzimmer
  uint8_t SwitchPin [4] = {0,2,5,4}; // UP_Window 1, DOWN, UP_Window 2, DOWN D3,D4,D1,D2
  uint8_t RelayPin [4] = {12,13,14,16}; //UP_Window 1, DOWN, UP_Window 2, DOWN D6,D7,D5,D0
  const int window_Time [4] = {25200,25200,24200,24200}; //Window 1Up, 2Up, 1Down, 2Down
  uint32_t IPStatic [4] = {192,168,2,13};
#endif

#ifdef Schlafzimmer
  uint8_t SwitchPin [4] = {0,2,5,4}; // UP_Window 1, DOWN, UP_Window 2, DOWN D3,D4,D1,D2
  uint8_t RelayPin [4] = {12,13,14,16}; //UP_Window 1, DOWN, UP_Window 2, DOWN D6,D7,D5,D0
  const int window_Time [4] = {19000,19000,19000,19000}; //Window 1Up, 2Up, 1Down, 2Down
  uint32_t IPStatic [4] = {192,168,2,14};    
#endif


// WiFi
const char* ssid = "klaushome";
const char* password = "Johann1965";


// static IP settings
uint8_t IPdns [4] = {192,168,2,1};
uint8_t IPSub [4] = {255,255,255,0};
