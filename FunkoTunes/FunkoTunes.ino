 
#include <stdint.h>
#include <ili9341_16_bits.h>

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "TM4C123GH6PM.h"


uint8_t greenLedState = HIGH;
uint8_t redLedState = LOW;

void Timer0IntHandler();
void Timer1IntHandler();
void TimerInit();

#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7, PC_6, PC_7, PD_6, PD_7, PE_4, PE_5, PC_4, PC_5};

#include "bitmapspostlab7.h"


int posicion_YRojo1 = 10;
int posicion_YVerde1 = 10;
int posicion_YAzul1 = 10;
int posicion_YAmarillo1 = 10;
int posicion_YRojo2 = 10;
int posicion_YVerde2 = 10;
int posicion_YAzul2 = 10;
int posicion_YAmarillo2 = 10;
int posicion_YRojo3 = 10;
int posicion_YVerde3 = 10;
int posicion_YAzul3 = 10;
int posicion_YAmarillo3 = 10;
int posicion_YRojo4 = 10;
int posicion_YVerde4 = 10;
int posicion_YAzul4 = 10;
int posicion_YAmarillo4 = 10;
int rojo1 = 0;
int verde1 = 0;
int amarillo1 = 0;
int azul1 = 0;
int rojo2 = 0;
int verde2 = 0;
int amarillo2 = 0;
int azul2 = 0;
int rojo3 = 0;
int verde3 = 0;
int amarillo3 = 0;
int azul3 = 0;
int rojo4 = 0;
int verde4 = 0;
int amarillo4 = 0;
int azul4 = 0;
int contadorRojo = 0;
int contadorVerde = 0;
int contadorAzul = 0;
int contadorAmarillo = 0;

int nivel1 [] = {1,1,2,2,3,3,4,4,2,3,2,1,3,4,2,3,1,1,3,2};
int nota = 0;

void setup() {

  pinMode(PD_7, INPUT_PULLUP);
  pinMode(PD_6, INPUT_PULLUP);
  pinMode(PC_7, INPUT_PULLUP);
  pinMode(PC_6, INPUT_PULLUP);
  
  lcdSetDataPins(DPINS);

  Serial.begin(9600);
  Serial.println("Iniciando pantalla...");
  lcdInit();
  Serial.println("Pintando el cielo...");
  FillRect(0,0, 320,240, 0x74D9);
  TimerInit();
  
//  LCD_Bitmap(20, 20, 20, 20, anilloRojo);
//  LCD_Bitmap(50, 20, 20, 20, anilloVerde);
//  LCD_Bitmap(80, 20, 20, 20, anilloAzul);
//  LCD_Bitmap(110, 20, 20, 20, anilloAmarillo);
}

void loop() {
  
}

void TimerInit(){
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);  
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
  MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
  MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
  
  Serial.println("hola");
  float period_0 = 2; // 200ms
  float period_1 = 0.1; // 200ms
  
  MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, MAP_SysCtlClockGet()*period_0); //(80MHZ / MAP_SysCtlClockGet)
  MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, MAP_SysCtlClockGet()*period_1); //5 veces por seg

  TimerIntRegister(TIMER0_BASE, TIMER_A, &Timer0IntHandler);
  TimerIntRegister(TIMER1_BASE, TIMER_A, &Timer1IntHandler);
  
  MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
  
  MAP_TimerEnable(TIMER0_BASE, TIMER_A);
  MAP_TimerEnable(TIMER1_BASE, TIMER_A);
}

