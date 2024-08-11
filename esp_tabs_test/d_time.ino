// /******************************************** TIME SETUP *****************************************************/
void RTC_time_setup()
{
  /* Check DS3231 connection */
  if (!rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  if (rtc.lostPower()) 
  {
    Serial.println("let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

/******************************************** TIME FUNCTION ********************************************/
//time information
const char* monthShortStr(uint8_t month) {
  static const char* monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  return monthNames[month - 1]; // Adjust month index to match array indexing (0-based vs. 1-based)
}

void printLocalTime()
{
  DateTime now = rtc.now();
  unsigned long currentTime_2 = millis();
  if (currentTime_2 - prevtime_T2 > interval_T2) 
  {
    tft.fillRect(320, 0, 150, 22, TFT_BLACK);
    prevtime_T2 = currentTime_2;
  }
  tft.setTextColor(White);
  tft.setFreeFont(&FreeSans9pt7b);
  tft.setTextSize(1);
  tft.setCursor(370,20);
  tft.printf("%02d:%02d", now.twelveHour(), now.minute());
  // Battery(); ////////////////////  هنااااااااا يا شمس 
  tft.setCursor(360,40);
  tft.printf("%s %02d %s", daysOfTheWeek[now.dayOfTheWeek()], now.day(), monthShortStr(now.month()));

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
  DateTime now = rtc.now();
  
  // Print current time for debugging
  // Serial.print("Current time: ");
  // Serial.print(now.hour());
  // Serial.print(":");
  // Serial.print(now.minute());
  // Serial.print(":");
  // Serial.println(now.second());
  // Print alarms for debugging
  // Serial.println("Alarms:");
  // for (int i = 0; i < numAlarms; i++) {
  //   Serial.printf("Alarm %d: %02d:%02d\n", i + 1, alarms[i].hour, alarms[i].minute);
  // }
  
  for (int i = 0; i < numAlarms; i++) 
  {
    if (now.hour() == alarms[i].hour && now.minute() == alarms[i].minute && now.second() == 0) 
    {
      check_on_alarm = 1;
      tft.fillScreen(Black);
      tft.setTextColor(White);
      tft.setFreeFont(&FreeSans18pt7b);
      tft.setTextSize(1);
      tft.setCursor(190,150);
      tft.print("Alarm ");
      tft.println(i + 1);
      Delete_All_Buttons();
      CANALARM_BUTTON();
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





