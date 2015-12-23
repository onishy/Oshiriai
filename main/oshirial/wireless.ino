void sendWireless(decode_results *results)
{
  // Check if the buffer overflowed
  if (results->overflow) {
    Serial.println("IR code too long. Edit IRremoteInt.h and increase RAWLEN");
    return;
  }

  wirelessComm(results->value);
}

void wirelessComm(unsigned long value)
{
  
}

