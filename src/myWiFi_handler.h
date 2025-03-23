#ifdef OTA

if (WiFi.status() != WL_CONNECTED) {
    switch (WiFi.status()) {
        case WL_NO_SHIELD:
            Serial.println("Wifi status = WL_NO_SHIELD      ");
            break;
        case WL_IDLE_STATUS:
            if (scheduledWifiReconnect == 0) {
                scheduledWifiReconnect = current_millis + WifiReconnectPeriod;
            };
            break;  // Serial.println("Wifi status = WL_IDLE_STATUS     - reconnecting");
        case WL_NO_SSID_AVAIL:
            if (scheduledWifiReconnect == 0) {
                scheduledWifiReconnect = current_millis + WifiReconnectPeriod;
            };
            break;  // Serial.println("Wifi status = WL_NO_SSID_AVAIL   - reconnecting");
        case WL_SCAN_COMPLETED:
            if (scheduledWifiReconnect == 0) {
                scheduledWifiReconnect = current_millis + WifiReconnectPeriod;
            };
            break;  // Serial.println("Wifi status = WL_SCAN_COMPLETED  - reconnecting");
        case WL_CONNECT_FAILED:
            if (scheduledWifiReconnect == 0) {
                scheduledWifiReconnect = current_millis + WifiReconnectPeriod;
            };
            break;  // Serial.println("Wifi status = WL_CONNECT_FAILED  - reconnecting");
        case WL_CONNECTION_LOST:
            if (scheduledWifiReconnect == 0) {
                scheduledWifiReconnect = current_millis + WifiReconnectPeriod;
            };
            break;  // Serial.println("Wifi status = WL_CONNECTION_LOST - reconnecting");
        case WL_DISCONNECTED:
            if (scheduledWifiReconnect == 0) {
                scheduledWifiReconnect = current_millis + WifiReconnectPeriod;
            };
            break;  // Serial.println("Wifi status = WL_DISCONNECTED    - reconnecting");
                    // case WL_CONNECTED       : Serial.println("Wifi status = WL_CONNECTED      "); break;
        default:
            break;
    }
}

if (current_millis > scheduledWifiReconnect) {
    // give it another try ...
    if (WifiReconnectCounter < WifiGiveUpAfterTries) {
        if (WiFi.status() != WL_CONNECTED) {
            // perform next connection attempt
            WifiReconnectCounter++;
            Serial.printf("\nReconnect attempt #%d\n", WifiReconnectCounter);
            setup_wifi();
            scheduledWifiReconnect = 0;
        }
    }

    // finally give up ...
    if (WifiReconnectCounter == WifiGiveUpAfterTries) {
        Serial.printf("Tried %d times to reconnect ... giving up\n\n", WifiReconnectCounter);
        WifiReconnectCounter++;  // ensure that this loop is not entered any more
    }
}
#endif
