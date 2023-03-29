#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#define PIR_PIN 12 // Cambia el número del pin según corresponda

// Debes cambiar estos valores por los de tu red Wi-Fi
const char* ssid = "Torre C Labs";
const char* password = "1q2w3e4r5t";

// Dirección IP de la otra ESP32
IPAddress serverIP(192, 168, 90, 58);


// Puerto por el que se realizará la comunicación
int serverPort = 80;

// Port number for the server
//int serverPort = 1234;

// Buzzer pin
int buzzerPin = 21;

// WiFi client and server objects
WiFiClient cliente;
WiFiServer server(serverPort);

void setup() {
  // Start serial communication
  Serial.begin(9600);
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi network");
  
  // Start server
  server.begin();
  Serial.println("Server started");
  
  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), deteccionMovimiento, RISING);
}

void loop() {
  // Check if there is a client connected to the server
  if (server.hasClient()) {
    // Accept the connection
    cliente = server.available();
    Serial.println("Cliente conectado");
    
    // Wait for data to be received
    while (cliente.connected() && !cliente.available()) {
      delay(1);
    }
    
    // Read the data from the client
    String message = cliente.readStringUntil('\n');
    Serial.println("Mensaje Recibido: " + message);
    
    // Check if the message is the expected one
    if (message = 1) {
      // Activate the buzzer
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
    }
    
    // Disconnect from the client
    cliente.stop();
    Serial.println("Cliente desconectado");
    delay(10000);
  }
  
  // Wait a bit before checking for new connections
  delay(100);
} 
void deteccionMovimiento() {
  Serial.println("Movimiento detectado, el sistema se detendra");
  // Detener el sistema por 10 segundos
  delay(10000);
  // Activar el sistema de nuevo
  Serial.println("El sistema se ha reactivado");
}