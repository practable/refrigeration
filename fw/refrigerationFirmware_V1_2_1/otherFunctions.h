/*   otherFunctions.h

  All other utility and setup functions



*/




void serial_begin() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  //Serial.println(F("\n"));
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
 Serial.println(F("{\"model\":\"frig00\",\"version\":\"refrigerationFirmware-V1.2.1\"}"));
}





void ethernet_begin() {
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println(F("{\"error\":\"Arduino: Ethernet shield was not found. Can't run without hardware\"}"));
    while (true) {
      delay(1);  // do nothing, no point running without Ethernet hardware
    }
  }
  delay(500);
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println(F("{\"error\":\"Arduino: Ethernet cable is not connected.\"}"));
  }
}
