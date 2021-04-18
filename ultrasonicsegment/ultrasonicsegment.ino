//This code reads the distance sensor and displays a number 1-9 on the seven segment display
// a 74HC5595 chip was used to translate the data and tell the Segment display
//which segments should be on to display each number


#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(12, 11);

byte seven_seg_digits[9] = { 
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110   // = 9
                             };
int lightPin = 0;
int latchPin = 3;
int clockPin = 4;
int dataPin = 2;


void sevenSegWrite(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}
void setup() 
{
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}
void loop() 
{
Serial.println(distanceSensor.measureDistanceCm());
int reading = distanceSensor.measureDistanceCm();
int numDisplay = reading / 10;
if (numDisplay > 9) numDisplay = 9;

sevenSegWrite(numDisplay);
delay(150);





}
