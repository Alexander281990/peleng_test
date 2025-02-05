#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String inputStr = Serial.readString();
    inputStr.trim(); // Убираем все пробелы в начале и конце строки
    if (inputStr.startsWith("eeprom ")) {
      String key = inputStr.substring(7, 9);
      key.trim();
      if (key == "-r") {
        String keyAddres = inputStr.substring(10, 12);
        keyAddres.trim();
        int addres = inputStr.substring(13).toInt(); // Преобразуем строку в число
        readEeprom(keyAddres, addres);
      } else {
        Serial.println("Ошибка: Неверная команда");
      }
    } else {
      Serial.println("Ошибка: Неверная команда");
    }
  }
}

void readEeprom(String s, int address) {
  if (s == "-a") {
    int value = EEPROM.read(address);
    Serial.print("Значение по адресу ");
    Serial.print(address);
    Serial.print(": ");
    Serial.println(value);
  } else {
    Serial.println("Ошибка: Неверная команда");
  }
}
