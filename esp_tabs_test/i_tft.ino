
void TFT_Init(void)
{
    //Initialize TFT
    tft.init();
    // Set the rotation
    tft.setRotation(1);
    uint16_t calData[5] = { 313, 3599, 253, 3529, 7  };
    tft.setTouch(calData);
    // Clear the screen
    tft.fillScreen(TFT_BLACK);
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
        int xwidth = tft.drawString(numberBuffer, DISP_X + 4, DISP_Y + 12);
        tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
        tft.drawString("Sent Successfully", DISP_X + 4, DISP_Y + 12);
        delay(3000);
        tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);

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
                                TFT_WHITE, keyLabelBSG[btnNumber], KEY_TEXTSIZE);

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
          numberBufferG[numberIndexG] = keyLabelBSG[btn][0];
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
        strncpy(Buffer_Result_, numberBufferG, NUM_LEN_G + 1);
        numberIndexG = 0;
        numberBufferG[numberIndexG] = '\0';
        tft.setTextDatum(TL_DATUM);
        tft.setFreeFont(&FreeSans18pt7b);
        tft.setTextColor(DISP_TCOLOR);
        int xwidth = tft.drawString(CodeBuffer, DISP_X + 4, DISP_Y + 12);
        tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
        tft.drawString("Sent Successfully", DISP_X + 4, DISP_Y + 12);
        delay(3000);
        tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);

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
  int xwidth = tft.drawString(CodeBuffer, DISP_X + 4, DISP_Y + 12);
  tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
  tft.drawString(message, DISP_X + 4, DISP_Y + 12);
  delay(3000);
  tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
}

void handleBackspace() 
{
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
      tft.setFreeFont(&FreeSans9pt7b);
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
          handleOutOfRange("from 0 to 59");
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
          handleOutOfRange("Out of range 00:59");
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
            exit_from_measure = 0;
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
              int xwidth = tft.drawString(CodeBuffer, DISP_X + 4, DISP_Y + 12);
              tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
              tft.drawString("Try again", DISP_X + 4, DISP_Y + 12);
              delay(3000);
              tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
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
          tft.fillScreen(Black);
          Delete_All_Buttons();
          switch(btn_connection_type)
          {
            case WIFI_connect:
              Send_ID_CODE_WIFI();
            break; 
            case SIM_connect:
              Send_ID_CODE_SIM();
            break;
          }
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
            int xwidth = tft.drawString(CodeBuffer, DISP_X + 4, DISP_Y + 12);
            tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
            tft.drawString("It must be 14 digits", DISP_X + 4, DISP_Y + 12);
            delay(3000);
            tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
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
        IdIndex = 0;
        IdBuffer[IdIndex] = '\0';
        EnterID_Page();
        break;
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

/* keypad of code */
void drawCodeKeypad() 
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

      CodeKey[btnNumber].initButton(&tft, (KEY_X + col * (KEY_W + KEY_SPACING_X)),
                                (KEY_Y + row * (KEY_H + KEY_SPACING_Y)),
                                KEY_W, KEY_H, TFT_DARKGREY, CodeColor[btnNumber],
                                TFT_WHITE, CodeLabel[btnNumber], KEY_TEXTSIZE);

      CodeKey[btnNumber].drawButton();
    }
  }
}

void CodeKeypad_Init()
{
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, 480, 320, TFT_BLACK);
  tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_DARKGREY);
  drawCodeKeypad();
}

