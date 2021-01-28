/*
 * 2020 Fall CST8227 Interfacing Midterm Practial
 * Author Wyatt wang0620@algonquinlive.com
*/


#include <Bounce2.h>
// Globals
const int buttonPin = 12; // Button  Pin
Bounce pushbutton = Bounce (buttonPin,10); //10 ms debounce

byte previousState = HIGH;         // what state was the button last time
unsigned int count = 0;            // how many times has it changed to low
unsigned long countAt = 0;         // when count changed
unsigned int countPrinted = 0;     // last count printed

const int dataPin = 14;  // blue wire to 74HC595 pin 14
const int latchPin = 15; // green to 74HC595 pin 12
const int clockPin = 16; // yellow to 74HC595 pin 11

/* uncomment one of the following lines that describes your display
    and comment out the line that does not describe your display */
const char common = 'a';    // common anode
//const char common = 'c';    // common cathode

void setup() {
  // initialize I/O pins
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  pinMode(buttonPin,INPUT_PULLUP);
  Serial.begin(57600);
  Serial.println("Pushbutton Bounce library test:");
}

void loop() {
  if(count==0)  myfnUpdateDisplay(myfnNumToBits(10));
  if(count==11) count=1;//reset counter
  if (pushbutton.update()) {
    if (pushbutton.fallingEdge()) {
      count = count + 1;
      countAt = millis();
    }
  } else {
    if (count != countPrinted) {
      unsigned long nowMillis = millis();
      if (nowMillis - countAt > 100) {
        Serial.print("PBS press #: ");
        Serial.print(count);
        Serial.print(" => ");
        Serial.println(myfnSegementDisplay(count));
        
        myfnUpdateDisplay(myfnNumToBits(count));
        delay(250);
        countPrinted = count;
      }
    }
  }

}

void myfnUpdateDisplay(byte eightBits) {
                   
  eightBits = eightBits ^ B11111111;  // then flip all bits using XOR
  digitalWrite(latchPin, LOW);  // prepare shift register for data
  shiftOut(dataPin, clockPin, LSBFIRST, eightBits); // send data
  digitalWrite(latchPin, HIGH); // update display
}
String myfnSegementDisplay(int someNumber){
    switch (someNumber) {

    case 1: // Segement A
      return "Segement A";
      break;
    case 2: // Segement B
      return "Segement B";
      break;
    case 3: // Segement C
      return "Segement C";
      break;
    case 4: // Segement D
      return "Segement D";
      break;
    case 5: // Segement E
      return "Segement E";
      break;
    case 6: // Segement F
      return "Segement F";
      break;
    case 7: // Segement G
      return "Segement G";
      break;
    case 8: // Segement Decimal Point
      return "Segement Decimal Point";
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
    case 1: // Segement A
      return B10000000;
      break;
    case 2: // Segement B
      return B01000000;
      break;
    case 3: // Segement C
      return B00100000;
      break;
    case 4: // Segement D
      return B00010000;
      break;
    case 5: // Segement E
      return B00001000;
      break;
    case 6: // Segement F
      return B00000100;
      break;
    case 7: // Segement G
      return B00000010;
      break;
    case 8: // Segement Decimal Point
      return B00000001;
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
