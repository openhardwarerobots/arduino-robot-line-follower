// Code for the line following miniQ v2.0 robot
// Based on the example code by DFRobot

// Motor pins
#define EN1 5 // Pin for run the left motor 
#define IN1 12 // Pin for control left motor direction
#define EN2 6 // Pin for run the right motor 
#define IN2 7 // Pin for control right motor direction

// Forward & back codes
#define Forward 0
#define Back 1         

// Data array for sensor readings
int data[5] = {};

void setup()
{
  // Declare motor pins as outputs
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT); 
  
  // Stop motors by default
  Motor(Forward,0,Forward,0);
}

void loop()
{
  
  // Read data from the sensors
  Read_Value();
  
  // Follow the line
  line_follow();
}

// Motor control function
void Motor(int M1_DIR,int M1_EN,int M2_DIR,int M2_EN)
{
  //////////M1-->left motor////////////////////////
  if(M1_DIR==Forward)//distinguish the command
    digitalWrite(IN1,Forward);
  else
    digitalWrite(IN1,Back);
  if(M1_EN==0)
    analogWrite(EN1,LOW);
 else
    analogWrite(EN1,M1_EN);

  ///////////M2-->right motor//////////////////////
  if(M2_DIR==Forward)
    digitalWrite(IN2,Forward);
  else
    digitalWrite(IN2,Back);
  if(M2_EN==0)
    analogWrite(EN2,LOW);
  else
    analogWrite(EN2,M2_EN);
}

// Read data from all sensors
void Read_Value(void)
{  
  char i;
  for(i=0;i<5;i++)
  {
    // Store data in data array
    data[i]=analogRead(i);
  }
}

// Function to follow lines
void line_follow()
{
  // Detect black line on the left
  if((data[0]<650 || data[1] <650) && (data[3]>800 && data[4]>800))
  { 
    // Therefore turn right
    Motor(Forward,0,Forward,110);
    delay(10);
  }
  
  // Black line on the right
  else  if((data[3]<650 || data[4] <650) && (data[0]>800 && data[1]>800))
  {
    // Therefore turn left
    Motor(Forward,110,Forward,0);
    delay(10);
  }
  
  // Line in middle
  else if(data[2]<700)
  {
    // Just go forward
    Motor(Forward,90,Forward,90);
    delay(20);
  }
  else 
  {
    // If we're lost, move slowly
    Motor(Forward,70,Forward,70);
  }
}
