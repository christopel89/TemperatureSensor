#include <OneWire.h>  

OneWire ds(2); 
#define BUZZER 6

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  float temp = get_temperature();
  Serial.print("C = ");
  Serial.println(temp);
  
  if(temp > 31)  {
    tone(BUZZER, 400);
    delay(100);
    noTone(BUZZER);
    delay(100);
  }
}
float get_temperature() {
  byte i;
  byte present = 0;

  byte data[12];
  byte addr[8];
  float Temp;

  if (!ds.search(addr)) {
    ds.reset_search();
    return;
  }
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion
  delay(1000);

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad

  for (i = 0; i < 9; i++) { 
    data[i] = ds.read();
  }
  
   
  Temp=(data[1]<<8)+data[0];
  Temp=Temp/16;

  return Temp;
}
