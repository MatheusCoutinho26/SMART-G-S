#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

const char* ssid = "VIVO-7738";
const char* password = "vivo123456";

//Your Domain name with URL path or IP address with path
String serverName = "https://fredaugusto.com.br/projetos/smartgas/enviar_dados.php";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 15000;
long randNumber;

/*
  Complete project details: https://RandomNerdTutorials.com/esp8266-nodemcu-https-requests/ 
  Based on the BasicHTTPSClient.ino Created on: 20.08.2018 (ESP8266 examples)
*/



void setup() {
  Serial.begin(115200);
  //Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  //Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  
  randomSeed(analogRead(0));
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // wait for WiFi connection
    if ((WiFi.status() == WL_CONNECTED)) {
  
      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  
      // Ignore SSL certificate validation
      client->setInsecure();
      
      //create an HTTPClient instance
      HTTPClient https;
      
      //Initializing an HTTPS communication using the secure client
      Serial.print("[HTTPS] begin...\n");


      randNumber = random(100, 900);
      String serverPath = serverName + "?valor=" + String(int(randNumber));

      Serial.println(serverPath);
      
      if (https.begin(*client, serverPath)) { // HTTPS
        Serial.print("[HTTPS] GET...\n");
        // start connection and send HTTP header
        int httpCode = https.GET();
        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            Serial.println(payload);
          }
        } else {
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
  
        https.end();
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }
    }
    Serial.println();
    Serial.println("Waiting 2min before the next round...");
    //delay(120000);
    
    lastTime = millis();
  }
}
