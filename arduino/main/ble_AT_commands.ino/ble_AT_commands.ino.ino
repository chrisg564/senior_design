#include <SoftwareSerial.h>
SoftwareSerial HM10(8, 7);

char appData;

String inData = "";


void setup()
{
  HM10.begin(9600);
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println("BTserial started at 9600");

}
void loop()
{
  HM10.listen();  // listen the HM10 port

  while (HM10.available() > 0) {   // if HM10 sends something then read

    appData = HM10.read();

    inData = String(appData);  // save the data in string format

    Serial.write(appData);

  }




  if (Serial.available()) {           // Read user input if available.

    delay(10);

    HM10.write(Serial.read());

  }
}

//#include <AltSoftSerial.h>
//AltSoftSerial BTserial;
//// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
//
//
//char c=' ';
//boolean NL = true;
//
//void setup()
//{
//    Serial.begin(9600);
//    Serial.print("Sketch:   ");   Serial.println(__FILE__);
//    Serial.print("Uploaded: ");   Serial.println(__DATE__);
//    Serial.println(" ");
//
//    BTserial.begin(9600);
//    Serial.println("BTserial started at 9600");
//}
//
//int speed = 0;
//
//void loop()
//{
//    // Read from the Bluetooth module and send to the Arduino Serial Monitor
//    if (BTserial.available())
//    {
//        c = BTserial.read();
//
//        Serial.print(c);
//    }
////
////
////    // Read from the Serial Monitor and send to the Bluetooth module
//    if (Serial.available())
//    {
//        c = Serial.read();
//
//        // do not send line end characters to the HM-10
//        if (c!=10 & c!=13 )
//        {
//             BTserial.write(c);
//        }
//
//        // Echo the user input to the main window.
//        // If there is a new line print the ">" character.
//        if (NL) { Serial.print("\r\n>");  NL = false; }
//        Serial.write(c);
//        if (c==10) { NL = true; }
//
//
//    }
//      if (speed > 25){
//        speed = 0;
//      } else {
//        speed++;
//      }
//
//      BTserial.print(String(speed));
////      BTserial.print("8,");
////      Serial.println("sent");
////delay(100);
//}
