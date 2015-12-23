#include <Wire.h>
#include <ST7032.h>

ST7032 lcd;

void setup() {
  // put your setup code here, to run once:
  lcd.setContrast(30);            // コントラスト設定
  lcd.print("hello, world!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
