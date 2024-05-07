#include "control.h"



//-----------------------  DEFINICIONES PARA CARACTERES GRANDES  (2X3)    ----------------------------------------------

#define B 0x20
#define FF 0xFF
#define C 0xA5

//custom characters
byte cc1[8] = {0x07,0x0F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}; //binarycode
byte cc2[8] = {0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00};
byte cc3[8] = {0x1C,0x1E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
byte cc4[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x0F,0x07};
byte cc5[8] = {0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F};
byte cc6[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1E,0x1C};
byte cc7[8] = {0x1F,0x1F,0x1F,0x00,0x00,0x00,0x1F,0x1F};
byte cc8[8] = {0x1F,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F};

// 0 1 2 3 4 5 6 7 8 9
char bn1[] = {
  1, 2, 3,  2, 3, B,  2, 7, 3,  2, 7, 3,  4, 5, FF, FF, 7, 7,  1, 7, 7,  2, 2, 6,  1, 7, 3,  1, 7, 3
};
char bn2[] = {
  4, 5, 6,  B, FF, B,  1, 8, 8,  5, 8, 6,  B, B, FF,  8, 8, 6,  4, 8, 6,  B, 1, B,  4, 8, 6,  5, 5, 6
};

//-----------------------  FIN DEFINICIONES PARA CARACTERES GRANDES  (2X3)    ------------------------------------------



DisplayLCD::DisplayLCD(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows) : lcdDisp(lcd_Addr, lcd_cols, lcd_rows)
{ 
  #ifdef EXTRADEBUG
   Serial.printf( "soy el Constructor de DisplayLCD numeros pasados: 0x%x %d %d\n", lcd_Addr , lcd_cols , lcd_rows );
  #endif
}  


void DisplayLCD::initLCD() {
  LOG_TRACE("");
  lcdDisp.init();
  clear();
  backlight();

  DefineLargeChar(); // Create the custom characters

  setCursor(5, 0);
  print("Ardomo Aqua");
  setCursor(3, 2);
  print("Inicializando");
}

void DisplayLCD::clear()
{
  LOG_TRACE("");
  lcdDisp.clear();
}

void DisplayLCD::setCursor(uint8_t col, uint8_t row)
{
  LOG_DEBUG("COLUMNA: ", col, "FILA:" ,row);
  lcdDisp.setCursor(col, row);
}

void DisplayLCD::backlight()
{
  lcdDisp.backlight();
}

void DisplayLCD::nobacklight()
{
  lcdDisp.noBacklight();
}

void DisplayLCD::display()
{
  lcdDisp.display();
}

void DisplayLCD::noDisplay()
{
  lcdDisp.noDisplay();
}

void DisplayLCD::setBacklight(bool value)				// alias for backlight() and nobacklight()
{
  lcdDisp.setBacklight(value);
}

void DisplayLCD::print(const char * text) {
  lcdDisp.print(text);
}

void DisplayLCD::check()
{
  clear();
  lcdDisp.print("----");
}


void DisplayLCD::blinkLCD(const char *textDisplay,int veces) //muestra texto recibido parpadeando n veces
{
    for (int i=0; i<veces; i++) {
      clear();
      delay(500);
      setCursor(7, 0);
      lcdDisp.print(textDisplay);
      delay(500);
    }
}

void DisplayLCD::blinkLCD(int veces) //parpadea contenido actual de la pantalla n veces
{
  if(veces) {                       
    // parpadea pantalla n veces
      for (int i=0; i<veces; i++) {
        lcdDisp.noDisplay(); // setBacklight(OFF);
        delay(DEFAULTBLINKMILLIS);
        lcdDisp.display(); // setBacklight(ON);
        delay(DEFAULTBLINKMILLIS);
      }
  }
}

void DisplayLCD::infoEstado(const char *estado) {
    LOG_TRACE("");
    infoEstadoI(estado, "");
}    

void DisplayLCD::infoEstado(const char *estado,  const char *zona) {
    LOG_TRACE("");
    infoEstadoI(estado, zona);
}    

void DisplayLCD::infoEstadoI(const char *estado, const char *zona) {
    LOG_DEBUG("[infoEstado] Recibido: ", estado, "ZONA: ", zona);
    lcdDisp.display();   // por si estuviera noDisplay por PAUSE
    setCursor(0, 0);
    lcdDisp.print(_blankline);
    setCursor(0, 0);
    lcdDisp.print(estado);
    setCursor(11, 0);
    lcdDisp.print(zona);
}    

void DisplayLCD::infoEstado2(const char* info2, int size) {
    LOG_DEBUG("[infoEstado2] Recibido: %s longitud: %d \n", info2, size);
    setCursor(0, 1);
    lcdDisp.print(_blankline);
    setCursor(0, 1);
    lcdDisp.print(verify(info2, size));
}    

void DisplayLCD::infoEstado2(const char* info2) {
    LOG_DEBUG("[infoEstado2] Recibido: %s \n", info2);
    //clear();
    setCursor(0, 1);
    lcdDisp.print(_blankline);
    setCursor(0, 1);
    lcdDisp.print(info2);
}    

void DisplayLCD::infoEstado2(const char* grupo, const char* info) {
    LOG_DEBUG("[infoEstado2] Recibido: %s \n", grupo);
    //clear();
    setCursor(0, 1);
    lcdDisp.print(_blankline);
    setCursor(0, 1);
    lcdDisp.print(grupo);
}    

// muestra info (hasta un maximo de 20 caracteres) en la linea pasada (1, 2 ,3 o 4)
void DisplayLCD::info20(char* info, int line) {
    int size = strlen(info) - 1;
    Serial.printf("[infoEstado 20] Recibido: %s de longitud: %d  \n", info, size);
    if(size>LCDMAXLEN) info[20] = 0x0; 
    info20(info, line, size);
}    

// muestra info (seran ya un maximo de 20 caracteres) en la linea pasada (1, 2 ,3 o 4)
void DisplayLCD::info20(const char* info, int line, int size) {
    Serial.printf("[infoEstado 20] Recibido: %s longitud: %d linea: %d \n", info, size, line);
    setCursor(0, line-1);
    lcdDisp.print(_blankline);
    setCursor(0, line-1);
    lcdDisp.print(info);
    //lcdDisp.print(verify(info, size));
}    


void DisplayLCD::info(const char *textDisplay) {
    Serial.print(F("[LCD.info] Recibido: "));Serial.println(textDisplay);
    clear();
    setCursor(0, 0);
    lcdDisp.print(textDisplay);
}

void DisplayLCD::info(const char *textDisplay, int dnum, int btype, int bnum) {
    Serial.printf("[LCD.info] Recibido: %s blink=%d \n", textDisplay, dnum);
    clear();
    setCursor(0, 0);
    lcdDisp.print(textDisplay);
    #ifndef displayLED
      if (btype == LONGBIP) longbip(bnum);
      if (btype == BIP) bip(bnum);
      if (btype == BIPOK) bipOK();
      if (btype == BIPKO) bipKO();
    #endif
    if(dnum) lcd.blinkLCD(dnum);
}


void DisplayLCD::displayTime(uint8_t minute, uint8_t second)
{
   displayTime(minute, second, LCDBIGCOL, LCDBIGROW);
}

void DisplayLCD::displayTime(uint8_t minute, uint8_t second, uint8_t col, uint8_t line) 
{
  printTwoNumber(minute, col, line);
  printColons(col+6, line);
  printTwoNumber(second, col+7, line);
}



void DisplayLCD::DefineLargeChar()    // send custom characters to the display 
{ 
    lcdDisp.createChar(1, cc1);
    lcdDisp.createChar(2, cc2);
    lcdDisp.createChar(3, cc3);
    lcdDisp.createChar(4, cc4);
    lcdDisp.createChar(5, cc5);
    lcdDisp.createChar(6, cc6);
    lcdDisp.createChar(7, cc7);
    lcdDisp.createChar(8, cc8);
}

void DisplayLCD::printTwoNumber(uint8_t number, uint8_t position, uint8_t line)  // muestra dos digitos en bigchar
{
  // Print position is NO hardcoded
  int digit0; // To represent the ones
  int digit1; // To represent the tens
  digit0 = number % 10;
  digit1 = number / 10;

  // Line 1 of the two-digit number
  //lcdDisp.setCursor(position, 0);
  lcdDisp.setCursor(position, line);  //linea superior 1 = segunda linea
  lcdDisp.write(bn1[digit1 * 3]);
  lcdDisp.write(bn1[digit1 * 3 + 1]);
  lcdDisp.write(bn1[digit1 * 3 + 2]);
  //lcdDisp.write(B); // Blank
  lcdDisp.write(bn1[digit0 * 3]);
  lcdDisp.write(bn1[digit0 * 3 + 1]);
  lcdDisp.write(bn1[digit0 * 3 + 2]);

  // Line 2 of the two-digit number
  //lcdDisp.setCursor(position, 1);
  lcdDisp.setCursor(position, line+1);  //linea inferior 2 = tercera linea
  lcdDisp.write(bn2[digit1 * 3]);
  lcdDisp.write(bn2[digit1 * 3 + 1]);
  lcdDisp.write(bn2[digit1 * 3 + 2]);
  //lcdDisp.write(B); // Blank
  lcdDisp.write(bn2[digit0 * 3]);
  lcdDisp.write(bn2[digit0 * 3 + 1]);
  lcdDisp.write(bn2[digit0 * 3 + 2]);
}

void DisplayLCD::printColons(uint8_t position, uint8_t line)
{
  lcdDisp.setCursor(position, line);
  lcdDisp.write (C);
  lcdDisp.setCursor(position, line+1);
  lcdDisp.write (C);
}

void DisplayLCD::printNoColons(uint8_t position, uint8_t line)
{
  lcdDisp.setCursor(position, line);
  lcdDisp.write (B);
  lcdDisp.setCursor(position, line+1);
  lcdDisp.write (B);
}

const char* DisplayLCD::verify(const char* info2, int msgl)
{
  if (msgl > 0 && msgl < MAXBUFF) return info2;
  else return "msg muy largo";
}
