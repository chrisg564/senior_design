const int led = 10;

void setup(){
	pinMode(led, OUTPUT);
	digitalWrite(led, LOW);
}


void loop(){
   for(int k=0; k <=255; k++){
      analogWrite(led, k);
      delay(5);
      }

   for(int k=255; k >= 0; k--){
      analogWrite(led, k);
      delay(5);
      }
}