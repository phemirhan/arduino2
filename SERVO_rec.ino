#include <Servo.h>
#include <SPI.h>
#include <LoRa.h>

int led1 = 3;
int led2 = 5;
bool z = 0;
int potx, poty;
Servo myservo,myservo2;
void setup() {
digitalWrite(7,HIGH);
myservo.attach(3);
myservo2.attach(5);
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  while (!Serial);
   cli();           // disable all interrupts
  TCCR2A = (1<<WGM21)|(0<<WGM20); // Mode CTC
  TIMSK2 = (1<<OCIE2A); // Local interruption OCIE2A
  TCCR2B = (0<<WGM22)|(1<<CS22)|(1<<CS21); // Frequency 16Mhz/ 256 = 62500
  OCR2A = 250;       //250*125 = 31250 = 16Mhz/256/2
  sei();             // enable all interrupts
pinMode(6,OUTPUT);

  Serial.println("LoRa Receiver");


  if (!LoRa.begin(433E6)) {

    Serial.println("Starting LoRa failed!");

    while (1);

  }

}
ISR(TIMER2_COMPA_vect){         // timer compare interrupt service routine
  static int counter=0;
  if (++counter >= 1250) { // 125 * 4 ms = 500 ms
    counter = 0;
    onTimer();
	digitalWrite(7,LOW);
  }
}

void loop() {
 z=0;
 String t,r;


  // try to parse packet

  int packetSize = LoRa.parsePacket();

  if (packetSize) {

    // received a packet

    //Serial.print("Received packet '");


    // read packet

    while (LoRa.available()) {

      char a= (char)LoRa.read();
     if (a == '.')
     {
       z=1;
     }
     else
     {
     if (z){
       r+=a;
     }
     else
     {
     t+=a;
     }
    }

    // print RSSI of packet

  //  Serial.print("' with RSSI ");

   // Serial.println(LoRa.packetRssi());

  }
  
  potx=t.toInt();
  poty=r.toInt();
   myservo.write(potx);  
  myservo2.write(poty);

}
 
 Serial.println(potx);
 Serial.print(poty);
 
}
