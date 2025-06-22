// #############################################################
// setup OTA (Over The Air) firmware update
// #############################################################

//-------------------
// configure handlers
//-------------------
ArduinoOTA.onStart([]() {
    OTAinProgress = true;
    Serial.println(F(" \r\nOTA: Start"));
});
ArduinoOTA.onEnd([]() {
    OTAinProgress = false;
    Serial.println(F(" \r\nOTA: End"));
});

ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) { Serial.printf(" OTA-Progress: %u%%\r", (progress / (total / 100))); });
ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA-Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
        Serial.println(F("OTA: Auth Failed"));
    else if (error == OTA_BEGIN_ERROR)
        Serial.println(F("OTA: Begin Failed"));
    else if (error == OTA_CONNECT_ERROR)
        Serial.println(F("OTA: Connect Failed"));
    else if (error == OTA_RECEIVE_ERROR)
        Serial.println(F("OTA: Receive Failed"));
    else if (error == OTA_END_ERROR)
        Serial.println(F("OTA: End Failed"));
});

//-------------
// OTA security
//-------------
#ifdef OTA_PASSWORD
ArduinoOTA.setPassword(OTA_PASSWORD);
// #else
// ArduinoOTA.setPasswordHash("cc5c5604f34e1f4794a55be205c9e2ef");  // use https://www.php-einfach.de/diverses/md5-sha1-hash-generator/?submit=1
#endif

//---------------
// finalize setup
//---------------
ArduinoOTA.setHostname(Hostname.c_str());
Serial.printf("OTA Hostname is: %s\n\r", ArduinoOTA.getHostname().c_str());
ArduinoOTA.begin();
