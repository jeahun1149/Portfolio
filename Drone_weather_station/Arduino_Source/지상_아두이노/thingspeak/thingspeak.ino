#include <SoftwareSerial.h> /* 블루투스 라이브러리 설정 */
#include <ESP8266WiFi.h> /* wifi 라이브러리 설정 */
#include <Wire.h> /* I2C 통신 라이브러리 설정*/
#include <LiquidCrystal_I2C.h> /* I2C LCD 라이브러리 설정*/
SoftwareSerial BT(12,13); //Connect HC-06 TX,RX 
LiquidCrystal_I2C lcd(0x27, 16, 2); /* lcd 해상도 설정 */
// replace with your channel’s thingspeak API key,
String apiKey = "CSVMXT4A4757B3F1";  // 여기에 API키값을 입력합니다.
const char* ssid = "TP-LINK_POCKET_3020_4083F8"; // ESP8266이 연결되는 SSID 입니다.
const char* password = "80090038"; // 비밀번호입니다.
const char* server = "api.thingspeak.com";

#define DHTPIN_A 13 // what pin we’re connected to
#define DHTPIN_B 12 // second dht11
/*
DHT dht1(DHTPIN_A, DHT11,15); //15번 카운트 값을 가져온다는 의미입니다. DHT 라이브러리를 참조하시면 됩니다.
DHT dht2(DHTPIN_B, DHT11,15);
*/
WiFiClient client;


String Connect = "DisConnect";
void setup() {
Serial.begin(9600); // 시리얼포트 연결
BT.begin(9600);//블루투스 연결
/* lcd 설정 */
lcd.begin(4,5);  // sda=0, scl=2
lcd.backlight(); //
lcd.print("Booting...");
delay(1000);


lcd.clear();
lcd.setCursor(0,0);
lcd.print("WiFi");
lcd.setCursor(0,1);
lcd.print("Connecting...");
delay(500);
/* wifi 연결 */
WiFi.begin(ssid, password);

Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print("wait..");
}

Serial.println("");
Serial.println("WiFi connected");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("WiFi");
lcd.setCursor(0,1);
lcd.print("Connected!!!");
delay(500);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Data");
lcd.setCursor(0,1);
lcd.print("Loading...");
}







void loop() {
  /* 블루투스를 통해 받은 데이터를 thingspeak로 전송 */
  if (BT.available()){
 String data = BT.readString();
 Serial.println(data);
 int TempIndex = data.indexOf('A');
 int HumiIndex = data.indexOf('B',TempIndex+1);
 int DustIndex = data.indexOf('C',HumiIndex+1);
 int UVIndex = data.indexOf('D',DustIndex+1);
 int APIndex = data.indexOf('E',UVIndex+1);
 String TempString = data.substring(TempIndex+1,HumiIndex);
String HumiString = data.substring(HumiIndex+1);
String DustString = data.substring(DustIndex+1);
String UVString = data.substring(UVIndex+1);
String APString = data.substring(APIndex+1);
int Temp = TempString.toInt();
int Humi = HumiString.toInt();
int Dust = DustString.toInt();
String AP = APString;
int UV = UVString.toInt();
 Serial.println(Temp);
 Serial.println(Humi);
 Serial.println(Dust);
 Serial.println(AP);
 Serial.println(UV);


  if (client.connect(server,80)) { // "184.106.153.149" or api.thingspeak.com
String postStr = apiKey;
postStr +="&field1=";
postStr += String(Temp);
postStr +="&field2=";
postStr += String(Humi);
postStr +="&field3=";
postStr += String(Dust);
postStr +="&field4=";
postStr += String(AP);
postStr +="&field5=";
postStr += String(UV);
postStr += "\r\n\r\n";
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);
Serial.println("=========================");
Serial.print("Temp : ");
Serial.println(Temp);
Serial.print("Humi : ");
Serial.println(Humi);
Serial.print("Dust " );
Serial.println(Dust);
Serial.print("AP : ");
Serial.println(AP);
Serial.print("UV : ");
Serial.println(UV);
Serial.println("% send to Thingspeak");
}

client.stop();

Serial.println("Waiting…");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("T:" + String(Temp) + " D:" + String(Dust) + " U:" + String(UV));
lcd.setCursor(0,1);
lcd.print("H:" + String(Humi) + " A:" + String(AP) + "atm");
// thingspeak needs minimum 15 sec delay between updates
//delay(40000);  // 데이터를 천천히 받기 위함 딜레이
  }
}
