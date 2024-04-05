#include "Control.h"
//#include "LiquidCrystal_I2C.h"
//#include "DisplayLCD.h"

#define B 0x20
#define FF 0xFF
#define C 0xA5

#define LCD2004_address 0x27  // direccion bus I2C

DisplayLCD lcd(LCD2004_address, 20, 4);  // 20 caracteres x 4 lineas
//lcd = new DisplayLCD(LCD2004_address, 20, 4);  // 20 caracteres x 4 lineas
//LiquidCrystal_I2C lcd(LCD2004_address, 20, 4);  // 20 caracteres x 4 lineas

int msecond, dots;

unsigned long lastSecond = millis();
unsigned long currentMillisLCD = 0;
unsigned long lastUpdateTime = 0;
unsigned long lastUpdateData = 0;

//custom characters
byte cc1[8] = {0x07,0x0F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};//binarycode
byte cc2[8] = {0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00};
byte cc3[8] = {0x1C,0x1E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
byte cc4[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x0F,0x07};
byte cc5[8] = {0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F};
byte cc6[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1E,0x1C};
byte cc7[8] = {0x1F,0x1F,0x1F,0x00,0x00,0x00,0x1F,0x1F};
byte cc8[8] = {0x1F,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F};


// send custom characters to the display


void DefineLargeChar() {
    lcd.lcdDisp.createChar(1, cc1);
    lcd.lcdDisp.createChar(2, cc2);
    lcd.lcdDisp.createChar(3, cc3);
    lcd.lcdDisp.createChar(4, cc4);
    lcd.lcdDisp.createChar(5, cc5);
    lcd.lcdDisp.createChar(6, cc6);
    lcd.lcdDisp.createChar(7, cc7);
    lcd.lcdDisp.createChar(8, cc8);
    }


void displayWiFi() {
  
  lcd.lcdDisp.clear();
  lcd.lcdDisp.print("Connecting to wifi");
  lcd.lcdDisp.setCursor(0, 1);
  //lcd.lcdDisp.print(ssid);
  delay(1000);
  lcd.lcdDisp.clear();
  lcd.lcdDisp.print("CONNECTED");
  delay(2000);
  }


// 0 1 2 3 4 5 6 7 8 9
char bn1[] = {
  1, 2, 3,  2, 3, B,  2, 7, 3,  2, 7, 3,  4, 5, FF, FF, 7, 7,  1, 7, 7,  2, 2, 6,  1, 7, 3,  1, 7, 3
};
char bn2[] = {
  4, 5, 6,  B, FF, B,  1, 8, 8,  5, 8, 6,  B, B, FF,  8, 8, 6,  4, 8, 6,  B, 1, B,  4, 8, 6,  5, 5, 6
};


void printTwoNumber(uint8_t number, uint8_t position, uint8_t line)//13
{
  // Print position is NO hardcoded
  int digit0; // To represent the ones
  int digit1; // To represent the tens
  digit0 = number % 10;
  digit1 = number / 10;

  // Line 1 of the two-digit number
  //lcd.lcdDisp.setCursor(position, 0);
  lcd.lcdDisp.setCursor(position, line);  //linea superior 1 = segunda linea
  lcd.lcdDisp.write(bn1[digit1 * 3]);
  lcd.lcdDisp.write(bn1[digit1 * 3 + 1]);
  lcd.lcdDisp.write(bn1[digit1 * 3 + 2]);
  //lcd.lcdDisp.write(B); // Blank
  lcd.lcdDisp.write(bn1[digit0 * 3]);
  lcd.lcdDisp.write(bn1[digit0 * 3 + 1]);
  lcd.lcdDisp.write(bn1[digit0 * 3 + 2]);

  // Line 2 of the two-digit number
  //lcd.lcdDisp.setCursor(position, 1);
  lcd.lcdDisp.setCursor(position, line+1);  //linea inferior 2 = tercera linea
  lcd.lcdDisp.write(bn2[digit1 * 3]);
  lcd.lcdDisp.write(bn2[digit1 * 3 + 1]);
  lcd.lcdDisp.write(bn2[digit1 * 3 + 2]);
  //lcd.lcdDisp.write(B); // Blank
  lcd.lcdDisp.write(bn2[digit0 * 3]);
  lcd.lcdDisp.write(bn2[digit0 * 3 + 1]);
  lcd.lcdDisp.write(bn2[digit0 * 3 + 2]);
}

void printColons(uint8_t position, uint8_t line)
{
  lcd.lcdDisp.setCursor(position, line);
  lcd.lcdDisp.write (C);
  lcd.lcdDisp.setCursor(position, line+1);
  lcd.lcdDisp.write (C);
}

void printNoColons(uint8_t position, uint8_t line)
{
  lcd.lcdDisp.setCursor(position, line);
  lcd.lcdDisp.write (B);
  lcd.lcdDisp.setCursor(position, line+1);
  lcd.lcdDisp.write (B);
}

void updateData() {
  lastUpdateData = millis();
}

void blinkLCD(const char *textDisplay,int veces)
{
    for (int i=0; i<veces; i++) {
      lcd.lcdDisp.clear();
      delay(500);
      lcd.lcdDisp.setCursor(7, 0);
      lcd.lcdDisp.print(textDisplay);
      delay(500);
    }
}

void infoLCD(const char *textDisplay, int dnum, int btype, int bnum) {
    Serial.print(F("[infoLCD] Recibido: "));Serial.println(textDisplay);
    lcd.lcdDisp.clear();
    lcd.lcdDisp.setCursor(7, 0);
    lcd.lcdDisp.print(textDisplay);
    for (int i=0; i<dnum; i++) {
      lcd.lcdDisp.clear();
      delay(500);
      lcd.lcdDisp.setCursor(7, 0);
      lcd.lcdDisp.print(textDisplay);
      delay(500);
    }
}

void initLCD() {

  //lcd.lcdDisp.init();
  //lcd.lcdDisp.backlight();
  //lcd.lcdDisp.clear();
  DefineLargeChar(); // Create the custom characters
  lcd.lcdDisp.setCursor(5, 0);
  lcd.lcdDisp.print("Ardomo Aqua");
  lcd.lcdDisp.setCursor(0, 2);
  lcd.lcdDisp.print("Inicializando");
  //delay(1000);
}

void displayTimer(uint8_t minute, uint8_t second, uint8_t col, uint8_t line) {
  printTwoNumber(minute, col, line);
  printColons(col+6, line);
  printTwoNumber(second, col+7, line);
}

