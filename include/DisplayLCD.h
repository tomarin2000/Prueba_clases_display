#ifndef DisplayLCD_h
  #define DisplayLCD_h
  #include "Control.h"

  //class DisplayLCD : public LiquidCrystal_I2C 
  class DisplayLCD
  {
   private:
      LiquidCrystal_I2C lcdDisp;
      bool _displayOff;
      unsigned long _lastBlinkPause;
      void DefineLargeChar(void);
      void printTwoNumber(uint8_t , uint8_t , uint8_t );
      void printColons(uint8_t , uint8_t);
      void printNoColons(uint8_t , uint8_t);

   public:
      DisplayLCD(uint8_t lcd1_Addr,uint8_t lcd1_cols,uint8_t lcd1_rows);
      // funciones (metodos) para display LCD
      void initLCD(void);
      void blinkLCD(const char *,int);
      void blinkLCD(int);
      void clear(void);
      void check(int);
      void print(const char *);
      void print(int);
      void setCursor(uint8_t, uint8_t);
      void setBacklight(bool);				// alias for backlight() and nobacklight()
      void backlight(void);
      void nobacklight(void);
      void displayTime(uint8_t minute, uint8_t second, uint8_t col, uint8_t line);
      void displayWiFi(void);
      void infoLCD(const char *, int , int , int );
  };

#endif  /*DisplayLCD_h*/
