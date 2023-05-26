#include <Wire.h>               /*~ Librería I2C ~*/
#include "LiquidCrystal_I2C.h"  /*~ Librería LCD ~*/

LiquidCrystal_I2C lcd(0x27,16,2);  /*~ Instancia de la clase para el manejo de la pantalla ( Dirección I2C, columnas, filas ) ~*/

byte customChar1[] = {
  B00000,
  B00100,
  B00110,
  B11111,
  B11111,
  B00110,
  B00100,
  B00000
};
byte customChar2[] = {
  B00000,
  B00100,
  B01100,
  B11111,
  B11111,
  B01100,
  B00100,
  B00000
};
byte customChar3[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000
};
byte customCharArribaRight[] = {
  B00000,
  B00000,
  B00000,
  B11110,
  B11110,
  B00110,
  B00110,
  B00110
};
byte customCharAbajoRight[] = {
  B00110,
  B00110,
  B00110,
  B11110,
  B11110,
  B00000,
  B00000,
  B00000
};
byte disabledLogo[] = {
  B01100,
  B01100,
  B01000,
  B01110,
  B11000,
  B11111,
  B10001,
  B01110
};

class LCD {
  public:
  public:
    void LCD_init ( void );
    void LCD_task (char dato,byte x, byte y);
    void LCD_pase (void);
    void LCD_no_hay(void);
    void LCD_background(void);
};


void LCD::LCD_init( void ){
  lcd.begin (); 					 	/*~ Inicializar la pantalla LCD ~*/
  lcd.backlight ( );

  lcd.createChar ( 2, customChar1 );
  lcd.createChar ( 3, customChar2 );
  lcd.createChar ( 4, customChar3 );
  lcd.createChar ( 5, customCharArribaRight );
  lcd.createChar ( 6, customCharAbajoRight );
  lcd.createChar(8, disabledLogo);
}

void LCD::LCD_pase(void){
  lcd.clear();
  lcd.setCursor ( 3, 0 );
  lcd.print ("BIENVENIDO");
  delay(1500);
  lcd.clear();
}

void LCD::LCD_no_hay(void){
  lcd.setCursor ( 0, 0 );
  lcd.print ("NO HAY ESPACIOS ");
  lcd.setCursor ( 2, 1 );
  lcd.print ("  DISPONIBLES   ");
}

void LCD::LCD_background(void){
  lcd.setCursor ( 0, 0 );
  lcd.write ( 3 );
  lcd.setCursor ( 1, 0 );
  lcd.write ( 4 );
  lcd.setCursor ( 2, 0 );
  lcd.write ( 4 );
  lcd.setCursor ( 4, 0 );
  lcd.write ( 3 );
  lcd.setCursor ( 5, 0 );
  lcd.write ( 4 );
  lcd.setCursor ( 7, 0 );
  lcd.write ( 3 );
  lcd.setCursor ( 8, 0 );
  lcd.write ( 4 );
  lcd.setCursor ( 10, 0 );
  lcd.write ( 3 );
  lcd.setCursor ( 11, 0 );
  lcd.write ( 4 );
  lcd.setCursor ( 13, 0 );
  lcd.write ( 3 );
  lcd.setCursor ( 14, 0 );
  lcd.write ( 4 );
  lcd.setCursor ( 15, 0 );
  lcd.write ( 5 );
  lcd.setCursor ( 0, 1 );
  lcd.write ( 4 );
  lcd.setCursor ( 1, 1 );
  lcd.write ( 4 );
  lcd.setCursor ( 2, 1 );
  lcd.write ( 2 );
  lcd.setCursor ( 4, 1 );
  lcd.write ( 4 );
  lcd.setCursor ( 5, 1 );
  lcd.write ( 2 );
  lcd.setCursor ( 7, 1 );
  lcd.write ( 4 );
  lcd.setCursor ( 8, 1 );
  lcd.write ( 2 );
  lcd.setCursor ( 10, 1 );
  lcd.write ( 4 );
  lcd.setCursor ( 11, 1 );
  lcd.write ( 2 );
  lcd.setCursor ( 13, 1 );
  lcd.write ( 4 );
  lcd.setCursor ( 14, 1 );
  lcd.write ( 2 );
  lcd.setCursor ( 15, 1 );
  lcd.write ( 6 );
}


void LCD::LCD_task(char dato,byte x, byte y){
 
  lcd.setCursor ( x, y );   	/*~ ( columnas, filas) Ubicamos el cursor en la primera posición(columna:0) de la primera línea(fila:0) ~*/
  if (dato == '1' || dato == '8'){
    lcd.write(8);
  } else{
    lcd.print (dato); /*~ Mostrar una cadena de texto (no exceder 16 caracteres por línea)~*/			
  }
  
}



