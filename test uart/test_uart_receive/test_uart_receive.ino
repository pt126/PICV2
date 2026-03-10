#include <HardwareSerial.h>



// Definir pinos para UART2
#define RXD2 16
#define TXD2 17
#define BAUDRATE 9600

void setup() {
  Serial.begin(9600);

  // Inicializar UART2 (já existe no core)
  Serial2.begin(BAUDRATE, SERIAL_8N1, RXD2, TXD2);
  Serial.println("UART2 iniciada. Aguardando dados...");
}

void loop() {
  if (Serial2.available()) {
    String recebido = Serial2.readStringUntil('\n');
    Serial.print("Recebido: ");
    Serial.println(recebido);
  }

  delay(2000);
}
