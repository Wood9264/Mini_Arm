# 蓝牙Xbox断线重连修复
```
void onLoop() {
    //数据超时判断
    if (isConnected()) {
      // 检测数据超时（如 2 秒无数据视为断线）
      if (millis() - receivedNotificationAt > 1000) {
        Serial.println("Force disconnect due to timeout");
        // 强制转化为扫描模式
        connectionState = ConnectionState::Scanning;
        if (pConnectedClient) {
          pConnectedClient->disconnect();
        }
      }
    }

    if (!isConnected()) {
      receivedNotificationAt = 0;
      receivedBatteryAt = 0;
      if (advDevice != nullptr) {
        auto connectionResult = connectToServer(advDevice);
        if (!connectionResult || !isConnected()) {
          NimBLEDevice::deleteBond(advDevice->getAddress());
          ++countFailedConnection;
          // reset();
          connectionState = ConnectionState::Scanning;
        } else {
          countFailedConnection = 0;
        }
        advDevice = nullptr;

      } else if (!isScanning()) {
        // reset();
        startScan();
      }
    }
  }
  ```