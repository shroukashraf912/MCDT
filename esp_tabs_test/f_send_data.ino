
#define JASON

// enum SendType {
//   SEND_DATA_BY_WIFI,
//   SEND_DATA_BY_SIM
// };

// SendState sendState = SEND_STATE_IDLE;


////////////////////////////////////////////////////////////////////لسة هيتعدل عليه 
/**********************************************************/
  // void Send_Data(void)
  // {
  //   HRValue = MAX30102._sHeartbeatSPO2.Heartbeat;
  //   SPO2Value = MAX30102._sHeartbeatSPO2.SPO2;
  //   TEMPValue = mlx.readObjectTempC();
  //   switch (sendState) 
  //   {
  //     case SEND_STATE_IDLE:
  //       // Do nothing if not ready to send
  //       break;

  //     case SEND_STATE_WEB_API:
  //       if (WiFi.status() == WL_CONNECTED)
  //       {
  //         WiFiClient client0;
  //         HTTPClient http;
  //         /* Your server's IP address or hostname */
  //         String serverAddress = "http://15.0.0.8";
  //         /* Endpoint URL to fetch information */
  //         String endpoint = "/api/Doctors/ListOfSpecialization";//////////////////////////
  //         /* Construct the complete URL */
  //         String webApiUrl_Data = serverAddress + endpoint;
  //         // Send data to the web API

  //         String webApiPayload = "{\"heartRate\":\"" + String(HRValue) +
  //                                "\",\"oxygen\":\"" + String(SPO2Value) +
  //                                "\",\"temperature\":\"" + String(TEMPValue) +
  //                                "\",\"bloodPressure\":\"" + String(BPValue) +
  //                                "\",\"bloodSuger\":\"" + String(BSGValue) + "\"}";
  //         http.begin(client0, webApiUrl_Data);
  //         http.addHeader("Content-Type", "application/json");
  //         int webApiResponseCode = http.POST(webApiPayload);
  //         Serial.print("Web API HTTP Response code: ");
  //         Serial.println(webApiResponseCode);
  //         http.end();
  //       }
  //       else
  //       {
  //         // TFT ====================================================
  //         Serial.println("WiFi Disconnected");
  //       }
  //       sendState = SEND_STATE_IDLE; // Reset state to idle
  //       break;
  //   }
  // }
/**********************************************************/

