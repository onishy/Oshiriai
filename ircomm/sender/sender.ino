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
  Serial.println(1145141919);
  irsend.sendSony(1145141919, 32);

  delay(1000);
}

void sendString(unsigned char* str, int len)
{
  unsigned char *data_char = (unsigned char*)calloc(sizeof(unsigned char), len);
  for(int i = 0; i < len; i++) {
    data_char[i] = str[i];
  }
  
  unsigned long *data = (unsigned long*)data_char;
  for(int i = 0; i < 1+len/8; i++) {
    irsend.sendSony(data[i], 32);
  }
  free(data_char);
}

