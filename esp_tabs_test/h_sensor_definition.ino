/***************************************** CONNECTION CHECK IN SETUP ******************************************/
/*
  ******************************************************************
  FUNCTION NAME: max30102_check
  ARGUMENTS:     VOID
  RETURNS:       VOID
  DESCRIPTION:   USE TO CHECK MAX30102 CONNECTION.
  ******************************************************************
*/
void max30102_check(void)
{
  /* Loop until MAX30102 initializes successfully */
  while (false == MAX30102.begin()) 
  {
    Serial.println("MAX30102 init fail!");
    delay(1000); /* Delay before retrying initialization */
  }
  Serial.println("MAX30102 init success!");
  /* Start collecting sensor data */
  MAX30102.sensorStartCollect(); 
}

/*
  ******************************************************************
  FUNCTION NAME: mlx90614_check
  ARGUMENTS:     VOID
  RETURNS:       VOID
  DESCRIPTION:   USE TO CHECK MLX90614 CONNECTION.
  ******************************************************************
*/
void mlx90614_check(void)
{
  /* If MLX90614 initialization fails, halt the program */
  if (!mlx.begin()) 
  {
    Serial.println("MLX90614 init fail!");
    while (1) ; /* Infinite loop to halt the program */
  }
  Serial.println("MLX90614 init success!");
}
/***************************************************************************************************************/
/******************************************** MEASUREMENT IN LOOP **********************************************/
/*
  ******************************************************************
  FUNCTION NAME: max30102_HR_SPO2
  ARGUMENTS:     VOID
  RETURNS:       VOID
  DESCRIPTION:   USE TO MEASURE HEART RATE AND SPO2 USING MAX30102.
  ******************************************************************
*/
void max30102_HR_SPO2(void)
{
  /* Print heart rate and SPO2 readings on the TFT display */
  tft.setTextColor(White);
  tft.setCursor(50,  140);
  /* Get heart rate and SPO2 readings from MAX30102 */
  MAX30102.getHeartbeatSPO2(); 
  tft.print("HR      | ");
  HR_BEFORE_CAL = MAX30102._sHeartbeatSPO2.Heartbeat;
  Serial.println(HR_BEFORE_CAL);
  if (HR_BEFORE_CAL >= 100)
  {
    HR_AFTER_CAL = HR_BEFORE_CAL * (0.8);
    Serial.println(HR_AFTER_CAL);
    tft.print(HR_AFTER_CAL);
  }
  else
  {
    HR_AFTER_CAL = HR_BEFORE_CAL ;
    tft.print(HR_AFTER_CAL);
  }
  tft.println(" bpm");
  tft.setCursor(50,  100);
  tft.print("SPO2 | ");
  tft.print(MAX30102._sHeartbeatSPO2.SPO2);
  tft.println(" %");
}
/*
  ******************************************************************
  FUNCTION NAME: mlx90614_TEMP
  ARGUMENTS:     VOID
  RETURNS:       VOID
  DESCRIPTION:   USE TO MEASURE TEMPERATURE USING MLX90614.
  ******************************************************************
*/
void mlx90614_TEMP(void)
{
  /* Print temperature reading on the TFT display */
  tft.setTextColor(White);
  tft.setCursor(50,  180);
  tft.print("TEMP | ");
  tft.print(mlx.readObjectTempC());
  tft.print(" C");
  tft.println();
}
/*********************************************************************************************************/
/************************************************** DEBUG ************************************************/
/*
  ******************************************************************
  FUNCTION NAME: Debug
  ARGUMENTS:     VOID
  RETURNS:       VOID
  DESCRIPTION:   USE TO PRINT SENSOR READINGS FOR DEBUGGING.
  ******************************************************************
*/
void Debug(void)
{
  /* Print heart rate, SPO2, and temperature readings on the serial monitor */
  MAX30102.getHeartbeatSPO2(); /* Get heart rate and SPO2 readings from MAX30102 */
  Serial.println(MAX30102._sHeartbeatSPO2.Heartbeat);
  Serial.println(MAX30102._sHeartbeatSPO2.SPO2);
  Serial.println(mlx.readObjectTempC()); /* Get temperature reading from MLX90614 */
  Serial.println("=====================");
}
/*********************************************************************************************************/
