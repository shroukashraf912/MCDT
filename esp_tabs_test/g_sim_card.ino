void SIM_INIT()
{
  // Initialize serial communication with SIM800L
  SerialAT.begin(9600, SERIAL_8N1, 16, 17); // Adjust RX and TX pins as needed
  delay(3000);

  // Restart SIM800 module
  Serial.println("Initializing modem...");
  if (!modem.restart()) {
    Serial.println("Failed to restart modem");
    return;
  }
  delay(10000); // Wait for the module to fully initialize

  // Unlock SIM card if PIN is provided
  if (strlen(simPIN)) {
    modem.simUnlock(simPIN);
  }

  // Check signal quality
  int signalQuality = modem.getSignalQuality();
  Serial.print("Signal quality: ");
  Serial.println(signalQuality);

  // Connect to the cellular network
  Serial.print("Connecting to network...");
  if (!modem.waitForNetwork(180000)) { // wait up to 180 seconds
    Serial.println(" failed");
    return;
  }
  Serial.println(" connected");

  // Connect to GPRS
  Serial.print("Connecting to GPRS...");
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    Serial.println(" failed");
    return;
  }
  Serial.println(" connected");
}

void checkForTrigger_SIM() {
  Serial.println("Checking for trigger...");

  // Construct the complete URL
  String endpoint = "/api/Bands/FlagStatus?uniqueId=";
  String ServiceUrl = String("http://") + server + endpoint + watchCode;

  if (client.connect(server, port)) {
    Serial.println("Connected to server");

    // Make an HTTP GET request
    client.print(String("GET ") + ServiceUrl + " HTTP/1.1\r\n");
    client.print(String("Host: ") + server + "\r\n");
    client.print("Connection: close\r\n\r\n");

    // Read response from the server
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break;
      }
    }

    // Read the rest of the response
    String response = client.readString();
    Serial.print("Response: ");
    Serial.println(response);

    // Parse the JSON response
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
      return;
    }

    // Check if "data" field equals "True"
    const char* dataValue = doc["data"];
    if (strcmp(dataValue, "True") == 0) {
      Serial.println("Data is True. Performing some actions...");
      sendDataRequested_SIM = true; // Set flag to send data
    }
  } else {
    Serial.println("Failed to connect to server");
  }

  // Disconnect from the server
  client.stop();
  Serial.println("Disconnected from server");
}

void sendData_SIM() {
  Serial.println("Sending data to server...");
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

  // Construct JSON payload
  String webApiPayload = "{\"heartRate\":\"" + String(HR_AFTER_CAL) +
                         "\",\"oxygen\":\"" + String(SPO2Value) +
                         "\",\"temperature\":\"" + String(TEMPValue) +
                         "\",\"bloodPressure\":\"" + String(BPValue) +
                         "\",\"bloodSugar\":\"" + String(BSGValue) + "\"}";

  // Construct the complete URL
  String endpoint = "/api/Bands/BandCurrentState?uniqueId=";
  String webApiUrl_Data = String("http://") + server + endpoint + watchCode;

  if (client.connect(server, port)) {
    Serial.println("Connected to server");

    // Make an HTTP POST request
    client.print(String("POST ") + webApiUrl_Data + " HTTP/1.1\r\n");
    client.print(String("Host: ") + server + "\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Connection: close\r\n");
    client.print("Content-Length: ");
    client.print(webApiPayload.length());
    client.print("\r\n\r\n");
    client.print(webApiPayload);

    Serial.println("Request sent");

    // Read response from the server
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break;
      }
    }

    String response = client.readString();
    Serial.print("Response: ");
    Serial.println(response);
  } else {
    Serial.println("Failed to connect to server");
  }

  // Disconnect from the server
  client.stop();
  Serial.println("Disconnected from server");
}

void Send_ID_CODE_SIM() {
  Serial.println("Sending ID and Code to server...");

  // Construct JSON payload
  StaticJsonDocument<200> jsonPayload;
  jsonPayload["patientNationalId"] = IdNum;
  String requestBody;
  serializeJson(jsonPayload, requestBody);

  // Construct the complete URL
  String endpoint = "/api/Bands/ChangePatientFromBand?uniqueId=";
  String webApiUrl_Id_Code = String("http://") + server + endpoint + watchCode;

  if (client.connect(server, port)) {
    Serial.println("Connected to server");

    // Make an HTTP PUT request
    client.print(String("PUT ") + webApiUrl_Id_Code + " HTTP/1.1\r\n");
    client.print(String("Host: ") + server + "\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Connection: close\r\n");
    client.print("Content-Length: ");
    client.print(requestBody.length());
    client.print("\r\n\r\n");
    client.print(requestBody);

    Serial.println("Request sent");

    // Read response from the server
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break;
      }
    }

    String response = client.readString();
    Serial.print("Response: ");
    Serial.println(response);

    // Parse the JSON response
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
      return;
    }

    const char* name_id = doc["patientNationalId"];
    if (name_id) {
      Serial.print("Received name: ");
      Serial.println(name_id);
    } else {
      Serial.println("Name not found in response");
    }
  } else {
    Serial.println("Failed to connect to server");
  }

  // Disconnect from the server
  client.stop();
  Serial.println("Disconnected from server");
}
