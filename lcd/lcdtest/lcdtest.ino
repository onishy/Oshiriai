#include <Wire.h>
#include <ST7032.h>
#include <IRremote.h>

ST7032 lcd;

// send
IRsend irsend;

// receive
int khz = 38; // 38kHz carrier frequency for the NEC protocol
int recvPin = 11;
IRrecv irrecv(recvPin);

void displayWeatherData(unsigned long data)
{
  int type = data / 1000;
  int temp = data % 1000;

  String typeStr;
  switch(type) {
    case 0: typeStr = "Sunny"; break;
    case 1: typeStr = "Cloudy"; break;
    case 2: typeStr = "Rainy"; break;
    default: typeStr = "Unknown Weather";
  }
  String tempStr = String(temp);

  lcd.print(typeStr + " " + tempStr);
}

void setup() {
  // put your setup code here, to run once:
  lcd.setContrast(30);            // コントラスト設定
  lcd.print("hello, world!");
}

unsigned long prev_time = 0;
void loop() {
  // put your main code here, to run repeatedly:
  // Receive first
  decode_results  results;        // Somewhere to store the results

  while (irrecv.decode(&results)) {  // Grab an IR code
    dumpInfo(&results);           // Output the results
    dumpRaw(&results);            // Output the results in RAW format
    dumpCode(&results);           // Output the results as source code
    Serial.println("");           // Blank line between entries
    irrecv.resume();              // Prepare for the next value

    if(results.decode_type == NEC) {
      displayWeatherData(results.value);
    }
  }

  if(millis() > prev_time + 500) {
    prev_time = millis();
    irsend.sendNEC(111, 32);
    irrecv.enableIRIn();
  }

}
