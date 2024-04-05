#include "control.h"


DisplayLCD::DisplayLCD(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows) : lcdDisp(lcd_Addr, lcd_cols, lcd_rows)
{ }
/*   
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
    }
    print("----");
}
 */  

