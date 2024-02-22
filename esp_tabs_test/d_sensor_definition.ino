/********************************************* CONNECTION CHECK *************************************************/

// check MAX30102 connection
void max30102_check(void)
{
  while (false == MAX30102.begin()) 
  {
    Serial.println("MAX30102 init fail!");
    delay(1000);
  }
  Serial.println("MAX30102 init success!");
  MAX30102.sensorStartCollect();
}


// check MLX90614 connection
void mlx90614_check(void)
{
  if (!mlx.begin()) 
  {
    Serial.println("MLX90614 init fail!");
    while (1) ;
  }
  Serial.println("MLX90614 init success!");
}

/***************************************************************************************************************/


/************************************************** MEASURMENT ************************************************/

// heart rate measue using MAX30102
void max30102_HR(void)
{
  tft.setCursor(10,  100);
  tft.print("HR      | ");
  tft.print(MAX30102._sHeartbeatSPO2.Heartbeat);
  tft.println(" bpm");
}

// SPO2 measue using MAX30102
void max30102_SPO2(void)
{
  tft.setCursor(10,  60);
  MAX30102.getHeartbeatSPO2();
  tft.print("SPO2 | ");
  tft.print(MAX30102._sHeartbeatSPO2.SPO2);
  tft.println(" %");
}

//TEMP measure using MLX90614
void mlx90614_TEMP(void)
{
  tft.setCursor(10,  140);
  tft.print("TEMP | ");
  tft.print(mlx.readObjectTempC());
  tft.print(" C");
  tft.println();
}

/***************************************************************************************************************/
