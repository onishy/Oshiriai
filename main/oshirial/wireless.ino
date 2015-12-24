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
  String postData = "name=mazamachi&id=" + String(3310209325);
  // Serial.println(value);

  Serial.print("POST /follow HTTP/1.1\r\n");
  Serial.print("HOST: 160.16.123.31\r\n");
  Serial.print("Cache-Control: no-cache\r\n");
  Serial.print("Content-Type: application/x-www-form-urlencoded\r\n");
  Serial.print("Content-Length: " + String(postData.length()) + "\r\n\r\n");
  Serial.print(postData);
  // Serial.print("GET /weather HTTP/1.1 \r\n");
  // Serial.print("host: tk2-237-28277.vs.sakura.ne.jp\r\n\r\n");

}
