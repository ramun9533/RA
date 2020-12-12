#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);
static unsigned int sw1 = 2; //switch límite del porton
static unsigned int paro = 3; // boton de paro de emergencia
static unsigned int sw2 = 4; //switch límite del porton
static unsigned int externa = 5; // accionamiento externo con otra señal, que puede ser de 110 VCA
static unsigned int giro1 = 7 ; // salida de giro
static unsigned int giro2 = 8 ; // salida de giro
static unsigned int proteccion =  9; // salida de protección, y para futuras mejoras
static unsigned int selec = 6 ; // opción 1 de seleccionar con que modo operará el sistema
static unsigned int selec1 = 12 ; // opción 2 de seleccionar con que modo operará el sistema
int Selec1 = 0;
int Selec = 0;
int serial = 0;
int Paro = 0;
int Sw1 = 0;
int Sw2 = 0;
int Externa = 0;
int Giro1 = 0;
int Giro2 = 0;
int Proteccion = 0;
void setup() {
  BTSerial.begin(9600);//Inicializar comunicacion
 pinMode(selec1, INPUT); 
  pinMode(selec, INPUT);
  pinMode(paro, INPUT);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(externa, INPUT);
  pinMode(giro1, OUTPUT);
  pinMode(proteccion, OUTPUT);
  pinMode(giro2, OUTPUT);
  digitalWrite (proteccion, LOW);
}
void loop() {
  Selec1 = digitalRead(selec1);
  Selec = digitalRead(selec);
  Paro = digitalRead(paro);
  Sw1 = digitalRead(sw1);
  Sw2 = digitalRead(sw2);
  Externa = digitalRead(externa);
  if (Paro == 1) // sentencia para el paro de emergencia
  {
    digitalWrite (proteccion, HIGH);
  } delay (10);
  
 while (BTSerial.available()) {    //pregunto sobre serial
    char data = (char)BTSerial.read();
   if ( data == 'H')
   { digitalWrite(serial, !digitalRead(serial)); // invierto de 0 a 1 o de 1 a 0
   }
  }
  if
  (!Selec1 and ((Selec and !serial and !Sw1) or ( !Selec and !Externa and !Sw1))) //lógica de selector en posición para usar el Bluetooth y/o entrada externa con switch límite #1
  //(!Externa and !Sw1) 
  {
    Giro1 = 0;
  }
  else {
    Giro1 = 1;
  }
  if (!Selec1 and ((Selec and serial and !Sw2) or (!Selec and Externa and !Sw2))) //lógica de selector en posición para usar el Bluetooth y/o entrada externa con switch límite #2
  //(!Externa and !Sw1) 
  //( Externa and !Sw2 )  
  {
    Giro2 = 0;
  } 
  else {
    Giro2 = 1;
  }
 
if (Selec1 and Sw1)  //posición selector para forzar Giro1

{
  Giro1 =0;
  }
if (Selec1 and Sw2) //posición selector para forzar Giro2


{
  Giro2 =0;
  }

  digitalWrite (giro2, Giro2);
  digitalWrite(giro1, Giro1);

   
}
