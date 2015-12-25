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
  float temp = (data % 1000) / 10.0;

  String typeStr;
  switch(type) {
    case 0: typeStr = "Clear"; break;
    case 1: typeStr = "Cloud"; break;
    case 2: typeStr = "Rain"; break;
    case 3: typeStr = "Snow"; break;
    case 4: typeStr = "Mist"; break;
    default: typeStr = "Unknown Weather";
  }
  String tempStr = String(temp);

  lcd.setCursor(0,0);
  lcd.print(typeStr);
  lcd.setCursor(0,1);
  lcd.print(tempStr+" C");
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(8, 2);
  lcd.setContrast(30);            // コントラスト設定
////  lcd.print("hello, world!");
//  lcd.setCursor(0,1);
//  lcd.print("hemi!");
}

unsigned long prev_time = 0;
unsigned long set_time = 0;
void loop() {
  // put your main code here, to run repeatedly:
  // Receive first
  decode_results  results;        // Somewhere to store the results

  unsigned long prev_data = 0;
  while (irrecv.decode(&results)) {  // Grab an IR code
    dumpInfo(&results);           // Output the results
    dumpRaw(&results);            // Output the results in RAW format
    dumpCode(&results);           // Output the results as source code
    Serial.println("");           // Blank line between entries
    irrecv.resume();              // Prepare for the next value


    if(results.decode_type == NEC) {
      Serial.print("Detected Signal!: ");
      if(prev_data != results.value) {
        prev_data = results.value;
        Serial.println(results.value);
        displayWeatherData(results.value);
        set_time = millis();     
      }
//      displayWeatherData(0254);
    }
  }

  if(millis() > prev_time + 500) {
    prev_time = millis();
    irsend.sendNEC(111, 32);
    irrecv.enableIRIn();
  }

  if(millis() > set_time + 2000) {
    prev_data = 0;
  }
  if(millis() > set_time + 5000) {
    prev_data = 0;
    lcd.clear();
  }

}
