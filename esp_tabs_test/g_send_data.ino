/********************************** Local Server ***************************/
void Send_Data(void)
{
  MAX30102.getHeartbeatSPO2();
  sensor1Value = MAX30102._sHeartbeatSPO2.SPO2;
  sensor2Value = MAX30102._sHeartbeatSPO2.Heartbeat;
  sensor3Value = MAX30102.getTemperature_C();

  if(WiFi.status() == WL_CONNECTED)
  {
      WiFiClient client;
      HTTPClient http;
    
      http.begin(client, serverName);
      
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Send HTTP POST request with sensor readings
      String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&value1=";
      httpRequestData += String(sensor1Value);
      httpRequestData += "&value2=";
      httpRequestData += String(sensor2Value);
      httpRequestData += "&value3=";
      httpRequestData += String(sensor3Value);
      
      int httpResponseCode = http.POST(httpRequestData);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      http.end();
    }
    else 
    {
      // TFT ====================================================
      Serial.println("WiFi Disconnected");
    }
}