void Timer0IntHandler() {
  MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  if (nivel1[nota] == 1){
    contadorRojo++;
    rojo1 = 1;
    
    if (contadorRojo == 5){
      contadorRojo = 0;
    }
    if (contadorRojo == 1){
      rojo1 = 1;
    }
    if (contadorRojo == 2){
      rojo2 = 1;
    }
    if (contadorRojo == 3){
      rojo3 = 1;
    }
    if (contadorRojo == 4){
      rojo4 = 1;
    }
  }
  if (nivel1[nota] == 2){
    contadorVerde++;
    verde1 = 1;
    if (contadorVerde == 5){
      contadorVerde = 0;
    }
    if (contadorVerde == 1){
      verde1 = 1;
    }
    if (contadorVerde == 2){
      verde2 = 1;
    }
    if (contadorVerde == 3){
      verde3 = 1;
    }
    if (contadorVerde == 4){
      verde4 = 1;
    }
  }
  if (nivel1[nota] == 3){
    contadorAzul++;
    azul1 = 1;
    if (contadorAzul == 5){
      contadorAzul = 0;
    }
    if (contadorAzul == 1){
      azul1 = 1;
    }
    if (contadorAzul == 2){
      azul2 = 1;
    }
    if (contadorAzul == 3){
      azul3 = 1;
    }
    if (contadorAzul == 4){
      azul4 = 1;
    }
  }
  if (nivel1[nota] == 4){
    contadorAmarillo++;
    amarillo1 = 1;
    if (contadorAmarillo == 5){
      contadorAmarillo = 0;
    }
    if (contadorAmarillo == 1){
      amarillo1 = 1;
    }
    if (contadorAmarillo == 2){
      amarillo2 = 1;
    }
    if (contadorAmarillo == 3){
      amarillo3 = 1;
    }
    if (contadorAmarillo == 4){
      amarillo4 = 1;
    }
  }
  nota++;
}