char* CodeKeypad_Loop()
{
  static char enteredCode[CODE_LEN + 1]; 
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

    if (CodeKey[btn].justReleased()) 
    {
      CodeKey[btn].drawButton();
    }

    if (CodeKey[btn].justPressed()) 
    {
      CodeKey[btn].drawButton(true);

      if (btn < 11) 
      {
        if (CodeIndex < CODE_LEN) 
        {
          CodeBuffer[CodeIndex] = CodeLabel[btn][0];
          CodeIndex++;
          CodeBuffer[CodeIndex] = '\0';
        }
      } 
      else if (btn == 11) 
      {
        CodeBuffer[CodeIndex] = '\0';
        if (CodeIndex > 0) 
        {
          CodeIndex--;
          CodeBuffer[CodeIndex] = '\0';
        }
      } 
      else if (btn == 13) 
      {
        // Handle "Send" button press
        // send id to web and get the name and the code of watch
        
        if (CodeIndex == CODE_LEN)
        {
          strncpy(enteredCode, CodeBuffer, CODE_LEN + 1);
          CodeIndex = 0;
          CodeBuffer[CodeIndex] = '\0';
          Connection_Page();
          break;
        }
        else
        {
            CodeIndex = 0;
            CodeBuffer[CodeIndex] = '\0';
            tft.setTextDatum(TL_DATUM);
            tft.setFreeFont(&FreeSans18pt7b);
            tft.setTextColor(DISP_TCOLOR);
            int xwidth = tft.drawString(CodeBuffer, DISP_X + 4, DISP_Y + 12);
            tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
            tft.drawString("It must be 9 digits", DISP_X + 4, DISP_Y + 12);
            delay(3000);
            tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
        }
      } 
      else if (btn == 12) 
      {
        // Handle "New" button press
        CodeIndex = 0;
        CodeBuffer[CodeIndex] = '\0';
      } 
      else if (btn == 14) 
      {
        // Handle "Back" button press
        CodeIndex = 0;
        CodeBuffer[CodeIndex] = '\0';
        Connection_Page();
        break;
      }

      tft.setTextDatum(TL_DATUM);
      tft.setFreeFont(&FreeSans18pt7b);
      tft.setTextColor(DISP_TCOLOR);
      int xwidth = tft.drawString(CodeBuffer, DISP_X + 4, DISP_Y + 12);
      tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
      delay(10);
    }
  }
  return enteredCode;
}
/*------------------------------------ END OF KEYPADS -------------------------------------*/
/*************************************** KEYBOARD ******************************************/
/* SSID OF WIFI 'KEYBOARD' */
void drawKeyboard_SSID() {
  if (capsLock_SSID) {
    drawKeyboard_capital_SSID();
  } else {
    drawKeyboard_small_SSID();
  }
}

void handleOutOfRange_WIFI(const char* message) 
{
  A_numberIndex = 0;
  A_numberBuffer[A_numberIndex] = '\0';
  tft.setTextDatum(TL_DATUM);
  tft.setFreeFont(&FreeSans18pt7b);
  tft.setTextColor(DISP_TCOLOR);
  int xwidth = tft.drawString(numberBuffer_SSID, DISP_X_KB + 4, DISP_Y_KB + 12);
  tft.fillRect(DISP_X_KB + 4 + xwidth, DISP_Y_KB + 1, DISP_W_KB - xwidth - 5, DISP_H_KB - 2, TFT_BLACK);
  tft.drawString(message, DISP_X_KB + 4, DISP_Y_KB + 12);
  delay(3000);
  tft.fillRect(DISP_X_KB + 4 + xwidth, DISP_Y_KB + 1, DISP_W_KB - xwidth - 5, DISP_H_KB - 2, TFT_BLACK);
}
void drawKeyboard_capital_SSID() {
  for (uint8_t row = 0; row < ROW_OF_KEYBOARD; row++) {
    for (uint8_t col = 0; col < COL_OF_KEYBOARD; col++) {
      uint8_t btnNumber = col + row * COL_OF_KEYBOARD;

      tft.setFreeFont(LABEL1_FONT);

      keyboard_SSID[btnNumber].initButton(&tft, (KEY_X_KB + col * (KEY_W_KB + KEY_SPACING_X_KB)),
                                (KEY_Y_KB + row * (KEY_H_KB + KEY_SPACING_Y_KB)),
                                KEY_W_KB, KEY_H_KB, TFT_DARKGREY, keyColor_SSID[btnNumber],
                                TFT_WHITE, keyLabel_C_SSID[btnNumber], KEY_TEXTSIZE);

      keyboard_SSID[btnNumber].drawButton();
    }
  }
}

