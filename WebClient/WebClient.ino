/*
 WiFiEsp example: WebClient

 This sketch connects to google website using an ESP8266 module to
 perform a simple web search.

 For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/

#include "WiFiEsp.h"
#include <Wire.h>
#include <HDC1080.h>
// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include <SoftwareSerial.h>
SoftwareSerial Serial1(2, 3); // RX, TX
SoftwareSerial mySerial(5, 11);
#endif

char ssid[] = "pleasebreath";            // your network SSID (name)
char pass[] = "tnawhatnlwk1";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
int port = 3000;

char server[] = "192.168.0.9";


HDC1080 hdcSensor;
float tc, tf, h;
unsigned char  pms[32]; 

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  Wire.begin();
  hdcSensor.turnOnHeater(true);
  hdcSensor.setTemperatureRes(HDC1080::T_RES_14);
  hdcSensor.setHumidityRes(HDC1080::H_RES_8);
  hdcSensor.updateConfigRegister();
  
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);
  
  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  
  printWifiStatus();

  Serial.println();
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial
  
  if (client.connect(server, port)) {
    Serial.println("Connected to server");
    // Make a HTTP request
    //client.println("GET /asciilogo.txt HTTP/1.1");
    client.println("GET http://192.168.0.9:3000/?tempOuter=777");
    //client.println("Host: arduino.cc");
    //client.println("Connection: close");
    client.println();
  }

  
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them
  /*while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }*/

  if(client.connected()){
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
    String str = "GET http://192.168.0.9:3000/?tempOuter=";
    str+=tc;
    str+="humidOuter=";
    str+=h;
    str+="pm10Outer=";
    str+=PM10;
    str+="pm25Outer=";
    str+=PM2_5;
    client.println(str);
    
    client.println();
  }
  
  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server...");
    client.stop();

    // do nothing forevermore
    while (true);
  }
}


void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
