/******************************************** TIME SETUP *****************************************************/
void time_setup(void)
{
  // set notification call-back function
  sntp_set_time_sync_notification_cb( timeavailable );

  /**
   * NTP server address could be aquired via DHCP,
   *
   * NOTE: This call should be made BEFORE esp32 aquires IP address via DHCP,
   * otherwise SNTP option 42 would be rejected by default.
   * NOTE: configTime() function call if made AFTER DHCP-client run
   * will OVERRIDE aquired NTP server address
   */
  sntp_servermode_dhcp(1);    // (optional)

  /**
   * This will set configured ntp servers and constant TimeZone/daylightOffset
   * should be OK if your time zone does not need to adjust daylightOffset twice a year,
   * in such a case time adjustment won't be handled automagicaly.
   */
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

  /**
   * A more convenient approach to handle TimeZones with daylightOffset 
   * would be to specify a environmnet variable with TimeZone definition including daylight adjustmnet rules.
   * A list of rules for your zone could be obtained from https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h
   */
  //configTzTime(time_zone, ntpServer1, ntpServer2);
  
}
/************************************************************************************************************/



/******************************************** TIME FUNCTION ********************************************/
//time information

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  
  unsigned long currentTime_2 = millis();
  if (currentTime_2 - prevtime_T2 > interval_T2) 
  {
    tft.fillRect(320, 0, 150, 22, TFT_BLACK);
    prevtime_T2 = currentTime_2;
  }
  tft.setFreeFont(&FreeSans9pt7b);
  tft.setTextSize(1);
  tft.setCursor(370,20);
  tft.println(&timeinfo, "%I:%M %p");
  tft.setCursor(360,40);
  tft.println(&timeinfo, "%a %d %b");
}

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval *t)
{
  Serial.println("Got time adjustment from NTP!");
  // printLocalTime();
}
/************************************************************************************************************/



/************************************************** ALARM SETUP *********************************************/
void alarm_setup(void) 
{
  for (int i = 0; i < MAX_ALARMS; i++) 
  {
    alarms[i].hour = 0;
    alarms[i].minute = 0;
  }
}

void addAlarm(int hour, int minute) 
{
  if (numAlarms < MAX_ALARMS) 
  {
    alarms[numAlarms].hour = hour;
    alarms[numAlarms].minute = minute;
    numAlarms++;
    Serial.println("Alarm added!");
  } 
  else 
  {
    Serial.println("Cannot add more alarms. Maximum limit reached.");
  }
}

void printAlarms() 
{
  Serial.println("Alarms:");
  for (int i = 0; i < numAlarms; i++) 
  {
    Serial.printf("Alarm %d-  %02d:%02d\n", i + 1, alarms[i].hour, alarms[i].minute);
  }
}
/***********************************************************************************************************/


/******************************************** ALARM ACTION ****************************************************/
void alarm_action(void) 
{
  time_t now;
  time(&now);
  struct tm* timeinfo;
  timeinfo = localtime(&now);

  for (int i = 0; i < numAlarms; i++) 
  {
    if (timeinfo->tm_hour == alarms[i].hour && timeinfo->tm_min == alarms[i].minute && timeinfo->tm_sec == 0) 
    {
      Serial.printf("Alarm %d:", i + 1);
      Serial.println("Nowwww!");
      // Trigger the buzzer
      digitalWrite(BUZZER_PIN, HIGH);
      delay(1000); // Adjust the delay duration based on your buzzer's characteristics
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
}
/***********************************************************************************************************/
void deleteAlarm(int index) 
{
  if (index >= 0 && index < numAlarms) 
  {
    // Overwrite the alarm at the specified index with the last alarm
    alarms[index] = alarms[numAlarms - 1];
    // Clear the last alarm
    alarms[numAlarms - 1].hour = 0;
    alarms[numAlarms - 1].minute = 0;
    numAlarms--;
  }
}





