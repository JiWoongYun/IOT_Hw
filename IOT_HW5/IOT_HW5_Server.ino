#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE Server...");

  // BLE 초기화
  BLEDevice::init("BLE_Distance_Server");  // 📢 Client에서 이 이름으로 스캔 필터링함

  // BLE Server 생성
  BLEServer *pServer = BLEDevice::createServer();

  // 서비스 생성 (UUID는 자유롭게 사용 가능)
  BLEService *pService = pServer->createService("12345678-1234-1234-1234-1234567890ab");

  // 특성 생성 (Read만 허용 - 실제 통신은 하지 않음)
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    "abcd",
    BLECharacteristic::PROPERTY_READ
  );

  pCharacteristic->setValue("Hello BLE Client");
  pService->start();

  // 광고 시작
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID("12345678-1234-1234-1234-1234567890ab");
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x06);  // compatibility
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("BLE Advertising started...");
}

void loop() {
  // 아무 것도 안 해도 됨 — Advertising만 하면 됨
  delay(1000);
}
