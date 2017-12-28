#include <ESP8266WiFi.h>
 
 
String apiKlic = "79WDEPPM4UNGWMUA";
 
const char* nazevWifi = "SRM-Event";
const char* hesloWifi = "SRMist#4444";
 
const char* server = "api.thingspeak.com";
 
WiFiClient client;
 
void setup() {
  
  Serial.begin(9600);
   
  WiFi.begin(nazevWifi, hesloWifi);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Pripojeno k WiFi siti ");
  Serial.println(nazevWifi);
  Serial.print("IP adresa: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  int cas = millis()/1000;
  int analog = analogRead(A0);
  
  if (client.connect(server,80)) {
    
    String zprava = apiKlic;
    zprava +="&field1=";
    zprava += String(cas);
    zprava +="&field2=";
    zprava += String(analog);
    zprava += "\r\n\r\n";
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKlic+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(zprava.length());
    client.print("\n\n");
    client.print(zprava);
    
    Serial.print("Cas od spusteni Arduina: ");
    Serial.print(cas);
    Serial.print(" vterin a analogovy pin A0: "); 
    Serial.println(analog);
    Serial.println("Udaje odeslany na Thingspeak.");
  }
   
  client.stop();
  
  Serial.println("Pauza pred dalsim odeslanim dat.");
  delay(30000);
}