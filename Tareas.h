#ifndef Tasks_h
#define Tasks_h
/*****************************************************************************************
*      DESCRIPCIÓN DE LA LIBRERÍA: El objetivo de esta librería es generar tiempos de    *
*       espera de ejecución sin la implementación de la función "delay()".               *
******************************************************************************************/
#include "MQTT.h"
MQTT mqtt;

#include "RTC.h"
DS1307_RTC RTC;

#include "LCD.h"
LCD lcd1;

#include "MSD.h"
MSD sd;

#include "RFID.h"
RFID rfid1;

#include "PCF8574.h"
PCF8574 pcf8574(0x38);

#include "ServoMotor.h"
SERVO servom;

#include "LDR.h"
LDR ldr;

#include <ArduinoJson.h>
String JsonTexto = "";

#define TIEMPO1 100                // Constante para indicar medio segundo (100 ms).
#define TIEMPO2 100                 // Constante para indicar 2 segundos (100 ms).
#define TIEMPO3 500                 // Constante para indicar 3 segundos (10000 ms).
#define TIEMPO4 1000                 // Constante para indicar 3 segundos (10000 ms).

class millis_tasks {

  public:
    uint64_t tiempo_anterior1 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO1.
             tiempo_anterior2 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO2.
             tiempo_anterior3 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO3.
             tiempo_anterior4 = 0,
             tiempo_actual = 0;      // Contador de tiempo que tendrá múltiplos de TIEMPO.
    uint32_t persona0,persona1,
             persona2,persona3;
    int precio;
    
  public:
    void tareas_init(void);
    void tarea1 ( void );            // Función que ejecuta una acción cada segundo.
    void tarea2 ( void );            // Función que ejecuta una acción cada dos segundos.
    void tarea3 ( void );            // Función que ejecuta una acción cada tres segundos.
    void tarea4 ( void );            // Función que ejecuta una acción cada tres segundos.
    void actualizar_tareas (void );  // Función que actualiza el conteo obtenido de la función "millis()".
 
};



void millis_tasks::tareas_init(void){
  mqtt.mqtt_init();
  RTC.RTC_init ( );             /* Inicializar configuración del reloj */
  lcd1.LCD_init();
  sd.MSD_init();
  rfid1.rfid_init();
  servom.servo_init();
  ldr.ldr_init();
  pcf8574.begin();

  for(int i=0;i<8;i++) {
    pcf8574.pinMode(i, INPUT);
  }

}



/*~~~~~~~~~~~~~~~~~~~~~~~~ tarea1 - Función que se ejecuta cada TIEMPO1( 100 MILISEGUNDOS) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea1 ( void ) {

  if ( ( tiempo_actual - tiempo_anterior1 ) >= TIEMPO1 ){

    rfid1.rfid_concedido();
    if (digitalRead(rfid1.pin_sensor_entrada) && rfid1.ejecutar == true){
      RTC.get_time();
      RTC.format_time();
      RTC.format_date();
      DynamicJsonDocument JSON ( 1024 );         /* Objeto donde se alamcenará el JSON */
      JSON [ "Nombre" ] = rfid1.PersonaNombre;             /* Almacena números enteros o flotantes */         
      JSON [ "Tarjeta" ] = rfid1.PersonaTarjeta;           /* Almacena texto, ya sea cadena o string */ 
      JSON [ "Hora" ] = RTC.tiempo;
      JSON [ "Fecha" ] = RTC.fecha;
      serializeJsonPretty(JSON, JsonTexto);
      sd.SaveFile_entrada(JsonTexto);
      if(rfid1.condicion0){
        persona0 = RTC.actual;
        rfid1.condicion0 = false;
      }
      if(rfid1.condicion1){
        persona1 = RTC.actual;
        rfid1.condicion1 = false;
      }
      if(rfid1.condicion2){
        persona2 = RTC.actual;
        rfid1.condicion2 = false;
      }
      if(rfid1.condicion3){
        persona3 = RTC.actual;
        rfid1.condicion3 = false;
      }

      servom.servo_entrada_abrir();
      lcd1.LCD_pase();
      tarea4();
      while(digitalRead(rfid1.pin_sensor_entrada)){

      }
      delay(3000);
      servom.servo_entrada_cerrar();

      JsonTexto = "";
      rfid1.ejecutar = false;
    } 

    tiempo_anterior1 = tiempo_actual;

  }

}

