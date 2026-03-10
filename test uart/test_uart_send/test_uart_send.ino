#include <HardwareSerial.h>

// Definir pinos para UART2
#define RXD2 16
#define TXD2 17
#define BAUDRATE 115200

// Criar objeto serial
HardwareSerial Serial2(2);

void setup() {
  // Serial de depuração (USB)
  Serial.begin(115200);
  
  // Inicializar UART2
  Serial2.begin(BAUDRATE, SERIAL_8N1, RXD2, TXD2);
  Serial.println("UART2 iniciada. Aguardando dados...");
}

void loop() {
  // Enviar dados a cada 2 segundos
  Serial2.println("Ola do ESP32 UART2");
  
  // // Verificar se há dados recebidos na UART2
  // if (Serial2.available()) {
  //   String recebido = Serial2.readStringUntil('\n');
  //   Serial.print("Recebido: ");
  //   Serial.println(recebido);
  // }
  
  delay(2000);
}
