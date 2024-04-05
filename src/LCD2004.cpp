#if NOUSAR

#include "Control.h"



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


void displayTimer(uint8_t minute, uint8_t second, uint8_t col, uint8_t line) {
  printTwoNumber(minute, col, line);
  printColons(col+6, line);
  printTwoNumber(second, col+7, line);
}

#endif
