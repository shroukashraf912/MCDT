void TFT_Init(void)
{
    //Initialize TFT
    tft.init();
    // Set the rotation
    tft.setRotation(1);
    touch_calibrate();
    // Clear the screen
    tft.fillScreen(TFT_BLACK);
}

void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("Formating file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}

/*---------------------------------------KEYPADS------------------------------------------*/
/* Keypad of Pressure */
void drawBPKeypad() 
{
  for (uint8_t row = 0; row < ROW_OF_KEYPAD; row++) {
    for (uint8_t col = 0; col < COL_OF_KEYPAD; col++) {
      uint8_t btnNumber = col + row * COL_OF_KEYPAD;

      if (btnNumber >= 11) 
      {
        tft.setFreeFont(&FreeSans9pt7b);
      } 
      else 
      {
        tft.setFreeFont(&FreeSans18pt7b);
      }

      BPKEY[btnNumber].initButton(&tft, (KEY_X + col * (KEY_W + KEY_SPACING_X)),
                                (KEY_Y + row * (KEY_H + KEY_SPACING_Y)),
                                KEY_W, KEY_H, TFT_DARKGREY, keyColor[btnNumber],
                                TFT_WHITE, keyLabel[btnNumber], KEY_TEXTSIZE);

      BPKEY[btnNumber].drawButton();
    }
  }
}

void BPKeypad_Init()
{
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, 480, 320, TFT_BLACK);
  tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_DARKGREY);
  drawBPKeypad();
}

char* BPKeypad_Loop()
{
  static char _Buffer_Result[NUM_LEN + 1];
  
  // Your existing loop code
  for (uint8_t btn = 0; btn < 15; btn++) 
  {
    if (btn >= 11) 
    {
      tft.setFreeFont(&FreeSans9pt7b);
    } 
    else 
    {
      tft.setFreeFont(&FreeSans18pt7b);
    }

    if (BPKEY[btn].justReleased()) 
    {
      BPKEY[btn].drawButton();
    }

    if (BPKEY[btn].justPressed()) 
    {
      BPKEY[btn].drawButton(true);

      if (btn < 11) 
      {
        if (numberIndex < NUM_LEN) 
        {
          numberBuffer[numberIndex] = keyLabel[btn][0];
          numberIndex++;
          numberBuffer[numberIndex] = '\0';
        }
      } 
      else if (btn == 11) 
      {
        numberBuffer[numberIndex] = '\0';
        if (numberIndex > 0) 
        {
          numberIndex--;
          numberBuffer[numberIndex] = '\0';
        }
      } 
      else if (btn == 13) 
      {
        // Handle "Send" button press
        strncpy(_Buffer_Result, numberBuffer, NUM_LEN + 1);
        numberIndex = 0;
        numberBuffer[numberIndex] = '\0';

        tft.setTextDatum(TL_DATUM);
        tft.setFreeFont(&FreeSans18pt7b);
        tft.setTextColor(DISP_TCOLOR);
        tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
        tft.drawString("Sent Successfully", DISP_X + 4, DISP_Y + 12);
        delay(3000);
        tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);

      } 
      else if (btn == 12) 
      {
        // Handle "New" button press
        numberIndex = 0;
        numberBuffer[numberIndex] = '\0';
        
      } 
      else if (btn == 14) 
      {
        // Handle "Back" button press
        numberIndex = 0;
        numberBuffer[numberIndex] = '\0';
        ENTERY_Page();
        break;
      }

      tft.setTextDatum(TL_DATUM);
      tft.setFreeFont(&FreeSans18pt7b);
      tft.setTextColor(DISP_TCOLOR);
      int xwidth = tft.drawString(numberBuffer, DISP_X + 4, DISP_Y + 12);
      tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
      delay(10);
    }
  }
  return _Buffer_Result;
}