void drawKeyboard_small_SSID() {
  for (uint8_t row = 0; row < ROW_OF_KEYBOARD; row++) {
    for (uint8_t col = 0; col < COL_OF_KEYBOARD; col++) {
      uint8_t btnNumber = col + row * COL_OF_KEYBOARD;

      tft.setFreeFont(LABEL1_FONT);

      keyboard_SSID[btnNumber].initButton(&tft, (KEY_X_KB + col * (KEY_W_KB + KEY_SPACING_X_KB)),
                                (KEY_Y_KB + row * (KEY_H_KB + KEY_SPACING_Y_KB)),
                                KEY_W_KB, KEY_H_KB, TFT_DARKGREY, keyColor_SSID[btnNumber],
                                TFT_WHITE, keyLabel_S_SSID[btnNumber], KEY_TEXTSIZE);

      keyboard_SSID[btnNumber].drawButton();
    }
  }
}
void SSID_Keyboard_Init()
{
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, 480, 320, TFT_BLACK);
  tft.fillRect(DISP_X_KB, DISP_Y_KB, DISP_W_KB, DISP_H_KB, TFT_BLACK);
  tft.drawRect(DISP_X_KB, DISP_Y_KB, DISP_W_KB, DISP_H_KB, TFT_DARKGREY);
  drawKeyboard_SSID();
  handleOutOfRange_WIFI("Enter SSID");
}

char* SSID_Keyboard_Loop()
{
  static char enteredssid[NUM_LEN_SSID + 1]; 
  for (uint8_t btn = 0; btn < 50; btn++) {
    tft.setFreeFont(LABEL1_FONT);

    if (keyboard_SSID[btn].justReleased()) {
      keyboard_SSID[btn].drawButton();
    }

    if (keyboard_SSID[btn].justPressed()) {
      keyboard_SSID[btn].drawButton(true);

      if (btn > 19 && btn < 46) {
        if (numberIndex_SSID < NUM_LEN_SSID) {
          char keys = keyLabel_C_SSID[btn][0];
          if (!capsLock_SSID) {
            keys = keyLabel_S_SSID[btn][0];
          }
          numberBuffer_SSID[numberIndex_SSID] = keys;
          numberIndex_SSID++;
          numberBuffer_SSID[numberIndex_SSID] = '\0';
        }
      } else if (btn <= 18) {
        if (numberIndex_SSID < NUM_LEN_SSID) {
          numberBuffer_SSID[numberIndex_SSID] = keyLabel_S_SSID[btn][0];
          numberIndex_SSID++;
          numberBuffer_SSID[numberIndex_SSID] = '\0';
        }
      } else if (btn == 19) {
        // Handle "Back" button press
        numberIndex_SSID = 0;
        numberBuffer_SSID[numberIndex_SSID] = '\0';
        Connection_Page();
        break;
      } else if (btn == 46) {
        // Handle "Cap" button press
        capsLock_SSID = !capsLock_SSID;
        if (capsLock_SSID) {
          drawKeyboard_capital_SSID();
        } else {
          drawKeyboard_small_SSID();
        }
      } else if (btn == 47) {
        // Delete button
        if (numberIndex_SSID > 0) {
          numberIndex_SSID--;
          numberBuffer_SSID[numberIndex_SSID] = '\0';
        }
      } else if (btn == 48) {
        // Handle "Tap" button press
        if (numberIndex_SSID < NUM_LEN_SSID) {
          numberBuffer_SSID[numberIndex_SSID] = ' ';
          numberIndex_SSID++;
          numberBuffer_SSID[numberIndex_SSID] = '\0';
        }
      } else if (btn == 49) {
        // Handle "Ent" button press
        strncpy(enteredssid, numberBuffer_SSID, NUM_LEN_SSID + 1);
        Serial.println(numberBuffer_SSID);
        numberIndex_SSID = 0;
        numberBuffer_SSID[numberIndex_SSID] = '\0';
        Delete_All_Buttons();
        PASSWIFI_Keyboard_Init();
        break;
      }

      tft.setTextDatum(TL_DATUM);
      tft.setFreeFont(&FreeSans18pt7b);
      tft.setTextColor(DISP_TCOLOR_KB);
      int xwidth = tft.drawString(numberBuffer_SSID, DISP_X_KB + 4, DISP_Y_KB + 12);
      tft.fillRect(DISP_X_KB + 4 + xwidth, DISP_Y_KB + 1, DISP_W_KB - xwidth - 5, DISP_H_KB - 2, TFT_BLACK);
      delay(10);
    }
  }
  return enteredssid;
}
/* PASSWORD OF WIFI 'KEYBOARD' */
void drawKeyboard_PASSWORD() {
  int xwidth = tft.drawString(numberBuffer_PASSWIFI, DISP_X_KB + 4, DISP_Y_KB + 12);
  tft.fillRect(DISP_X_KB + 4 + xwidth, DISP_Y_KB + 1, DISP_W_KB - xwidth - 5, DISP_H_KB - 2, TFT_BLACK);
  if (capsLock_PASSWIFI) {
    drawKeyboard_capital_PASSWIFI();
  } else {
    drawKeyboard_small_PASSWIFI();
  }
}

