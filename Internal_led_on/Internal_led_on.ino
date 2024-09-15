#include <esp_now.h>
#include <WiFi.h>


typedef struct struct_message {
  int potValue;
} struct_message;

const int ledPin= 2; 


void OnDataRecv(const esp_now_recv_info* info, const uint8_t* incomingData, int len) {
  struct_message* data = (struct_message*)incomingData;
  
  int potValue = data->potValue;

if(potValue<=2050){
    digitalWrite(ledPin, LOW);
  else{
   digitalWrite(ledPin, HIGH);
  }
  
  Serial.print("Alınan Potansiyometre Değeri: ");
  Serial.println(potValue);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  
  delay(1000);
}