/* Keypad of Suger */
void drawBSGKeypad() 
{
  for (uint8_t row = 0; row < ROW_OF_KEYPAD; row++) {
    for (uint8_t col = 0; col < COL_OF_KEYPAD; col++) {
      uint8_t btnNumber = col + row * COL_OF_KEYPAD;

      if (btnNumber >= 11) 
      {
        tft.setFreeFont(&FreeSans9pt7b);
      } 
      else 
      {
        tft.setFreeFont(&FreeSans18pt7b);
      }

      BSGKEY[btnNumber].initButton(&tft, (KEY_X + col * (KEY_W + KEY_SPACING_X)),
                                (KEY_Y + row * (KEY_H + KEY_SPACING_Y)),
                                KEY_W, KEY_H, TFT_DARKGREY, keyColor[btnNumber],
                                TFT_WHITE, keyLabel[btnNumber], KEY_TEXTSIZE);

      BSGKEY[btnNumber].drawButton();
    }
  }
}

void BSGKeypad_Init()
{
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, 480, 320, TFT_BLACK);
  tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_DARKGREY);
  drawBSGKeypad();
}

char* BSGKeypad_Loop()
{
  static char Buffer_Result_[NUM_LEN_G + 1];
  
  // Your existing loop code
  for (uint8_t btn = 0; btn < 15; btn++) 
  {
    if (btn >= 11) 
    {
      tft.setFreeFont(&FreeSans9pt7b);
    } 
    else 
    {
      tft.setFreeFont(&FreeSans18pt7b);
    }

    if (BSGKEY[btn].justReleased()) 
    {
      BSGKEY[btn].drawButton();
    }

    if (BSGKEY[btn].justPressed()) 
    {
      BSGKEY[btn].drawButton(true);

      if (btn < 11) 
      {
        if (numberIndexG < NUM_LEN_G) 
        {
          numberBufferG[numberIndexG] = keyLabel[btn][0];
          numberIndexG++;
          numberBufferG[numberIndexG] = '\0';
        }
      } 
      else if (btn == 11) 
      {
        numberBufferG[numberIndexG] = '\0';
        if (numberIndexG > 0) 
        {
          numberIndexG--;
          numberBufferG[numberIndexG] = '\0';
        }
      } 
      else if (btn == 13) 
      {
        // Handle "Send" button press
        strncpy(Buffer_Result_, numberBufferG, NUM_LEN_G + 1);
        numberIndexG = 0;
        numberBufferG[numberIndexG] = '\0';
        tft.setTextDatum(TL_DATUM);
        tft.setFreeFont(&FreeSans18pt7b);
        tft.setTextColor(DISP_TCOLOR);
        tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
        tft.drawString("Sent Successfully", DISP_X + 4, DISP_Y + 12);
        delay(3000);
        tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);

      } 
      else if (btn == 12) 
      {
        // Handle "New" button press
        numberIndexG = 0;
        numberBufferG[numberIndexG] = '\0';
      } 
      else if (btn == 14) 
      {
        // Handle "Back" button press
        numberIndexG = 0;
        numberBufferG[numberIndexG] = '\0';
        ENTERY_Page();
        break;
      }

      tft.setTextDatum(TL_DATUM);
      tft.setFreeFont(&FreeSans18pt7b);
      tft.setTextColor(DISP_TCOLOR);
      int xwidth = tft.drawString(numberBufferG, DISP_X + 4, DISP_Y + 12);
      tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
      delay(10);
    }
  }
  return Buffer_Result_;
}
/* Keypad of Alarm */
void drawAKeypad() 
{
  for (uint8_t row = 0; row < ROW_OF_KEYPAD; row++) {
    for (uint8_t col = 0; col < COL_OF_KEYPAD; col++) {
      uint8_t btnNumber = col + row * COL_OF_KEYPAD;

    if (btnNumber >= 10) 
    {
      tft.setFreeFont(&FreeSans9pt7b);
    } else {
      tft.setFreeFont(&FreeSans18pt7b);
    }

      Alarmkey[btnNumber].initButton(&tft, (KEY_X + col * (KEY_W + KEY_SPACING_X)),
                                (KEY_Y + row * (KEY_H + KEY_SPACING_Y)),
                                KEY_W, KEY_H, TFT_DARKGREY, AkeyColor[btnNumber],
                                TFT_WHITE, AkeyLabel[btnNumber], KEY_TEXTSIZE);

      Alarmkey[btnNumber].drawButton();
    }
  }
}
void handleOutOfRange(const char* message) 
{
  A_numberIndex = 0;
  A_numberBuffer[A_numberIndex] = '\0';

  tft.setTextDatum(TL_DATUM);
  tft.setFreeFont(&FreeSans18pt7b);
  tft.setTextColor(DISP_TCOLOR);
  tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  tft.drawString(message, DISP_X + 4, DISP_Y + 12);
  delay(3000);
  tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
}

