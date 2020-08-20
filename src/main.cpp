#include <Arduino.h>
#include <M5StickC.h>
#include <esp_now.h>
#include <WiFi.h>

// uint8_t Address[] = {0x50, 0x02, 0x91, 0x8D, 0x21, 0x14}; //HAS GREEN MARK
uint8_t Address[] = {0x50, 0x02, 0x91, 0x8D, 0xD9, 0x60};

typedef struct struct_message {
    float x;
    float y;
    float z;
} struct_message;

float x;
float y;
float z;

float incomingX;
float incomingY;
float incomingZ;


struct_message tx_message;
struct_message rx_message;

String success;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&rx_message, incomingData, sizeof(rx_message));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingX = rx_message.x;
  incomingY = rx_message.y;
  incomingZ = rx_message.z;
}

void updateDisplay();

void setup(void) {
  Serial.begin(115200);

  M5.begin();
  M5.IMU.Init();
  M5.Lcd.setRotation(0);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, Address, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

 
}

void loop() {
  M5.IMU.getAccelData(&x,&y,&z);

  tx_message.x = x;
  tx_message.y = y;
  tx_message.z = z;

  esp_err_t result = esp_now_send(Address, (uint8_t *) &tx_message, sizeof(tx_message));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  updateDisplay();

  delay(25);
}

void updateDisplay()
{
  M5.Lcd.fillScreen(TFT_DARKGREY);
  M5.Lcd.setCursor(5, 5, 2);
  M5.Lcd.setTextColor(TFT_ORANGE); 
  M5.Lcd.println("SHAKE IT!"); 
  M5.Lcd.setCursor(0, 25, 4);
  M5.Lcd.println(incomingX);
  M5.Lcd.println(incomingY);
  M5.Lcd.println(incomingZ);
}
