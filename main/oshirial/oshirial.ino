#include <IRremote.h>

// wink detect
int sensorPin = A0;    // select the input pin for the Photoreflector
int sensorValueIn = 0;  // variable to store the value coming from the sensor

int prev_sensorValueIn = 0;
int threshold = 100;

// send
IRsend irsend;

// receive
int khz = 38; // 38kHz carrier frequency for the NEC protocol
int recvPin = 11;
IRrecv irrecv(recvPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();  // Start the receiver
}

int wait_cnt = 0;
unsigned long prev_time = 0;
void loop() {
  // Receive first
  decode_results  results;        // Somewhere to store the results

  while (irrecv.decode(&results)) {  // Grab an IR code
    dumpInfo(&results);           // Output the results
    dumpRaw(&results);            // Output the results in RAW format
    dumpCode(&results);           // Output the results as source code
    Serial.println("");           // Blank line between entries
    irrecv.resume();              // Prepare for the next value

    sendWireless(&results);
  }

  if(millis() > prev_time + 1000) {
    prev_time = millis();
    sensorValueIn = analogRead(sensorPin);  // put the value from the sensor
    int diff = sensorValueIn - prev_sensorValueIn;
//    Serial.println(diff);   // show the sensor's value on the terminal
  
    if(diff > threshold){
      Serial.println("Wink detected!");
      for(int i = 0; i < 5; i++) {
        irsend.sendSony(1145141919, 32);
        delay(500);    
      }
      irrecv.enableIRIn();
    }
    threshold = sensorValueIn / 20;
    prev_sensorValueIn = sensorValueIn;
  }
}
