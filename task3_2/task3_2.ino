/*  =================================================================================================================== */
/*  ============================================== Task 3.2 Model Answer ============================================== */
/*  ================================================ Localization Code ================================================ */
/*  =================================================================================================================== */

/* Configure Pins for the 4 ultrasonic sensors */
#define Trig_Right    6
#define Echo_Right    5
#define Trig_Left     12
#define Echo_Left     13
#define Trig_Up       2
#define Echo_Up       3
#define Trig_Down     8
#define Echo_Down     9


/* Set Room Dimensions */
#define ROOM_LENGTH_CM  600
#define ROOM_WIDTH_CM   500

/* Variables for storing xy co-ordinates */
int x = 0;
int y = 0;


/* Variables for storing distance to the walls from each sensor in cm */
int distance_right  = 0;
int distance_left   = 0;
int distance_up     = 0;
int distance_down   = 0;



void setup()
{
  /* Initialize Serial Communication For serial monitor */
  Serial.begin(9600);

  /*  Set the pin modes for each pin of every sensor  */
  pinMode(Trig_Right,OUTPUT);
  pinMode(Echo_Right,INPUT);
  
  pinMode(Trig_Left,OUTPUT);
  pinMode(Echo_Left,INPUT);
  
  pinMode(Trig_Up,OUTPUT);
  pinMode(Echo_Up,INPUT);
   
  pinMode(Trig_Down,OUTPUT);
  pinMode(Echo_Down,INPUT);

}

void loop()
{
  /* calculate location of robot in xy-coordinates  */
   calculate_coordinates();

  /* Prints the current location of robot on serial monitor */
  Serial.print("x:");
  Serial.print(x);
  Serial.print(", y:");
  Serial.println(y);
}
/***********************************************************************************/
/*
 * @Brief:
 *  Function to calculate distance with an ultrasonic sensor
*/
int calculate_distance_ultra(int trigPin, int echoPin)
{
  int distance = 0;

  /* Sending pulse on trig pin*/
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
 
  /* Recieve pulse on echo pin and read time travelled */
  long long duration = pulseIn(echoPin, HIGH);

  /* Calculate distance in cm 
   * Speed of Sound = 340 m/s
   * duration is in microseconds
   * distance = (duration/10^6)[s] * (Speed*100)[cm/s] 
   * so we get distance in cm
  */
  distance = (duration * 0.0343)/2;
  
  return distance;
}
/***********************************************************************************/

/*   
 * @Brief:
 *  Function to get distance from the sensors on the robot to every wall 
*/
void get_distance_from_sensors()
{
  distance_right = calculate_distance_ultra(Trig_Right, Echo_Right);
  distance_left  = calculate_distance_ultra(Trig_Left , Echo_Left);
  distance_up    = calculate_distance_ultra(Trig_Up   , Echo_Up);
  distance_down  = calculate_distance_ultra(Trig_Down , Echo_Down);
}
/***********************************************************************************/
/*   
 * @Brief:
 *  Function to calculate the co-ordinates of robot's location
*/
void calculate_coordinates()
{
  /* Variables to store the x and y calculated from each sensor */
  int x_left=0, x_right=0;
  int y_down=0, y_up=0;

  /* Get the distance to every wall from each sensor */
  get_distance_from_sensors();

  /* 
   *  x_left: represents the x-coordinate calculated from the left sensor
   *  x_right: also represents the x-coordinate but calculated from the subtracting the distance to the right wall from the width of the room 
  */
  x_left  = distance_left;
  x_right = (ROOM_WIDTH_CM  - distance_right);

   /* 
   *  y_down: represents the y-coordinate calculated from the down sensor
   *  y_up: also represents the y-coordinate but calculated from the subtracting the distance to the up wall from the length of the room 
  */ 
  y_down = distance_down;
  y_up   = (ROOM_LENGTH_CM - distance_up);

  /* Get the average of both readings to increase accuracy */
   x = (x_left + x_right)/2;
  /* Get the average of both readings to increase accuracy */
   y = (y_down + y_up)/2;

  /* Ensure that readings are within dimension */
   constrain(x,0,ROOM_WIDTH_CM);
   constrain(y,0,ROOM_LENGTH_CM);
}
