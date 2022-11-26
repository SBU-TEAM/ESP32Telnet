/* ------------------------------------------------- */
// include the debug macros?
#define DEBUG_ON 1

// define the output channels
#define DEBUG_USE_SERIAL 1
#define DEBUG_USE_TELNET 1

// customize the output prefix, the serial and/or telnet port if needed
// #define DEBUG_PREFIX "[DEBUG]\t"
// #define DEBUG_SERIAL Serial
// #define DEBUG_TELNET telnet
/* ------------------------------------------------- */

#include "ESPTelnet.h"

/* ------------------------------------------------- */

#define WIFI_SSID       "Robotics"
#define WIFI_PASSWORD   "@Auriga1399#"
#define SERIAL_SPEED    115200

/* ------------------------------------------------- */

ESPTelnet telnet;
int a = 19;
int b = 0;
bool led_on = false;

/* ------------------------------------------------- */

void toggleLed(int pin, bool init = false) {
  if (init) {
    pinMode(2, OUTPUT);
  }
  digitalWrite(pin, led_on ? LOW : HIGH);
  led_on = !led_on;
}

/* ------------------------------------------------- */

bool isConnected() {
  return (WiFi.status() == WL_CONNECTED);
}

/* ------------------------------------------------- */

bool connectToWiFi(const char* ssid, const char* password, int max_tries = 20, int pause = 200) {
  int i = 0;
  WiFi.mode(WIFI_STA);
  #if defined(ARDUINO_ARCH_ESP8266)
    WiFi.forceSleepWake();
    delay(200);
  #endif
  WiFi.begin(ssid, password);
  do {
    delay(pause);
    Serial.print(".");
  } while (!isConnected() || i++ < max_tries);
    Serial.println();  
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  return isConnected();
}

/* ------------------------------------------------- */
/* ------------------------------------------------- */

void setup() {
  toggleLed(2, true);
  // you need to initalize the Serial port yourself
  Serial.begin(SERIAL_SPEED);
  while(!Serial) {
    delay(20);
  }
  Serial.println("\n");

  DEBUG_INFO;
  DEBUG_WHERE;

  connectToWiFi(WIFI_SSID, WIFI_PASSWORD);
  toggleLed(2);
  // you need to initalize the ESPTelnet class port yourself
  #if DEBUG_USE_TELNET
    telnet.begin();
  #endif  
  DEBUG_MSG(WiFi.localIP().toString());
  DEBUG_MSG("Testing the debug class...");
  DEBUG_WHERE;
  DEBUG_VAR(a);

// for now only working with Serial
//  DEBUG_VAR(a, DEC);
//  DEBUG_VAR(a, HEX);
//  DEBUG_VAR(a, BIN);
}

/* ------------------------------------------------- */

void loop() {
  DEBUG_VAR(b);
  // DEBUG_WHERE;
  Serial.println("hello world!");
  toggleLed(2);

  b++;
  // don't forget to inlude the loop 
 #if DEBUG_USE_TELNET
  telnet.loop();
#endif  
  // delay(10);
}