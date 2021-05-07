// Robo India Tutorial 
// Simple code upload the tempeature and humidity data using thingspeak.com
// Hardware: NodeMCU,DHT11

#include <dht11.h>
dht11 DHT11;
#include <ESP8266WiFi.h>
 
String apiKey = "VQP27OBT8HVB8JQJ";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "ESPServer";     // replace with your wifi ssid and wpa2 key
const char *pass =  "RAJ@1234";
const char* server = "api.thingspeak.com";

WiFiClient client;
void setup() 
{
       Serial.begin(115200);
       delay(10);
       DHT11.attach(D2);
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  int chk = DHT11.read();
  float t=DHT11.temperature;
  float h=DHT11.humidity;
  int D1= 75;
  int D2= 50;
  int D3= 25;
  int D4= 90;
//    int x = ThingSpeak.writeField(myChannelNumber, 1, number, apiKey);

       
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr +="&field3=";
                             postStr += String(D1);
                             postStr +="&field4=";
                             postStr += String(D2);
                             postStr +="&field5=";
                             postStr += String(D3);
                             postStr +="&field6=";
                             postStr += String(D4);
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
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}
