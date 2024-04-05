#ifndef control_h
  #define control_h
  
  #ifndef _GNU_SOURCE  // LOCAL WORK-AROUND
   #define _GNU_SOURCE // evitar error uint no definido en platformio (no en compilacion) tras update a espressif8266 3.2.0
  #endif               // ver: https://community.platformio.org/t/error-acessing-eeprom-of-esp8266-after-plattform-update/22747/2
  
    #include <Arduino.h>
    #include<iostream>
  //Para mis clases
  #include "Display.h"
  #include "Configure.h"
  #include "LiquidCrystal_I2C.h"
  #include "A1.h"
  #include "DisplayLCD.h"

  #define LCD2004_address 0x27  // direccion bus I2C
  
  #include <Wire.h>

  using namespace std;


  #ifdef DEVELOP
    //Comportamiento general para PRUEBAS . DESCOMENTAR LO QUE CORRESPONDA
    #define DEBUG
    //#define EXTRADEBUG
    #define EXTRADEBUG1
    #define TRACE
    //#define EXTRATRACE
    #define VERBOSE
  #endif

  #ifdef RELEASE
    //Comportamiento general para uso normal . DESCOMENTAR LO QUE CORRESPONDA
    //#define DEBUG
    //#define EXTRADEBUG
    //#define TRACE
    //#define EXTRATRACE
    #define VERBOSE
  #endif

  #ifdef DEMO
    //Comportamiento general para DEMO . DESCOMENTAR LO QUE CORRESPONDA
    #define DEBUG
    //#define EXTRADEBUG
    //#define TRACE
    //#define EXTRATRACE
    #define VERBOSE
  #endif

  #ifdef DEVELOP
    #define HOSTNAME "ardomot"
  #else
    #define HOSTNAME "ardomo"
  #endif  

  //#define CONFIG_LITTLEFS_SPIFFS_COMPAT 1  // modo compatibilidad con SPIFFS

  /* You only need to format LittleFS the first time you run a
   test or else use the LITTLEFS plugin to create a partition
   https://github.com/lorol/arduino-esp32littlefs-plugin */
   
  #define FORMAT_LITTLEFS_IF_FAILED true
  #ifndef clean_FS
    #define clean_FS false
  #endif
       

  //-------------------------------------------------------------------------------------
                            #define VERSION  "3.0b.1"
  //-------------------------------------------------------------------------------------

  #define xNAME true //actualiza desc de botones con el Name del dispositivo que devuelve Domoticz

  //Comportamiento General
  #define STANDBYSECS         15
  #ifdef RELEASE
    #define DEFAULTMINUTES      10
    #define DEFAULTSECONDS      0
  #endif
  #ifdef DEVELOP
    #define DEFAULTMINUTES      0
    #define DEFAULTSECONDS      10
  #endif
  #ifdef DEMO
    #define DEFAULTMINUTES      0
    #define DEFAULTSECONDS      7
  #endif
  #define DEFAULTBLINK        5
  #define DEFAULTBLINKMILLIS  500
  #define MINMINUTES          0
  #define MAXMINUTES          59  // corte automatico de seguridad a los 60 min. en los arduinos
  #define MINSECONDS          5
  #define HOLDTIME            3000
  #define MAXCONNECTRETRY     10
  #define VERIFY_INTERVAL     15
  #define DEFAULT_SWITCH_RETRIES 5
  #define DELAYRETRY          2000
  #define MAXledLEVEL         255 // nivel maximo leds on y wifi (0 a 255)
  #define DIMMLEVEL           50 // nivel atenuacion leds on y wifi (0 a 255)
  #define I2C_CLOCK_SPEED     400000  // frecuencia del bus I2C en Hz (default 100000)
  #define ROTARY_ENCODER_STEPS 4 // TODO documentar
 //----------------  dependientes del HW   ----------------------------------------

  #ifdef ESP32
    // GPIOs  I/O usables: 2 4 5 16 17 18 19 21 22 23 25 26 27 32 33  (15/15)
    // GPIOs  I/O los reservo para JTAG: 12 13 14 15
    // GPIOs    I usables: 34 35 36 39 (4/4)
    #define ENCCLK                GPIO_NUM_32
    #define ENCDT                 GPIO_NUM_33
    #define ENCSW                 100           // ficticio, no tratamos el boton del encoder con ClicEncoder, se hace por programa
    #define bENCODER              GPIO_NUM_34   // este es el real conectado a GPIO solo INPUT
    #define BUZZER                GPIO_NUM_4
    #define LEDR                  GPIO_NUM_27  
    #define LEDG                  GPIO_NUM_26 
    #define LEDB                  GPIO_NUM_25 
    #define DISPCLK               GPIO_NUM_18
    #define DISPDIO               GPIO_NUM_19
    #define I2C_SDA               GPIO_NUM_21
    #define I2C_SCL               GPIO_NUM_22
    #define I2C_SDA1              GPIO_NUM_16
    #define I2C_SCL1              GPIO_NUM_17
    #define lZONA1                1             // mcpO GPA0
    #define lZONA2                2             // mcpO GPA1
    #define lZONA3                3             // mcpO GPA2
    #define lZONA4                4             // mcpO GPA3
    #define lZONA5                5             // mcpO GPA4
    #define lZONA6                6             // mcpO GPA5
    #define lZONA7                7             // mcpO GPA6
    #define lZONA8                8             // mcpO GPA7
    #define lZONA9                9             // mcpO GPB0
    #define lGRUPO1               13            // mcpO GPB4
    #define lGRUPO2               14            // mcpO GPB5
    #define lGRUPO3               15            // mcpO GPB6
    #define lGRUPO4               16            // mcpO GPB7
    #define mcpOUT                0x20  //direccion del MCP23017 para salidas (leds)
    #define mcpIN                 0x21  //direccion del MCP23017 para entradas (botones)


  #endif

  #ifdef NODEMCU
    #define ENCCLK                D0
    #define ENCDT                 D1
    #define ENCSW                 100
    #define BUZZER                2
    #define HC595_DATA            D8
    #define HC595_LATCH           D4
    #define HC595_CLOCK           D5
    #define CD4021B_CLOCK         D5
    #define CD4021B_LATCH         D6
    #define CD4021B_DATA          D7
    #define DISPCLK               D3
    #define DISPDIO               D2

    #define LEDR                  4
    #define LEDG                  5
    #define LEDB                  3 
    #define lGRUPO1               6
    #define lGRUPO2               7
    #define lGRUPO3               8
    #define lZONA1                10
    #define lZONA2                11
    #define lZONA3                12
    #define lZONA4                13
    #define lZONA5                14
    #define lZONA6                15
    #define lZONA7                16
  #endif
 //----------------  fin dependientes del HW   ----------------------------------------


  //Para legibilidad del codigo
  #define ON  1
  #define OFF 0
  #define SHOW 1
  #define HIDE 0
  #define READ 1
  #define CLEAR 0
  #define LONGBIP 1
  #define BIP 2
  #define BIPOK 3
  #define BIPKO 4
  #define NOBLINK 0

  //Enums
  enum _estados {
    STANDBY       ,
    REGANDO       ,
    CONFIGURANDO  ,
    TERMINANDO    ,
    PAUSE         ,
    STOP          ,
    ERROR         ,
  };
  #define _ESTADOS "STANDBY" , "REGANDO" , "CONFIGURANDO" , "TERMINANDO" , "PAUSE" , "STOP" , "ERROR"

  enum _fases {
    CERO          = 0,
    E0            = 0xFF,
    E1            = 1,
    E2            = 2,
    E3            = 3,
    E4            = 4,
    E5            = 5,
  };

  enum _flags {
    ENABLED      = 0x01,
    disabled     = 0x02,  // DISABLED en mayusculas daba error al compilar por ya definido en una libreria
    ONLYSTATUS   = 0x04,
    ACTION       = 0x08,
    DUAL         = 0x10,
    HOLD         = 0x20,
  };

  //----------------  dependientes del HW   ----------------------------------------
  // ojo esta es la posición del bit de cada boton en el stream serie - no modificar -
  #ifdef ESP32
  enum _botones {
    bZONA1      = 0x0001,  // A0
    bZONA2      = 0x0002,  // A1
    bZONA3      = 0x0004,  // A2
    bZONA4      = 0x0008,  // A3
    bZONA5      = 0x0010,  // A4
    bZONA6      = 0x0020,  // A5
    bZONA7      = 0x0040,  // A6
    //          = 0x0080,  // A7  (NO USAR)
    bZONA8      = 0x0100,  // B0
    bZONA9      = 0x0200,  // B1  
    bGRUPO1     = 0x0400,  // B2
    bMULTIRIEGO = 0x0800,  // B3
    bGRUPO3     = 0x1000,  // B4
    bPAUSE      = 0x2000,  // B5
    bSTOP       = 0x4000,  // B6
    //          = 0x8000,  // B7  (NO USAR)
  };
  #endif

  #ifdef NODEMCU
  enum _botones {
    bZONA1      = 0x0001,
    bZONA2      = 0x0002,
    bZONA3      = 0x0004,
    bZONA4      = 0x0008,
    bZONA6      = 0x0010,
    bMULTIRIEGO = 0x0020,
    bZONA7      = 0x0040,
    bZONA5      = 0x0080,
    bSPARE13    = 0x0100,
    bGRUPO3     = 0x0200,
    bGRUPO1     = 0x0400,
    bSTOP       = 0x0800,
    bENCODER    = 0x1000,
    bSPARE15    = 0x2000,
    bSPARE16    = 0x4000,
    bPAUSE      = 0x8000,
  };
  #endif

  //Pseudobotones
  //#define bMULTIRIEGO   0xFF03
  #define bGRUPO2   0xFF01
  //#define bCONFIG   0xFF02

  //----------------  dependientes del HW (número, orden)  ----------------------------
    // lista de todos los botones de zonas de riego disponibles:
    // OJO! el número y orden debe coincidir con las especificadas en Boton[]
  #define _ZONAS  bZONA1 , bZONA2 , bZONA3 , bZONA4 , bZONA5 , bZONA6 , bZONA7 , bZONA8
    // lista de todos los botones (selector) de grupos disponibles:
  #define _GRUPOS bGRUPO1 , bGRUPO2 , bGRUPO3
  #define _NUMZONAS            8  // numero de zonas (botones riego individual)
  #define _NUMGRUPOS           3  // numero de grupos multirriego
 //----------------  fin dependientes del HW   ----------------------------------------

  //estructura para salvar un grupo
  struct Grupo_parm {
    uint16_t id;
    int size;
    uint16_t serie[16];  // ojo! numero de la zona, no es el boton asociado a ella
    char desc[20];
  } ;

  //estructura para salvar parametros de un boton
  struct Boton_parm {
    char  desc[20];
    uint16_t   idx;
  } ;

  //estructura para parametros configurables
  struct Config_parm {
    uint8_t   initialized=0;
    static const int  n_Zonas = _NUMZONAS; //no modificable por fichero de parámetros (depende HW) 
    Boton_parm botonConfig[n_Zonas];
    uint8_t   minutes = DEFAULTMINUTES; 
    uint8_t   seconds = DEFAULTSECONDS;
    char domoticz_ip[40];
    char domoticz_port[6];
    char ntpServer[40];
    static const int  n_Grupos = _NUMGRUPOS;  //no modificable por fichero de parámetros (depende HW)
    Grupo_parm groupConfig[n_Grupos];
  };

  // estructura de un grupo de multirriego *nueva
  // (todos son pointer al multirriego correspondiente en config menos los indicados)
  struct S_MULTI {
    uint16_t *id;        //apuntador al id del selector grupo en estructura config (bGrupo_x)
    uint16_t serie[16];  //contiene los id de los botones del grupo (bZona_x)
    uint16_t *zserie;    //apuntador a config con las zonas del grupo (Zona_x)
    int *size;           //apuntador a config con el tamaño del grupo
    int w_size;          //variable auxiliar durante ConF
    int actual;          //variable auxiliar durante un multirriego 
    char *desc;          //apuntador a config con la descripcion del grupo
  } ;

  union S_bFLAGS
  {
    uint8_t all_flags;
    struct
    {
      uint8_t enabled       : 1,
              disabled      : 1,
              onlystatus    : 1,
              action        : 1,
              dual          : 1,
              hold          : 1,
              holddisabled  : 1,
              spare0        : 1;
    };
  };

  struct S_initFlags     {
    uint8_t initParm    : 1,
            initWifi      : 1,
            spare1        : 1;
  };

  union S_simFlags
  {
    uint8_t all_simFlags;
    struct
    {
    uint8_t ErrorOFF       : 1,
            ErrorON        : 1,
            ErrorVerifyON  : 1,
            ErrorVerifyOFF : 1,
            ErrorPause     : 1;
    };
  };

  struct S_BOTON {
    uint16_t   id;
    int   estado;
    int   ultimo_estado;
    int   led;
    S_bFLAGS  flags;
    char  desc[20];
    uint16_t   idx;
  } ;

  struct S_Estado {
    uint8_t estado; 
    uint8_t fase; 
  } ;

  const uint16_t ZONAS[] = {_ZONAS};
  const uint16_t GRUPOS[]  = {_GRUPOS};
  const int NUMZONAS = sizeof(ZONAS)/sizeof(ZONAS[0]); // (8) numero de zonas (botones riego individual)
  const int NUMGRUPOS = sizeof(GRUPOS)/sizeof(GRUPOS[0]); // (3) numero de grupos multirriego
  const char nEstado[][15] = {_ESTADOS};

   //Globales a todos los módulos
  #ifdef __MAIN__

    S_BOTON Boton [] =  { 
      //ID,          S   uS  LED          FLAGS                             DESC          IDX
      {bZONA1   ,   0,  0,  lZONA1   ,   ENABLED | ACTION,                 "ZONA1",       0},
      {bZONA2 ,     0,  0,  lZONA2 ,     ENABLED | ACTION,                 "ZONA2",       0},
      {bZONA3    ,  0,  0,  lZONA3    ,  ENABLED | ACTION,                 "ZONA3",       0},
      {bZONA4    ,  0,  0,  lZONA4    ,  ENABLED | ACTION,                 "ZONA4",       0},
      {bZONA5    ,  0,  0,  lZONA5    ,  ENABLED | ACTION,                 "ZONA5",       0},
      {bZONA6 ,     0,  0,  lZONA6 ,     ENABLED | ACTION,                 "ZONA6",       0},
      {bZONA7  ,    0,  0,  lZONA7  ,    ENABLED | ACTION,                 "ZONA7",       0},
      {bZONA8  ,    0,  0,  lZONA8  ,    ENABLED | ACTION,                 "ZONA8",       0},
      {bZONA9,      0,  0,  0,           disabled,                         "spare9",      0},
      {bMULTIRIEGO, 0,  0,  0,           ENABLED | ACTION,                 "MULTIRIEGO",  0},
      {bGRUPO1,     0,  0,  lGRUPO1,     ENABLED | ONLYSTATUS | DUAL,      "GRUPO1",      0},
      {bGRUPO2  ,   0,  0,  lGRUPO2  ,   disabled,                         "GRUPO2",      0},
      {bGRUPO3,     0,  0,  lGRUPO3,     ENABLED | ONLYSTATUS | DUAL,      "GRUPO3",      0},
      {bPAUSE,      0,  0,  0,           ENABLED | ACTION | DUAL | HOLD,   "PAUSE",       0},
      {bSTOP,       0,  0,  0,           ENABLED | ACTION | DUAL,          "STOP",        0}
    };
    int NUM_S_BOTON = sizeof(Boton)/sizeof(Boton[0]);

    S_MULTI multi;  //estructura con variables del multigrupo activo
    S_initFlags initFlags ;
    bool connected;
    bool NONETWORK;
    bool falloAP;
    bool saveConfig = false;
    bool sLEDR = LOW;
    bool sLEDG = LOW;
    bool sLEDB = LOW;
    
    const char *parmFile = "/config_parm.json";       // fichero de parametros activos
    const char *defaultFile = "/config_default.json"; // fichero de parametros por defecto

    unsigned long currentMillisLoop = 0;
    unsigned long lastMillisLoop = 0;
    int numloops = 0;

  #else
    extern S_BOTON Boton [];
    extern S_MULTI multi;
    extern S_initFlags initFlags;
    extern bool connected;
    extern bool NONETWORK;
    extern bool falloAP;
    extern bool saveConfig;
    extern bool sLEDR;
    extern bool sLEDG;
    extern bool sLEDB;
    extern int NUM_S_BOTON;
    extern const char *parmFile;       // fichero de parametros activos
    extern const char *defaultFile; // fichero de parametros por defecto

    extern long currentMillisLoop;
    extern long lastMillisLoop;
    extern int numloops;


  #endif

  #ifdef __MAIN__
    //Globales a este módulo
    S_Estado Estado;
    S_BOTON  *boton;
    S_BOTON  *ultimoBoton;
    S_simFlags simular; // estructura flags para simular errores
    Config_parm config; //estructura parametros configurables y runtime
    Display      *display;
    Configure    *configure;
    time_t utc;
    time_t lastRiegos[NUMZONAS];
    uint factorRiegos[NUMZONAS];
    uint8_t minutes;
    uint8_t seconds;
    uint8_t prevseconds;
    uint8_t prevminutes;
    char  descDomoticz[20];
    int value;
    int encvalue;
    int savedValue;
    int ledID = 0;
    bool tiempoTerminado;
    bool reposo = false;
    unsigned long standbyTime;
    bool displayOff = false;
    unsigned long lastBlinkPause;
    bool multirriego = false;
    bool multiSemaforo = false;
    bool holdPause = false;
    unsigned long countHoldPause;
    bool flagV = OFF;
    //int ledState = LOW;
    bool timeOK = false;
    bool factorRiegosOK = false;
    bool errorOFF = false;
    bool webServerAct = false;
    bool VERIFY;
    bool encoderSW = false;
    char errorText[7];
    //bool clean_FS = false;


  #endif

  //Funciones (prototipos)
  void apagaLeds(void);
  void bip(int);
  void bipOK(void);
  void bipKO(void);
  int  bID_bIndex(uint16_t);
  int  bID_zIndex(uint16_t);
  void blinkPause(void);
  void blinkPauseError(void);
  void check(void);
  bool checkWifi(void);
  void cleanFS(void);
  bool copyConfigFile(const char*, const char*);
  void dimmerLeds(bool);
  void displayGrupo(uint16_t *, int);
  void displayTimer(uint8_t, uint8_t, uint8_t, uint8_t);
  bool domoticzSwitch(int,char *, int);
  void enciendeLeds(void);
  void endWS(void);
  void filesInfo(void);
  void flagVerificaciones(void);
  int  getFactor(uint16_t);
  uint16_t getMultiStatus(void);
  String *httpGetDomoticz(String *);
  void infoDisplay(const char *, int, int, int);
  void infoLCD(const char *, int, int, int);
  void initCD4021B(void);
  void initClock(void);
  void initFactorRiegos(void);
  void initGPIOs(void);
  void initHC595(void);
  void initLastRiegos(void);
  void initLCD(void);
  void initLeds(void);
  void initMCP23017 (void);
  bool initRiego(uint16_t);
  void initWire(void);
  void led(uint8_t,int);
  void ledConf(int);
  void ledPWM(uint8_t, int);
  void ledRGB(int,int,int);
  bool ledStatusId(int);
  void leeSerial(void);
  bool loadConfigFile(const char*, Config_parm&);
  void loadDefaultSignal(uint);
  void longbip(int);
  void mcpIinit(void);
  void mcpOinit(void);
  void memoryInfo(void);
  void parpadeoLedON(void);
  void parpadeoLedWifi(void);
  void parpadeoLedZona(void);
  S_BOTON *parseInputs(bool);
  void printCharArray(char*, size_t);
  void printFile(const char*);
  void printMulti(void);
  void printMultiGroup(Config_parm&, int);
  void printParms(Config_parm&);
  void procesaBotones(void);
  bool procesaBotonMultiriego(void);
  void procesaBotonPause(void);
  void procesaBotonStop(void);
  void procesaBotonZona(void);
  void procesaEncoder(void);
  void procesaEstados(void);
  void procesaEstadoConfigurando(void);
  void procesaEstadoError(void);
  void procesaEstadoRegando(void);
  void procesaEstadoStandby(void);
  void procesaEstadoTerminando(void);
  void procesaEstadoStop(void);
  void procesaEstadoPause(void);
  void procesaWebServer(void);
  bool queryStatus(uint16_t, char *);
  void refreshTime(void);
  void refreshDisplay(void);
  void reposoOFF(void);
  void resetFlags(void);
  void resetLeds(void);
  bool saveConfigFile(const char*, Config_parm&);
  void setEstado(uint8_t);
  int  setMultibyId(uint16_t , Config_parm&);
  bool setupConfig(const char*, Config_parm&);
  void setupEstado(void);
  void setupInit(void);
  void setupParm(void);
  void setupRedWM(Config_parm&);
  void setupWS(void);
  void starConfigPortal(Config_parm&);
  void StaticTimeUpdate(void);
  void statusError(uint8_t);
  bool stopRiego(uint16_t);
  bool stopAllRiego(void);
  bool testButton(uint16_t, bool);
  void timeByFactor(int,uint8_t *,uint8_t *);
  void ultimosRiegos(int);
  void Verificaciones(void);
  void wifiClearSignal(uint);
  void zeroConfig(Config_parm&);

#endif
