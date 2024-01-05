/* adamController Example



*/

#include <SPI.h>
#include <Ethernet.h>



// These should be depreciated
//#include <ArduinoRS485.h>  // ArduinoModbus depends on the ArduinoRS485 library
//#include <ArduinoModbus.h>

#include "adamController.h"  // Now all modbus is handled internally to adamController class

#include "sensorObj.h"



//sensorObj TS1(VOLTAGE_SENSOR, "degC", "TS1");
//sensorObj TS1(VOLTAGE_SENSOR, "degC", "TS2");
//sensorObj TS1(VOLTAGE_SENSOR, "degC", "TS3");
//sensorObj TS1(VOLTAGE_SENSOR, "degC", "TS4");
//sensorObj TS1(VOLTAGE_SENSOR, "degC", "TS5");
//sensorObj TS1(VOLTAGE_SENSOR, "degC", "TS6");

sensorObj temp_s[6] = {
  sensorObj(VOLTAGE_SENSOR, "v", "TS1"),
  sensorObj(VOLTAGE_SENSOR, "v", "TS2"),
  sensorObj(VOLTAGE_SENSOR, "v", "TS3"),
  sensorObj(VOLTAGE_SENSOR, "v", "TS4"),
  sensorObj(VOLTAGE_SENSOR, "v", "TS5"),
  sensorObj(VOLTAGE_SENSOR, "v", "TS6")
};

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
// The IP address will be dependent on your local network:
byte mac[] = { 0xA8, 0X61, 0x0A, 0xAE, 0xE1, 0x48 };

//Define the ip address for the client (local modbus controller) (the device this firmware is running on)
IPAddress ip(192, 168, 1, 100);

// Define the IP for the server (remote modbus device)
IPAddress adam6052_ip(192, 168, 1, 111);  // update with the IP Address of your Modbus server (the remote IO controller)
IPAddress adam6024_ip(192, 168, 1, 114);  // update with the IP Address of your Modbus server (the remote IO controller)

// Create an Ethernet Client
EthernetClient ethClient;


// Create an adamController object and pass the Ethernet Client and IP Address for the server
adamController adam6052(ethClient, adam6052_ip, DAC_OUTPUT, "ADAM-6052-A");
adamController adam6024(ethClient, adam6024_ip, DAC_OUTPUT, "ADAM-6024-B");




void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  Serial.println("\n");
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("\nAdvantec ADAM industrial Controller Library - Example");
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Arduino: Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1);  // do nothing, no point running without Ethernet hardware
    }
  }

  delay(500);

  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Arduino: Ethernet cable is not connected.");
  }

  // adam6052.begin();
  adam6024.begin();
  delay(1000);
  // adam6052.set_coils(0b00000000);
  // init Temp Sensors
  for (int i = 0; i < 6; i++) {
    temp_s[i].set_range_min(-10);
    temp_s[i].set_range_max(10);
    temp_s[i].setCalibration();
  }
}


uint16_t iteration = 0;


void loop() {
  Serial.print("\nArduino: Iteration: ");
  Serial.println(iteration);


  // TS1.updateHistory();

  adamAnalogController();
  // adamDigitalController();


  delay(2000);
  iteration++;
}


void adamAnalogController() {
  adam6024.check_modbus_connect();

  adam6024.read_analog_inputs();

  for (int i = 0; i < 6; i++) {
    Serial.print(adam6024.d_array.i_data[i]);
    Serial.print(" : ");
    float voltage = temp_s[i].calcProcessVar(adam6024.d_array.i_data[i]);
    Serial.print(" ");
    Serial.print(voltage);
    Serial.print(" V, ");
    temp_s[i].updateHistory(voltage);
    Serial.println("");
  }
  Serial.println("");
}


void adamDigitalController() {

  adam6052.check_modbus_connect();
  int error;
  int randomVal = random(256);
  if (adam6052.modbusConnected) {
    error = adam6052.set_coils(randomVal);
    if (error == -1) {
      Serial.println("Arduino: Error setting coils");
    }
    int value = adam6052.read_coils();
    if (value == randomVal) {
      Serial.println("Arduino: values match coils written successfully");
    } else {
      Serial.println("Arduino: Error: Mismatch between coils written & coils read");
    }
    adam6052.read_digital_inputs();
  }  // if modbusConnected
  else {
    Serial.println("Arduino: Error: Modbus connection dropped");
  }
}


// Comment here for reasons