/*  =================================================================================================================== */
/*  ============================================== Task 3.1 Model Answer ============================================== */
/*  ==================================================== Slave Code =================================================== */
/*  =================================================================================================================== */


/* Include Library for I2C Communication*/
#include <Wire.h>

/* Configure Pin For The LED (PWM pin) */
#define led             11

/* Determine The Slave Address */
#define SLAVE_ADDRESS   8

/* Define Perecentage to PWM */
#define BRIGHTNESS_0_PERCENT        0
#define BRIGHTNESS_50_PERCENT       127
#define BRIGHTNESS_75_PERCENT       192
#define BRIGHTNESS_100_PERCENT      255     

/* Variable To Store State of the 2 buttons */
int ButtonsState = 0;

void setup() {
  // put your setup code here, to run once:

  /*  Set The led Pin as OUTPUT  */
  pinMode(led, OUTPUT);

  /*  Initialize Serial Communication with Serial Monitor  */
  Serial.begin(9600);
  
  /*  Initialize the I2C communication peripheral as a Slave  */
  Wire.begin(SLAVE_ADDRESS);

  /* Set handler for receiving data on I2C port */
  Wire.onReceive(ReadRecievedData);
}

void loop() {
  // put your main code here, to run repeatedly:

  /* Control Led brightness based on state of buttons */
  ContorlLEDBrightness();

}


/*
 * @Breif:
 *  Reads the data receieved from I2C Buffer
*/
void ReadRecievedData(int bytes)
{
  /*  Check if there is data available in I2C buffer  */
  if(Wire.available())
   /* Read message from the buffer */
   ButtonsState = Wire.read();
}


/* @Brief: 
 *  Function to control led brightness based on buttons state recieved from slave
 *  and
 *  Prints a message to the serial monitor
 *  
*/
void ContorlLEDBrightness()
{         
  switch(ButtonsState)
  {
    /* No button is pressed */
    case 0:
      analogWrite(led, BRIGHTNESS_0_PERCENT);
      Serial.println("No message");
      break;
    /*Button 1 is Pressed */  
    case 1:
      analogWrite(led, BRIGHTNESS_50_PERCENT);
      Serial.println("Vector focused");
      break;
    /*Button 2 is Pressed */  
    case 2:
      analogWrite(led, BRIGHTNESS_75_PERCENT);
      Serial.println("Vector distracted");
      break;
    /*Button 1 and Button 2 are Pressed */  
    case 3:
      analogWrite(led, BRIGHTNESS_100_PERCENT);
      Serial.println("Glitch");
      break;      
  }
}
