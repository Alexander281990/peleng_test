#include <EEPROM.h>

void setup() {
  Serial.begin(9600);


}

void loop() {
  if (Serial.available() > 0) {
    String inputStr = Serial.readString();
    inputStr.trim();
    
    if (inputStr.startsWith("eeprom ")) {
      handleFunction(inputStr.substring(7));
    } else {
      Serial.println("Ошибка: Неверная команда");
    }
  }

}

void handleFunction(String str) {

  Serial.print(str);
  
}