void handleBackspace() {
  A_numberBuffer[A_numberIndex] = '\0';
  if (A_numberIndex > 0) {
    A_numberIndex--;
    A_numberBuffer[A_numberIndex] = '\0';
  }
}

void AKeypad_Init()
{
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, 480, 320, TFT_BLACK);
  tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_DARKGREY);
  ADD.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  ABACK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  for (int btn = 0; btn < MAX_ALARMS; btn++) 
  {
    EDIT[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    DEL[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  drawAKeypad();
}
void handleEditKeypad() 
{
  for (uint8_t btn = 0; btn < 15; btn++) {
    if (btn >= 10) {
      tft.setFreeFont(LABEL1_FONT);
    } else {
      tft.setFreeFont(&FreeSans18pt7b);
    }

    if (Alarmkey[btn].justReleased()) {
      Alarmkey[btn].drawButton();
    }

    if (Alarmkey[btn].justPressed()) {
      Alarmkey[btn].drawButton(true);

      if (btn < 10) {
        if (A_numberIndex < A_NUM_LEN) {
          A_numberBuffer[A_numberIndex] = AkeyLabel[btn][0];
          A_numberIndex++;
          A_numberBuffer[A_numberIndex] = '\0';
        }
      } else if (btn == 10) {
        int enteredHour = atoi(A_numberBuffer);

        if (enteredHour > 24) {
          handleOutOfRange("from 0 to 24");
        } else {
          alarmHour = enteredHour;
          alarms[editAlarmIndex].hour = enteredHour;
          Serial.print("Hour stored: ");
          Serial.println(alarmHour);
        }
      } else if (btn == 11) {
        int enteredMinute = atoi(A_numberBuffer);

        if (enteredMinute > 60) {
          handleOutOfRange("from 0 to 60");
        } else {
          alarmMinute = enteredMinute;
          alarms[editAlarmIndex].minute = enteredMinute;
          Serial.print("Minute stored: ");
          Serial.println(alarmMinute);
        }
      } else if (btn == 12) {
        handleBackspace();
      } else if (btn == 13) {
      // Handle "Set" button press
      if (editAlarmIndex != -1) 
      {
        // Reset editAlarmIndex to indicate that no alarm is being edited
        editAlarmIndex = -1;
      }
    } else if (btn == 14) 
    {
      // Handle "Back" button press
      currentState = EXIT_PAGE; // Go back to the main page without saving changes
      Alarm_Page();
      break;
    }

      // Display the entered numbers on the screen
      tft.setTextDatum(TL_DATUM);
      tft.setFreeFont(&FreeSans18pt7b);
      tft.setTextColor(DISP_TCOLOR);
      int xwidth = tft.drawString(A_numberBuffer, DISP_X + 4, DISP_Y + 12);
      tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
      delay(10);
    }
  }
}

void AKeypad_Loop()
{

    /* Press on Alarm keypad */
  
  for (uint8_t btn = 0; btn < 15; btn++) 
  {
    if (btn >= 10) 
    {
      tft.setFreeFont(&FreeSans9pt7b);
    } else {
      tft.setFreeFont(&FreeSans18pt7b);
    }

    if (Alarmkey[btn].justReleased()) 
    {
      Alarmkey[btn].drawButton();
    }

    if (Alarmkey[btn].justPressed()) 
    {
      Alarmkey[btn].drawButton(true);

      if (btn < 10) 
      {
        if (A_numberIndex < A_NUM_LEN) 
        {
          A_numberBuffer[A_numberIndex] = AkeyLabel[btn][0];
          A_numberIndex++;
          A_numberBuffer[A_numberIndex] = '\0';
        }
      } 
      else if (btn == 10) 
      {
        int enteredHour = atoi(A_numberBuffer);

        if (enteredHour > 23) 
        {
          handleOutOfRange("Out of range 0:23");
        }
        else 
        {
          alarmHour = enteredHour;
          Serial.print("Hour stored: ");
          Serial.println(alarmHour);
        }
      } 
      else if (btn == 11) 
      {
        int enteredMinute = atoi(A_numberBuffer);

        if (enteredMinute > 59) 
        {
          handleOutOfRange("Out of range 0:59");
        } 
        else 
        {
          alarmMinute = enteredMinute;
          Serial.print("Minute stored: ");
          Serial.println(alarmMinute);
        }
      } 
      else if (btn == 13) 
      {
        // Handle "Set" button press
        addAlarm(alarmHour, alarmMinute);
        printAlarms();
      } 
      else if (btn == 12) 
      {
        handleBackspace();
      } 
      else if (btn == 14) 
      {
        // Handle "Back" button press
        currentState = EXIT_PAGE;
        A_numberIndex = 0;
        A_numberBuffer[A_numberIndex] = '\0';
        Alarm_Page();
        break;
      }

      tft.setTextDatum(TL_DATUM);
      tft.setFreeFont(&FreeSans18pt7b);
      tft.setTextColor(DISP_TCOLOR);
      int xwidth = tft.drawString(A_numberBuffer, DISP_X + 4, DISP_Y + 12);
      tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
      delay(10);
    }
  }
}
/* Keypad of Password */
void drawPassKeypad() 
{
  for (uint8_t row = 0; row < ROW_OF_KEYPAD; row++) {
    for (uint8_t col = 0; col < COL_OF_KEYPAD; col++) {
      uint8_t btnNumber = col + row * COL_OF_KEYPAD;

      if (btnNumber >= 11) 
      {
        tft.setFreeFont(&FreeSans9pt7b);
      } 
      else 
      {
        tft.setFreeFont(&FreeSans18pt7b);
      }

      PassKey[btnNumber].initButton(&tft, (KEY_X + col * (KEY_W + KEY_SPACING_X)),
                                (KEY_Y + row * (KEY_H + KEY_SPACING_Y)),
                                KEY_W, KEY_H, TFT_DARKGREY, PassColor[btnNumber],
                                TFT_WHITE, PassLabel[btnNumber], KEY_TEXTSIZE);

      PassKey[btnNumber].drawButton();
    }
  }
}

void PassKeypad_Init()
{
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, 480, 320, TFT_BLACK);
  tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_DARKGREY);
  drawPassKeypad();
}

