#include "bluetooth.h"

Bluetooth::Bluetooth() {
  Serial.println("Bluetooth avaiable");
  m_bt_serial.begin("Nissan");
}

String Bluetooth::get_message() {
  String msg = "";
  while (m_bt_serial.available()) {
    char ch = m_bt_serial.read();
    msg += ch;
  }

  // Remove LF
  while (msg.indexOf(10) != -1) {
    msg.remove(msg.indexOf(10));
  }

  // Remove CR
  while (msg.indexOf(13) != -1) {
    msg.remove(msg.indexOf(13));
  }

  return msg;
}
