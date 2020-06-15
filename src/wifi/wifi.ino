#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include<SoftwareSerial.h>
SoftwareSerial s(D6,D5); //RX,TX
int data;
const char* ssid = "Solanki";
const char* password = "solanki1234";
const char* host = "maker.ifttt.com";
const int httpsPort = 443; 
String url = "/trigger/accident/with/key/d2aRkZ04xuLxTQ_4mlaZUv";
const int API_TIMEOUT = 10000;  //keep it long if you want to receive headers from client
void setup () {
  s.begin(9600);
  Serial.begin(9600);
  Serial.begin(115200);
  Serial.println();
  BearSSL::WiFiClientSecure client;
  client.setInsecure();
  client.setTimeout(API_TIMEOUT);
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 String url = "/trigger/accident/with/key/d2aRkZ04xuLxTQ_4mlaZUv";
}

void loop() {
  // put your main code here, to run repeatedly:

s.write('s');
if(s.available()>0)
{
  data=s.read();
  Serial.println(data);
  if(data>100)
  {
   
  BearSSL::WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  Serial.print("requesting URL: ");
  Serial.println(url);
 client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');

  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
  }
 }
  
  }