void drawKeyboard_capital_PASSWIFI() {
  for (uint8_t row = 0; row < ROW_OF_KEYBOARD; row++) {
    for (uint8_t col = 0; col < COL_OF_KEYBOARD; col++) {
      uint8_t btnNumber = col + row * COL_OF_KEYBOARD;

      tft.setFreeFont(LABEL1_FONT);

      keyboard_PASSWORD[btnNumber].initButton(&tft, (KEY_X_KB + col * (KEY_W_KB + KEY_SPACING_X_KB)),
                                (KEY_Y_KB + row * (KEY_H_KB + KEY_SPACING_Y_KB)),
                                KEY_W_KB, KEY_H_KB, TFT_DARKGREY, keyColor_PASSWIFI[btnNumber],
                                TFT_WHITE, keyLabel_C_PASSWIFI[btnNumber], KEY_TEXTSIZE);

      keyboard_PASSWORD[btnNumber].drawButton();
    }
  }
}

void drawKeyboard_small_PASSWIFI() {
  for (uint8_t row = 0; row < ROW_OF_KEYBOARD; row++) {
    for (uint8_t col = 0; col < COL_OF_KEYBOARD; col++) {
      uint8_t btnNumber = col + row * COL_OF_KEYBOARD;

      tft.setFreeFont(LABEL1_FONT);

      keyboard_PASSWORD[btnNumber].initButton(&tft, (KEY_X_KB + col * (KEY_W_KB + KEY_SPACING_X_KB)),
                                (KEY_Y_KB + row * (KEY_H_KB + KEY_SPACING_Y_KB)),
                                KEY_W_KB, KEY_H_KB, TFT_DARKGREY, keyColor_PASSWIFI[btnNumber],
                                TFT_WHITE, keyLabel_S_PASSWIFI[btnNumber], KEY_TEXTSIZE);

      keyboard_PASSWORD[btnNumber].drawButton();
    }
  }
}

void PASSWIFI_Keyboard_Init()
{
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, 480, 320, TFT_BLACK);
  tft.fillRect(DISP_X_KB, DISP_Y_KB, DISP_W_KB, DISP_H_KB, TFT_BLACK);
  tft.drawRect(DISP_X_KB, DISP_Y_KB, DISP_W_KB, DISP_H_KB, TFT_DARKGREY);
  drawKeyboard_PASSWORD();
  handleOutOfRange_WIFI("Enter Password");
}

