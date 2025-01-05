#pragma once 

#include <BluetoothSerial.h>

class Bluetooth {
  public:
  Bluetooth();
  String get_message();

 private:
  BluetoothSerial m_bt_serial;
};

