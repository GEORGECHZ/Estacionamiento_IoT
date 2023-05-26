
const byte pin_luz = 16;
const byte pin_ldr = 35;

class LDR{
  public:
  public:
    void ldr_init(void);
    void funcion(void);
};


void LDR::ldr_init(void){
  pinMode(pin_luz, OUTPUT);
  pinMode(pin_ldr, INPUT);
}

void LDR::funcion(void){
  int datos = analogRead(pin_ldr);
  if(datos < 500){
    digitalWrite(pin_luz, LOW);
  } else {
    digitalWrite(pin_luz, HIGH);
  }
}