void PASSWORD_Keyboard_Loop()
{
  for (uint8_t btn = 0; btn < 50; btn++) 
  {
    tft.setFreeFont(LABEL1_FONT);

    if (keyboard_PASSWORD[btn].justReleased()) {
      keyboard_PASSWORD[btn].drawButton();
    }

    if (keyboard_PASSWORD[btn].justPressed()) 
    {
      keyboard_PASSWORD[btn].drawButton(true);

      if (btn > 19 && btn < 46) 
      {
        if (numberIndex_PASSWIFI < NUM_LEN_PASSWIFI) {
          char keys = keyLabel_C_PASSWIFI[btn][0];
          if (!capsLock_PASSWIFI) {
            keys = keyLabel_S_PASSWIFI[btn][0];
          }
          numberBuffer_PASSWIFI[numberIndex_PASSWIFI] = keys;
          numberIndex_PASSWIFI++;
          numberBuffer_PASSWIFI[numberIndex_PASSWIFI] = '\0';
        }
      } else if (btn <= 18) {
        if (numberIndex_PASSWIFI < NUM_LEN_PASSWIFI) {
          numberBuffer_PASSWIFI[numberIndex_PASSWIFI] = keyLabel_S_PASSWIFI[btn][0];
          numberIndex_PASSWIFI++;
          numberBuffer_PASSWIFI[numberIndex_PASSWIFI] = '\0';
        }
      } else if (btn == 19) {
        // Handle "Back" button press
        numberIndex_PASSWIFI = 0;
        numberBuffer_PASSWIFI[numberIndex_PASSWIFI] = '\0';
        Connection_Page();
        break;
      } else if (btn == 46) {
        // Handle "Cap" button press
        capsLock_PASSWIFI = !capsLock_PASSWIFI;
        if (capsLock_PASSWIFI) {
          drawKeyboard_capital_PASSWIFI();
        } else {
          drawKeyboard_small_PASSWIFI();
        }
      } else if (btn == 47) {
        // Delete button
        if (numberIndex_PASSWIFI > 0) {
          numberIndex_PASSWIFI--;
          numberBuffer_PASSWIFI[numberIndex_PASSWIFI] = '\0';
        }
      } else if (btn == 48) {
        // Handle "Tap" button press
        if (numberIndex_PASSWIFI < NUM_LEN_PASSWIFI) {
          numberBuffer_PASSWIFI[numberIndex_PASSWIFI] = ' ';
          numberIndex_PASSWIFI++;
          numberBuffer_PASSWIFI[numberIndex_PASSWIFI] = '\0';
        }
      }
      else if (btn == 49) 
      {
        // Handle "Ent" button press;
        password = numberBuffer_PASSWIFI;
        // Ensure all buttons are deleted before starting a new process
        Delete_All_Buttons();
        Serial.println("Done :)");
        Serial.println(ssid);
        Serial.println(password);
        // Try connecting to WiFi
        wifi_connect();  // Still in page until wifi connected 
        Serial.println("Done :))");
        // Check if connected to WiFi before proceeding
        if (WiFi.status() == WL_CONNECTED) {
          EnterID_Page();  // Go to ID page if WiFi is connected
        } else {
          // Optionally handle WiFi connection failure
          Serial.println("WiFi connection failed.");
        }

        // Break the loop to prevent further processing
        break;
      }


      tft.setTextDatum(TL_DATUM);
      tft.setFreeFont(&FreeSans18pt7b);
      tft.setTextColor(DISP_TCOLOR_KB);
      int xwidth = tft.drawString(numberBuffer_PASSWIFI, DISP_X_KB + 4, DISP_Y_KB + 12);
      tft.fillRect(DISP_X_KB + 4 + xwidth, DISP_Y_KB + 1, DISP_W_KB - xwidth - 5, DISP_H_KB - 2, TFT_BLACK);
      delay(10);
    }
  }
}
/**************************************** END OF KEYBOARDS *********************************/

