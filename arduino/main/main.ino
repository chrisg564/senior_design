#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
int PIN_EN_OUT = 4;
int PIN_STATE_IN = 5;


void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);

  sendCommand("AT");
  sendCommand("AT+ROLE0");
  sendCommand("AT+UUID0xFFE0");
  sendCommand("AT+CHAR0xFFE1");
  sendCommand("AT+NAMEbluino");
}

void sendCommand(const char * command) {
  Serial.print("Command send :");
  Serial.println(command);
  mySerial.println(command);
  //wait some time
  delay(100);

  char reply[100];
  int i = 0;
  while (mySerial.available()) {
    reply[i] = mySerial.read();
    i += 1;
  }
  //end the string
  reply[i] = '\0';
  Serial.print(reply);
  Serial.println("Reply end");
  delay(50);
}

void writeSerialToBLE(int value) {
  mySerial.println(value);
}

void writeToBLE(char value) {
  Serial.print("Writing hex :");
  Serial.println(value, HEX);
  mySerial.write(value);
}

char j = 0;
void loop() {
  // writeToBLE(j);
  j += 1;
  delay(500);
}

// #include <SoftwareSerial.h>
// #include <TimerOne.h>


// // Define the data transmit/receive pins in Arduino

// #define TxD 3
// #define RxD 2

// SoftwareSerial mySerial(RxD, TxD); // RX, TX for Bluetooth

// void setup() {
//   pinMode(9, OUTPUT);
//   pinMode(10, OUTPUT);

//   Timer1.initialize(10);  // Frequency, 100us = 10khz, 10 >>>------> 100KHz
//   // Timer1.pwm(9,512);       // 50% DC on pin 9
//   // Timer1.pwm(9, 512);
//   Timer1.pwm(9, 100);

//   //Timer1.pwm(10,255);    // 25% DC on pin 10

//   // D.C.
//   // 10KHz
//   // You can use 2 to 1023
//   // 0 & 1 gives a constant LOW
//   // 1024 gives a constant HIGH
//   // 2 gives ~125ns HIGH pulses
//   // 1023 gives ~125ns low pulses
//   // 512 gives 50us

//   // Blue tooth
//   mySerial.begin(9600); // For Bluetooth
//   Serial.begin(9600); // For the IDE monitor Tools -> Serial Monitor
//   sendCommand("AT");
//   sendCommand("AT+ROLE0");
//   sendCommand("AT+UUID0xFF00");
//   sendCommand("AT+CHAR0xFF01");
//   sendCommand("AT+NAMELightBlue");
// }



// void loop() {
//   // Timer1.pwm(9, 1000);
//   // for(int i=0; i < 50000; i++){
//   //     // wait
//   // }
//   // int temp = 0;
//   // while (true) {
//   //   Timer1.pwm(9, temp);
//   //   temp++;
//   //   for (int i = 0; i < 10000; i++) {
//   //     // wait
//   //   }
//   //   if (temp == 512) {
//   //     temp = 0;
//   //   }
//   // }
//   // for(int i=0; i < 10000; i++){
//   //   Timer1.pwm(9,100); //10
//   // }
//   // for(int i=0; i < 10000; i++){
//   //   Timer1.pwm(9,255); //25
//   // }
//   // for(int i=0; i < 10000; i++){
//   //   Timer1.pwm(9,512); //50
//   // }

//   //BT
  
  

// }