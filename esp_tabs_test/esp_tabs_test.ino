/* 
 ********************************************************************************** 
 *  AUTHER      : Shrouk Ashraf & Ahmed Mohamed 
 *  DATE        : 22/1/2024
 *  DESCRIPTION : Medical watch
 *  VERSION     : 1.8 esp //finish web connection
 **********************************************************************************
*/

/********************************** INCLUDES **************************************/
/* WIFI Library */
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

/* SIM Library */
#include <Wire.h>
#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
#include <HardwareSerial.h>

/* TFT SPI libraries */
#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h>

/* MLX90614 Library */
#include <Adafruit_MLX90614.h>

/* MAX30102 Library */
#include <DFRobot_BloodOxygen_S.h>

/* DS3231 Library */
#include "RTClib.h"

/* NTP time library */
// #include "time.h"
// #include "sntp.h"


/* OTA library */
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

/**********************************************************************************/