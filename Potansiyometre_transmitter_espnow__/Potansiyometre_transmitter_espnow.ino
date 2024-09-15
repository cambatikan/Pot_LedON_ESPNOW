#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xE0,0x5A,0x1B,0xA7,0x17,0x74}; // Alıcı ESP32 MAC adresi
int potPin = 33;
int potValue;

typedef struct struct_message {
  int potValue;
} struct_message;

struct_message myData;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\nVeri Gönderildi, Durum: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Başarılı" : "Başarısız");
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı");
    return;
  }
  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;


  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Alıcı eklenemedi");
    return;
  }
}

void loop() {
  potValue = analogRead(potPin);

  myData.potValue = potValue;
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));


  Serial.print("Gönderilen Potansiyometre Değeri: ");
  Serial.println(potValue);

  delay(500);
}
