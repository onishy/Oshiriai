//softui 18th Jul, 2013

int sensorPin = A0;    // select the input pin for the Photoreflector
int sensorValueIn = 0;  // variable to store the value coming from the sensor

int prev_sensorValueIn = 0;
int threshold = 10;

void setup() {

  Serial.begin(9600);   // serial communication for checking the degrees 

}

void loop() {
  sensorValueIn = analogRead(sensorPin);  // put the value from the sensor
  int diff = sensorValueIn - prev_sensorValueIn;
  Serial.println(diff);   // show the sensor's value on the terminal

  if(diff > threshold){
    Serial.println("Wink detected!");
  }
  threshold = sensorValueIn / 20;
  prev_sensorValueIn = sensorValueIn;
  delay (150); // wait

}