/****************************************** PAGES *****************************************/
void EnterID_Page(void)
{
  tft.fillScreen(Black);
  Delete_All_Buttons();
  MLabel();
  tft.setTextColor(White);
  tft.setFreeFont(&FreeSans18pt7b);
  tft.setTextSize(1);
  tft.setCursor(150,150);
  tft.println("Enter an ID");
  ID_BUTTON();
}
void Connection_Page(void)
{
  Delete_All_Buttons();
  tft.fillScreen(Black);
  MLabel();
  WIFI_BUTTON();
  SIM_BUTTON();
  CODE_BUTTON();
}

void Setup_Page (void)
{
  MLabel ();
  tft.setFreeFont(&FreeSans12pt7b);
  tft.setCursor(20,150);
  tft.setTextColor(TFT_WHITE);
  // Use the received name from the API response
  tft.println("Name:  " + String(name_id));
  tft.setCursor(20,200);
  tft.print("National ID: ");
  tft.println(IdNum);
  SETUP_BUTTON();
}
void Password_Page (void)
{
  Delete_All_Buttons();
  tft.setTextColor(White);
  tft.setFreeFont(&FreeSans18pt7b);
  tft.setTextSize(1);
  tft.setCursor(170,160);
  tft.fillScreen(Black);
  tft.println("Password");
  PASS_BUTTON();
  Ba_Pass_BUTTON();
}

