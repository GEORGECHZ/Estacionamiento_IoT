// Se incluye la biblioteca para conectarse a la red WiFi
#include <WiFi.h> 
// Se incluye la biblioteca para conectarse a un servidor MQTT
#include <PubSubClient.h> 



// Se define la dirección del servidor MQTT
const char* mqtt_server = "test.mosquitto.org"; 
// Se crea un objeto WiFiClient para conectarse a la red WiFi
WiFiClient espClient; 
// Se crea un objeto PubSubClient para conectarse al servidor MQTT utilizando el objeto espClient
PubSubClient client(espClient); 

class MQTT {
  public:
    const char* ssid = "Irak22fg";
    const char* password = "karfi2220g";
    void setup_wifi();
  public:
    void mqtt_init(void);
    void reconnect(void);
    void connect(void);
    void publicar(const char* mensaje);
};


void MQTT::mqtt_init(void){
  //Llamar a la funcion setup_wifi para conectarse a internet
  setup_wifi();

  //llamar al servidor y el puerto MQTT
  client.setServer(mqtt_server, 1883);
}


void MQTT::reconnect(void){
  // Mientras el cliente PubSubClient no esté conectado al servidor MQTT
  while (!client.connected()) { 
    Serial.print("Intentando la conexión MQTT..."); 

    // Se define un ID de cliente aleatorio
    String clientId = "ESP32Client-"; 
    // Se agrega un número aleatorio hexadecimal al ID de cliente
    clientId += String(random(0xffff), HEX); 

    // Si la conexión al servidor MQTT tiene éxito
    if (client.connect(clientId.c_str())) { 
      // Se imprime un mensaje indicando que se conectó al servidor MQTT
      Serial.println("conectado"); 
      // Se suscribe al tema "gmcr/recibir"
      client.subscribe("ESIoT/recibir"); 
    } else { // Si la conexión al servidor MQTT falla
     // Se imprime un mensaje indicando que la conexión falló
      Serial.print("fallido, rc =");
      // Se imprime el estado del cliente PubSubClient
      Serial.print(client.state()); 
      // Se indica que se intentará conectar de nuevo en 5 segundos
      Serial.println(" inténtalo de nuevo en 5 segundos"); 
      delay(2000); // Se espera 5 segundos antes de intentar conectarse de nuevo
    }
  }
}

void MQTT::connect(void){
  //Si el cliente se conecta, llamar a funcion reconnect
  if (!client.connected()) {

    reconnect();

  }
  //Bucle para que el cliente siga publicando o suscribiendo mensajes
  client.loop();
 
}


void MQTT::publicar(const char* mensaje){
  client.publish("ESIoT/cobros", mensaje);
}


void MQTT::setup_wifi(){
  delay(10);

  // Empezamos por conectarnos a una red WiFi

  Serial.println();

  Serial.print("Conectado a ");

  Serial.println(ssid);

 

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

 

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

 

  randomSeed(micros());

 

  Serial.println("");

  Serial.println("WiFi conectado");

  Serial.println("Dirección IP: ");

  Serial.println(WiFi.localIP());
}