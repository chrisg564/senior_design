//void setup() {
//  pinMode(3, OUTPUT); // Set pin 8 as an output
//}
//
//void loop() {
//  digitalWrite(3, HIGH); // Set pin 8 to a high state
//  delay(1000); // Wait for 1 second
//  digitalWrite(2, LOW); // Set pin 8 to a low state
//  delay(1000); // Wait for 1 second
//}
#include <AltSoftSerial.h>
AltSoftSerial BTSerial; 
 
char c=' ';
boolean NL = true;
 
void setup() 
{
    Serial.begin(9600);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    BTSerial.begin(9600);  
    Serial.println("BTserial started at 9600");
 
    // If using an HC-05 in AT command mode the baud rate is likely to be 38400
    // Comment out the above 2 lines and uncomment the following 2 lines. 
    // BTSerial.begin(38400); 
    // Serial.println("BTserial started at 38400");
 
    Serial.println("");
    delay(100);
    sendCommand("AT");
    delay(100);
    sendCommand("AT+ROLE0");
    delay(100);
    sendCommand("AT+UUID0xFFE0");
    delay(100);
    sendCommand("AT+CHAR0xFFE1");
    delay(100);
    sendCommand("AT+NAMEg5sendesign");
    delay(100);

    BTSerial.write("test");
 
}

void sendCommand(const char * command){
  Serial.print("Command send :");
  Serial.println(command);
  BTSerial.println(command);
  //wait some time
  delay(100);
  
  char reply[100];
  int i = 0;
  while (BTSerial.available()) {
    reply[i] = BTSerial.read();
    i += 1;
  }
  //end the string
  reply[i] = '\0';
  Serial.write(reply);
}

void writeToBLE(char value) {
//  Serial.print("Writing hex :");
//  Serial.println(value, HEX);
  BTSerial.write(value);
}
char j = 0;
void loop()
{
 
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (BTSerial.available())
    {
        c = BTSerial.read();
        Serial.write(c);
    }
 
 
    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();
        BTSerial.write(c);   
 
        // Echo the user input to the main window. The ">" character indicates the user entered text.
        if (NL) { Serial.print(">");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
    }

    writeToBLE(j);
    j += 1;
    delay(500);
    
 
}
//#include <TimerOne.h>
////UNO only
//
//void setup()
//{
//pinMode(9,OUTPUT);
//pinMode(10,OUTPUT);
//
//Timer1.initialize(10);  // Frequency, 100us = 10khz, 10 >>>------> 100KHz
//// Timer1.pwm(9,512);       // 50% DC on pin 9
//Timer1.pwm(9, 255);
////Timer1.pwm(10,255);    // 25% DC on pin 10
//
//// D.C. 
//// 10KHz
//// You can use 2 to 1023 
//// 0 & 1 gives a constant LOW 
//// 1024 gives a constant HIGH
//// 2 gives ~125ns HIGH pulses
//// 1023 gives ~125ns low pulses
//// 512 gives 50us
//}
//
//void loop()
//{
//}
