#include <EEPROM.h>
#include <charMap.h>
#include <GyverOLED.h>
#include <icons_7x7.h>
#include <icons_8x8.h>

GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;

int count_click = 0;
//int eeprom_read = 0;

void setup() {
  pinMode(12, OUTPUT);
  pinMode(11, INPUT);
  pinMode(10, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(10, LOW);

  pinMode(4, OUTPUT);
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(2, LOW);

  Serial.begin(9600);
  
  oled.init();

  count_click = EEPROM.read(0);
  printScale(count_click);

}

void loop() {
  
  if(digitalRead(11) == 1) {
    count_click ++;
    printScale(count_click);
    delay(150);
  }
  if(digitalRead(3) == 1) {
    EEPROM.update(0, count_click);
  }


}


void printScale(int x) {
  oled.clear();
  oled.setScale(2);
  oled.setCursor(0, 0);
  oled.print(x);
  oled.update();
}
