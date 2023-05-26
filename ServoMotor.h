#include <ESP32Servo.h>

Servo Sentrada;
Servo Ssalida;

class SERVO {
  public:
  public:
    void servo_init(void);
    void servo_entrada_abrir(void);
    void servo_salida_abrir(void);
    void servo_entrada_cerrar(void);
    void servo_salida_cerrar(void);
};


void SERVO::servo_init(void){
  Sentrada.attach(12);
  Ssalida.attach(14);
}

void SERVO::servo_entrada_abrir(void){
  for(byte i=0;i<90;i+=5){
    Sentrada.write(i);
    delay(100);
  }
}

void SERVO::servo_entrada_cerrar(void){
  for(byte i=90;i>0;i-=5){
    Sentrada.write(i);
    delay(100);
  }
}

void SERVO::servo_salida_abrir(void){
  for(byte i=0;i<90;i+=5){
    Ssalida.write(i);
    delay(100);
  }
}

void SERVO::servo_salida_cerrar(void){
  for(byte i=90;i>0;i-=5){
    Ssalida.write(i);
    delay(100);
  }
}