void Main_Page (void)
{
  MLabel ();
  Delete_All_Buttons();
  tft.setFreeFont(&FreeSans12pt7b);
  TOTAL_BUTTON();
  INFO_BUTTON();
  LOCK_BUTTON();
  HSTGP_Page();
  while(exit_from_measure == 0)
  {
    uint16_t TOUCH_X = 0, TOUCH_Y = 0;
    bool pressed = tft.getTouch(&TOUCH_X, &TOUCH_Y);
    /* Upload code by OTA */
    ArduinoOTA.handle();
    /* Measure heart rate and oxygen sensor */
    MAX30102.getHeartbeatSPO2();
    /* Measure temperature sensor */
    mlx.readObjectTempC();
    if ((millis() - lastTime_main) > timerDelay_main) 
    {
      if(check_on_alarm == 0){
        tft.fillRect(0, 50, 480, 140, TFT_BLACK);
        HSTGP_Page();
      }
      lastTime_main = millis();
    }
    if (pressed && LOCK.contains(TOUCH_X, TOUCH_Y)) 
    {
      LOCK.press(true);
    }
    else 
    {
      LOCK.press(false);
    }
    if (LOCK.justReleased()) 
    {
      LOCK.drawButton();
      exit_from_measure = 1;
      enter_page = set_up;
    }
    if (LOCK.justPressed()) 
    {
      tft.fillScreen(TFT_BLACK);
      Delete_All_Buttons();
    }
    /******************************************************************/
    if (pressed && TOTAL.contains(TOUCH_X, TOUCH_Y)) 
    {
      TOTAL.press(true);
    } 
    else 
    {
      TOTAL.press(false);
    }
    if (TOTAL.justReleased()) 
    {
      TOTAL.drawButton();
      exit_from_measure = 1;
      enter_page = Alarm_Entry;
    }
    if (TOTAL.justPressed()) 
    {
      tft.fillScreen(TFT_BLACK);
      Delete_All_Buttons();
    }
    /******************************************************************/
      if (pressed && INFO.contains(TOUCH_X, TOUCH_Y)) 
    {
      INFO.press(true);
    } 
    else 
    {
      INFO.press(false);
    }
    if (INFO.justReleased()) 
    {
      INFO.drawButton();
      exit_from_measure = 1;
      enter_page = Info;
    }
    if (INFO.justPressed()) 
    {
      tft.fillScreen(TFT_BLACK);
      Delete_All_Buttons();
    }
    /******************************************************************/
    if (pressed && CANCALA.contains(TOUCH_X, TOUCH_Y))
    {
      CANCALA.press(true);
    } 
    else 
    {
      CANCALA.press(false);
    }
    if (CANCALA.justReleased()) 
    {
      CANCALA.drawButton();
      exit_from_measure = 1;
      enter_page = set_up;
    }
    if (CANCALA.justPressed()) 
    {
      tft.fillScreen(TFT_BLACK);
      Delete_All_Buttons();
    }
    alarm_action();
    /* CHECK DATA REQUEST */
   
  switch(btn_connection_type)
  {
    case WIFI_connect:
        if (sendDataRequested_WIFI) 
        {
          sendData_WIFI();
          sendDataRequested_WIFI = false; // Reset flag after sending data
        }
    break; 
    case SIM_connect:
        if (sendDataRequested_SIM) 
        {
          sendData_SIM();
          sendDataRequested_SIM = false; // Reset flag after sending data
        }
    break;
  }
  
  
  // Check for trigger from cloud service
  
  if ((millis() - lastTime) > 3000) 
  {
    switch(btn_connection_type)
    {
      case WIFI_connect:
          checkForTrigger_WIFI();
      break; 
      case SIM_connect:
          checkForTrigger_SIM(); 
      break;
    }
      lastTime = millis();
  }
    printLocalTime();
  }
  tft.fillScreen(TFT_BLACK);
  switch(enter_page)
  {
    case still_in_main:
      break;
    case set_up: Setup_Page();
      break;
    case Alarm_Entry: AE_Page(); 
      break;
    case Info: INFO_Page(); 
      break;
  }
  
}
void AE_Page(void)
{
  MLabel ();
  Delete_All_Buttons();
  tft.setFreeFont(&FreeSans12pt7b);
  ALARM_BUTTON();
  ENTERY_BUTTON();
  AE_BUTTON();
}
void INFO_Page(void)
{
  tft.setTextColor(White);
  tft.setFreeFont(&FreeSans12pt7b);
  tft.setCursor(50,50);
  tft.print("Code: ");
  tft.println(watchCode);
  tft.setCursor(50,100);
  // tft.println("Name: Shrouk Ashraf ");
  tft.println("Name: " + String(name_id)); //name from web 
  tft.setCursor(50,150);
  tft.print("National ID: ");
  tft.println(IdNum);
  tft.setCursor(50,200);
  tft.print("IP: ");
  tft.println(WiFi.localIP());
  RESET_BUTTON();
  PINFO_BUTTON();
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
void HSTGP_Page(void)
{
    tft.setFreeFont(&FreeSans12pt7b);
    // Vital measurements
    max30102_HR_SPO2();
    mlx90614_TEMP();
}
/*****************************************************************************************/

/********************************* Buttons_Initialization ********************************/
void ID_BUTTON()
{
  ID.initButton(&tft,240,270,150,60,Blue,Blue,TFT_WHITE,"ID", KEY_TEXTSIZE);
  ID.drawButton();
}


void WIFI_BUTTON()
{
  WIFI.initButton(&tft,120,150,150,60,Blue,Blue,TFT_WHITE,"WIFI", KEY_TEXTSIZE);
  WIFI.drawButton();
}
void SIM_BUTTON()
{
  SIM.initButton(&tft,365,150,150,60,Blue,Blue,TFT_WHITE,"SIM", KEY_TEXTSIZE);
  SIM.drawButton();
}


void SETUP_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  SETUP.initButton(&tft,240,270,150,60,Blue,Blue,TFT_WHITE,"Enter", KEY_TEXTSIZE);
  SETUP.drawButton();
}


void PASS_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  PASS.initButton(&tft,100,270,150,60,TFT_DARKGREY,TFT_DARKGREY,TFT_WHITE,"Enter", KEY_TEXTSIZE);
  PASS.drawButton();
}
void Ba_Pass_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  Ba_Pass.initButton(&tft,380,270,150,60,TFT_DARKGREY,TFT_DARKGREY,TFT_WHITE,"Previous", KEY_TEXTSIZE);
  Ba_Pass.drawButton();
}


