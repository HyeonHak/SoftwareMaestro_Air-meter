#include <SoftwareSerial.h> 
#include <Wire.h>
#include <HDC1080.h>

SoftwareSerial mySerial(5, 11); // RX, TX 

HDC1080 hdcSensor;
float tc, tf, h;
unsigned char  pms[32]; 

void setup() { 
  // initialize digital pin LED_BUILTIN as an output. 
   
  pinMode(LED_BUILTIN, OUTPUT); 
  Serial.begin(9600); 
  mySerial.begin(9600); 
  Wire.begin();
  hdcSensor.turnOnHeater(true);
  hdcSensor.setTemperatureRes(HDC1080::T_RES_14);
  hdcSensor.setHumidityRes(HDC1080::H_RES_8);
  hdcSensor.updateConfigRegister();
  Serial.println("Setting..");
} 

void loop() { 
  
  if(mySerial.available()>=32){ 

    for(int j=0; j<32 ; j++){ 
      pms[j]=mySerial.read(); 
    } 
     
    int PM1_0=(pms[10]<<8)  | pms[11]; 
    int PM2_5=(pms[12]<<8)  | pms[13];
    int PM10 =(pms[14]<<8)  | pms[15];
    
    Serial.print("PM1.0 : "); 
    Serial.print(PM1_0);
    Serial.print(" PM2.5 : "); 
    Serial.print(PM2_5);
    Serial.print(" PM1.0 : "); 
    Serial.println(PM10);
    tf = hdcSensor.getTemperatureHumidity(tc, h);
  
  
    Serial.print(tc);
    Serial.print("C ");
    Serial.print(h);
    Serial.println("H");

  }
  
  
}