void Timer1IntHandler() {
  MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
  
  if (rojo1 == 1){
    LCD_Bitmap(190, posicion_YRojo1, 20, 20, anilloRojo);
    LCD_Bitmap(20, posicion_YRojo1, 20, 20, anilloRojo);
    H_line( 20, posicion_YRojo1 - 1, 20, 0x74D9);
    H_line( 190, posicion_YRojo1 - 1, 20, 0x74D9);
    posicion_YRojo1++;
  }
  if (rojo2 == 1){
    LCD_Bitmap(190, posicion_YRojo2, 20, 20, anilloRojo);
    LCD_Bitmap(20, posicion_YRojo2, 20, 20, anilloRojo);
    H_line( 20, posicion_YRojo2 - 1, 20, 0x74D9);
    H_line( 190, posicion_YRojo2 - 1, 20, 0x74D9);
    posicion_YRojo2++;
  }
  if (rojo3 == 1){
    LCD_Bitmap(190, posicion_YRojo3, 20, 20, anilloRojo);
    LCD_Bitmap(20, posicion_YRojo3, 20, 20, anilloRojo);
    H_line( 20, posicion_YRojo3 - 1, 20, 0x74D9);
    H_line( 190, posicion_YRojo3 - 1, 20, 0x74D9);
    posicion_YRojo3++;
  }
  if (rojo4 == 1){
    LCD_Bitmap(190, posicion_YRojo4, 20, 20, anilloRojo);
    LCD_Bitmap(20, posicion_YRojo4, 20, 20, anilloRojo);
    H_line( 20, posicion_YRojo4 - 1, 20, 0x74D9);
    H_line( 190, posicion_YRojo4 - 1, 20, 0x74D9);
    posicion_YRojo4++;
  }
  
  if (verde1 == 1){
    LCD_Bitmap(220, posicion_YVerde1, 20, 20, anilloVerde);
    LCD_Bitmap(50, posicion_YVerde1, 20, 20, anilloVerde);
    H_line( 50, posicion_YVerde1 - 1, 20, 0x74D9);
    H_line( 220, posicion_YVerde1 - 1, 20, 0x74D9);
    posicion_YVerde1++;
  }
  if (verde2 == 1){
    LCD_Bitmap(220, posicion_YVerde2, 20, 20, anilloVerde);
    LCD_Bitmap(50, posicion_YVerde2, 20, 20, anilloVerde);
    H_line( 50, posicion_YVerde2 - 1, 20, 0x74D9);
    H_line( 220, posicion_YVerde2 - 1, 20, 0x74D9);
    posicion_YVerde2++;
  }
  if (verde3 == 1){
    LCD_Bitmap(220, posicion_YVerde3, 20, 20, anilloVerde);
    LCD_Bitmap(50, posicion_YVerde3, 20, 20, anilloVerde);
    H_line( 50, posicion_YVerde3 - 1, 20, 0x74D9);
    H_line( 220, posicion_YVerde3 - 1, 20, 0x74D9);
    posicion_YVerde3++;
  }
  if (verde4 == 1){
    LCD_Bitmap(220, posicion_YVerde4, 20, 20, anilloVerde);
    LCD_Bitmap(50, posicion_YVerde4, 20, 20, anilloVerde);
    H_line( 50, posicion_YVerde4 - 1, 20, 0x74D9);
    H_line( 220, posicion_YVerde4 - 1, 20, 0x74D9);
    posicion_YVerde4++;
  }

  if (azul1 == 1){
    LCD_Bitmap(250, posicion_YAzul1, 20, 20, anilloAzul);
    LCD_Bitmap(80, posicion_YAzul1, 20, 20, anilloAzul);
    H_line( 80, posicion_YAzul1 - 1, 20, 0x74D9);
    H_line( 250, posicion_YAzul1 - 1, 20, 0x74D9);
    posicion_YAzul1++;
  }
  if (azul2 == 1){
    LCD_Bitmap(250, posicion_YAzul2, 20, 20, anilloAzul);
    LCD_Bitmap(80, posicion_YAzul2, 20, 20, anilloAzul);
    H_line( 80, posicion_YAzul2 - 1, 20, 0x74D9);
    H_line( 250, posicion_YAzul2 - 1, 20, 0x74D9);
    posicion_YAzul2++;
  }
  if (azul3 == 1){
    LCD_Bitmap(250, posicion_YAzul3, 20, 20, anilloAzul);
    LCD_Bitmap(80, posicion_YAzul3, 20, 20, anilloAzul);
    H_line( 80, posicion_YAzul3 - 1, 20, 0x74D9);
    H_line( 250, posicion_YAzul3 - 1, 20, 0x74D9);
    posicion_YAzul3++;
  }
  
  if (azul4 == 1){
    LCD_Bitmap(250, posicion_YAzul4, 20, 20, anilloAzul);
    LCD_Bitmap(80, posicion_YAzul4, 20, 20, anilloAzul);
    H_line( 80, posicion_YAzul4 - 1, 20, 0x74D9);
    H_line( 250, posicion_YAzul4 - 1, 20, 0x74D9);
    posicion_YAzul4++;
  }

  if (amarillo1 == 1){
    LCD_Bitmap(280, posicion_YAmarillo1, 20, 20, anilloAmarillo);
    LCD_Bitmap(110, posicion_YAmarillo1, 20, 20, anilloAmarillo);
    H_line( 110, posicion_YAmarillo1 - 1, 20, 0x74D9);
    H_line( 280, posicion_YAmarillo1 - 1, 20, 0x74D9);
    posicion_YAmarillo1++;
  }
  if (amarillo2 == 1){
    LCD_Bitmap(280, posicion_YAmarillo2, 20, 20, anilloAmarillo);
    LCD_Bitmap(110, posicion_YAmarillo2, 20, 20, anilloAmarillo);
    H_line( 110, posicion_YAmarillo2 - 1, 20, 0x74D9);
    H_line( 280, posicion_YAmarillo2 - 1, 20, 0x74D9);
    posicion_YAmarillo2++;
  }
  if (amarillo3 == 1){
    LCD_Bitmap(280, posicion_YAmarillo3, 20, 20, anilloAmarillo);
    LCD_Bitmap(110, posicion_YAmarillo3, 20, 20, anilloAmarillo);
    H_line( 110, posicion_YAmarillo3 - 1, 20, 0x74D9);
    H_line( 280, posicion_YAmarillo3 - 1, 20, 0x74D9);
    posicion_YAmarillo3++;
  }
  if (amarillo4 == 1){
    LCD_Bitmap(280, posicion_YAmarillo4, 20, 20, anilloAmarillo);
    LCD_Bitmap(110, posicion_YAmarillo4, 20, 20, anilloAmarillo);
    H_line( 110, posicion_YAmarillo4 - 1, 20, 0x74D9);
    H_line( 280, posicion_YAmarillo4 - 1, 20, 0x74D9);
    posicion_YAmarillo4++;
  }

  if (posicion_YRojo1 == 120){
    FillRect(190,posicion_YRojo1-1, 22,22, 0x74D9);
    FillRect(20,posicion_YRojo1-1, 22,22, 0x74D9);
    posicion_YRojo1 = 10;
    rojo1 = 0;
  }
  if (posicion_YRojo2 == 120){
    FillRect(190,posicion_YRojo2-1, 22,22, 0x74D9);
    FillRect(20,posicion_YRojo2-1, 22,22, 0x74D9);
    posicion_YRojo2 = 10;
    rojo2 = 0;
  }
  if (posicion_YRojo3 == 120){
    FillRect(190,posicion_YRojo3-1, 22,22, 0x74D9);
    FillRect(20,posicion_YRojo3-1, 22,22, 0x74D9);
    posicion_YRojo3 = 10;
    rojo3 = 0;
  }
  if (posicion_YRojo4 == 120){
    FillRect(190,posicion_YRojo4-1, 22,22, 0x74D9);
    FillRect(20,posicion_YRojo4-1, 22,22, 0x74D9);
    posicion_YRojo4 = 10;
    rojo4 = 0;
  }
  if (posicion_YVerde1 == 120){
    FillRect(220,posicion_YVerde1-1, 22,22, 0x74D9);
    FillRect(50,posicion_YVerde1-1, 22,22, 0x74D9);
    posicion_YVerde1 = 10;
    verde1 = 0;
  }
  if (posicion_YVerde2 == 120){
    FillRect(220,posicion_YVerde2-1, 22,22, 0x74D9);
    FillRect(50,posicion_YVerde2-1, 22,22, 0x74D9);
    posicion_YVerde2 = 10;
    verde2 = 0;
  }
  if (posicion_YVerde3 == 120){
    FillRect(220,posicion_YVerde3-1, 22,22, 0x74D9);
    FillRect(50,posicion_YVerde3-1, 22,22, 0x74D9);
    posicion_YVerde3 = 10;
    verde3 = 0;
  }
  if (posicion_YVerde4 == 120){
    FillRect(220,posicion_YVerde4-1, 22,22, 0x74D9);
    FillRect(50,posicion_YVerde4-1, 22,22, 0x74D9);
    posicion_YVerde4 = 10;
    verde4 = 0;
  }
  if (posicion_YAzul1 == 120){
    FillRect(250,posicion_YAzul1-1, 22,22, 0x74D9);
    FillRect(80,posicion_YAzul1-1, 22,22, 0x74D9);
    posicion_YAzul1 = 10;
    azul1 = 0;
  }
  if (posicion_YAzul2 == 120){
    FillRect(250,posicion_YAzul2-1, 22,22, 0x74D9);
    FillRect(80,posicion_YAzul2-1, 22,22, 0x74D9);
    posicion_YAzul2 = 10;
    azul2 = 0;
  }
  if (posicion_YAzul3 == 120){
    FillRect(250,posicion_YAzul3-1, 22,22, 0x74D9);
    FillRect(80,posicion_YAzul3-1, 22,22, 0x74D9);
    posicion_YAzul3 = 10;
    azul3 = 0;
  }
  if (posicion_YAzul4 == 120){
    FillRect(250,posicion_YAzul4-1, 22,22, 0x74D9);
    FillRect(80,posicion_YAzul4-1, 22,22, 0x74D9);
    posicion_YAzul4 = 10;
    azul4 = 0;
  }
  if (posicion_YAmarillo1 == 120){
    FillRect(280,posicion_YAmarillo1-1, 22,22, 0x74D9);
    FillRect(110,posicion_YAmarillo1-1, 22,22, 0x74D9);
    posicion_YAmarillo1 = 10;
    amarillo1 = 0;
  }
  if (posicion_YAmarillo2 == 120){
    FillRect(280,posicion_YAmarillo2-1, 22,22, 0x74D9);
    FillRect(110,posicion_YAmarillo2-1, 22,22, 0x74D9);
    posicion_YAmarillo2 = 10;
    amarillo2 = 0;
  }
  if (posicion_YAmarillo3 == 120){
    FillRect(280,posicion_YAmarillo3-1, 22,22, 0x74D9);
    FillRect(110,posicion_YAmarillo3-1, 22,22, 0x74D9);
    posicion_YAmarillo3 = 10;
    amarillo3 = 0;
  }
  if (posicion_YAmarillo4 == 120){
    FillRect(280,posicion_YAmarillo4-1, 22,22, 0x74D9);
    FillRect(110,posicion_YAmarillo4-1, 22,22, 0x74D9);
    posicion_YAmarillo4 = 10;
    amarillo4 = 0;
  }
}
