# 숨좀쉬자(PleaseBreath) - Arduino (In / Out Air Quality Sensor)
> 공기 청정 기기를 제어하여 실내 환경을 쾌적하게 만드는 AI　공기 관리 솔루션

![pb](./image/pb.png)

## 파일 설명 

air_quality_sensor - 온습도센서 값을 char*형으로 변환해 bluetooth통신으로 전달

## 실행 방법

Compile with Arduino IDE

## 와이파이 연결 방법
https://blog.naver.com/roboholic84/221261124179
- AT 명령어 무반응 
툴 -> 프로그래머 USBasp로 되어 있는지 확인
AT+UART_DEF=9600,8,1,0,0를 시리얼에서 입력하고 mySerial(9600)으로 변경할 것.
이미 9600으로 되어있다면 115200으로 변경하고 컴파일 후 실행
와이파이 모드 변경 : AT+CWMODE=1
와이파이 목록 명령어 : AT+CWLAP
와이파이 접속 명령어 : AT+CWJAP="SSID","PASS"


## 업데이트 내역

* 0.0.1
    * 작업 진행 중
    * 미세먼지 센서 + 온습도 센서
    * 와이파이 모듈 연결 확인
* 0.1.0
    * 와이파이 Time Out 문제 해결
        * Client Repeating 가능하도록 수정
* 0.2.0
    * 미세먼지, 온습도, Voc 센서
    * 각 센서코드는 Hyeon Branch
    
## 개발자

민필규 – pilgyu147@gmail.com

[https://github.com/pilgyumin](https://github.com/pilgyumin/)

안유진 - ujahnn@gmail.com

[https://github.com/ahnyujin](https://github.com/ahnyujin/)

조현학 - zhh102000@gmail.com

[https://git.swmgit.org/zhh1020](https://git.swmgit.org/zhh1020/)    