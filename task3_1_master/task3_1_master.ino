/*  =================================================================================================================== */
/*  ============================================== Task 3.1 Model Answer ============================================== */
/*  ==================================================== Master Code =================================================== */
/*  =================================================================================================================== */


/* Include Library for I2C Communication*/
#include <Wire.h>

/* Configure Pins For The 2 Push Buttons */
#define Button1         2
#define Button2         3

/* Determine The Slave Address */
#define SLAVE_ADDRESS   8

/* Variables To Store Each Button State */ 
bool isPressed_Button1 = false;
bool isPressed_Button2 = false;

/* Variable To Encode The States of The 2 Push Buttons into 1 Variable */
int encodedState = 0;

void setup() {
  // put your setup code here, to run once:

  /*  Set The Push Buttons Pins as INPUT  */
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);

  //attachInterrupt(digitalPinToInterrupt(Button1),Button1_Pressed,RISING);
  //attachInterrupt(digitalPinToInterrupt(Button2),Button1_Pressed,RISING);  
  /*  Initialize the I2C communication peripheral as a Slave  */
  Wire.begin();

}

void loop() {
  // put your main code here, to run repeatedly:  
  
  /*  Monitor The States of The 2 Push Buttons  */
  isPressed_Button1 = digitalRead(Button1);
  isPressed_Button2 = digitalRead(Button2);

  /* Call the Function To Encode the States of the 2 Push Buttons into 1 variable */
  encodedState = encodeButtonStates();

  /* Send encoded state of the 2 push buttons to slave */
  SendEncodedState();
  
  /* Delay For debouncing */
  delay(400);
  
}

/*  @Brief: 
 *   Function that encodes the status of the 2 push buttons to the corresponding binary to decimal value 
 *  Ex:
 *  00 ====> 0
 *  01 ====> 1
 *  10 ====> 2
 *  11 ====> 3
 *  
 *  @return: 
 *   Returns the encoded state
*/
int encodeButtonStates()
{
  encodedState = 0;
  
  if( isPressed_Button1 == true && isPressed_Button2 == false)
  {
    encodedState = 1;
  }
  else if( isPressed_Button1 == false && isPressed_Button2 == true)
  {
    encodedState = 2;
  } 
  else if( isPressed_Button1 == true && isPressed_Button2 == true)
  {
    encodedState = 3;
  } 

  return encodedState;
}

/* 
 *  @Brief:
 *    Function To send data to the slave
 *  
*/
void SendEncodedState()
{
  /* Initialize Communication */
  Wire.beginTransmission(SLAVE_ADDRESS);
  /* Send The Data */
  Wire.write(encodedState);
  /* End Communication*/
  Wire.endTransmission();
}
/**********************************************************************************/
/* ISR function for using interrupts to monitor the buttons */

/*
void Button1_Pressed()
{
  isPressed_Button1 = !isPressed_Button1;
}
void Button2_Pressed()
{
  isPressed_Button2 = !isPressed_Button2;
}
*/
/**********************************************************************************/
