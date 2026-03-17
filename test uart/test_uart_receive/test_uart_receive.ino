// #include <HardwareSerial.h>

// #define RXD2 16
// #define TXD2 17
// #define BAUDRATE 9600

// void setup() {
//   Serial.begin(9600);
//   Serial2.begin(BAUDRATE, SERIAL_8N1, RXD2, TXD2);
//   Serial.println("UART2 started. Waiting for data...");
// }

// void loop() {
//   if (Serial2.available()) {
//     String received = Serial2.readStringUntil('\n');
//     Serial.print("Received: ");
//     Serial.println(received);
//   }
// }



#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

#define RXD2 16
#define TXD2 17
#define BAUDRATE 9600

String uartMessage = "";

// ---------------- LoRaWAN KEYS (OTAA) ----------------
static const u1_t PROGMEM APPEUI[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
static const u1_t PROGMEM DEVEUI[8] = { 0x70,0x5E,0x07,0xD0,0x7E,0xD5,0xB3,0x70 };
static const u1_t PROGMEM APPKEY[16] = { 
  0x39,0x53,0xFD,0xAF,0xA3,0x04,0x6F,0x90,
  0x14,0xDB,0xC1,0x67,0xCF,0xD1,0xA8,0x20
};

void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8); }
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8); }
void os_getDevKey (u1_t* buf) { memcpy_P(buf, APPKEY, 16); }

// ---------------- PIN MAP ----------------
const lmic_pinmap lmic_pins = {
  .nss = 4,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 21,
  .dio = {22, 15, LMIC_UNUSED_PIN}
};

static osjob_t sendjob;

void do_send(osjob_t* j) {
  if (LMIC.opmode & OP_TXRXPEND) {
    Serial.println("TX pendente, não envio.");
    return;
  }

  if (uartMessage.length() == 0) {
    Serial.println("Sem mensagem UART para enviar.");
    return;
  }

  int len = uartMessage.length();
  if (len > 51) len = 51;

  LMIC_setTxData2(1, (uint8_t*)uartMessage.c_str(), len, 0);

  Serial.print("LoRaWAN enviou: ");
  Serial.println(uartMessage);

  uartMessage = "";
}

void onEvent(ev_t ev) {
  Serial.print("EVENTO: ");
  Serial.println(ev);

  if (ev == EV_JOINED) {
    Serial.println("LoRaWAN JOIN OK!");
    LMIC_setLinkCheckMode(0);
  }

  if (ev == EV_TXCOMPLETE) {
    Serial.println("TX completo.");
  }
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  Serial.println("Iniciando LoRaWAN...");

  os_init();
  LMIC_reset();
  LMIC_setClockError(MAX_CLOCK_ERROR * 1 / 100);

  do_send(&sendjob);
}

void loop() {
  if (Serial2.available()) {
    uartMessage = Serial2.readStringUntil('\n');
    uartMessage.trim();
    Serial.print("UART recebeu: ");
    Serial.println(uartMessage);

    do_send(&sendjob);
  }

  os_runloop_once();
}