void PassKeypad_Loop()
{
  // Your existing loop code
  for (uint8_t btn = 0; btn < 15; btn++) 
  {
    if (btn >= 11) 
    {
      tft.setFreeFont(&FreeSans9pt7b);
    } 
    else 
    {
      tft.setFreeFont(&FreeSans18pt7b);
    }

    if (PassKey[btn].justReleased()) 
    {
      PassKey[btn].drawButton();
    }

    if (PassKey[btn].justPressed()) 
    {
      PassKey[btn].drawButton(true);

      if (btn < 11) 
      {
        if (PassIndex < PASS_LEN) 
        {
          PassBuffer[PassIndex] = PassLabel[btn][0];
          PassIndex++;
          PassBuffer[PassIndex] = '\0';
        }
      } 
      else if (btn == 11) 
      {
        PassBuffer[PassIndex] = '\0';
        if (PassIndex > 0) 
        {
          PassIndex--;
          PassBuffer[PassIndex] = '\0';
        }
      } 
      else if (btn == 13) 
      {
        // Handle "Send" button press
        int enteredPass = atoi(PassBuffer);
          if (enteredPass == 1234)
          {
            PassIndex = 0;
            PassBuffer[PassIndex] = '\0';
            Main_Page ();
            break;
          }
          else
          {
              PassIndex = 0;
              PassBuffer[PassIndex] = '\0';

              tft.setTextDatum(TL_DATUM);
              tft.setFreeFont(&FreeSans18pt7b);
              tft.setTextColor(DISP_TCOLOR);
              tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
              tft.drawString("Try again", DISP_X + 4, DISP_Y + 12);
              delay(3000);
              tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
          }
      } 
      else if (btn == 12) 
      {
        // Handle "New" button press
        PassIndex = 0;
        PassBuffer[PassIndex] = '\0';
      } 
      else if (btn == 14) 
      {
        // Handle "Back" button press
        PassIndex = 0;
        PassBuffer[PassIndex] = '\0';
        Password_Page ();
        break;
      }

      tft.setTextDatum(TL_DATUM);
      tft.setFreeFont(&FreeSans18pt7b);
      tft.setTextColor(DISP_TCOLOR);
      int xwidth = tft.drawString(PassBuffer, DISP_X + 4, DISP_Y + 12);
      tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
      delay(10);
    }
  }
}
/* Keypad of ID */
void drawIdKeypad() 
{
  for (uint8_t row = 0; row < ROW_OF_KEYPAD; row++) {
    for (uint8_t col = 0; col < COL_OF_KEYPAD; col++) {
      uint8_t btnNumber = col + row * COL_OF_KEYPAD;

      if (btnNumber >= 11) 
      {
        tft.setFreeFont(&FreeSans9pt7b);
      } 
      else 
      {
        tft.setFreeFont(&FreeSans18pt7b);
      }

      IdKey[btnNumber].initButton(&tft, (KEY_X + col * (KEY_W + KEY_SPACING_X)),
                                (KEY_Y + row * (KEY_H + KEY_SPACING_Y)),
                                KEY_W, KEY_H, TFT_DARKGREY, IdColor[btnNumber],
                                TFT_WHITE, IdLabel[btnNumber], KEY_TEXTSIZE);

      IdKey[btnNumber].drawButton();
    }
  }
}

