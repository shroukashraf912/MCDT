#define BAUD_RATE 115200

int HR_BEFORE_CAL = 0;
int HR_AFTER_CAL = 0;
/***************************************** Global Variables ***********************************************/
/*********************************** WIFI **************************************/
char* ssid = NULL;
char* password = NULL;
/*******************************************************************************/
/********** STORE VALUES OF BLOOD_SUGER_GLOCOSE AND BLOOD_PRESSURE *************/
char* BSG_Result = NULL;
char* BP_Result = NULL;
/*******************************************************************************/
// /****************************** SERVER *****************************************/
// const char* serverName = "http://192.168.1.4";
// /* Define your cloud service's API endpoint URL of request data */
// const char* cloudServiceUrl = "http://192.168.1.4/trigger"; // web API of check request data

WiFiClient client0;
HTTPClient http;

/* Flag to indicate if data should be sent */
bool sendDataRequested_WIFI = false;
bool sendDataRequested_SIM = false;
enum SendState {
    WIFI_connect,
    SIM_connect
};

SendState btn_connection_type;
// Cloud server details
const char server[] = "197.132.143.30"; // Server IP
const int port = 80; // HTTP port

/* value to be sent */
// float HRValue = 0;
// float SPO2Value = 0;
// float TEMPValue = 0;
// char* BPValue = BP_Result;
// char* BSGValue = BSG_Result;


char* IdNum = NULL;
char* watchCode = NULL; // Global variable to hold watch code
String name_id = ""; // Global variable to hold the received name
/******************************************************************************/
/******************************* Time delay ***********************************/
/* FOR SEND DATA THAT DELAY EXIST IN MAIN LOOP */
unsigned long lastTime = 0;
unsigned long timerDelay = 600000; // Timer set to 10 minutes (600000)

/* FOR MEASUREMENT DATA THAT DELAY EXIST IN MAIN_PAGE FUNCTION*/
unsigned long lastTime_main = 0;
unsigned long timerDelay_main = 5000; // Set timer to 5 seconds (5000)

unsigned long prevtime_T1 = 0;
long interval_T1 = 2000; // Timer set to 2 seconds (1000)

/* FOR TIME AND DATE */
unsigned long prevtime_T2 = 0;
long interval_T2 = 1000; // Timer set to 1 second (1000)

/* FOR BATTERY */
unsigned long prevtime_T3 = 0;
long interval_T3 = 600000; // Timer set to 10 minutes (600000)
/******************************************************************************/
/************************** Status of Nested loop *****************************/
enum Enter_Page 
{
  still_in_main,
  set_up,
  Alarm_Entry,
  Info
};
Enter_Page enter_page = still_in_main;
int check_on_alarm = 0;
/******************************************************************************/
/********************************* TFT ****************************************/
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 60
#define Blue 0x09F0
#define White TFT_WHITE
#define Black TFT_BLACK
#define Send_C 0x32D4
#define New_C  0x53D7
#define HM_C 0x74BB
uint16_t tft_width = 480, tft_height = 320;
/******************************************************************************/
/*----------------------------- KEYPADS -------------------------------------*/

// Keypad start position, key sizes and spacing
#define KEY_X 80  // Centre of key
#define KEY_Y 80
#define KEY_W 142  // Width and height
#define KEY_H 40
#define KEY_SPACING_X 18  // X and Y gap
#define KEY_SPACING_Y 13
#define KEY_TEXTSIZE 1  // Font size multiplier

// Using two fonts since numbers are nice when bold
#define LABEL1_FONT &FreeSansOblique12pt7b  // Key label font 1
#define LABEL2_FONT &FreeSansBold12pt7b     // Key label font 2

// Numeric display box size and location
#define DISP_X 10
#define DISP_Y 2
#define DISP_W 460
#define DISP_H 50
#define DISP_TSIZE 1
#define DISP_TCOLOR TFT_WHITE

// lengths of Keypad
#define ROW_OF_KEYPAD 5
#define COL_OF_KEYPAD 3
/******************************************************************************/
/****************Glucose and pressure keypad configurations*******************/
// Number length, buffer for storing it, and character index
#define NUM_LEN 12
char numberBuffer[NUM_LEN + 1] = "";
uint8_t numberIndex = 0;

#define NUM_LEN_G 12
char numberBufferG[NUM_LEN + 1] = "";
uint8_t numberIndexG = 0;

// Declaration of keyColor and keyLabel
char keyLabel[15][5] = { "1" ,     "2",    "3",
                         "4" ,     "5",    "6", 
                         "7" ,     "8",    "9", 
                         "/" ,     "0",  "Del",
                         "Clr", "Send", "Back"
                        };
uint16_t keyColor[15] = {TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_DARKGREY,
                         New_C, Send_C, Blue
                        };
char keyLabelBSG[15][5] = { "1" ,     "2",    "3",
                            "4" ,     "5",    "6", 
                            "7" ,     "8",    "9", 
                            "." ,     "0",  "Del",
                            "Clr", "Send", "Back"
                          };  
/*******************************************************************************/
/**************************Alarm keypad configurations**************************/
#define A_NUM_LEN 2
char A_numberBuffer[A_NUM_LEN + 1] = "";
uint8_t A_numberIndex = 0;

// const int MAX_ALARMS = 4;
struct Alarm {
  int hour;
  int minute;
};
Alarm alarms[MAX_ALARMS];
int numAlarms = 0;

char AkeyLabel[15][5] = { "1", "2", "3",
                          "4", "5", "6",
                          "7", "8", "9",
                          "0", "Hour", "Min",
                          "Del", "Set", "Back"};

uint16_t AkeyColor[15] = {TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, HM_C, HM_C,
                         TFT_DARKGREY, Send_C, Blue};

