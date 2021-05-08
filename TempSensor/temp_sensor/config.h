const char WIFI_SSID[] = "osnw";
const char WIFI_PASS[] = "osnw2021";

// for WPA2-Enterprise - set to false to fall back to WPA2-PSK
const bool WPA2ENTERPRISE = false;
const char WIFI_username[] = "116713";
const char WIFI_identity[] = "116713";

// custom MAC for WPA2-Enterprise
uint8_t target_esp_mac[6] = {0x24, 0x0a, 0xc4, 0x30, 0x9c, 0x23};

// Target Server
const char SERVER_BASE[] = "http://osnw-horvath.edu.cs.fhwn.ac.at/upload.php";

// DHT Sensor
uint8_t DHTPin = D4;

// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11   // DHT 11//
//#define DHTTYPE DHT21   // DHT 21 (AM2301)//
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
