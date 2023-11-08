/*Please feel free to edit this code to fit your specific application.
This code is written in a way such that you can change the control pins (D3, D4, D5) 
without having to change any other part of the code*/

#include <Servo.h> // Includes servo library
Servo servoMotor; // Registers MG995_Servo as a servo
char Bluetooth = 0;
/* fwd/rwd */
const int MTRspeed = 3;//ensure this pin is labelled PWM (~) on the Arduino. If not, assign a new pin with PWM
const int FWD = 4;//Digital pin 4 will drive the motor forward
const int REV = 5;//Digital pin 5 will drive the motor reverse
/* servo */
const int SERV = 6;// Assigns servo to PWM pin 6
const int steerLeft = 7;// Pin 7 steers left
const int steerRight = 8;//pin 8 steers right

/*"const" means constant. It is not necessary to include this for the execution of the program, 
but from a coding/troubleshooting standpoint it is good practice to 
differentiate between constant and non-constant integers*/

void setup() {
  Serial.begin(9600);//rate of serial transmission (Baud). Do not edit this line
  pinMode (MTRspeed, OUTPUT);//declare pin D3 (motor speed control) as an output
  pinMode (FWD, OUTPUT);//declare pin D4 (motor forward) as an output
  pinMode (REV, OUTPUT);//declare pin D5 (motor reverse) as an output
  servoMotor.attach(SERV); // Attaches servo to PWM pin 6
/* probably the servo */
  pinMode (steerLeft, OUTPUT); // makes these outputs for left and right
  pinMode (steerRight, OUTPUT);
}

void loop() {
 
  
  if (Serial.available() == 0)//if there is no character in the serial monitor, do nothing
  {
  }


  if (Serial.available() > 0) /*if there is a character in the serial monitor,
  determine the character and run the corresponding code*/
  {
    Bluetooth = Serial.read();//read the character from the serial monitor and set it equal to char Bluetooth
    Serial.print(Bluetooth);//print the character sent from your smartphone to the serial monitor

    if (Bluetooth == 'F')//if value is 'F' drive the motor forward
    {
      analogWrite(MTRspeed, 255);//write the motor to maximum speed
      digitalWrite(FWD, HIGH);//drive the motor forward by writing pin D4 to logic 1 (HIGH)
      digitalWrite(REV, LOW);//ensure the motor controller cannot drive the motor FWD and REV at the same time
    }

    if (Bluetooth == 'D')//if value is 'D' drive the motor backward
    {
      analogWrite(MTRspeed, 255);//write the motor to maximum speed
      digitalWrite(FWD, LOW);//ensure the motor controller cannot drive the motor FWD and REV at the same time
      digitalWrite(REV, HIGH);//drive the motor backward by writing pin D5 to logic 1 (HIGH)
    }

    if (Bluetooth == 'B')//if value is 'B' stop the motor
    {
      digitalWrite(FWD, LOW);//write pin D4 to logic 0 (LOW)
      digitalWrite(REV, LOW);//write pin D5 to logic 0 (LOW)
    }

    if (Bluetooth == 'L')// Turn left if Left arrow is pressed
    {
      // Serial.println("L"); // Print test
      servoMotor.write(55); // Turns the servo clockwise, I saw a picture on https://www.instructables.com/Arduino-Servo-Motors/ and it looks right
      delay(1000); // Turns left for 1.5 seconds
    }
    if (Bluetooth == 'R')// Turn right if Right arrow is pressed
    {
      // Serial.println("R"); // Print test
      servoMotor.write(35); // Turns the servo clockwise, 180 represents 180 degrees on a unit circle so it's to the right
      delay(1000); // Waits 1.5 seconds
    }
    if (Bluetooth == 'A')// Turn right if Right arrow is pressed
    {
      // Serial.println("R"); // Print test
      servoMotor.write(45); // Turns the servo clockwise, 180 represents 180 degrees on a unit circle so it's to the right
      delay(1000); // Waits 1.5 seconds
    }
  }
}
