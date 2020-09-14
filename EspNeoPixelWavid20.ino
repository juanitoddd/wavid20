
#include "EspMQTTClient.h"
#include <Adafruit_NeoPixel.h>

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;

int pixels = 167;

String scene = "blinkSlow";

Adafruit_NeoPixel cuadro = Adafruit_NeoPixel(pixels, D4, NEO_GRB + NEO_KHZ800);

EspMQTTClient client(
  "juanddd",
  "manonegra",
  "192.168.0.111",  // Home Assistant MQTT Broker server ip
  "juanddd",
  "manonegra",
  "ESP_Led_2"     // Client name that uniquely identify your device
          // The MQTT port, default to 1883. this line can be omitted
);

void onConnectionEstablished(){

  Serial.println("onConnectionEstablished");
  // Subscribe to "mytopic/test" and display received message to Serial
  client.subscribe("iot/test", [](const String & payload) {
    
    scene = payload;
    Serial.println(payload);
    
  });
  
}
 
void setup() {

  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

  Serial.begin(115200);

  // Optional functionnalities of EspMQTTClient : 
  
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  
  // client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  // client.enableLastWillMessage("iot/test", "accident");  // You can activate the retain flag by setting the third parameter to true

  client.setMqttReconnectionAttemptDelay(2000);

  client.setWifiReconnectionAttemptDelay(5000);

  client.enableMQTTPersistence();
  
  cuadro.begin();
  cuadro.show();

  delay(500);
  Serial.println("Set-up Finish");
}

// the loop function runs over and over again forever
void loop() {

  client.loop();

  if(scene == "initial") {
      
    scene_initial();
    
  } else if(scene == "takeoff") {
    
    scene_takeoff();
    
  } else if(scene == "cruising") { 

    scene_cruising();
    
  } else if(scene == "accident") {

    scene_accident();
    
  } else if(scene == "landing") {

    scene_landing();
    
  } else if(scene == "blinkSlow") {

    blinkSlow();
    
  } else if(scene == "blinkFast") {

    blinkFast();
    
  }
}

void blinkFast() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(100);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(200);                      // Wait for two seconds (to demonstrate the active low LED)
}

void blinkSlow() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}

void scene_accident() {
  
  cuadro.setBrightness(100);
  for(int i = 0; i < pixels; i++) {
    cuadro.setPixelColor(i,255,0,0);
    cuadro.show(); 
  };
    
  delay(500) ;

  for(int i = 0; i < pixels; i++) {
    cuadro.setPixelColor(i,0,0,0);
    cuadro.show(); 
  };
}

void scene_landing() {

  for(int i = 0; i < pixels; i++) {
    cuadro.setPixelColor(i,255,255,255);
    cuadro.show();
  }
  
}

void scene_cruising() {

  cuadro.setBrightness(100);

  for(int i = 0; i < pixels; i++) {
    cuadro.setPixelColor(i,255,255,255);
    cuadro.show();
    if(i <= pixels - 80){
      cuadro.setPixelColor(i + 80,255,255,255);
      cuadro.show();
    } else {
      cuadro.setPixelColor(i - 80,255,255,255);
      cuadro.show();
    }
    delay(1) ;
    cuadro.setPixelColor(i,0,0,0);
    cuadro.show();
    if(i <= pixels - 80){
      cuadro.setPixelColor(i + 80,0,0,0);
      cuadro.show(); 
    } else {
      cuadro.setPixelColor(i - 80,0,0,0);
      cuadro.show(); 
    }
  };
}

void scene_takeoff(){
  
  cuadro.setBrightness(100);
  for(int i = 0; i < pixels; i = i + 3) {
    cuadro.setPixelColor(i,255,255,255);
    cuadro.show();
    if(i <= pixels - 80){
     cuadro.setPixelColor(i + 80,255,255,255);
     cuadro.show();
    } else {
      cuadro.setPixelColor(i - 80,255,255,255);
      cuadro.show();
    }
    delay(1) ;
    cuadro.setPixelColor(i,0,0,0);
    cuadro.show();
    if(i <= pixels - 80){
      cuadro.setPixelColor(i + 80,0,0,0);
      cuadro.show(); 
    } else {
      cuadro.setPixelColor(i - 80,0,0,0);
      cuadro.show(); 
    }
  };
}

void scene_initial() {

  cuadro.setBrightness(50);
  for(int i = 0; i < pixels; i++) {
    cuadro.setPixelColor(i,255,255,255);
    cuadro.show();
  };
  
}