void INFO_BUTTON()
{
  INFO.initButton(&tft,80,270,130,60,Blue,Blue,TFT_WHITE,"Info", KEY_TEXTSIZE);
  INFO.drawButton();
}
void LOCK_BUTTON()
{
  LOCK.initButton(&tft,240,270,130,60,Blue,Blue,TFT_WHITE,"Lock", KEY_TEXTSIZE);
  LOCK.drawButton();
}
void TOTAL_BUTTON()
{
  TOTAL.initButton(&tft,400,270,130,60,Blue,Blue,TFT_WHITE,"Setup", KEY_TEXTSIZE);
  TOTAL.drawButton();
}


void PINFO_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  PINFO.initButton(&tft,100,270,150,60,Blue,Blue,TFT_WHITE,"Previous", KEY_TEXTSIZE);
  PINFO.drawButton();
}
void RESET_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  RESET.initButton(&tft,380,270,150,60,Blue,Blue,TFT_WHITE,"Reset", KEY_TEXTSIZE);
  RESET.drawButton();
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


void ALARM_BUTTON()
{
  CLOCK.initButton(&tft,120,150,150,60,Blue,Blue,TFT_WHITE,"Clock", KEY_TEXTSIZE);
  CLOCK.drawButton();
}
void ENTERY_BUTTON()
{
  ENTERY.initButton(&tft,365,150,150,60,Blue,Blue,TFT_WHITE,"Entery", KEY_TEXTSIZE);
  ENTERY.drawButton();
}
void AE_BUTTON()
{
  AE.initButton(&tft,240,270,130,60,Blue,Blue,TFT_WHITE,"Previous", KEY_TEXTSIZE);
  AE.drawButton();
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

void ADD_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  ADD.initButton(&tft,100,270,150,60,Blue,Blue,TFT_WHITE,"Set alarm", KEY_TEXTSIZE);
  ADD.drawButton();
}
void BACK_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  ABACK.initButton(&tft,380,270,150,60,Blue,Blue,TFT_WHITE,"Previous", KEY_TEXTSIZE);
  ABACK.drawButton();
}
void CANALARM_BUTTON()
{
  CANCALA.initButton(&tft,240,270,150,60,Blue,Blue,TFT_WHITE,"Exit", KEY_TEXTSIZE);
  CANCALA.drawButton();
}
void CODE_BUTTON()
{
  CODE.initButton(&tft,240,270,130,60,Blue,Blue,TFT_WHITE,"CODE", KEY_TEXTSIZE);
  CODE.drawButton();
}
void BTotal_BUTTON()
{
  tft.setFreeFont(&FreeSans9pt7b);
  BaHSTBu.initButton(&tft,380,270,150,60,Blue,Blue,TFT_WHITE,"Previous", KEY_TEXTSIZE);
  BaHSTBu.drawButton();
}

/**************************************************************************************************/
void MLabel ()
{
  tft.fillScreen(Black);
  tft.fillRect(0,20,480,40,Black);
  printLocalTime();
  tft.setFreeFont(&FreeSans9pt7b);
  tft.setTextSize(1);
  tft.setCursor(70,20);
  tft.setTextColor(TFT_WHITE);
  tft.println("MDCT");
  tft.setCursor(10,40);
  tft.println("Your Care Our Mission");
}
void Delete_All_Buttons()
{
  for (int btn = 0; btn < 15; btn++) 
  {
    PassKey[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    IdKey[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    CodeKey[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    BPKEY[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    BSGKEY[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    Alarmkey[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  for (int btn = 0; btn < 50; btn++) 
  {
    keyboard_PASSWORD[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    keyboard_SSID[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  for (int btn = 0; btn < MAX_ALARMS; btn++) 
  {
    EDIT[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    DEL[btn].initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  ID.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  WIFI.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  SIM.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  CODE.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  SETUP.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  PASS.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  Ba_Pass.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  INFO.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  LOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  TOTAL.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  PINFO.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  RESET.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  YES.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  CANC.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  CLOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  ENTERY.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  AE.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  ADD.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  ABACK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  BSG.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  BP.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  Ba_EN.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  BaHSTBu.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  CANCALA.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
}
