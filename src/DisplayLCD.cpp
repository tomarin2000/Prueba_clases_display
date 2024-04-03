#include "DisplayLCD.h"


//DisplayLCD::DisplayLCD(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)
DisplayLCD::DisplayLCD(uint8_t lcd1_Addr, uint8_t lcd1_cols, uint8_t lcd1_rows) : lcdDisp(lcd1_Addr, lcd1_cols, lcd1_rows)
//DisplayLCD::DisplayLCD(uint8_t lcd1_Addr, uint8_t lcd1_cols, uint8_t lcd1_rows)
{
  #ifdef EXTRADEBUG
   Serial.println(F("DISPLAYLCD: constructor"));
  #endif
  #ifdef EXTRADEBUG
   Serial.println(F("DISPLAYLCD: init"));
  #endif
  lcdDisp.init();
  #ifdef EXTRADEBUG
   Serial.println(F("DISPLAYLCD: clear"));
  #endif
  lcdDisp.clear();
  #ifdef EXTRADEBUG
   Serial.println(F("DISPLAYLCD: backlight ON"));
  #endif
  lcdDisp.backlight();
  #ifdef EXTRADEBUG
   Serial.println(F("DISPLAYLCD: exit constructor"));
  #endif
}  

void DisplayLCD::clear()
{
  lcdDisp.clear();
}

void DisplayLCD::check(int veces)
{
  uint8_t t[5];
  t[4]=0;

  for(int repeat=0;repeat<veces;repeat++)
  {
    clearDisplay();
    for(int i=0;i<10;i++)
    {
      for(int j=0;j<4;j++)
        t[j]=i;
      printRaw(t);
      delay(300);
    }
    print("----");
  }
}

