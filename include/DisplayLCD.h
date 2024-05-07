#ifndef DisplayLCD_h
  #define DisplayLCD_h
  #include "Control.h"
  #include "LiquidCrystal_I2C.h"

  #define LCDBIGROW 2           // linea por defecto para timer en numeros grandes
  #define LCDBIGCOL 7           // columna por defecto para timer en numeros grandes
  #define LCDMAXLEN 20          // numero maximo de caracteres por linea pantalla lcd
  #define MAXBUFF LCDMAXLEN+1   // tamaño maximo del buffer (mas 0 terminacion)


  class DisplayLCD
  {
   private:
      LiquidCrystal_I2C lcdDisp;
      bool _displayOff;
      unsigned long _lastBlinkPause;
      const char* _blankline = "                    ";
      const char* _info2;
      const char* verify(const char* info2, int size);
      void DefineLargeChar(void);
      void printTwoNumber(uint8_t , uint8_t , uint8_t );
      void printColons(uint8_t , uint8_t);
      void printNoColons(uint8_t , uint8_t);
      void infoEstadoI(const char *estado, const char *zona);

   public:
      //char buff[LCDMAXLEN + 1];
      DisplayLCD(uint8_t lcd1_Addr,uint8_t lcd1_cols,uint8_t lcd1_rows);
      void initLCD(void);
      void blinkLCD(const char *,int);
      void blinkLCD(int);
      void clear(void);
      void check(void);
      void print(const char *);
      void print(int);
      void setCursor(uint8_t, uint8_t);
      void setBacklight(bool);	// alias for backlight() and nobacklight()
      void backlight(void);
      void nobacklight(void);
      void display(void);        // muestra texto del display
      void noDisplay(void);      // oculta texto del display
      void displayTime(uint8_t minute, uint8_t second);
      void displayTime(uint8_t minute, uint8_t second, uint8_t col, uint8_t line);
      void info(const char *textDisplay);
      void info(const char *textDisplay, int dnum, int btype, int bnum);
      void infoEstado(const char* estado);
      void infoEstado(const char* estado, const char* zona);
      void info20(char* info, int line);
      void info20(const char* info, int line, int size);
      void infoEstado2(const char* info2);
      void infoEstado2(const char* info2, int size);
      void infoEstado2(const char* grupo, const char*  msg);
  };

#endif  /*DisplayLCD_h*/