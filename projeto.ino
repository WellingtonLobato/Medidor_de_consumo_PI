//Declaracao de bibliotecas
#include <SPI.h>
#include <LCD5110_Graph_SPI.h>
#include "EmonLib.h"
#include <avr/eeprom.h>

//Definicoes que seram usadas
#define WINDOW 15
#define DELTA 1500


//Declaracao de variaveis e objetos
EnergyMonitor emon1; //Monitorador de energia

LCD5110 myLCD(5,6,3); //Variavel do LCD -Fica de boa com essa aqui-
extern uint8_t SmallFont[]; //Configuracao da fonte do display

unsigned long measureTime;
boolean flag=false;
double delta=0;

//Variaveis pra calcular os valores relacionados ao sensor
double Irms;
double W;
double kwhTotal;
double vlreais;
unsigned long ltmillis, tmillis, timems, previousMillis;

//Variaveis de conversao ------------------------------------------------------
char charBufIrms[30]; //Variavel pra converter o double da Corrente pra string
char charBufW[30]; //Variavel pra converter o double de Wats para string
char charBufKwh[30]; //Variavel pra converter o double de Kwh para string
char charBufVl[30]; //Variavel pra converter o double vlReais para string

//________________________________________________________________

void setup(){
  emon1.current(0,111.1); //Corrente:pino de entrada, calibracao
  
  myLCD.InitLCD(70); //Inicializa o LCD
  myLCD.setFont(SmallFont); //Seleciona a fonte que sera usada
  myLCD.update(); //Funcao update sempre reseta o display e mostra algo novo

  
  while (!flag) {
    myLCD.print("Calibrando...", 0, 0);
    myLCD.update();
    delay(100);
    flag = true;
  }

  myLCD.print("Pronto        ", 0, 0);
  myLCD.print("para ", 0, 10);
  myLCD.print("usar!!!", 0, 20);
  myLCD.update();
  delay(2000);
  myLCD.print("                     ", 0, 0);
  myLCD.print("           ", 0, 10);
  myLCD.print("           ", 0, 20);
  myLCD.update();  
  
}
void loop(){
  ltmillis = tmillis;
  tmillis = millis();
  timems = tmillis - ltmillis;
  
  Irms = emon1.calcIrms(1480); //Calcula apenas a corrente
  W =Irms*127.0; //Calcula os Watts
  
  
  dtostrf(Irms, 8, 7, charBufIrms);
  dtostrf(W, 8, 7, charBufW); 

  for (int i=100; i>=20; i--)
  {
    myLCD.print("Watts:",0,i-100);
    myLCD.print(charBufW,0,i-90);
    myLCD.print("Corrente",0,i-80);
    myLCD.print(charBufIrms,0,i-70);
    myLCD.update();    
    delay(100);
  }
}
