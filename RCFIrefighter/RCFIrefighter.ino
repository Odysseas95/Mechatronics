#include <AFMotor.h>

const int FsensorMin = 0;     // sensor minimum
const int FsensorMax = 1024;  // sensor maximum
//creates two objects to control the terminal 3 and 4 of motor shield 
AF_DCMotor motor1(1); 
AF_DCMotor motor2(2); 

char command; 

void setup() 
{       
  pinMode(51, OUTPUT);
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop(){
  
//FLAME SENSOR
// read the sensor on analog A14:
  int FsensorReading = analogRead(A14);
  int range = map(FsensorReading, FsensorMin, FsensorMax, 0, 3);// map the sensor range (four options)
  
  // range value:
  switch (range) {
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("** Close Fire **");
    digitalWrite(51, HIGH);
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("** Distant Fire **");
    digitalWrite(51, HIGH);
    break;
  case 2:    // No fire detected.
    Serial.println("No Fire");
    digitalWrite(51, LOW);
    break;
  }
  delay(50);  // delay between reads

//MOTOR DRIVE
  if(Serial1.available() > 0){ 
    command = Serial1.read(); 
    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    //Serial.println(command);
    switch(command){
    case 'F':  
      forward();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
    }
  } 
}
void forward()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
}

void back()
{
  motor1.setSpeed(255); 
  motor1.run(BACKWARD); //rotate the motor counterclockwise
  motor2.setSpeed(255); 
  motor2.run(BACKWARD); //rotate the motor counterclockwise
}

void left()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(0);
  motor2.run(RELEASE); //turn motor2 off
}

void right()
{
  motor1.setSpeed(0);
  motor1.run(RELEASE); //turn motor1 off
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
}

void Stop()
{
  motor1.setSpeed(0);
  motor2.run(RELEASE); //turn motor1 off
  motor2.setSpeed(0);
  motor2.run(RELEASE); //turn motor2 off
}