int alarmHour = 0;     // Alarm hour (24-hour format)
int alarmMinute = 0;   // Alarm minute

/* Add a state variable for edit mode */
enum State {
  TIME_PAGE,
  EDIT_PAGE,
  EXIT_PAGE
};
State currentState = EXIT_PAGE;  // Initial page
int editAlarmIndex = -1; // Index of the alarm being edited, -1 means no alarm is being edited
/******************************************************************************/
/************************Password keypad configurations************************/
#define PASS_LEN 6
char PassBuffer[PASS_LEN + 1] = "";
uint8_t PassIndex = 0;


// Declaration of keyColor and keyLabel
char PassLabel[15][5] = { "1" ,     "2",    "3",
                          "4" ,     "5",    "6", 
                          "7" ,     "8",    "9", 
                          "." ,     "0",  "Del",
                          "Clr", "Ent", "Back"  
                        };

uint16_t PassColor[15] = {TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_DARKGREY,
                         New_C, Send_C, Blue
                        };
/******************************************************************************/
/***************************ID keypad configurations***************************/
#define ID_LEN 14
char IdBuffer[ID_LEN + 1] = "";
uint8_t IdIndex = 0;


// Declaration of keyColor and keyLabel
char IdLabel[15][5] = { "1" ,     "2",    "3",
                         "4" ,     "5",    "6", 
                         "7" ,     "8",    "9", 
                         "." ,     "0",  "Del",
                         "Clr", "Ent", "Back"  };

uint16_t IdColor[15] = { TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_DARKGREY,
                             New_C,    Send_C, Blue
                        };
/******************************************************************************/
/************************Code keypad configurations****************************/
#define CODE_LEN 9
char CodeBuffer[CODE_LEN + 1] = "";
uint8_t CodeIndex = 0;


// Declaration of keyColor and keyLabel
char CodeLabel[15][5] = { "1" ,     "2",    "3",
                         "4" ,     "5",    "6", 
                         "7" ,     "8",    "9", 
                         "." ,     "0",  "Del",
                         "Clr", "Ent", "Back"  };

uint16_t CodeColor[15] = { TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_DARKGREY,
                             New_C,    Send_C, Blue
                        };
/******************************************************************************/
/*--------------------------------END OF KEYPADS------------------------------*/
/******************************************************************************/
/*----------------------------- KEYBOARDS ------------------------------------*/

// Keyboard keyboard_SSID sizes and spacing
#define KEY_X_KB 35  // Centre of keyboard_SSID
#define KEY_Y_KB 90
#define KEY_W_KB 40  // Width and height
#define KEY_H_KB 40
#define KEY_SPACING_X_KB 5  // X and Y gap
#define KEY_SPACING_Y_KB 5
#define KEY_TEXTSIZE 1  // Font size multiplier

// Display box size and location
#define DISP_X_KB 10
#define DISP_Y_KB 2
#define DISP_W_KB 460
#define DISP_H_KB 50
#define DISP_TSIZE_KB 1
#define DISP_TCOLOR_KB TFT_WHITE

// Keyboard dimensions
#define ROW_OF_KEYBOARD 5
#define COL_OF_KEYBOARD 10
/******************************************************************************/
/*********************************SSID KEYBOARD ------------------------------------*/
// Number length, buffer for storing it, and character index
#define NUM_LEN_SSID 22
char numberBuffer_SSID[NUM_LEN_SSID + 1] = "";
uint8_t numberIndex_SSID = 0;
bool capsLock_SSID = false;

// Array to store keyboard_SSID labels
char keyLabel_C_SSID[50][5] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    "!", "@", "#", "$", "%", "^", "&", "*", "_", "Ba",
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
    "A", "S", "D", "F", "G", "H", "J", "K", "L", "Z",
    "X", "C", "V", "B", "N", "M", "Ca", "Dl", "Tp", "En",
};

char keyLabel_S_SSID[50][5] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    "!", "@", "#", "$", "%", "^", "&", "*", "_", "Ba",
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
    "a", "s", "d", "f", "g", "h", "j", "k", "l", "z",
    "x", "c", "v", "b", "n", "m", "Ca", "Dl", "Tp", "En",
};

uint16_t keyColor_SSID[50] = {
    TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK,
    TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, Blue,
    TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK,
    TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK,
    TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, New_C, TFT_DARKGREY, TFT_BLACK, Send_C
};
/*********************************wifi PASSWOED KEYBOARD ------------------------------------*/

// Number length, buffer for storing it, and character index
#define NUM_LEN_PASSWIFI 22
char numberBuffer_PASSWIFI[NUM_LEN_PASSWIFI + 1] = "";
uint8_t numberIndex_PASSWIFI = 0;
bool capsLock_PASSWIFI = false;

// Array to store keyboard_PASSWORD labels
char keyLabel_C_PASSWIFI[50][5] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    "!", "@", "#", "$", "%", "^", "&", "*", "_", "Ba",
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
    "A", "S", "D", "F", "G", "H", "J", "K", "L", "Z",
    "X", "C", "V", "B", "N", "M", "Ca", "Dl", "Tp", "En",
};

char keyLabel_S_PASSWIFI[50][5] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    "!", "@", "#", "$", "%", "^", "&", "*", "_", "Ba",
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
    "a", "s", "d", "f", "g", "h", "j", "k", "l", "z",
    "x", "c", "v", "b", "n", "m", "Ca", "Dl", "Tp", "En",
};

uint16_t keyColor_PASSWIFI[50] = {
    TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK,
    TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, Blue,
    TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK,
    TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK,
    TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, TFT_BLACK, New_C, TFT_DARKGREY, TFT_BLACK, Send_C
};




/*----------------------------- END OF KEYBOARDS -----------------------------*/