void IdKeypad_Init()
{
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, 480, 320, TFT_BLACK);
  tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_DARKGREY);
  drawIdKeypad();
}

char* IdKeypad_Loop()
{
  static char enteredId[ID_LEN + 1]; 
  // Your existing loop code
  for (uint8_t btn = 0; btn < 15; btn++) 
  {
    if (btn >= 11) 
    {
      tft.setFreeFont(&FreeSans9pt7b);
    } 
    else 
    {
      tft.setFreeFont(&FreeSans18pt7b);
    }

    if (IdKey[btn].justReleased()) 
    {
      IdKey[btn].drawButton();
    }

    if (IdKey[btn].justPressed()) 
    {
      IdKey[btn].drawButton(true);

      if (btn < 11) 
      {
        if (IdIndex < ID_LEN) 
        {
          IdBuffer[IdIndex] = IdLabel[btn][0];
          IdIndex++;
          IdBuffer[IdIndex] = '\0';
        }
      } 
      else if (btn == 11) 
      {
        IdBuffer[IdIndex] = '\0';
        if (IdIndex > 0) 
        {
          IdIndex--;
          IdBuffer[IdIndex] = '\0';
        }
      } 
      else if (btn == 13) 
      {
        // Handle "Send" button press
        // send id to web and get the name and the code of watch
        
        if (IdIndex == ID_LEN)
        {
          strncpy(enteredId, IdBuffer, ID_LEN + 1);
          IdIndex = 0;
          IdBuffer[IdIndex] = '\0';
          Setup_Page();//send to web to get name
          break;
        }
        else
        {
            IdIndex = 0;
            IdBuffer[IdIndex] = '\0';
            tft.setTextDatum(TL_DATUM);
            tft.setFreeFont(&FreeSans18pt7b);
            tft.setTextColor(DISP_TCOLOR);
            tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
            tft.drawString("It must be 14 digits", DISP_X + 4, DISP_Y + 12);
            delay(3000);
            tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
        }
      } 
      else if (btn == 12) 
      {
        // Handle "New" button press
        IdIndex = 0;
        IdBuffer[IdIndex] = '\0';
      } 
      else if (btn == 14) 
      {
        // Handle "Back" button press
        // IdIndex = 0;
        // IdBuffer[IdIndex] = '\0';
        // Password_Page ();
        // break;
      }

      tft.setTextDatum(TL_DATUM);
      tft.setFreeFont(&FreeSans18pt7b);
      tft.setTextColor(DISP_TCOLOR);
      int xwidth = tft.drawString(IdBuffer, DISP_X + 4, DISP_Y + 12);
      tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
      delay(10);
    }
  }
  return enteredId;
}

