/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

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