/*
  ******************************************************************
  FUNCTION NAME: checkForTrigger
  ARGUMENTS:     VOID
  RETURNS:       VOID
  DESCRIPTION:   USE TO CHECK THE REQUEST FROM WEB APPLICATION 
                 TO GET VALUES OF SENSORS.

                 //http://197.132.143.30/api/Bands/FlagStatus?uniqueId=737368000
  ******************************************************************
*/
void checkForTrigger_WIFI(void) 
{
  // Define your server's IP address or hostname
  // String serverAddress = "http://197.132.143.30";
  // Endpoint URL to send data
  String endpoint = "/api/Bands/FlagStatus?uniqueId=";
  // Unique ID
  String uniqueId = watchCode;
  // Construct the complete URL
  // String ServiceUrl = serverAddress + endpoint + uniqueId;
  String ServiceUrl = String("http://") + server + endpoint + watchCode;

  if (http.begin(client0, ServiceUrl)) 
  {
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) 
    {
      Serial.print("service HTTP response code: ");
      Serial.println(httpResponseCode);
      
      // Check if the response indicates trigger
      if (httpResponseCode == 200) 
      {
        String payload = http.getString();
        Serial.println("Response: " + payload);
        // Parse JSON data
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error) 
        {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
          return;
        }

        // Check if "data" field equals "True"
        const char* dataValue = doc["data"];
        if (strcmp(dataValue, "True") == 0) 
        {
          // Perform some actions if data is "True"
          Serial.println("Data is True. Performing some actions...");
          // Action: Set a flag and call a function
          sendDataRequested_WIFI = true; // Set flag to send data
        }
      }
    } 
    else 
    {
      Serial.print("Error in HTTP GET request: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } 
  else 
  {
    Serial.println("Failed to connect to server.");
  }
}

/*
  ******************************************************************
  FUNCTION NAME: SendData
  ARGUMENTS:     VOID
  RETURNS:       VOID
  DESCRIPTION:   USE TO SEND THE SENSORS, BLOOD_SUGER AND BLOOD_PRESSURE  
                 WHEN WEB APPLICATION REQUEST THAT VALUES.

                 // http://197.132.143.30/api/Bands/BandCurrentState?uniqueId=737368000
  ******************************************************************
*/
void sendData_WIFI() 
{
  // Read sensor values
  HR_BEFORE_CAL = MAX30102._sHeartbeatSPO2.Heartbeat;
  if (HR_BEFORE_CAL >= 100)
  {
    HR_AFTER_CAL = HR_BEFORE_CAL * (0.8);
  }
  else
  {
    HR_AFTER_CAL = HR_BEFORE_CAL;
  }

  float SPO2Value = MAX30102._sHeartbeatSPO2.SPO2;
  float TEMPValue = mlx.readObjectTempC();
  char* BPValue = BP_Result; 
  char* BSGValue = BSG_Result;
  
  // int BPIntValue = atoi(BPValue); // Convert blood pressure to integer
  // int BSGIntValue = atoi(BSGValue); // Convert blood sugar to integer

  // Construct JSON payload
  String webApiPayload = "{\"heartRate\":\"" + String(HR_AFTER_CAL) +
                          "\",\"oxygen\":\"" + String(SPO2Value) +
                          "\",\"temperature\":\"" + String(TEMPValue) +
                          "\",\"bloodPressure\":\"" + String(BPValue) +
                          "\",\"bloodSugar\":\"" + String(BSGValue) + "\"}";

  // String webApiPayload = String("{"
  //                             "\"heartRate\":" + String(static_cast<int>(HRValue)) +
  //                             ",\"oxygen\":" + String(static_cast<int>(SPO2Value)) +
  //                             ",\"temperature\":" + String(static_cast<int>(TEMPValue)) +
  //                             ",\"bloodPressure\":" + String(static_cast<int>(BPIntValue)) +
  //                             ",\"bloodSugar\":" + String(static_cast<int>(BSGIntValue)) +
  //                             "}");

  // Send data to the web API
  if (WiFi.status() == WL_CONNECTED) 
  {
    // Define your server's IP address or hostname
    // String serverAddress = "http://197.132.143.30";
    // Endpoint URL to send data
    String endpoint = "/api/Bands/BandCurrentState?uniqueId=";
    // Unique ID
    String uniqueId = watchCode;
    // Construct the complete URL
    // String webApiUrl_Data = serverAddress + endpoint + uniqueId;
    String webApiUrl_Data = String("http://") + server + endpoint + watchCode;


    // Send data to the web API
    if (http.begin(client0, webApiUrl_Data)) 
    {
      http.addHeader("Content-Type", "application/json");
      int webApiResponseCode = http.POST(webApiPayload);
      Serial.print("Web API HTTP Response code: ");
      Serial.println(webApiResponseCode);
      http.end();
    } 
    else 
    {
      Serial.println("Failed to connect to server.");
    }
  } 
  else 
  {
    Serial.println("WiFi not connected.");
  }
}

/*
  ******************************************************************
  FUNCTION NAME: Send_ID_CODE
  ARGUMENTS:     VOID
  RETURNS:       VOID
  DESCRIPTION:   USE TO SEND THE NATIONAL ID AND THE CODE OF WATCH
                 IN WEB APPLICATION TO GET THE NAME OF PATIENT.

                 // http://197.132.143.30/api/Bands/ChangePatientFromBand?uniqueId=737368000
  ******************************************************************
*/
void Send_ID_CODE_WIFI(void) 
{
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi Disconnected");
    return;
  }

  WiFiClient client0;
  HTTPClient http;
  /* Your server's IP address or hostname */
  // String serverAddress = "http://197.132.143.30";
  /* Endpoint URL to fetch information */
  String endpoint = "/api/Bands/ChangePatientFromBand?uniqueId=";
  // Unique ID
  String uniqueId = watchCode;
  /* Construct the complete URL */
  // String webApiUrl_Id_Code = serverAddress + endpoint + uniqueId;
  String webApiUrl_Id_Code = String("http://") + server + endpoint + watchCode;


  http.begin(client0, webApiUrl_Id_Code);
  // Specify the HTTP method as PUT
  http.addHeader("Content-Type", "application/json");
 // Construct the JSON payload
  StaticJsonDocument<200> jsonPayload;
  jsonPayload["patientNationalId"] = IdNum;
  String requestBody;
  serializeJson(jsonPayload, requestBody);

  Serial.print("Request URL: ");
  Serial.println(webApiUrl_Id_Code);
  Serial.print("Request Body: ");
  Serial.println(requestBody);

  int httpResponseCode = http.PUT(requestBody); // Use PUT method
  Serial.print("Web API HTTP Response code: ");
  Serial.println(httpResponseCode);

  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();
    Serial.print("Response: ");
    Serial.println(response);
    
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
      return;
    }

    const char* name_ID = doc["patientNationalId"];
    if (name_ID) {
      Serial.print("Received name: ");
      Serial.println(name_ID);
      name_id = String(name_ID);
    } else {
      Serial.println("Name not found in response");
    }
  } else {
    Serial.print("Failed to get response from API, error: ");
    Serial.println(http.errorToString(httpResponseCode).c_str());
  }

  http.end();
}

/*
  ******************************************************************
  FUNCTION NAME: Send_Normalization
  ARGUMENTS:     VOID
  RETURNS:       VOID
  DESCRIPTION:   USE TO SEND TO WEB APPLICATION THAT EXIT PROBLEM 
                 IN A MEASURMENT OF SENSORS FOR A PATIENT BY  SEND 
                 isActive FOR NORMAL PATIENT AND isNotactive FOR 
                 NOT NORMAL .

                 // http://197.132.143.30/api/Bands/BandAlarm?uniqueId=737368000&bandAlarm=true
  ******************************************************************
*/

void Another_Function() {
  // Use the received name from the API response
  Serial.println("Name received from API: " + String(name_id));
}
