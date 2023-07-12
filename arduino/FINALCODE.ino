const int PASpin = 3;  // Replace with the appropriate pin number
const int intermediatepin = 2;

volatile unsigned long pulseStartTime = 0;
volatile unsigned long prevpulseStartTime = 0;
volatile unsigned long pulseEndTime = 0;
volatile boolean pulseDetected = false;
unsigned long pulseDuration = 0;

const int lowPWMValue = 50;     // (.835 V)
const int highPWMValue = 200;   // (3.64V)

void setup() {
  //Initialize Pins   
  pinMode(A0, INPUT);
  pinMode(intermediatepin, OUTPUT);  

  pinMode(PASpin, INPUT);
  attachInterrupt(digitalPinToInterrupt(PASpin), handleInterrupt, RISING);
  Serial.begin(9600);
}

void loop() {

  bool currval = an2dig();

 if (pulseDetected) {
    //unsigned long pulseEndTime = micros();
    unsigned long pulseDuration = pulseStartTime - prevpulseStartTime;

    unsigned long frequencyx1000 = 1000000000.0 / (12.000*pulseDuration);  // Calculate frequency in Hz
     Serial.print("\nFreq: ");
    Serial.println(frequencyx1000);

    int mappedValue = map(frequencyx1000, 0, 2000, highPWMValue, lowPWMValue);  // Map frequency to 0-100 range


    Serial.print("Mapped value: ");
    Serial.println(mappedValue);

    prevpulseStartTime = pulseStartTime;
    pulseDetected = false;
  }
}

void handleInterrupt() {

  pulseStartTime = micros();
  pulseDetected = true;
}

bool an2dig(){
  int value = analogRead(A0);
  bool pasval = (value>40);
  digitalWrite(intermediatepin,pasval);

  return pasval;
}
