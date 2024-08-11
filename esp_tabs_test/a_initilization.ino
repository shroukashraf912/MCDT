/********************************* INITIALIZATION OF MAX30102 *********************************/
#define I2C_COMMUNICATION
#ifdef I2C_COMMUNICATION
#define I2C_ADDRESS 0x57
DFRobot_BloodOxygen_S_I2C MAX30102(&Wire, I2C_ADDRESS);
#endif
/*********************************************************************************************/


/************************************** INTIALIZATION MLX90614 *******************************/ 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
/*********************************************************************************************/


/************************************** INTIALIZATION NTP ************************************/ 
// const char* ntpServer1 = "pool.ntp.org";
// const char* ntpServer2 = "time.nist.gov";
// const long  gmtOffset_sec = 5400; /* 1.5 hours difference */
// const int   daylightOffset_sec = 5400;

// const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

/* 3- Initialization of DS3231 */
/* 3.1- define object */
RTC_DS3231 rtc;
/* 3.2- define days of the week */
char daysOfTheWeek[7][12] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

/*********************************************************************************************/
int exit_from_measure = 0;

/************************************** INTIALIZATION TFT_SPI *******************************/ 
/*
 * This is the file name used to store the calibration data.
 * You can change this to create new calibration files.
 * The SPIFFS file name must start with "/".
*/
#define CALIBRATION_FILE "/TouchCalData2"
/*
 * Set REPEAT_CAL to true instead of false to run calibration again, otherwise it will only be done once.
 * Repeat calibration if you change the screen rotation.
*/
#define REPEAT_CAL false
const int MAX_ALARMS = 4;
#define BUZZER_PIN 13 // Change this to the GPIO pin connected to the buzzer

TFT_eSPI tft = TFT_eSPI();
/* Invoke the TFT_eSPI button class and create all the button objects */
TFT_eSPI_Button BPKEY[15];     // keypad of blood pressure
TFT_eSPI_Button BSGKEY[15];    // keypad of bloof suger glucose
TFT_eSPI_Button Alarmkey[15];  // keypad of set alarm
TFT_eSPI_Button PassKey[15];   // keypad of enter password
TFT_eSPI_Button IdKey[15];     // keypad of Id
TFT_eSPI_Button CodeKey[15];     // keypad of watch Code in web
TFT_eSPI_Button EDIT[MAX_ALARMS]; // button of edit alarm  
TFT_eSPI_Button DEL[MAX_ALARMS];  // button of delete alarm
TFT_eSPI_Button BSG;           //Blood Suger Glucose
TFT_eSPI_Button BP;            // blood_pressure
TFT_eSPI_Button ADD;           // button of set alarm
TFT_eSPI_Button ABACK;         // previous button from alarm page
TFT_eSPI_Button TOTAL;         // button of measurements page
TFT_eSPI_Button CLOCK;         // button of Clock page
TFT_eSPI_Button LOCK;          // button lock the Main page
TFT_eSPI_Button Ba_EN;         // previous button from entry page
TFT_eSPI_Button BaHSTBu;       // previous button from measurements page
TFT_eSPI_Button ENTERY;        // button of entry page
TFT_eSPI_Button INFO;          // button of information page
TFT_eSPI_Button PINFO;         // previous button from information page
TFT_eSPI_Button RESET;         // button of reset esp
TFT_eSPI_Button PASS;          // button of enter the password
TFT_eSPI_Button YES;           // button to accept to make a restart for esp
TFT_eSPI_Button CANC;          // button to cancel a restart for esp
TFT_eSPI_Button SETUP;  
TFT_eSPI_Button CANCALA; 
TFT_eSPI_Button WIFI;
TFT_eSPI_Button SIM;
TFT_eSPI_Button ID;
TFT_eSPI_Button Ba_Pass;
TFT_eSPI_Button AE;
TFT_eSPI_Button CODE;
TFT_eSPI_Button keyboard_SSID[50];
TFT_eSPI_Button keyboard_PASSWORD[50];
/*********************************************************************************************/



// SIM card PIN (leave empty if not defined)
const char simPIN[] = "";

// Define APN for your cellular network provider
const char apn[] = "internet.vodafone.net";
const char gprsUser[] = "";
const char gprsPass[] = "";



// Initialize TinyGSM client
HardwareSerial SerialAT(2);
TinyGsm modem(SerialAT);
TinyGsmClient client(modem);