void loop() 
{
  uint16_t t_x = 0, t_y = 0;
  bool pressed = tft.getTouch(&t_x, &t_y);

    /* Press on Alarm keypad */
  for (uint8_t b = 0; b < 15; b++) 
  {
    if (pressed && Alarmkey[b].contains(t_x, t_y)) 
    {
      Alarmkey[b].press(true);
    } 
    else 
    {
      Alarmkey[b].press(false);
    }
  }
  // buttons of BSG and BP
  for (uint8_t b = 0; b < 15; b++) 
  {
    if (pressed && BPKEY[b].contains(t_x, t_y)) 
    {
      BPKEY[b].press(true);  // tell the button it is pressed
    } else {
      BPKEY[b].press(false);  // tell the button it is NOT pressed
    }
  }
  for (uint8_t b = 0; b < 15; b++) 
  {
    if (pressed && BSGKEY[b].contains(t_x, t_y)) 
    {
      BSGKEY[b].press(true);  // tell the button it is pressed
    } else {
      BSGKEY[b].press(false);  // tell the button it is NOT pressed
    }
  }
  for (uint8_t b = 0; b < 15; b++) 
  {
    if (pressed && PassKey[b].contains(t_x, t_y)) 
    {
      PassKey[b].press(true);  // tell the button it is pressed
    } else {
      PassKey[b].press(false);  // tell the button it is NOT pressed
    }
  }
  for (uint8_t b = 0; b < 15; b++) 
  {
    if (pressed && IdKey[b].contains(t_x, t_y)) 
    {
      IdKey[b].press(true);
    } 
    else 
    {
      IdKey[b].press(false);
    }
  }
  /******************************************************************/
  // Press on CLOCK button
  if (pressed && CLOCK.contains(t_x, t_y)) 
  {
    CLOCK.press(true);
  } 
  else 
  {
    CLOCK.press(false);
  }

  // Handle CLOCK button press
  if (CLOCK.justReleased()) 
  {
    CLOCK.drawButton();
    Alarm_Page(); // Navigate to Alarm page
  }

  if (CLOCK.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    TOTAL.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    ENTERY.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    INFO.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    CLOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    LOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  // Press on ADD button
  if (pressed && ADD.contains(t_x, t_y)) 
  {
    ADD.press(true);
  } 
  else 
  {
    ADD.press(false);
  }

  // Handle ADD button press
  if (ADD.justReleased()) 
  {
    ADD.drawButton();
    AKeypad_Init();
  }

  if (ADD.justPressed()) 
  {
    currentState = TIME_PAGE;
  }

  // Check touch events for edit and delete buttons
  for (int i = 0; i < numAlarms; i++) 
  {
    if (pressed && EDIT[i].contains(t_x, t_y)) 
    {
      EDIT[i].press(true);
    } 
    else 
    {
      EDIT[i].press(false);
    }

    if (pressed && DEL[i].contains(t_x, t_y)) 
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
  // Press on Back button
  if (pressed && ABACK.contains(t_x, t_y)) 
  {
    ABACK.press(true);
  } 
  else 
  {
    ABACK.press(false);
  }

  // Handle Back button press
  if (ABACK.justReleased()) 
  {
    ABACK.drawButton();
    Main_Page(); // Navigate to Measure page
  }
  if (ABACK.justPressed()) 
  {
    ADD.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    ABACK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    tft.fillScreen(TFT_BLACK);
  }

  /******************************************************************/
  if (pressed && BP.contains(t_x, t_y)) 
  {
    BP.press(true);
  } 
  else 
  {
    BP.press(false);
  }

  // Handle Back button press
  if (BP.justReleased()) 
  {
    BP.drawButton();
    BPKeypad_Init();// Navigate to Measure page
  }
  if (BP.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    BSG.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    BP.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    Ba_EN.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && BSG.contains(t_x, t_y)) 
  {
    BSG.press(true);
  } 
  else 
  {
    BSG.press(false);
  }

  // Handle Back button press
  if (BSG.justReleased()) 
  {
    BSG.drawButton();
    BSGKeypad_Init();// Navigate to Measure page 
  }
  if (BSG.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    BSG.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    BP.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    Ba_EN.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && TOTAL.contains(t_x, t_y)) 
  {
    TOTAL.press(true);
  } 
  else 
  {
    TOTAL.press(false);
  }
  // Handle Back button press
  if (TOTAL.justReleased()) 
  {
    TOTAL.drawButton();
      HSTGP_Page(); // Stay in HSTGP_Page until BaHSTBu is released
  }
  if (TOTAL.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    TOTAL.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    ENTERY.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    INFO.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    CLOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    LOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  // Press on Back button
  if (pressed && BaHSTBu.contains(t_x, t_y)) 
  {
    BaHSTBu.press(true);
  } 
  else 
  {
    BaHSTBu.press(false);
  }

  // Handle BaHSTBu button press
  if (BaHSTBu.justReleased()) 
  {
    BaHSTBu.drawButton(); // Navigate to Measure page
    Main_Page();
  }

  if (BaHSTBu.justPressed()) 
  {
    BaHSTBu.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    tft.fillScreen(TFT_BLACK);
  }

  /******************************************************************/
  if (pressed && ENTERY.contains(t_x, t_y)) 
  {
    ENTERY.press(true);
  } 
  else 
  {
    ENTERY.press(false);
  }

  // Handle Back button press
  if (ENTERY.justReleased()) 
  {
    ENTERY.drawButton();
    ENTERY_Page();
  }
  if (ENTERY.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    TOTAL.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    ENTERY.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    INFO.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    CLOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    LOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && Ba_EN.contains(t_x, t_y)) 
  {
    Ba_EN.press(true);
  } 
  else 
  {
    Ba_EN.press(false);
  }

  // Handle Back button press
  if (Ba_EN.justReleased()) 
  {
    Ba_EN.drawButton();
    Main_Page();
  }
  if (Ba_EN.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    BSG.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    BP.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    Ba_EN.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && INFO.contains(t_x, t_y)) 
  {
    INFO.press(true);
  } 
  else 
  {
    INFO.press(false);
  }

  // Handle Back button press
  if (INFO.justReleased()) 
  {
    INFO.drawButton();
    INFO_Page();
  }
  if (INFO.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    TOTAL.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    ENTERY.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    INFO.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    CLOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    LOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && RESET.contains(t_x, t_y)) 
  {
    RESET.press(true);
  } 
  else 
  {
    RESET.press(false);
  }
  if (RESET.justReleased()) 
  {
    RESET.drawButton();
    Reset_Page();
  }
  if (RESET.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    RESET.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    PINFO.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && PINFO.contains(t_x, t_y)) 
  {
    PINFO.press(true);
  } 
  else 
  {
    PINFO.press(false);
  }
  // Handle Back button press
  if (PINFO.justReleased()) 
  {
    PINFO.drawButton();
    Main_Page();
  }
  if (PINFO.justPressed()) 
  {
    tft.fillScreen(Black);
    RESET.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    PINFO.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && LOCK.contains(t_x, t_y)) 
  {
    LOCK.press(true);
  } 
  else 
  {
    LOCK.press(false);
  }

  // Handle Back button press
  if (LOCK.justReleased()) 
  {
    LOCK.drawButton();
    Setup_Page();
  }
  if (LOCK.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    TOTAL.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    ENTERY.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    INFO.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    CLOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    LOCK.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && PASS.contains(t_x, t_y)) 
  {
    PASS.press(true);
  } 
  else 
  {
    PASS.press(false);
  }
  if (PASS.justReleased()) 
  {
    PASS.drawButton();
    PassKeypad_Init();// Navigate to Measure page 
  }
  if (PASS.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    PASS.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && CANC.contains(t_x, t_y)) 
  {
    CANC.press(true);
  } 
  else 
  {
    CANC.press(false);
  }
  if (CANC.justReleased()) 
  {
    CANC.drawButton();
    INFO_Page();
  }
  if (CANC.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    YES.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    CANC.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && YES.contains(t_x, t_y)) 
  {
    YES.press(true);
  } 
  else 
  {
    YES.press(false);
  }
  if (YES.justReleased()) 
  {
    YES.drawButton();
  }
  if (YES.justPressed()) 
  {
    ESP.restart();
    tft.fillScreen(TFT_BLACK);
    YES.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    CANC.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  
  /******************************************************************/
  if (pressed && SETUP.contains(t_x, t_y))
  {
    SETUP.press(true);
  } 
  else 
  {
    SETUP.press(false);
  }
  if (SETUP.justReleased()) 
  {
    SETUP.drawButton();
    Password_Page();
  }
  if (SETUP.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    SETUP.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && CANCALA.contains(t_x, t_y))
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
    tft.fillScreen(TFT_BLACK);
    CANCALA.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  if (pressed && WIFI.contains(t_x, t_y))
  {
    WIFI.press(true);
  } 
  else 
  {
    WIFI.press(false);
  }
  if (WIFI.justReleased()) 
  {
    WIFI.drawButton();
    wifi_connect();  
    Setup_Page();
  }
  if (WIFI.justPressed()) 
  {
    tft.fillScreen(TFT_BLACK);
    WIFI.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
    SIM.initButton(&tft, 0, 0, 0, 0, TFT_BLACK, TFT_BLACK, TFT_BLACK, "", 0);
  }
  /******************************************************************/
  BP_Page();
  BSG_Page();
  PassKeypad_Loop();
  IdNum = IdKeypad_Loop();
  alarm_action();

    
// Send data section under test ************************************

  if ((millis() - lastTime) > timerDelay) 
  {
      Send_Data();
      lastTime = millis();
  }
 /****************************************************************/
  // Debug();
  MAX30102.getHeartbeatSPO2();
  mlx.readObjectTempC();
}
