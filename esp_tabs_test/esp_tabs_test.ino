/* 
 ********************************************************************************** 
 *  AUTHER      : Shrouk Ashraf & Ahmed Mohamed 
 *  DATE        : 22/1/2024
 *  DESCRIPTION : Medical watch
 *  VERSION     : 1.4 esp //debug
 **********************************************************************************
 */

/********************************** INCLUDES **************************************/
/* WIFI Library */
#include <WiFi.h>
#include <HTTPClient.h>

/* TFT SPI libraries */
#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h>

/* MLX90614 Library */
#include <Adafruit_MLX90614.h>

/* MAX30102 Library */
#include <DFRobot_BloodOxygen_S.h>

/* NTP time library */
#include "time.h"
#include "sntp.h"

/**********************************************************************************/