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
      String keyAddres = inputStr.substring(10, 12);
      int addres = inputStr.substring(13).toInt(); // Преобразуем строку в число
      if (key == "-r") {
        readEeprom(keyAddres, addres);
      } else if (key == "-e") {
        clearEeprom(keyAddres, addres);
      } else if (key == "-w") {
        int vIndex = inputStr.indexOf("-v"); // Узнаем с какой позиции начинается "-v"
        String keyValue = inputStr.substring(vIndex, vIndex + 2);
        int writeValue = inputStr.substring(vIndex + 3).toInt();
        writeEeprom(keyAddres, addres, keyValue, writeValue);
      } else if (key == "-d") {
        writeDump();
      } else {
        Serial.println("Ошибка: Неверная команда");
      }
    } else {
      Serial.println("Ошибка: Неверная команда");
    }
  }
}


//Функция для чтения ячейки памяти
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


// Функция для очистки ячейки памяти
void clearEeprom(String s, int address) {
  if (s == "-a") {
    EEPROM.write(address, 0);
    Serial.print("Значение по адресу ");
    Serial.print(address);
    Serial.print(": ");
    Serial.println("Успешно стерто");
  } else {
    Serial.println("Ошибка: Неверная команда");
  }
}

// Функция для записи ячейки памяти
void writeEeprom(String s, int address, String kV, int wV) {
  if (s == "-a" && kV == "-v") {
    EEPROM.write(address, wV);
    Serial.print("Значение по адресу ");
    Serial.print(address);
    Serial.print(": ");
    Serial.println("Успешно записано");
  } else {
    Serial.println("Ошибка: Неверная команда");
  }
}

void writeDump() {
  for (int i = 0; i < EEPROM.length(); i++) {
    if (i % 8 == 0) {
      if (i > 0) {
        Serial.println();
      }
      printDecimalAddress(i);
      Serial.print(" : ");
    }
    int value = EEPROM.read(i);
    if (value < 16) Serial.print("0"); // Добавляем ноль перед однозначными числами
    Serial.print(value, HEX);
    Serial.print(" ");
  }
  Serial.println(); // Добавляем перенос строки
  Serial.println("Дамп завершен");
}

void printDecimalAddress(int address) {
  char buffer[5];
  sprintf(buffer, "%04d", address); // Форматируем адрес с ведущими нулями (4 символа)
  Serial.print(buffer);
}