/*-----------------------------------------------------------------------------------------*/

/****************************************** PAGES *****************************************/
void Setup_Page (void)
{
  MLabel ();
  printLocalTime();
  for (int btn = 0; btn < 15; btn++) 
  {
    PassKey[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    IdKey[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    BPKEY[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    BSGKEY[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  ADD.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  ABACK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  for (int btn = 0; btn < MAX_ALARMS; btn++) 
  {
    EDIT[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    DEL[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  PASS.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  tft.setFreeFont(&FreeSans12pt7b);
  tft.setCursor(20,150);
  tft.setTextColor(TFT_WHITE);
  tft.println("Name - Shrouk Ashraf Abdelfattah Ahmed");
  tft.setCursor(20,200);
  tft.print("ID       - ");
  tft.println(IdNum);
  SETUP_BUTTON();
}
void Main_Page (void)
{
  MLabel ();
  printLocalTime();
  for (int btn = 0; btn < 15; btn++) 
  {
    PassKey[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    IdKey[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    BPKEY[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    BSGKEY[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  ADD.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  ABACK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  for (int btn = 0; btn < MAX_ALARMS; btn++) 
  {
    EDIT[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    DEL[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  tft.setFreeFont(&FreeSans12pt7b);
  TOTAL_BUTTON();
  ALARM_BUTTON();
  ENTERY_BUTTON();
  INFO_BUTTON();
  LOCK_BUTTON();
}
void Password_Page (void)
{
  for (int btn = 0; btn < 15; btn++) 
  {
    PassKey[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  SETUP.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  tft.fillScreen(Black);
  tft.setTextColor(White);
  tft.setFreeFont(&FreeSans18pt7b);
  tft.setTextSize(1);
  tft.setCursor(170,100);
  tft.println("Password");
  PASS_BUTTON();
}
void HSTGP_Page(void)
{
  // int x =1;
  // x = BaHSTBu.isPressed();
  // while (x == 0) 
  // {
    

    unsigned long currentTime = millis();
    if (currentTime - prevtime_T1 > interval_T1) {
      tft.fillRect(0, 0, 480, 230, TFT_BLACK);
      prevtime_T1 = currentTime;
    }

    tft.setFreeFont(&FreeSans12pt7b);
    
    // Vital measurements
    max30102_HR();
    max30102_SPO2();
    mlx90614_TEMP();

    // Display BSG result
    tft.setTextSize(1);
    tft.setCursor(10, 180);
    tft.print("BSG    | ");
    tft.print(BSG_Result);
    tft.print(" mg/dL");

    // Display BP result
    tft.setCursor(10, 220);
    tft.print("BR       | ");
    tft.print(BP_Result);
    tft.print(" mmHg");

    // Display the total button
    BTotal_BUTTON();

    // delay(100);
    // if (BaHSTBu.isPressed())
    // {
    //   break;
    // }
  // }

  // Code here will be executed once BaHSTBu is released
  // Main_Page();
  // uint16_t t_x_hstgp = 0, t_y_hstgp = 0;
  // bool pressed_hstgp = tft.getTouch(&t_x_hstgp, &t_y_hstgp);

  // // For debugging, you can print the touch coordinates to the serial monitor
  // Serial.print("HSTGP_Page - t_x_hstgp: ");
  // Serial.print(t_x_hstgp);
  // Serial.print(", t_y_hstgp: ");
  // Serial.println(t_y_hstgp);
  
}
void BSG_Page (void)
{
  BSG_Result = BSGKeypad_Loop();
  //send the result to the total measured
  while (BSG_Result != 0)
  {
    Serial.println(BSG_Result);
    break;
  }
}
void BP_Page (void)
{
  BP_Result = BPKeypad_Loop();
  while (BP_Result != 0)
  {
    Serial.println(BP_Result);
    break;
  }

}
void Alarm_Page (void)
{
    // Remove the keypad buttons
  
  for (int btn = 0; btn < 15; btn++) 
  {
    Alarmkey[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(210,50);
  tft.setTextColor(TFT_WHITE);
  tft.setFreeFont(&FreeSans18pt7b);
  // Print the alarms
  tft.println("Alarm");
  for (int i = 0; i < numAlarms; i++) 
  {
    tft.setTextColor(TFT_WHITE);
    tft.printf("Alarm %d - %02d:%02d\n", i + 1, alarms[i].hour, alarms[i].minute);
  
    // Set position and size for Edit and Delete buttons
    int btnX = 300;
    int btnY = 80 + i * 40;
    int btnW = 80;
    int btnH = 30;
    tft.setFreeFont(&FreeSans9pt7b);
    // Initialize Edit button
    EDIT[i].initButton(&tft, btnX, btnY, btnW, btnH, New_C, New_C, TFT_WHITE, "Edit", 1);
    EDIT[i].drawButton();

    // Initialize Delete button
    DEL[i].initButton(&tft, btnX + btnW + 40, btnY, btnW, btnH, TFT_DARKGREY, TFT_DARKGREY, TFT_WHITE, "Delete", 1);
    DEL[i].drawButton();

    tft.setFreeFont(&FreeSans18pt7b);
  }
  ADD_BUTTON();
  BACK_BUTTON();
}
void ENTERY_Page (void)
{
  for (int btn = 0; btn < 15; btn++) 
  {
    BPKEY[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    BSGKEY[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  tft.fillScreen(Black);
  BSG_BUTTON();
  BP_BUTTON();
  BaOfEntry_BUTTON();
}
void INFO_Page(void)
{
  tft.setTextColor(White);
  tft.setFreeFont(&FreeSans12pt7b);
  // tft.setTextSize(2);
  tft.setCursor(50,50);
  tft.println("Code: 2019004");
  tft.setCursor(50,100);
  tft.println("Name: Shrouk Ashraf Abdelfattah");
  tft.setCursor(50,150);
  tft.println("ID:   2394829200202");
  tft.setCursor(50,200);
  tft.println("IP:    192.189.1.1");
  RESET_BUTTON();
  PINFO_BUTTON();
}
void Reset_Page(void)
{
  tft.fillScreen(Black);
  tft.setTextColor(White);
  tft.setFreeFont(&FreeSans18pt7b);
  tft.setTextSize(1);
  tft.setCursor(120,150);
  tft.println("Are you sure?");
  CANCEL_BUTTON();
  YES_BUTTON();
}
void Connection_Page(void)
{
  
}
/*****************************************************************************************/

/********************************* Buttons_Initialization ********************************/
void LOCK_BUTTON()
{
  LOCK.initButton(&tft,240,270,150,60,Blue,Blue,TFT_WHITE,"Lock", KEY_TEXTSIZE);
  LOCK.drawButton();
}
void BaOfEntry_BUTTON ()
{
  Ba_EN.initButton(&tft,240,270,150,60,Blue,Blue,TFT_WHITE,"Previous", KEY_TEXTSIZE);
  Ba_EN.drawButton();
}
void BSG_BUTTON()
{
  BSG.initButton(&tft,120,150,150,60,Blue,Blue,TFT_WHITE,"BSG", KEY_TEXTSIZE);
  BSG.drawButton();
}
void BP_BUTTON()
{
  BP.initButton(&tft,365,150,150,60,Blue,Blue,TFT_WHITE,"BP", KEY_TEXTSIZE);
  BP.drawButton();
}
void TOTAL_BUTTON()
{
  TOTAL.initButton(&tft,125,110,150,60,Blue,Blue,TFT_WHITE,"Measure", KEY_TEXTSIZE);
  TOTAL.drawButton();
}
void ALARM_BUTTON()
{
  CLOCK.initButton(&tft,125,190,150,60,Blue,Blue,TFT_WHITE,"Clock", KEY_TEXTSIZE);
  CLOCK.drawButton();
}
void BACK_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  ABACK.initButton(&tft,380,270,150,60,Blue,Blue,TFT_WHITE,"Previous", KEY_TEXTSIZE);
  ABACK.drawButton();
}
void BTotal_BUTTON()
{
  BaHSTBu.initButton(&tft,380,270,150,60,Blue,Blue,TFT_WHITE,"Back", KEY_TEXTSIZE);
  BaHSTBu.drawButton();
}
void ADD_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  ADD.initButton(&tft,100,270,150,60,Blue,Blue,TFT_WHITE,"Set alarm", KEY_TEXTSIZE);
  ADD.drawButton();
  /*
      int16_t x
      int16_t y
      uint16_t w
      uint16_t h
      uint16_t outline
      uint16_t fill
      uint16_t textcolor
      char * label
      uint8_t textsize
  */
}

void ENTERY_BUTTON()
{
  ENTERY.initButton(&tft,365,110,150,60,Blue,Blue,TFT_WHITE,"Entery", KEY_TEXTSIZE);
  ENTERY.drawButton();
}

void INFO_BUTTON()
{
  INFO.initButton(&tft,365,190,150,60,Blue,Blue,TFT_WHITE,"Info", KEY_TEXTSIZE);
  INFO.drawButton();
}

void RESET_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  RESET.initButton(&tft,380,270,150,60,Blue,Blue,TFT_WHITE,"Reset", KEY_TEXTSIZE);
  RESET.drawButton();
}
void PINFO_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  PINFO.initButton(&tft,100,270,150,60,Blue,Blue,TFT_WHITE,"Previous", KEY_TEXTSIZE);
  PINFO.drawButton();
}
void PASS_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  PASS.initButton(&tft,240,150,180,60,TFT_DARKGREY,TFT_DARKGREY,TFT_WHITE,"Enter", KEY_TEXTSIZE);
  PASS.drawButton();
}
void YES_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  YES.initButton(&tft,100,270,150,60,Blue,Blue,TFT_WHITE,"Yes", KEY_TEXTSIZE);
  YES.drawButton();
}
void CANCEL_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  CANC.initButton(&tft,380,270,150,60,Blue,Blue,TFT_WHITE,"Cancel", KEY_TEXTSIZE);
  CANC.drawButton();
}
void SETUP_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  SETUP.initButton(&tft,240,270,150,60,Blue,Blue,TFT_WHITE,"Enter", KEY_TEXTSIZE);
  SETUP.drawButton();
}
/**************************************************************************************************/
void MLabel ()
{
  tft.fillScreen(Black);
  tft.setFreeFont(&FreeSans9pt7b);
  tft.setTextSize(1);
  tft.fillRect(0,20,480,40,Black);
  tft.setCursor(70,20);
  tft.setTextColor(TFT_WHITE);
  tft.println("MDCT");
  tft.setCursor(10,40);
  tft.println("Your Care Our Mission");
}