/*~~~~~~~~~~~~~~~~~~~~~~~~ tarea2 - Función que se ejecuta cada TIEMPO2 ( 100 MILISEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea2 ( void ) {
  if ( ( tiempo_actual - tiempo_anterior2 ) >= TIEMPO2 ){
    rfid1.rfid_concedido();
    if (digitalRead(rfid1.pin_sensor_salida) && rfid1.ejecutar == true){
      RTC.get_time();
      RTC.format_time();
      RTC.format_date();
      if(rfid1.condicion0){
        uint32_t minutos = RTC.actual - persona0;
        precio = minutos * .5;
        rfid1.condicion0 = false;
      }
      if(rfid1.condicion1){
        uint32_t minutos = RTC.actual - persona1;
        precio = minutos * .5;
        rfid1.condicion1 = false;
      }
      if(rfid1.condicion2){
        uint32_t minutos = RTC.actual - persona2;
        precio = minutos * .5;
        rfid1.condicion2 = false;
      }
      if(rfid1.condicion3){
        uint32_t minutos = RTC.actual - persona3;
        precio = minutos * .5;
        rfid1.condicion3 = false;
      }
      DynamicJsonDocument JSON ( 1024 );         /* Objeto donde se alamcenará el JSON */
      JSON [ "Nombre" ] = rfid1.PersonaNombre;             /* Almacena números enteros o flotantes */         
      JSON [ "Tarjeta" ] = rfid1.PersonaTarjeta;           /* Almacena texto, ya sea cadena o string */ 
      JSON [ "Hora" ] = RTC.tiempo;
      JSON [ "Fecha" ] = RTC.fecha;
      JSON [ "Precio" ] = precio;
      serializeJsonPretty(JSON, JsonTexto);
      sd.SaveFile_salida(JsonTexto);
      
      mqtt.connect();
      mqtt.publicar(JsonTexto.c_str());

      servom.servo_salida_abrir();
      while(digitalRead(rfid1.pin_sensor_salida)){

      }
      delay(3000);
      servom.servo_salida_cerrar();

      JsonTexto = "";
      rfid1.ejecutar = false;
    }

     tiempo_anterior2 = tiempo_actual;

  }
 
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ tarea3 - Función que se ejecuta cada TIEMPO3 ( 10 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea3 ( void ) {

  if ( ( tiempo_actual - tiempo_anterior3 ) >= TIEMPO3 ){

     ldr.funcion();

     tiempo_anterior3 = tiempo_actual;

  }
  
}


void millis_tasks :: tarea4 ( void ) {

  if ( ( tiempo_actual - tiempo_anterior4 ) >= TIEMPO4 || digitalRead(rfid1.pin_sensor_entrada)){

    //lcd1.LCD_pase();

    if (pcf8574.digitalRead(0)&&pcf8574.digitalRead(1)&&pcf8574.digitalRead(2)&&pcf8574.digitalRead(3)&&pcf8574.digitalRead(4)&&pcf8574.digitalRead(5)&&pcf8574.digitalRead(6)&&pcf8574.digitalRead(7)){
      lcd1.LCD_no_hay();
      return tarea4();
    }

    lcd1.LCD_background();

    if(pcf8574.digitalRead(0)){
      lcd1.LCD_task('x',3,1);
    } else{
      lcd1.LCD_task('1',3,1);
    }
    if(pcf8574.digitalRead(1)){
      lcd1.LCD_task('x',6,1);
    } else{
      lcd1.LCD_task('2',6,1);
    }
    if(pcf8574.digitalRead(2)){
      lcd1.LCD_task('x',9,1);
    } else{
      lcd1.LCD_task('3',9,1);
    }
    if(pcf8574.digitalRead(3)){
      lcd1.LCD_task('x',12,1);
    } else{
      lcd1.LCD_task('4',12,1);
    }
    if(pcf8574.digitalRead(4)){
      lcd1.LCD_task('x',12,0);
    } else{
      lcd1.LCD_task('5',12,0);
    }
    if(pcf8574.digitalRead(5)){
      lcd1.LCD_task('x',9,0);
    } else{
      lcd1.LCD_task('6',9,0);
    }
    if(pcf8574.digitalRead(6)){
      lcd1.LCD_task('x',6,0);
    } else{
      lcd1.LCD_task('7',6,0);
    }
    if(pcf8574.digitalRead(7)){
      lcd1.LCD_task('x',3,0);
    } else{
      lcd1.LCD_task('8',3,0);
    }

    
    

    tiempo_anterior4 = tiempo_actual;

  }
  
}


/*~~~~~~~~~~~~~~~~~~~~~~~~ actualizar_tareas - Función que actualiza el contador de "millis()" ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: actualizar_tareas ( void ) {

  tiempo_actual = millis( );

}

#endif