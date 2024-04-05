#define __MAIN__
#include "Control.h"



/*----------------------------------------------*
 *               Setup inicial                  *
 *----------------------------------------------*/
void setup()
{
  #ifdef RELEASE
                NONETWORK=false; 
                VERIFY=true; 
  #endif
  #ifdef DEVELOP
                NONETWORK=true;
                VERIFY=true; 
  #endif
  #ifdef DEMO
                NONETWORK=true;
                VERIFY=false;
  #endif

  Serial.begin(115200);
  Serial.println("\n\n PRUEBAS CLASES" + String(VERSION) + "    Built on " __DATE__ " at " __TIME__ );
  initWire();
  //Para el display
  #ifdef DEBUG
   Serial.println(F("Inicializando displays"));
  #endif
  display = new Display(DISPCLK,DISPDIO);
  display->clearDisplay();
  initLCD();
  //Para el Configure le paso (encoder y ?) display porque lo usara.
  #ifdef DEBUG
   Serial.println(F("Inicializando Configure"));
  #endif
  configure = new Configure(display);
  
  check();          //Chequeo de display
  refreshTime();

  #ifdef TRACE
    Serial.println(F("TRACE: ending setup"));
  #endif
}


/*----------------------------------------------*
 *            Bucle principal                   *
 *----------------------------------------------*/

void loop()
{


}

              /*----------------------------------------------*
              *                 Funciones                    *
              *----------------------------------------------*/


void initWire() {

  Wire.begin(I2C_SDA, I2C_SCL, I2C_CLOCK_SPEED);     // primer bus I2C para la pantalla lcd
  Wire1.begin(I2C_SDA1, I2C_SCL1, I2C_CLOCK_SPEED);  // segundo bus I2C para los MCPs
}

/**---------------------------------------------------------------
 * Chequeo de perifericos
 */
void check(void)
{
  display->print("----");
    #ifdef TRACE
    Serial.println(F("TRACE: in display check"));
    #endif
  display->check(1);
}



void blinkPauseError()
{
  if (!displayOff) {
    if (millis() > lastBlinkPause + DEFAULTBLINKMILLIS) {
      display->print(errorText);
      displayOff = true;
      lastBlinkPause = millis();
    }
  }
  else {
    if (millis() > lastBlinkPause + DEFAULTBLINKMILLIS) {
      refreshTime();
      displayOff = false;
      lastBlinkPause = millis();
    }
  }
}


void StaticTimeUpdate(void)
{
  if (Estado.estado == ERROR) return; //para que en caso de estado ERROR no borre el código de error del display
  if (minutes < MINMINUTES) minutes = MINMINUTES;
  if (minutes > MAXMINUTES) minutes = MAXMINUTES;
  display->printTime(minutes, seconds);
  #ifdef displayLCDStaticTimeUpdate
    //if(prevseconds != seconds || prevminutes != minutes) displayTimer(minutes, seconds, 7, 2); //LCD solo se actualiza si cambia
    prevseconds = seconds;  //LCD
    prevminutes = minutes;  //LCD
  #endif  
}


void refreshDisplay()
{
  display->refreshDisplay();
}


void refreshTime()
{
  unsigned long curMinutes = 33;
  unsigned long curSeconds = 33;
  display->printTime(curMinutes,curSeconds);
  #ifdef displayLCDrefreshTime
    //if(prevseconds != curSeconds) displayTimer(curMinutes, curSeconds, 7, 2); //LCD solo se actualiza si cambia
    prevseconds = curSeconds;  //LCD
  #endif  

}


/**
 * @brief muestra en el display texto informativo y suenan bips de aviso
 * 
 * @param textDisplay = texto a mostrar en el display
 * @param dnum = veces que parpadea el texto en el display
 * @param btype = tipo de bip emitido
 * @param bnum = numero de bips emitidos
 */
void infoDisplay(const char *textDisplay, int dnum, int btype, int bnum) {
  #ifdef displayLED
    display->print(textDisplay);
    if (btype == LONGBIP) longbip(bnum);
    if (btype == BIP) bip(bnum);
    if (btype == BIPOK) bipOK();
    if (btype == BIPKO) bipKO();
    display->blink(dnum);
  #endif
  #ifdef displayLCD
    //infoLCD(textDisplay, dnum, btype, bnum);
  #endif
}



/**---------------------------------------------------------------
 * pasa a estado ERROR
 */
void statusError(uint8_t errorID) 
{
  strcpy(errorText, "Err");    
  Estado.estado = ERROR;
  Estado.fase = errorID;
  if (errorID == E0) strcpy(errorText, "Err0");
  else sprintf(errorText, "Err%d", errorID);
  Serial.printf("[statusError]: %s \n", errorText);
  display->print(errorText);
  bipKO();
  if (errorID == E5) longbip(5); // resaltamos error al parar riego
}


  /**---------------------------------------------------------------
   * lectura del puerto serie para debug
   */
  void leeSerial() 
  {
    if (Serial.available() > 0) {
      // lee cadena de entrada
      String inputSerial = Serial.readString();
      int inputNumber = inputSerial.toInt();
      if ((!inputNumber || inputNumber>6) && inputNumber != 9) {
          Serial.println(F("Teclee: "));
          Serial.println(F("   1 - simular error NTP"));
          Serial.println(F("   2 - simular error apagar riego"));
          Serial.println(F("   3 - simular error encender riego"));
          Serial.println(F("   4 - simular EV no esta ON en Domoticz"));
          Serial.println(F("   5 - simular EV no esta OFF en Domoticz"));
          Serial.println(F("   6 - simular error al salir del PAUSE"));
          Serial.println(F("   9 - anular simulacion errores"));
      }
      switch (inputNumber) {
            case 1:
                Serial.println(F("recibido:   1 - simular error NTP"));
                timeOK = false;
                break;
            case 2:
                Serial.println(F("recibido:   2 - simular error apagar riego"));
                simular.ErrorOFF = true;
                break;
            case 3:
                Serial.println(F("recibido:   3 - simular error encender riego"));
                simular.ErrorON = true;
                break;
            case 4:
                Serial.println(F("recibido:   4 - simular EV no esta ON en Domoticz"));
                simular.ErrorVerifyON = true;
                break;
            case 5:
                Serial.println(F("recibido:   5 - simular EV no esta OFF en Domoticz"));
                simular.ErrorVerifyOFF = true;
                break;
            case 6:
                Serial.println(F("recibido:   6 - simular error al salir del PAUSE"));
                simular.ErrorPause = true;
                break;
            case 9:
                Serial.println(F("recibido:   9 - anular simulacion errores"));
                timeOK = true;                         
                simular.all_simFlags = false;
      }
    }
  }

