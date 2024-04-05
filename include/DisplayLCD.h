#ifndef DisplayLCD_h
  #define DisplayLCD_h
  #include "Control.h"

  //class DisplayLCD : public LiquidCrystal_I2C 
  class DisplayLCD
  {
   private:
      LiquidCrystal_I2C lcdDisp;

   public:
      DisplayLCD(uint8_t lcd1_Addr,uint8_t lcd1_cols,uint8_t lcd1_rows);
      // funciones (metodos) para display LCD
      void clear(void);
      void check(int);
      void initLCD(void);
      void print(void);
      void setCursor(uint8_t, uint8_t);
      void DefineLargeChar(void);
      void backlight(void);
      void nobacklight(void);
      void setBacklight(bool);				// alias for backlight() and nobacklight()
      void printTwoNumber(uint8_t , uint8_t , uint8_t );
      void printColons(uint8_t , uint8_t);
      void printNoColons(uint8_t , uint8_t);
      void displayTimer(uint8_t , uint8_t , uint8_t , uint8_t );
      void displayWiFi(void);
      void blinkLCD(const char *,int );
      void infoLCD(const char *, int , int , int );
  };

#endif  /*DisplayLCD_h*/
