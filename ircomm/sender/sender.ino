/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

IRsend irsend;
void sendString(unsigned char* str, int len);

void setup()
{
  Serial.begin(9600);
}

void loop() {
  int khz = 38; // 38kHz carrier frequency for the NEC protocol

  irsend.sendSony(1145141919, 32);

  delay(1000);
}

void sendString(unsigned char* str, int len)
{
  unsigned int signal[len+1];
  signal[0] = 8000;
  for(int i = 0; i < len; i++) {
    signal[i+1] = 150+(str[i]-'a')*USECPERTICK*2;
  }
    
  Serial.print("Sending signal: ");
  for(int i = 0; i < len+1; i++) {
    Serial.print(signal[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
  
  irsend.sendRaw(signal, len+1, 38);
}

