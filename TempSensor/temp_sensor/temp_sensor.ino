#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
#include "config.h"

// https://gist.github.com/Matheus-Garbelini/2cd780aed2eddbe17eb4adb5eca42bd6
extern "C" {
  #include "user_interface.h"
  #include "wpa2_enterprise.h"
  #include "c_types.h"
  }
  
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);
float Temperature;
float Humidity;

// https://randomnerdtutorials.com/esp8266-nodemcu-http-get-post-arduino
///Your Domain name with URL path or IP address with path
String serverName = SERVER_BASE;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;

// Set timer to 5 seconds (5000)
unsigned long timerDelay = 15000;

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(DHTPin, INPUT);
  delay(100);
  dht.begin();


  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  
//connect to your local wi-fi network
if (WPA2ENTERPRISE){
  Serial.println("WPA2 Enterprise connection found...");
  WiFi.mode(WIFI_STA);
  Serial.printf("SDK version: %s\n", system_get_sdk_version());
  Serial.printf("Free Heap: %4d\n",ESP.getFreeHeap());
  
  // Setting ESP into STATION mode only (no AP mode or dual mode)
  wifi_set_opmode(STATION_MODE);
  struct station_config wifi_config;
  Serial.println("Doing Wifi_Config stuff:");
  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, WIFI_SSID);
  strcpy((char*)wifi_config.password, WIFI_PASS);

  
Serial.print("[OLD] ESP32 Board MAC Address:  ");
Serial.println(WiFi.macAddress());
wifi_station_set_config(&wifi_config);

// crashes without setting custom mac address
wifi_set_macaddr(STATION_IF,target_esp_mac);
Serial.print("[NEW] ESP32 Board MAC Address:  ");
Serial.println(WiFi.macAddress());
wifi_station_set_wpa2_enterprise_auth(1);

// Clean up to be sure no old data is still inside
wifi_station_clear_cert_key();
wifi_station_clear_enterprise_ca_cert();
wifi_station_clear_enterprise_identity();
wifi_station_clear_enterprise_username();
wifi_station_clear_enterprise_password();
wifi_station_clear_enterprise_new_password();
wifi_station_set_enterprise_identity((uint8*)WIFI_identity, strlen(WIFI_identity));
wifi_station_set_enterprise_username((uint8*)WIFI_username, strlen(WIFI_username));
wifi_station_set_enterprise_password((uint8*)WIFI_PASS, strlen((char*)WIFI_PASS));
wifi_station_connect();
}else{
  WiFi.begin(WIFI_SSID, WIFI_PASS);
}

//check wi-fi is connected to wi-fi network
while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  
  
 if ((millis() - lastTime) > timerDelay) {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    Temperature = dht.readTemperature(); // Gets the values of the temperature
    Humidity = dht.readHumidity(); // Gets the values of the humidity

    HTTPClient http;
    String fullHTTP = String(SERVER_BASE) + "?id=XXXXX&temperature=" + String(Temperature) + "&humidity=" + String(Humidity);

    http.begin(fullHTTP.c_str());
    int httpCode =http.GET();
    http.end();
    
     Serial.println("Temp: " + String(Temperature));
      Serial.println("Humi: " + String(Humidity));
  
      Serial.println("Sending data now!");
    }else 
    {Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }

}
