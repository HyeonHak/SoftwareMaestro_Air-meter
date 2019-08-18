#include <Wire.h>
#include <HDC1080.h>
#include <SoftwareSerial.h>

HDC1080 hdcSensor;

float tc, tf, h;
const int temperaturePin = 0;
const int TX = 2;
const int RX = 3;
SoftwareSerial BLE(TX,RX);


void setup() {
  Serial.begin(9600);
  Wire.begin();
  BLE.begin(9600);
  Serial.println("Setting...");
  
  hdcSensor.turnOnHeater(true);
  hdcSensor.setTemperatureRes(HDC1080::T_RES_14);
  hdcSensor.setHumidityRes(HDC1080::H_RES_8);
  hdcSensor.updateConfigRegister();
  Serial.println("Setting end...");
}

void loop() {

  int humid;
  int Temperate;
  
  char str_humid[10];
  char str_Temperate[10];
  /*
   * 현재는 정수형을 입력하지만 실수형으로 변경
   */

  
  tf = hdcSensor.getTemperatureHumidity(tc, h);
  Temperate = (int)tc;
  humid = (int)h;

  Serial.print(tc);
  Serial.print("C ");
  Serial.print(h);
  Serial.println("H");
  
  
  sprintf(str_Temperate,"%d",Temperate); //센서값 char*형변환
  sprintf(str_humid,"%d",humid); //센서값 char*형변환
  

  BLE.write(" ");
  BLE.write(str_Temperate);
  BLE.write(str_humid);

  delay(1000); 
}
