const char WIFI_SSID[] = "SSID";
const char WIFI_PASS[] = "WLAN-PSK";

// for WPA2-Enterprise - set to false to fall back to WPA2-PSK
const bool WPA2ENTERPRISE = true;
const char WIFI_username[] = "FHWN_Username";
const char WIFI_identity[] = "FHWN_Username";

// custom MAC for WPA2-Enterprise
uint8_t target_esp_mac[6] = {0x24, 0x0a, 0xc4, 0xXX, 0xXX, 0xXX};

// Target Server
const char SERVER_BASE[] = "http://my.server.name/url-to/upload-script.php";

// DHT Sensor
uint8_t DHTPin = D2;

// Uncomment one of the lines below for whatever DHT 
sensor type you're using!
#define DHTTYPE DHT11   // DHT 11//
#define DHTTYPE DHT21   // DHT 21 (AM2301)//
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321