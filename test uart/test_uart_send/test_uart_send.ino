#include <HardwareSerial.h>

#define RXD2 16
#define TXD2 17
#define BAUDRATE 9600

void setup() {
  // Serial USB para debug
  Serial.begin(9600);
  delay(1000);

  Serial.println();
  Serial.println("A iniciar...");

  // UART2
  Serial2.begin(BAUDRATE, SERIAL_8N1, RXD2, TXD2);

  Serial.print("UART2 iniciada com baudrate = ");
  Serial.println(BAUDRATE);
  Serial.print("TXD2 = GPIO ");
  Serial.println(TXD2);
  Serial.print("RXD2 = GPIO ");
  Serial.println(RXD2);
}

void loop() {
  String mensagem = "Ola do ESP32 UART2";

  // Enviar pela UART2
  Serial2.println(mensagem);

  // Mostrar no Serial Monitor o que foi enviado
  Serial.print("Enviado pela UART2: ");
  Serial.println(mensagem);

  delay(2000);
}
