void setup()
{
  // start serial monitor
  Serial.begin(BAUD_RATE);
  // while (!Serial);
   pinMode(BUZZER_PIN, OUTPUT);
  // Initialize the TFT screen
  TFT_Init();
  // scan wifi
  wifi_scan();
  
  //connect to wifi
  // wifi_connect();  

  //set the time
  time_setup();

  //clock alarm 
  alarm_setup();

  // // setup sensors
  max30102_check();
  mlx90614_check();

  Serial.println("Setup done");
  IdKeypad_Init();
}