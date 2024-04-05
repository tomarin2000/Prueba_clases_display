#ifndef DisplayLCD_h
  #define DisplayLCD_h
  //#include "LiquidCrystal_I2C.h"    // clases display LCD
  //#include "TM1637.h"               // clases display LEDs
  #include "Control.h"

  //class DisplayLCD : public LiquidCrystal_I2C 
  class DisplayLCD : public A1 {
   //private:
   //   LiquidCrystal_I2C lcdDisp;
   //using LiquidCrystal_I2C::LiquidCrystal_I2C;

   public:
      DisplayLCD(int x, int y, int z);
      //DisplayLCD(uint8_t lcd1_Addr,uint8_t lcd1_cols,uint8_t lcd1_rows);
      //LiquidCrystal_I2C lcdDisp;
      // funciones (metodos) para display LCD
      void clear(void);
      void check(int);
      
  };

#endif
