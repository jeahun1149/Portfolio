#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#ifndef UNIT_TEST
#include <Arduino.h>
#endif

//#define JODO A0
//#define DHT_PIN D6
//DHT11 dht11(DHT_PIN);

//String apiKey = "0BHEX6PHKYDU8TAG";  // 여기에 API키값을 입력합니다.
//const char* server2 = "api.thingspeak.com";

// Netwrok 변수 ===============================
const char* ssid = "The kind coffee"; // ESP8266이 연결되는 SSID 입니다.
const char* password = "10041004"; // ESP8266이 연결되는 SSID의 Password 입니다.
const char* NetworkID = "IoT_GateWay"; // ESP8266의 SSID 입니다.
const char* NetworkPW = "Q2w8E1r2A5s6D9f";  // ESP8266 SSID의 Password 입니다.
// 변수 설정 ==================================
String command;
String LS = "OFF";
int LV;
String IoT1;
int IoT1_Value;
String IoT2;
int IoT2_Value;
String IoT3;
int IoT3_Value;
String IoT4;
int IoT4_Value;
// ============================================
ESP8266WebServer server(80);
WiFiClient client;

// Method =====================================
void APset(){
WiFi.softAP(NetworkID, NetworkPW);
Serial.print("NetworkID : ");
Serial.print(NetworkID);
Serial.println(" ...OK");
Serial.print("NetworkPW : ");
Serial.print(NetworkPW);
Serial.println(" ...OK");
}

void WIFIset(){
//WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
//delay(1000);
//WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
WiFi.begin(ssid, password);
Serial.print("Connecting to ");
Serial.println(ssid);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print("wait..");
}
Serial.println("");
Serial.println("WiFi connected");
IPAddress IPserver = WiFi.localIP();
Serial.print("IP address : ");
Serial.println(IPserver);
}

void WebServer(){
}

void respond(){
  
  server.send(200,"text/html","A" + (String)IoT1_Value + "B" + (String)IoT2_Value + "C" + (String)IoT3_Value + "D" + (String)IoT4_Value);
}

void Server_Status(){
  server.send(200,"text/html","OK");
}

void IoT1_ch(){
  server.send(200,"text/html",(String)IoT1_Value);
}
// ===========================================
void setup() {
  Serial.begin(9600);
  WIFIset();
  APset();
server.on("/",respond);
server.on("/Server",Server_Status);
server.on("/IoT1",IoT1_ch);
server.begin();
server.onNotFound([](){
command=server.uri();
server.send(200,"text/plain",command);
});
}
void upload(){
/*
  if (client.connect(server2,80)) { // "184.106.153.149" or api.thingspeak.com
    int err;
  if((err=dht11.read(Humi, Temp))==0) 
  {
  Serial.print("Temp : ");
  Serial.println(Temp,0);
  Serial.print("Humi : ");
  Serial.println(Humi,0);
String postStr = apiKey;
postStr +="&field1=";
postStr += String((int)Temp);
postStr +="&field2=";
postStr += String((int)Humi);
postStr +="&field3=";
postStr += String(Dust);
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
  }
  
  }
*/
}

void loop() {
  
  server.handleClient();
  respond();
  upload();

  if(command.endsWith("L")){
    int Val = command.length()-1;
    IoT1_Value = command.substring(1,Val).toInt();
    Serial.print("LightValue : ");
    Serial.println(IoT1_Value);
    IoT1_ch();
    command = "";
  }

  if(command.equals("/Light_OFF")){
    Serial.print("LightValue : ");
    IoT1_Value=0;
    IoT1_ch();
    command = "";
  }
//int a = analogRead(A0);

//delay(1000);
 }
