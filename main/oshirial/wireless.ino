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
//  unsigned long id = 3310209325;
  String postData = "name=show_me_tech&id=" + String(value);
//  Serial.println(value);
  Serial.print("POST /follow HTTP/1.1\r\n");
  Serial.print("HOST: 160.16.123.31\r\n");
  Serial.print("Cache-Control: no-cache\r\n");
  Serial.print("Content-Type: application/x-www-form-urlencoded\r\n");
  Serial.print("Content-Length: " + String(postData.length()) + "\r\n\r\n");
  Serial.print(postData);
}

unsigned long encodeWeather(float temp, String weather)
{
  int type = 4;
  if(weather == "Clear") {
    type = 0;
  } else if(weather == "Clouds") {
    type = 1;
  } else if(weather == "Rain") {
    type = 2;
  } else if(weather == "Snow") {
    type = 3;
  }

  unsigned long result = type * 1000 + (int)(temp * 10);
  return result;
}

unsigned long getWeatherInfo()
{

  Serial.print("GET /weather HTTP/1.1 \r\n");
  Serial.print("host: tk2-237-28277.vs.sakura.ne.jp\r\n\r\n");
  String s = "";
  char c;
  while(Serial.available())
  {
    c = char(Serial.read());
    s += c;
    // Serial.print(char(Serial.read()));
    delay(1);
  }
  // Serial.print(s.substring(s.length()-4));
  delay(100);
  int num = s.substring(s.length()-4).toInt();
  // Serial.print(num, DEC);
  return (unsigned long) num;
//  return 2254;
}
