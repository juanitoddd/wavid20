
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

String scene = "accident";

Adafruit_NeoPixel cuadro = Adafruit_NeoPixel(pixels, D4, NEO_GRB + NEO_KHZ800);

EspMQTTClient client(
  "UPC3699094",
  "ewbc7eUyzjs8",
  "192.168.0.165",  // Home Assistant MQTT Broker server ip
  "mqttuser",
  "mqttpass",
  "ESP-Led",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
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

  Serial.begin(115200);

  // Optional functionnalities of EspMQTTClient : 
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  client.enableLastWillMessage("iot/test", "accident");  // You can activate the retain flag by setting the third parameter to true

  cuadro.begin();
  cuadro.show();
  
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
    
  }

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
