#include <SoftwareSerial.h>

//SoftwareSerial mySerial(19,18); // RX, TX

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);//기본 통신 속도가 9600인 제품은 9600으로 수정해 주세요
}

void loop() {
  if (Serial3.available()) {
    Serial.write(Serial3.read());
  }
  if (Serial.available()) {
    Serial3.write(Serial.read());
  }
}
