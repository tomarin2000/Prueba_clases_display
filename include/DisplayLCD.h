#ifndef DisplayLCD_h
  #define DisplayLCD_h
  #include "LiquidCrystal_I2C.h"    // clases display LCD
  #include "TM1637.h"               // clases display LEDs
  #include "Control.h"

  class DisplayLCD : public LiquidCrystal_I2C 
  {
   //private:
   //   LiquidCrystal_I2C lcdDisp;
   //using LiquidCrystal_I2C::LiquidCrystal_I2C;

   public:
      LiquidCrystal_I2C lcdDisp;
      DisplayLCD(uint8_t lcd1_Addr,uint8_t lcd1_cols,uint8_t lcd1_rows);
      // funciones (metodos) para display leds 7 segmentos
      void printRaw(uint8_t *);
      void print(const char *);
      void print(int);
      void printTime(int,int);
      void blink(int);
      void clearDisplay(void);
      void check(int);
      void refreshDisplay(void);
      // funciones (metodos) para display LCD
      void clear(void);
      
  };

#endif
