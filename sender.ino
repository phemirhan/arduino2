#include <SPI.h>
#include <LoRa.h> 
int potx = A0;
int poty = A1;
 
void setup() {
  Serial.begin(9600);
  pinMode(potx,INPUT);
  pinMode(poty,INPUT);

  while (!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
 
void loop() {

  int x = map(analogRead(potx),0,1024,0,255);
  int y = map(analogRead(poty),0,1024,0,255);
  String a = String(x)+"-"+String(y);
  //Serial.println(a);

  LoRa.beginPacket();
  LoRa.print(a);

  LoRa.endPacket();
  delay(50);
 

}