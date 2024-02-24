#define BAUD_RATE 115200


/***************************** WIFI ********************************************/
const char* ssid = "ARK";
const char* password = "abo0156962#";
/*******************************************************************************/


/********************************* TFT *****************************************/
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 60
#define Blue 0x09F0
#define White TFT_WHITE
#define Black TFT_BLACK
#define Send_C 0x32D4
#define New_C  0x53D7
#define HM_C 0x74BB
uint16_t tft_width = 480, tft_height = 320;
bool HSI_Button = false;

/*------------------------------------------------------- KEYPADS ---------------------------------------------------------*/

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
                         "." ,     "0",  "Del",
                         "Clr", "Send", "Back"
                        };
uint16_t keyColor[15] = {TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_DARKGREY,
                         New_C, Send_C, Blue
                        };
              
char* BSG_Result = NULL;
char* BP_Result = NULL;

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

char AkeyLabel[15][5] = {"1", "2", "3",
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

// Add a state variable for edit mode
enum State {
  TIME_PAGE,
  EDIT_PAGE,
  EXIT_PAGE
};
State currentState = EXIT_PAGE;  // Initial page
int editAlarmIndex = -1; // Index of the alarm being edited, -1 means no alarm is being edited

/******************************************************************************/
unsigned long prevtime_T1 = millis();
long interval_T1 = 6000;

unsigned long prevtime_T2 = millis();
long interval_T2 = 1000;
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
                         "Clr", "Ent", "Back"                    };

uint16_t PassColor[15] = {TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_DARKGREY,
                         New_C, Send_C, Blue
                        };
/******************************************************************************/

/************************ID keypad configurations************************/
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
char* IdNum = NULL;
/******************************************************************************/
/*-----------------------------------------------------------------------------------------------------------------------------*/