#include <LiquidCrystal.h>

const int A_PIN = 0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte CH_0[8] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
};

const byte CH_1[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};

const byte CH_2[8] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
};

const byte CH_3[8] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
};

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

 lcd.createChar(0, CH_0);
 lcd.createChar(1, CH_1);
 lcd.createChar(2, CH_2);
 lcd.createChar(3, CH_3);
 lcd.begin(16, 2);
 lcd.print("Hello, World!");
}

void loop() {
  // put your main code here, to run repeatedly:
  //int x = analogRead(A_PIN_X) * (5000/1023);
  int v = analogRead(A_PIN);// * (14/1023);

  lcd.setCursor(0, 0);
  lcd.print("[");
  int i = 0;
  for (; i < v; i++) {
    lcd.print("|");
  }
  for (; i < 14; i++) {
    lcd.print(" ");
  }
  lcd.print("]");

  lcd.setCursor(0, 1);
  lcd.print(analogRead(A_PIN));
  lcd.print(" ");
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.write(byte(255));
}
