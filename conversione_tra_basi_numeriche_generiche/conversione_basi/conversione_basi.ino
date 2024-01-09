#include <Keypad.h>
#include <LiquidCrystal.h>

// Keypad
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {7, 6, 5, 4};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
///////

// Display
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
///////

long num=0;

char hexSymbolConvert(int number) {
  if (number >= 0 && number <= 9) {
    return '0' + number;
  } else {
    switch (number) {
      case 10:
        return 'A';
      case 11:
        return 'B';
      case 12:
        return 'C';
      case 13:
        return 'D';
      case 14:
        return 'E';
      case 15:
        return 'F';
    }
  }
}

void convert(long num, int base) {
  char tmp_output[17] = {0};
  char output[17] = {0};
  int idx = 0;

  long quoziente = num;
  int resto;

  while (quoziente != 0) {
    resto = quoziente % base;
    tmp_output[idx++] = hexSymbolConvert(resto);

    quoziente = quoziente / base;
  }
  tmp_output[idx] = '\0';
  
  for (int i=0; i<idx; ++i) {
    output[idx-1-i] = tmp_output[i];
  }
  output[idx] = '\0';

  //Serial.println(output);

  clearConv();
  lcd.setCursor(0, 1);
  lcd.print(output);
}

void clearAll() {
  num = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(0);
}

void clearConv() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(num);
}

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  clearAll();
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    if (key == 'A') {
      convert(num, 2);
    } else if (key == 'B') {
      convert(num, 8);
    } else if (key == 'C') {
      convert(num, 16);
    } else if (key == 'D') {
      convert(num, 6);
    } else if (key == '*') {
      clearAll();
    } else {
      num = (key - '0') + num * 10;

      lcd.setCursor(0, 0);
      lcd.print(num);
    }
  }
}
