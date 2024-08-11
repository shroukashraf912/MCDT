void loop() 
{
/* Local Variables */
  uint16_t touch_X = 0, touch_Y = 0;
/*********************************************/
  /* Get the touch place x and y dimensions */
  bool pressed = tft.getTouch(&touch_X, &touch_Y); 
  /* Upload code by OTA */
  ArduinoOTA.handle();
  /* Display time in all pages */
  // printLocalTime();
  /* Measure heart rate and oxygen sensor */
  MAX30102.getHeartbeatSPO2();
  /* Measure temperature sensor */
  mlx.readObjectTempC();
/*********************************************/
/****************************************************Keypads Check*******************************************************/
  /* check on Alarm keypad */
  for (uint8_t b = 0; b < 15; b++) 
  {
    if (pressed && Alarmkey[b].contains(touch_X, touch_Y)) 
    {
      Alarmkey[b].press(true); // tell the button it is pressed
    } 
    else 
    {
      Alarmkey[b].press(false); // tell the button it is NOT pressed
    }
  }
  /* check on Blood_Pressure keypad to enter the value*/
  for (uint8_t b = 0; b < 15; b++) 
  {
    if (pressed && BPKEY[b].contains(touch_X, touch_Y)) 
    {
      BPKEY[b].press(true);  // tell the button it is pressed
    } else {
      BPKEY[b].press(false);  // tell the button it is NOT pressed
    }
  }
  /* check on Blood_Suger_Glucose keypad to enter the value*/
  for (uint8_t b = 0; b < 15; b++) 
  {
    if (pressed && BSGKEY[b].contains(touch_X, touch_Y)) 
    {
      BSGKEY[b].press(true);  // tell the button it is pressed
    } else {
      BSGKEY[b].press(false);  // tell the button it is NOT pressed
    }
  }
  /* check on Password Keypad keys */
  for (uint8_t b = 0; b < 15; b++) 
  {
    if (pressed && PassKey[b].contains(touch_X, touch_Y)) 
    {
      PassKey[b].press(true);  // tell the button it is pressed
    } else {
      PassKey[b].press(false);  // tell the button it is NOT pressed
    }
  }
  /* check on ID Keypad keys  */
  for (uint8_t b = 0; b < 15; b++) 
  {
    if (pressed && IdKey[b].contains(touch_X, touch_Y)) 
    {
      IdKey[b].press(true); // tell the button it is pressed
    } 
    else 
    {
      IdKey[b].press(false); // tell the button it is NOT pressed
    }
  }
   /* check on watch code in tha web application Keypad keys  */
  for (uint8_t b = 0; b < 15; b++) 
  {
    if (pressed && CodeKey[b].contains(touch_X, touch_Y)) 
    {
      CodeKey[b].press(true); // tell the button it is pressed
    } 
    else 
    {
      CodeKey[b].press(false); // tell the button it is NOT pressed
    }
  }
  /* check on SSID Keyboard keys  */
  for (uint8_t b = 0; b < 50; b++) 
  {
    if (pressed && keyboard_SSID[b].contains(touch_X, touch_Y)) 
    {
      keyboard_SSID[b].press(true);  // tell the button it is pressed
    } 
    else 
    {
      keyboard_SSID[b].press(false);  // tell the button it is NOT pressed
    }
  }
  /* check on Password Keyboard keys  */
  for (uint8_t b = 0; b < 50; b++) 
  {
    if (pressed && keyboard_PASSWORD[b].contains(touch_X, touch_Y)) 
    {
      keyboard_PASSWORD[b].press(true);  // tell the button it is pressed
    } 
    else 
    {
      keyboard_PASSWORD[b].press(false);  // tell the button it is NOT pressed
    }
  }
/************************************************************************************************************************/
/********************************************Normal Buttons in pages Check***********************************************/
/* id Check button exist in the first page in begining of system */
  if (pressed && ID.contains(touch_X, touch_Y)) 
  {
    ID.press(true); // tell the button it is pressed
  } 
  else 
  {
    ID.press(false); // tell the button it is NOT pressed
  }
  if (ID.justReleased()) 
  {
    ID.drawButton(); 
    IdKeypad_Init(); // Go to national Id keypad
  }
  if (ID.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK); // fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* Watch code check button exist in the connection page */
  if (pressed && CODE.contains(touch_X, touch_Y)) 
  {
    CODE.press(true); // tell the button it is pressed
  } 
  else 
  {
    CODE.press(false); // tell the button it is NOT pressed
  }
  if (CODE.justReleased()) 
  {
    CODE.drawButton();
    CodeKeypad_Init(); // Go to watch code in web keypad
  }
  if (CODE.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK); // fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* WIFI check button exist in the connection page */
  if (pressed && WIFI.contains(touch_X, touch_Y))
  {
    WIFI.press(true); // tell the button it is pressed
  } 
  else 
  {
    WIFI.press(false); // tell the button it is NOT pressed
  }
  if (WIFI.justReleased()) 
  {
    WIFI.drawButton();
    /* Scan the wifi exist */
    SSID_Keyboard_Init();
  }
  if (WIFI.justPressed()) 
  {
    btn_connection_type = WIFI_connect;
    tft.fillScreen(TFT_BLACK); // fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
    wifi_scan();
  }
/******************************************************************/ 
/* SIM check button exist in the connection page " don't make it yet "*/
  if (pressed && SIM.contains(touch_X, touch_Y))
  {
    SIM.press(true); // tell the button it is pressed
  } 
  else 
  {
    SIM.press(false); // tell the button it is NOT pressed
  }
  if (SIM.justReleased()) 
  {
    SIM.drawButton();
    /* Scan the wifi exist */
    SIM_INIT();
    EnterID_Page();
  }
  if (SIM.justPressed()) 
  {
    btn_connection_type = SIM_connect;
    tft.fillScreen(TFT_BLACK); // fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
    ///////////////////////////////////////////////////////////////////////////////////////////////////
  }
/******************************************************************/
/* enter check button exist in the setup page go to password page */
  if (pressed && SETUP.contains(touch_X, touch_Y))
  {
    SETUP.press(true); // tell the button it is pressed
  } 
  else 
  {
    SETUP.press(false); // tell the button it is NOT pressed
  }
  if (SETUP.justReleased()) 
  {
    SETUP.drawButton();
    Password_Page(); // go to password page
  }
  if (SETUP.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* password button check exist in the password page */
  if (pressed && PASS.contains(touch_X, touch_Y)) 
  {
    PASS.press(true); // tell the button it is pressed
  } 
  else 
  {
    PASS.press(false); // tell the button it is NOT pressed
  }
  if (PASS.justReleased()) 
  {
    PASS.drawButton();
    PassKeypad_Init(); //go to page of keypad of password
  }
  if (PASS.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }

/******************************************************************/
/* back button from password page to setup page check */
  if (pressed && Ba_Pass.contains(touch_X, touch_Y)) 
  {
    Ba_Pass.press(true); // tell the button it is pressed
  } 
  else 
  {
    Ba_Pass.press(false); // tell the button it is NOT pressed
  }
  if (Ba_Pass.justReleased()) 
  {
    Ba_Pass.drawButton();
    Setup_Page (); // go to setup page 
  }
  if (Ba_Pass.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* back button from info page to main page check */
  if (pressed && PINFO.contains(touch_X, touch_Y)) 
  {
    PINFO.press(true); // tell the button it is pressed
  } 
  else 
  {
    PINFO.press(false); // tell the button it is NOT pressed
  }
  if (PINFO.justReleased()) 
  {
    PINFO.drawButton();
    exit_from_measure = 0; // make that variable is false to still in the nested loop in the main page
    Main_Page(); // go to main page
  }
  if (PINFO.justPressed()) 
  {
    tft.fillScreen(Black);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* reset button check "reset the system"*/
  if (pressed && RESET.contains(touch_X, touch_Y)) 
  {
    RESET.press(true); // tell the button it is pressed
  } 
  else 
  {
    RESET.press(false); // tell the button it is NOT pressed
  }
  if (RESET.justReleased()) 
  {
    RESET.drawButton();
    Reset_Page(); // go to reset page
  }
  if (RESET.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* cancel reset button check "cancel reset the system"*/
  if (pressed && CANC.contains(touch_X, touch_Y)) 
  {
    CANC.press(true); // tell the button it is pressed
  } 
  else 
  {
    CANC.press(false); // tell the button it is NOT pressed
  }
  if (CANC.justReleased()) 
  {
    CANC.drawButton();
    INFO_Page(); // back to info page
  }
  if (CANC.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* accept reset button check "yes reset the system"*/
  if (pressed && YES.contains(touch_X, touch_Y)) 
  {
    YES.press(true); // tell the button it is pressed
  } 
  else 
  {
    YES.press(false); // tell the button it is NOT pressed
  }
  if (YES.justReleased()) 
  {
    YES.drawButton();
  }
  if (YES.justPressed()) 
  {
    ESP.restart(); // restart the system
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/*----------------------------------------------------Alarm_Entry page-----------------------------------------------*/
/* entry button check exist in Alarm_Entry_page */
  if (pressed && ENTERY.contains(touch_X, touch_Y)) 
  {
    ENTERY.press(true); // tell the button it is pressed
  } 
  else 
  {
    ENTERY.press(false); // tell the button it is NOT pressed
  }
  if (ENTERY.justReleased()) 
  {
    ENTERY.drawButton();
    ENTERY_Page(); //go to entry page
  }
  if (ENTERY.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }

/******************************************************************/
/* clock button check exist in Alarm_Entry_page */
  if (pressed && CLOCK.contains(touch_X, touch_Y)) 
  {
    CLOCK.press(true); // tell the button it is pressed
  } 
  else 
  {
    CLOCK.press(false); // tell the button it is NOT pressed
  }
  if (CLOCK.justReleased()) 
  {
    CLOCK.drawButton();
    Alarm_Page(); // go to alarm page to add or edit or delete specific alarm
  }
  if (CLOCK.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* back button check exist in Alarm_Entry_page */
  if (pressed && AE.contains(touch_X, touch_Y)) 
  {
    AE.press(true); // tell the button it is pressed
  } 
  else 
  {
    AE.press(false); // tell the button it is NOT pressed 
  }
  if (AE.justReleased()) 
  {
    AE.drawButton();
    exit_from_measure = 0; // make that variable is false to still in the nested loop in the main page
    Main_Page (); // back to main page
  }
  if (AE.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/*------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------Alarm page--------------------------------------------------*/
/* Press on ADD button exist in alarm page to go to keypad of alarm */
  if (pressed && ADD.contains(touch_X, touch_Y)) 
  {
    ADD.press(true); // tell the button it is pressed
  } 
  else 
  {
    ADD.press(false); // tell the button it is NOT pressed 
  }
  if (ADD.justReleased()) 
  {
    ADD.drawButton();
    AKeypad_Init(); // alarm keypad page to set alarm
  }
  if (ADD.justPressed()) 
  {
    currentState = TIME_PAGE;
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* Press on Back button exist in alarm page to go Alarm_Entry page */
  if (pressed && ABACK.contains(touch_X, touch_Y)) 
  {
    ABACK.press(true); // tell the button it is pressed
  } 
  else 
  {
    ABACK.press(false); // tell the button it is NOT pressed 
  }
  if (ABACK.justReleased()) 
  {
    ABACK.drawButton();
    AE_Page(); // Navigate to Alarm_Entry page
  }
  if (ABACK.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* Check touch events for edit and delete buttons */
  for (int i = 0; i < numAlarms; i++) 
  {
    if (pressed && EDIT[i].contains(touch_X, touch_Y)) 
    {
      EDIT[i].press(true);
    } 
    else 
    {
      EDIT[i].press(false);
    }

    if (pressed && DEL[i].contains(touch_X, touch_Y)) 
    {
      DEL[i].press(true);
    } 
    else 
    {
      DEL[i].press(false);
    }
  }
  // Handle edit and delete button presses
  for (int i = 0; i < numAlarms; i++) 
  {
    // Check if Edit button is pressed
    if (EDIT[i].justReleased()) 
    {
      EDIT[i].drawButton();
      AKeypad_Init();
    }
    if (EDIT[i].justPressed()) 
    {
      // Handle edit action (you can implement this)
      Serial.println("Edit button pressed for Alarm " + String(i + 1));
      editAlarmIndex = i;
      currentState = EDIT_PAGE;
    }

    // Check if Delete button is pressed
    if (DEL[i].justReleased()) 
    {
      DEL[i].drawButton();
    }
    if (DEL[i].justPressed()) 
    {
      // Handle delete action
      deleteAlarm(i);
      Serial.println("Alarm " + String(i + 1) + " deleted");
      Alarm_Page();
      break;
    }

  }
  // Handle the loop based on the current state
  switch (currentState)
  {
    case TIME_PAGE:  AKeypad_Loop();     break;
    case EDIT_PAGE: handleEditKeypad();  break;
    case EXIT_PAGE: break;
    default: break;
  }
/******************************************************************/
/*------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------BP&BSG page-------------------------------------------------*/
/* Blood_pressure button check exist in "BP_BSG" Entry page */
  if (pressed && BP.contains(touch_X, touch_Y)) 
  {
    BP.press(true); // tell the button it is pressed
  } 
  else 
  {
    BP.press(false); // tell the button it is NOT pressed 
  }
  if (BP.justReleased()) 
  {
    BP.drawButton();
    BPKeypad_Init(); // Navigate to Blood_pressure keypad page
  }
  if (BP.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* Blood_Suger_Glocose button check exist in "BP_BSG" Entry page */
  if (pressed && BSG.contains(touch_X, touch_Y)) 
  {
    BSG.press(true); // tell the button it is pressed
  } 
  else 
  {
    BSG.press(false); // tell the button it is NOT pressed 
  }
  if (BSG.justReleased()) 
  {
    BSG.drawButton();
    BSGKeypad_Init(); // Navigate to Blood_Suger_Glocose keypad page
  }
  if (BSG.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/* back button check exist in "BP_BSG" Entry page */
  if (pressed && Ba_EN.contains(touch_X, touch_Y)) 
  {
    Ba_EN.press(true); // tell the button it is pressed
  } 
  else 
  {
    Ba_EN.press(false); // tell the button it is NOT pressed 
  }
  if (Ba_EN.justReleased()) 
  {
    Ba_EN.drawButton();
    AE_Page(); // Navigate to Alarm_Entry_page
  }
  if (Ba_EN.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }
/******************************************************************/
/*------------------------------------------------------------------------------------------------------------------*/
/******************************************************************/
/* cancel alarm button check if alarm come*/
  if (pressed && CANCALA.contains(touch_X, touch_Y))
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
    Setup_Page();
  }
  if (CANCALA.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);// fill the scree black color 
    Delete_All_Buttons(); // delete all buttons in the previous page
  }

/******************************************************************/
/************************************************************************************************************************/
// Press on Back button in page of measure
  // if (pressed && BaHSTBu.contains(touch_X, touch_Y)) 
  // {
  //   BaHSTBu.press(true);
  // } 
  // else 
  // {
  //   BaHSTBu.press(false);
  // }
  // if (BaHSTBu.justReleased()) 
  // {
  //   BaHSTBu.drawButton();
  //   Main_Page();
  // }
  // if (BaHSTBu.justPressed()) 
  // {
  //   tft.fillScreen(TFT_BLACK);// fill the scree black color 
  //   Delete_All_Buttons(); // delete all buttons in the previous page
  // }

/******************************************************************/
/* Loops of Keypads */
  IdNum      = IdKeypad_Loop();       // loop of Id keypad
  watchCode  = CodeKeypad_Loop();     // loop of watch code of web keypad
  PassKeypad_Loop();                  // loop of Password keypad
  BSG_Result = BSGKeypad_Loop();      // loop of blood suger glocose keypad
  BP_Result  = BPKeypad_Loop();       // loop of blood pressure keypad
  ssid = SSID_Keyboard_Loop();
  PASSWORD_Keyboard_Loop();
/******************************************************************/
/* when alarm is come execute that function */
  alarm_action();
/****************************************************************/
/* Send data section under test**********************************/
  // Send_Data();
  // if ((millis() - lastTime) > timerDelay) 
  // {
  //     sendState = SEND_STATE_WEB_API; 
  //     lastTime = millis();
  // }

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
  
  /* Display time in all pages */
  printLocalTime();
/****************************************************************/
 
}
