#include <Wire.h>               /* Librería para el uso del protocolo I2C. */

/*RTClib.h, requiere de la instalación de dos librerías:
RTClib: Permite el uso de varios relojes del fabricante Adafruit.
Adafruit BusIO: Es necesaria cargarla para configurar ciertos elementos de los componentes eléctronicos de Adafruit.*/

#include "RTClib.h"
  RTC_DS1307 rtc;

class DS1307_RTC {
  
  public:
      uint8_t hora = 0, minuto = 0, segundo = 0, dia = 0, mes = 0;
      uint16_t ano = 0;
      uint32_t actual = 0;
      String fecha , tiempo ;
      
  public:
    void RTC_init ( void );
    void get_time ( void );
    void format_date (void );
    void format_time ( void ) ;
    void show_time ( void );

  };

/* Función que configura lo necesario para que el reloj se inicialice */
void DS1307_RTC::RTC_init ( void ) {
  rtc.begin();
}

/* Función que configura lo necesario para que el reloj se inicialice */
void DS1307_RTC::get_time ( void ) {

      DateTime horaActual = rtc.now();
      segundo = horaActual.second ( );
      minuto = horaActual.minute ( );
      hora = horaActual.hour ( );
      dia = horaActual.day ( );
      mes = horaActual.month ( );
      ano = horaActual.year ( );
      actual = horaActual.unixtime();
      Serial.println(actual);
      
  }

/* Función que le da un formato legible a la fecha. */
void DS1307_RTC::format_date ( void ) {

  fecha = "";
    if ( dia < 10 ) fecha += '0';
  fecha += dia;
  fecha += "/";
    if ( mes < 10 ) fecha += '0';
  fecha += mes;
  fecha += "/";
  fecha += ano;
  
}

/* Función que le da un formato legible al tiempo. */
void DS1307_RTC::format_time ( void ) {

  tiempo = "";
  if ( hora < 10 ) tiempo += '0';
    tiempo += hora;
    tiempo += ":";
  
  if ( minuto < 10 ) tiempo += '0';
    tiempo += minuto;
    tiempo += ":";

  if ( segundo < 10 ) tiempo += '0';
    tiempo += segundo;
   
}

void DS1307_RTC :: show_time ( void ) {
  
  format_time ( );                    /* Dar formato al tiempo */
  Serial.print ( F ( "Hora: " ) );
  Serial.println ( tiempo );
  format_date ( );
  Serial.print ( F ( "Fecha: " ) );
  delay(200);
  Serial.println ( fecha );          /* Dar formato a la fecha */

}
