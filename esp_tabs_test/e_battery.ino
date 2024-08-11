/**** voltmeter intialization ****/
#define Battery_pin 32

float input_volt = 0.0;
float Battery_volt = 3.7; 
float charge_rate = 0.0;

float temp=0.0;

float r1=1000.0;    

float r2=1000.0;      
/************************************/
/*
  ******************************************************************
  FUNCTION NAME: Battery
  ARGUMENTS:     VOID
  RETURNS:       VOID
  DESCRIPTION:   USE TO DETERMINE THE POWER CONSUMPTION OF WATCH AND 
                 PRINT IT ON THE TFT TOUCH SCREEN.
  ******************************************************************
*/
void Battery(void)
{
  int analogvalue = analogRead(Battery_pin);

  temp = (analogvalue * 5) / 1024.0;  // edit here
  input_volt = temp / (r2/(r1+r2));
  charge_rate = (input_volt / Battery_volt) * 100;
  if (input_volt < 0.1) 
  {
    input_volt=0.0;
  }
  tft.print(charge_rate);
  tft.println(" %");
}