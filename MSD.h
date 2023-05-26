#ifndef MSD_h
#define MSD_h
/* Librerías fabricante necesarias para utilizar la SD */
#include <SD.h>
#include <SPI.h>
#include <ArduinoJson.h>

#define MSD_PIN 5    /* Pin de control SD */  
File MSD_File;       /* Archivo para escribir  o leer en la SD */
class MSD  {
  // VARIABLES
  public:
    uint8_t contador = 0;      /* */
    String filename_entrada = "/entradas_1.json";   /* Nombre de archivo que incluye "/" que indica la ubicación en raíz */
    String filename_salida = "/salidas_1.json";   /* Nombre de archivo que incluye "/" que indica la ubicación en raíz */
  // MÉTODOS
  public:
   void MSD_init ( void );
   void SaveFile_entrada ( String dato );
   void SaveFile_salida ( String dato );
   void ReadFile ( void );

};

void MSD::MSD_init ( void ){

   while ( !SD.begin ( MSD_PIN ) ) {
        Serial.println ( F ( "Falló la inicialización del módulo MicroSD"  ));
        delay(1000);
    }
    Serial.println ( F ( "La librería MicroSD ha inicializado con éxito" ) );
}

void MSD :: SaveFile_entrada ( String dato ) {
    
    // Abrir o crear en caso de que no exista.
    MSD_File = SD.open ( filename_entrada, FILE_APPEND );
    if ( MSD_File ) {

        // Almacenar JSON en el archivo.
        //serializeJson(*doc, JSON);
        MSD_File.println ( dato );
        MSD_File.close ( );
      
    } else {
        // if the file didn't open, print an error:
        Serial.print ( F ( "Error opening " ) );
        Serial.println ( filename_entrada );
 
       
    }
    Serial.println ( "Verificando si existe el archivo: ");
    if ( SD.exists ( filename_entrada ) ) {
    Serial.println ( filename_entrada );
    Serial.println( " existe" );
    } else {
        Serial.println ( filename_entrada );
    Serial.println( " no existe" );
    }
     // Esperar un segundo entre lecturas
      delay ( 1000 );
}


void MSD :: SaveFile_salida ( String dato ) {
    
    // Abrir o crear en caso de que no exista.
    MSD_File = SD.open ( filename_salida, FILE_APPEND );
    if ( MSD_File ) {

        // Almacenar JSON en el archivo.
        //serializeJson(*doc, JSON);
        MSD_File.println ( dato );
        MSD_File.close ( );
      
    } else {
        // if the file didn't open, print an error:
        Serial.print ( F ( "Error opening " ) );
        Serial.println ( filename_salida );
 
       
    }
    Serial.println ( "Verificando si existe el archivo: ");
    if ( SD.exists ( filename_salida ) ) {
    Serial.println ( filename_salida );
    Serial.println( " existe" );
    } else {
        Serial.println ( filename_salida );
    Serial.println( " no existe" );
    }
     // Esperar un segundo entre lecturas
      delay ( 1000 );
}


void MSD :: ReadFile ( void ) {

    //String filename = "/TestMicroSD.txt";
    // re-open the file for reading:
  MSD_File = SD.open( filename_salida );
  if ( MSD_File ) {
    Serial.println( "Archivo:" );

    // read from the file until there's nothing else in it:
    while ( MSD_File.available ( ) ) {

      Serial.write ( MSD_File.read ( ) );

    }
    // close the file:
    MSD_File.close ( );
  } else {
    // if the file didn't open, print an error:
    Serial.println ( "Error abriendo el archivo" );
  }

}


#endif