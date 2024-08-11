void setup()
{
  /* start serial monitor */
  Serial.begin(BAUD_RATE);
  /* Initialize the TFT screen */
  TFT_Init(); 
  /* Check if wifi connected or not if yes break the loop if no still in loop */
  // while (WiFi.status() != WL_CONNECTED);
  /* Make the pin of buzzer output */
  pinMode(BUZZER_PIN, OUTPUT);
  /* set the time */
  // time_setup();
  RTC_time_setup();
  /* clock alarm */
  alarm_setup();
  /* Setup of Heart rate and Oxygen Sensor */
  max30102_check();
  /* Setup of Temperature Sensor */
  mlx90614_check();
  /* Display time */
  // printLocalTime();
  /* Start the system */
  Connection_Page();
  /* print on serial when all setup done */
  Serial.println("Setup done");

  /* OTA "Over The Air" */
  WiFi.mode(WIFI_STA);
  /* Port defaults to 3232 */
  ArduinoOTA.setPort(3232);
  /* Hostname defaults to esp3232-[MAC] */
  ArduinoOTA.setHostname("myesp32");
  /* No authentication by default */
  ArduinoOTA.setPassword("admin");
  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
  
  /* Set up callbacks for OTA (Over-The-Air) updates */
  ArduinoOTA
      /* Callback triggered when OTA update starts */
      .onStart([]() 
      {
          String type;
          /* Check if the update is for the sketch or the filesystem */
          if (ArduinoOTA.getCommand() == U_FLASH)
              type = "sketch";
          else // U_SPIFFS
              type = "filesystem";

          /* Notify the start of the update process */
          Serial.println("Start updating " + type);
      })
      /* Callback triggered when OTA update ends */
      .onEnd([]() 
      {
          /* Notify the end of the update process */
          Serial.println("\nEnd");
      })
      /* Callback triggered during OTA update to report progress */
      .onProgress([](unsigned int progress, unsigned int total) 
      {
          /* Print progress percentage */
          Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      })
      /* Callback triggered if there's an error during OTA update */
      .onError([](ota_error_t error) 
      {
          /* Print error message based on error type */
          Serial.printf("Error[%u]: ", error);
          if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
          else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
          else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
          else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
          else if (error == OTA_END_ERROR) Serial.println("End Failed");
      });

  /* Begin OTA */
  ArduinoOTA.begin();

  /* Notify readiness for OTA updates */
  Serial.println("Ready");
  /* Print local IP address */
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}