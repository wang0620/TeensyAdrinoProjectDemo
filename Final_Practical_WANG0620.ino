/********************************************************
 * Practical Question : Fall 2020
 * 
 * Level Achieved : A-/B+
 * 
 * Status: Working, able to show both Celsius and row on monitor and correctly display temperature level on 7-segement 
 * 
 * @author Weiong Wang
 */
       //TODO: you write code to earn marks :)
#include <Time.h>
const float MIN_TEMP =15.0;    //no student has reported lower than 15 degrees Celsius
const float MAX_TEMP =33.0;   //no student has reported higher than 33 degrees Celsius

const int dataPin = 14;  // blue wire to 74HC595 pin 14
const int latchPin = 15; // green to 74HC595 pin 12
const int clockPin = 16; // yellow to 74HC595 pin 11

/* uncomment one of the following lines that describes your display
    and comment out the line that does not describe your display */
const char common = 'a';    // common anode
//const char common = 'c';    // common cathode
  
 float code;
 float celsius;
 int therm = A6;
 IntervalTimer timer1;
 IntervalTimer timer2;
void setup() {
  // initialize I/O pins
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(therm,INPUT);

  Serial.begin(57600);
  Serial.println(" Read the thermistor:");
  //timer1.begin(mockTempValue, 6e+6);
}

void loop() {

  code = analogRead(therm);
 // timer1.begin(mockTempValue, 6e+6);
  
  celsius= code;//TODO
  
  if (code <= 289) {
    celsius = 5 + (code - 289) / 9.82;
  }
  if (code > 289 && code <= 342) {
    celsius = 10 + (code - 342) / 10.60;
  }
  if (code > 342 && code <= 398) {
    celsius = 15 + (code - 398) / 11.12;
  }
  if (code > 398 && code <= 455) {
    celsius = 20 + (code - 455) / 11.36;
  }
  if (code > 455 && code <= 512) {
    celsius = 25 + (code - 512) / 11.32;
  }
  if (code > 512 && code <= 566) {
    celsius = 30 + (code - 566) / 11.00;
  }
  if (code > 566 && code <= 619) {
    celsius = 35 + (code - 619) / 10.44;
  }
  if (code > 619 && code <= 667) {
    celsius = 40 + (code - 667) / 9.73;
  }
  if (code > 667) {
    celsius = 45 + (code - 712) / 8.90;
  }
  
  Serial.print("Temperature:  ");
  int raw = code;
  Serial.print(raw);
  Serial.print(" (raw) ");
  Serial.print(celsius);
  Serial.println(" Celsius ");
  if(celsius >= MIN_TEMP && celsius<= MAX_TEMP){
    myfnUpdateDisplay(myfnNumToBits(1));
    //Serial.println(myfnSegementDisplay(1));
    } 
  if(celsius < MIN_TEMP){
    myfnUpdateDisplay(myfnNumToBits(2));
    //Serial.println(myfnSegementDisplay(2));
  }  
  if(celsius > MAX_TEMP){
    myfnUpdateDisplay(myfnNumToBits(3));
   // Serial.println(myfnSegementDisplay(3));
    }  
  
  delay(2000);

}

void mockTempValue(){
  if (code!=0){
     code = -80;
   Serial.println("INJECT LOW");   
   analogWrite(therm,code);
    }

  }

void myfnUpdateDisplay(byte eightBits) {
  //if (common == 'a') {                  // using a common anonde display?
  eightBits = eightBits ^ B11111111;  // then flip all bits using XOR
  // }
  digitalWrite(latchPin, LOW);  // prepare shift register for data
  shiftOut(dataPin, clockPin, LSBFIRST, eightBits); // send data
  digitalWrite(latchPin, HIGH); // update display
}
String myfnSegementDisplay(int someNumber){
    switch (someNumber) {

    case 1: // n
      return "Temperature is Normal, 7 Segement display 'n'.";
    case 2: // L
      return "Temperature is Low, 7 Segement display 'L'.";
      break;
    case 3: // H
      return "Temperature is High, 7 Segement display 'H'.";
      break;
    case 9: //8.
      return "8.";
      break;
    case 10: //All Segement off
      return "All Segement off";
      break;
    default: // ERROR
      return B10010010; // Error condition, displays three vertical bars
      break;
  }
  
}

byte myfnNumToBits(int someNumber) {
  switch (someNumber) {
    case 1: // n
      return B00101010;
      break;
    case 2: // L
      return B00011100;
      break;
    case 3: // H
      return B01101110;
      break;
   
    case 9: //8.
      return B11111111;
      break;
    case 10: //All Segement off
      return B00000000;
      break;
    default: // Segement A
      return B10010010; // Error condition, displays three vertical bars
      break;
  }
}
