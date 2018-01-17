// config load and save
#include <EEPROM.h>


bool loadConfig() {
  int address=2,delta=40;
  
  if (int(EEPROM.read(0)*256)+EEPROM.read(1)!=1965) {
    Serial.println("Config not defined or EEPROM read failed");
    Serial.println(String(EEPROM.read(0))+String(EEPROM.read(1))+" "+String(int(EEPROM.read(0)*256)+EEPROM.read(1)));
    return false;
  }
  for (int i=0;i<36;i++) {
    ssid[i]=EEPROM.read(address+i);
    if (ssid[i]==0) {
      break;
    }
  }
  address+=delta;  
  for (int i=0;i<36;i++) {
    password[i]=EEPROM.read(address+i);
    if (password[i]==0) {
      break;
    }
  }
  address+=delta;
                                               //Std, Küche, Durchg, Wohnz,  Schlaf
  IPStatic[3] = EEPROM.read(address++);          //10    12      11      13      14
  for (int i=0;i<4;i++) {
    SwitchPin[i] = EEPROM.read(address++);        //0     0       0       0       0
  }                                               //2     2       2       2       2
                                                  //5     5       5       5
                                                  //4     4       4       4
  for (int i=0;i<4;i++) {
    RelayPin[i] = EEPROM.read(address++);         //12    12      12      12      12
  }                                               //13    13      13      13      13
                                                  //14    14      14      14
                                                  //16    16      16      16
  //high byte first
  for (int i=0;i<4;i++) {
    windowTime[i] = ((EEPROM.read(address++)*256+EEPROM.read(address++))*256+EEPROM.read(address++))*256+EEPROM.read(address++);
  }                                                //5000  18800 19000   25200   19000
                                                  //10000 18500 19000   24200   19000
                                                  //5000  19200 19000   25200   19000
                                                  //10000 18700 19000   24200   19000 

  Serial.println(String(address));
  Serial.print("Loaded SSID: ");
  Serial.println(ssid);  
  Serial.print("Loaded parameters: ");
  Serial.println(password);

  return true;
}

void saveConfig() {
  int address=2, delta=40;
  long help;

  EEPROM.write(0, highByte(1965));
  EEPROM.write(1, lowByte(1965));
  Serial.println("write: "+String(highByte(1965))+String(lowByte(1965)));

  for (int i=0;i<36;i++) {
    EEPROM.write(address+i,ssid[i]);
    EEPROM.write(address+i+delta,password[i]);
  }
  Serial.print(ssid);
  Serial.println(password);
  
  EEPROM.write(address+delta-5,0);
  EEPROM.write(address+2*delta-5,0);
  address+=2*delta; 
  Serial.println(String(address));
                                              
  EEPROM.write(address++,IPStatic[3]);          
  for (int i=0;i<4;i++) {
     EEPROM.write(address++,SwitchPin[i]);      
  }                                             
  Serial.println(String(address));
  for (int i=0;i<4;i++) {
     EEPROM.write(address++,RelayPin[i]);         
  }                                             
  Serial.println(String(address));
  //high byte first
  for (int i=0;i<4;i++) {
    help = windowTime[i];
    EEPROM.write(address+3,lowByte(help));
    help = help/256;
    EEPROM.write(address+2,lowByte(help));
    help = help/256;
    EEPROM.write(address+1,lowByte(help));
    help = help/256;
    EEPROM.write(address,lowByte(help));
    address+=4;
  }                                                
  Serial.println(String(address));
  EEPROM.commit();
  Serial.print("Config saved and committed.");
}

void loadStandardValues(){
  ssid = "klaushome";
  password = "Johann1965";
  IPStatic[3] = 10;
  SwitchPin[0] = 0;
  SwitchPin[1] = 2;
  SwitchPin[2] = 5;
  SwitchPin[3] = 4;
  RelayPin[0] = 12;
  RelayPin[1] = 13;
  RelayPin[2] = 14;
  RelayPin[3] = 16;
  windowTime[0] = 5000;
  windowTime[1] = 10000;
  windowTime[2] = 5000;
  windowTime[3] = 10000;
  saveConfig();
  Serial.println("Standard Config set");  
}



