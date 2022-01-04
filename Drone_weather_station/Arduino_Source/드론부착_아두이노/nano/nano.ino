/* Pin 설정 */
#define DU_PIN 8
#define UV_PIN A2
#define LED_PIN 7
#define DHT_PIN 4
#define DHTTYPE DHT22

/* 라이브러리 설정 */
#include <SoftwareSerial.h> 
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>

SoftwareSerial BT(2,3); //Connect HC-06 TX,RX 
DHT dht(DHT_PIN, DHTTYPE);
Adafruit_BMP085 bmp;

/* 변수 설정 */
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0.0;
float calcVoltage = 0.0;
float dustDensity = 0.0;
float ratio = 0;
float concentration = 0;
float posPerCF = 0;
float Dust = 0;



unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;//sampe 30s ;
unsigned long lowpulseoccupancy = 0;
void setup()  
{
  Serial.begin(9600); //시리얼포트 연결
  BT.begin(9600);//블루투스 연결
  dht.begin(); //온습도 센서 연결
  bmp.begin(); //기압 센서 연결
  pinMode(LED_PIN,OUTPUT);
  pinMode(DU_PIN,INPUT);
  starttime = millis();//get the current time;
}
void loop()
{ 
  // 먼지센서 측정
  duration = pulseIn(DU_PIN, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  int sensorValue;
  long  sum = 0;
  // 자외선 측정
  for (int i = 0; i < 1024; i++)
  {
    sensorValue = analogRead(UV_PIN);
    sum = sensorValue + sum;
    delay(2);
  }
  sum = sum >> 10;

  if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    posPerCF = concentration * 100;
    Dust = posPerCF / 7000;
    lowpulseoccupancy = 0;
 //온습도 측정 및 수집된 데이터 지상으로 전송
  float Temp = dht.readTemperature();
  float Humi = dht.readHumidity();
  int UV = sum * 4980.0 / 1023.0;
  float AP = (bmp.readPressure()/100)/1013.25;
  String TempS = String(Temp);
  String HumiS = String(Humi);
  String DustS = String(Dust);
  String UVS = String(UV);
  String APS = String(AP);
  String result = "A"+TempS+"B"+HumiS+"C"+DustS+"D"+UVS+"E"+APS;
  if (BT.available()){
    Serial.write(BT.read());}
  if (Serial.available())
    BT.write(Serial.read());
    Serial.println(result);
    BT.print(result);
    starttime = millis();
  }
}
