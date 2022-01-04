#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#define Power D4

/* Set these to your desired credentials. */
const char *ssid = "IoT_GateWay";  //ENTER YOUR WIFI SETTINGS
const char *password = "Q2w8E1r2A5s6D9f";
 
//Web/Server address to read/write from 
const char *host = "192.168.4.1";   //https://circuits4you.com website or IP address of server
 
//=======================================================================
//                    Power on setup
//=======================================================================
 
void setup() {
  delay(1000);
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
//======================================================================
  pinMode(Power,OUTPUT);
//======================================================================
}
 
//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  HTTPClient http;    //Declare object of class HTTPClient
 
  String Link;
 
  //GET Data
  Link = "http://192.168.4.1";
  
  http.begin(Link);     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload
  String data = payload;
  //Serial.println(httpCode);   //Print HTTP return code
  Serial.println(data);    //Print request response payload
 
  http.end();  //Close connection
  if(httpCode == 200){
    
   int IoT1_Index = data.indexOf('A');
 int IoT2_Index = data.indexOf('B',IoT1_Index+1);
 int IoT3_Index = data.indexOf('C',IoT2_Index+1);
 int IoT4_Index = data.indexOf('D',IoT3_Index+1);
 String IoT1_String = data.substring(IoT1_Index+1,IoT2_Index);
String IoT2_String = data.substring(IoT2_Index+1);
String IoT3_String = data.substring(IoT3_Index+1);
String IoT4_String = data.substring(IoT4_Index+1);
int IoT1 = IoT1_String.toInt();
int IoT2 = IoT2_String.toInt();
int IoT3 = IoT3_String.toInt();
int IoT4 = IoT4_String.toInt();
  Serial.println(IoT1); 
  //Serial.println(IoT2); 
  //Serial.println(IoT3); 
  //Serial.println(IoT4);
  if(IoT1 == 255){
    digitalWrite(Power,HIGH);}
  else if(IoT1 == 0){
    digitalWrite(Power,LOW);}
  }
  delay(100);  //GET Data at every 5 seconds
}
