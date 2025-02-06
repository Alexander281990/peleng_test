#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String inputStr = Serial.readString();
    inputStr.trim();
    if (inputStr.startsWith("eeprom ")) {
      String command = inputStr.substring(7); 
      if (command.startsWith("-r -a ")) {
        int address = command.substring(6).toInt();
        readEeprom(address);
      } else if (command.startsWith("-e -a ")) {
        int address = command.substring(6).toInt();
        clearEeprom(address);
      } else if (command.startsWith("-w -a ")) {
        int addrEnd = command.indexOf(" -v ");
        if (addrEnd != -1) {
          int address = command.substring(6, addrEnd).toInt();
          int value = command.substring(addrEnd + 4).toInt();
          writeEeprom(address, value);
        } else {
          Serial.println("Ошибка: Неверная команда");
        }
      } else if (command.equals("-d")) {
        writeDump();
      } else {
        Serial.println("Ошибка: Неверная команда");
      }
    } else {
      Serial.println("Ошибка: Неверная команда");
    }
  }
}

// Функция для чтения ячейки памяти
void readEeprom(int address) {
  int value = EEPROM.read(address);
  Serial.print("Значение по адресу ");
  Serial.print(address);
  Serial.print(": ");
  Serial.println(value);
}

// Функция для очистки ячейки памяти
void clearEeprom(int address) {
  EEPROM.write(address, 0);
  Serial.print("Значение по адресу ");
  Serial.print(address);
  Serial.println(": Успешно стерто");
}

// Функция для записи ячейки памяти
void writeEeprom(int address, int value) {
  EEPROM.write(address, value);
  Serial.print("Значение по адресу ");
  Serial.print(address);
  Serial.println(": Успешно записано");
}

// Функция для вывода дампа
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
  Serial.println();
  Serial.println("Дамп завершен");
}

// Функция для вывода 4 символов перед двоеточием в выводе дампа
void printDecimalAddress(int address) {
  char buffer[5];
  sprintf(buffer, "%04d", address); // Форматируем адрес с ведущими нулями (4 символа)
  Serial.print(buffer);
}
