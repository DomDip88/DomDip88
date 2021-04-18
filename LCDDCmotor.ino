//This code uses a Joystick to control the position of a motor and then displays its position on an LCD 14x2 display, 
//the program required me to set up a range of numbers in order to keep the joycon centered to account for drift
//Dominic DiPiero
#include <LiquidCrystal.h>
int vrxPin = A0; // x pin
int vryPin = A1; // y pin
int vrxVal, vryVal; // value from joystick
LiquidCrystal lcd(12, 13, 6, 4, 3, 2);
int enablePin = 5;//hbridge Enable
int switchPin = A2;
int in1Pin = 9; //hbridge in1
int in2Pin = 10; //hbridge in2
int motorSpeed; // dc Motor PWM goes to EN
bool motorDirection = true; // dc motor direction
int center = 512; //value received from joystick when at rest maybe need X and y Independent
int deadzone = 12;
bool switchFlag = false;
int switchVal;
int motorSpeedDisp;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(vrxPin, INPUT);
  pinMode(vryPin, INPUT);
  pinMode(switchPin, INPUT);
  pinMode(enablePin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Hello, World!");
}

void loop() {
  
  //motorSpeedDisp = 0;
  getJoystick();
  setMotor(motorSpeed, motorDirection);
  lcdShow();
  
}


void getJoystick () { //gets data from joystick
  vrxVal = analogRead(vrxPin);
  vryVal = analogRead(vryPin);
  switchVal = analogRead(switchPin);
  if(switchVal < 5){
    switchFlag = !switchFlag;
    delay(500);
  }
  
}
void setMotor(int motorSpeed, bool motorDirection) { // dc motor driver determines 
  if (vrxVal < center - deadzone && switchFlag == false) { //
    motorSpeed = map(vrxVal, 0, center, 0, 255);
    analogWrite(enablePin, 255 - motorSpeed);
    digitalWrite(in1Pin, motorDirection);
    digitalWrite(in2Pin, !motorDirection);
   
    motorSpeedDisp = 255 - motorSpeed;
     //lcd.setCursor(0, 0);
    //lcd.print("DC motor: ");
    //lcd.println(motorSpeedDisp);
  }
 else if (vrxVal > center + deadzone && switchFlag == false) {
    motorSpeed = map(vrxVal, center, 1023, 0, 255);
    analogWrite(enablePin, motorSpeed);
    digitalWrite(in1Pin,  !motorDirection);
    digitalWrite(in2Pin, motorDirection);
   
    motorSpeedDisp = -motorSpeed;
    // lcd.setCursor(0, 0);
    //lcd.print("DC motor: ");
    //lcd.println(motorSpeedDisp);
  }
 else{
  motorSpeed = 0;
  analogWrite(enablePin, motorSpeed);
  motorSpeedDisp = motorSpeed;
  
 }
}
void lcdShow(){
  //lcd.setCursor(0, 0);
    //lcd.print("+: ");
  lcd.setCursor(0, 1);
  if(motorSpeedDisp > 255){
    motorSpeedDisp = 255;
  }
  else if (motorSpeed < -255){
    motorSpeedDisp = -255;
  }
  lcd.print(motorSpeedDisp);
  delay(50);
  lcd.clear();
  lcd.setCursor(0, 0);
}
