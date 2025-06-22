#include <WiFi.h>

String        MACaddress;
String        Hostname;

unsigned long connect_timeout        = 5000;
unsigned long scheduledWifiReconnect = 0;     // time when next reconnect will be attempted
unsigned long WifiReconnectPeriod    = 5000;  // time between reconnect attempts
uint8_t       WifiGiveUpAfterTries   = 5;     // max number of connection attempts
uint8_t       WifiReconnectCounter   = 0;

//---------------------------------------------------------------------------
// setup function for WiFi
//---------------------------------------------------------------------------
bool setup_wifi() {
    Serial.println("\n\r-------- Setting up WiFi ...");

    WiFi.mode(WIFI_STA);  // standard mode - see https://stackoverflow.com/questions/55059105/different-wifi-modes-in-arduino-for-esp32
    Serial.printf("Trying to connect to <%s> ", WIFI_SSID);
#if defined(WIFI_HOSTNAME)
    WiFi.setHostname(WIFI_HOSTNAME);
#endif
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // initialize connection with SSID and password

    //---------------------------------------
    // try primary WiFi connect until timeout
    //---------------------------------------
    unsigned long current_millis  = millis();
    unsigned long previous_millis = current_millis;
    bool          wifisuccess     = true;

    while (WiFi.status() != WL_CONNECTED && wifisuccess == true) {
        current_millis = millis();
        if (current_millis - previous_millis >= connect_timeout) {
            Serial.println("Failed to connect.");
            wifisuccess = false;  // exit loop
        }
        delay(100);
        Serial.print(".");
    }

    //-------------------
    // successful connect
    //-------------------
    Serial.println("");
    Serial.printf("WiFi connected to <%s>\n", WiFi.SSID().c_str());

    Serial.print("IP Address is: ");
    Serial.println(WiFi.localIP());

    Hostname = WiFi.getHostname();
    Serial.print("Hostname is: ");
    Serial.println(Hostname);

    MACaddress = WiFi.macAddress();
    Serial.print("MAC address is: ");
    Serial.println(MACaddress);

    Serial.print("signal strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

    return true;
}
