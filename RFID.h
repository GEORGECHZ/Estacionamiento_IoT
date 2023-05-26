#include <SPI.h>
#include <MFRC522.h>

// Pines del módulo RFID-RC522
#define RST_PIN    0     // Pin RST del módulo RFID-RC522
#define SDA_PIN    4     // Pin SDA del módulo RFID-RC522 

// Crear instancia del objeto MFRC522
MFRC522 rfid(SDA_PIN, RST_PIN);

byte allowedUIDs[][4] = {
  {0x13, 0xE3, 0x09, 0x1F},  // Primer número de serie permitido
  {0x73, 0x20, 0x02, 0x1F},   // Segundo número de serie permitido
  {0x13, 0x76, 0x8C, 0x1C},   // Tercer número de serie permitido
  {0x93, 0xF6, 0x09, 0x1F}    // Cuarto número de serie permitido
};


struct Persona {
  String nombre;
  String tarjeta;
  // Agrega aquí más datos de la persona que deseas almacenar
};

Persona personas[] = {
  {"Juan Flores", "4652831160426087"},
  {"Maria Rubio", "4652838544562222"},
  {"Pedro Figueroa", "5423657345122126"},
  {"Ana Chávez", "340925965859900"}
};


class RFID {
  public:
    bool checkUID(byte* uid, byte uidSize);
    String PersonaNombre, PersonaTarjeta;
    int indice = -1; 
    bool ejecutar=false,condicion0=false,condicion1=false,
         condicion2=false,condicion3=false;
    byte pin_sensor_entrada = 15;     // pin sensor infrarrojo
    byte pin_sensor_salida = 2;     // pin sensor infrarrojo
  public:
    void rfid_init(void);
    void rfid_concedido(void);
    void rfid_leer(void);
};




void RFID::rfid_init(void){
  pinMode(pin_sensor_entrada, INPUT);
  pinMode(pin_sensor_salida, INPUT);
  SPI.begin();        // Inicializar la comunicación SPI
  rfid.PCD_Init();    // Inicializar el módulo RFID-RC522
  Serial.println ( F ( "La librería RFID ha inicializado con éxito" ) );
}


void RFID::rfid_concedido(void){
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial() && (digitalRead(pin_sensor_entrada)||digitalRead(pin_sensor_salida))) {
    // Comparar el número de serie leído con el número de serie permitido
    if (checkUID(rfid.uid.uidByte, rfid.uid.size)) {
      Serial.println("Acceso concedido");
      // Realizar acciones adicionales si se concede el acceso
      PersonaNombre = "";
      PersonaTarjeta = ""; 
      // Verificar si se encontró un índice válido
      if (indice != -1) {
        // Utilizar los datos de la persona asociados al número de serie
        Persona persona = personas[indice];
        PersonaNombre = persona.nombre;
        PersonaTarjeta = persona.tarjeta;
        Serial.println(PersonaNombre);
        Serial.println(PersonaTarjeta);
      }
    } else {
      Serial.println("Acceso denegado");
      // Realizar acciones adicionales si se deniega el acceso
    }
    rfid.PICC_HaltA();   // Detener la comunicación con la tarjeta RFID
  }
}


void RFID::rfid_leer(void){
  // Comprobar si se detecta una tarjeta RFID
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Leer el número de serie de la tarjeta RFID
    Serial.print("Número de serie: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();
    rfid.PICC_HaltA();   // Detener la comunicación con la tarjeta RFID
  }
}




// Función para verificar si el número de serie coincide con el número de serie permitido
bool RFID::checkUID(byte* uid, byte uidSize) {
  for (byte i = 0; i < sizeof(allowedUIDs) / sizeof(allowedUIDs[0]); i++) {
    if (uidSize == sizeof(allowedUIDs[i])) {
      bool match = true;
      indice = i;
      for (byte j = 0; j < uidSize; j++) {
        if (uid[j] != allowedUIDs[i][j]) {
          match = false;
          break;
        }
      }
      if (match) {
        if(indice == 0){
          condicion0 = true;
        } else if(indice == 1){
          condicion1 = true;
        } else if(indice == 2){
          condicion2 = true;
        } else if(indice == 3){
          condicion3 = true;
        }
        ejecutar = true;
        return true;
      }
    }
  }
  return false;
}
