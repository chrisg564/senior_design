//PWM lib (uses pin 9 and 10)
#include <TimerOne.h>

//BLE lib
#include <SoftwareSerial.h>
SoftwareSerial HM10(8, 7);


// Pin setup
// D5 is and output pin for the relay - HIGH is on, LOW is off
// D7 goes to a Voltage divider to get 3.3V then RXD on the HM-10
// D8 goes directly to TXD on HM-10

char c = ' ';
boolean NL = true;

char appData;
String inData = "";

int speed = 0;
int DC = 0;
bool relay = false;

void setup()
{
  // BLE setup
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");

  HM10.begin(9600);
  Serial.println("BTserial started at 9600");

  // Emergency stop
  pinMode(5, OUTPUT);

  //PWM
  pinMode(10, OUTPUT);
  // Needs testing, but should use 20kHz instead of 100kHz
  Timer1.initialize(50);  // Frequency, 100us = 10khz, 10 >>>------> 100KHz
}



void loop()
{
  // Read from the Bluetooth module and send to the Arduino Serial Monitor
  HM10.listen();  // listen the HM10 port

  while (HM10.available() > 0) {   // if HM10 sends something then read
    appData = HM10.read();
    inData = String(appData);  // save the data in string format
    //    Serial.write(appData);
    // Change the duty cycle according to input
    if (inData == "i") {
      DC += 5;
      Timer1.pwm(10, DC); // change DC on pin 10
      Serial.println("DC is " + String(DC));
    }
    if (inData == "d") {
      DC -= 5;
      Timer1.pwm(10, DC); // change DC on pin 10
      Serial.println("DC is " + String(DC));
    }
    if (inData == "s") {
      relay = !relay;
      if (relay) {
        digitalWrite(5, HIGH);
      } else {
        digitalWrite(5, LOW);
      }
      Serial.println("relay changed");
    }

    // Change the duty cycle, this is mainly for debugging and testing
    if (inData == "[") {
      String temp = "";
      while (inData != "]") {
        appData = HM10.read();
        inData = String(appData);  // save the data in string format
        temp += inData;
      }
      DC = temp.toInt();
      Timer1.pwm(10, DC); // change DC on pin 10
      Serial.println("DC is " + String(DC));
    }
  }


  // Read from the Serial Monitor and send to the Bluetooth module
  if (Serial.available()) {           // Read user input if available.
    delay(10);
    HM10.write(Serial.read());
  }


  if (speed > 25) {
    speed = 0;
  } else {
    speed++;
  }

  char buffer[10];
  itoa(speed, buffer, 10);
  const char* stringValue = buffer;
  HM10.println(stringValue);
  //      BTserial.print("8,");
  //      Serial.println("sent");
  delay(100);
}
