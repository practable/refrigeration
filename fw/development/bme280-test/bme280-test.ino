/*   bme280-test
    

Program size using Adafruit BME280 library
```
Sketch uses 14792 bytes (5%) of program storage space. Maximum is 253952 bytes.
Global variables use 870 bytes (10%) of dynamic memory, leaving 7322 bytes for local variables. Maximum is 8192 bytes.
```

After doing basic F(String Macro) Update
```
Sketch uses 14804 bytes (5%) of program storage space. Maximum is 253952 bytes.
Global variables use 490 bytes (5%) of dynamic memory, leaving 7702 bytes for local variables. Maximum is 8192 bytes.
```
Saved half of dynamic memory with simple update.

## Back up to 6% dynamic memory before big re-write

## i2c pins for Arduino Mega:
SCL 21
SDA 20



*/


#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C


unsigned long delayTime;

void setup() {
    Serial.begin(115200);
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;
    //Wire.begin(0x76);
    // default settings
  status = bme.begin(0x76); 
    Serial.print("Status Update: ");
    Serial.println(status); 
    // You can also pass in a Wire library object like &Wire2
  // status = bme.begin(0x76, &Wire);
    while (!status) {
        Serial.println(F("Could not find a valid BME280 sensor, check wiring, address, sensor ID!"));
        Serial.print(F("SensorID was: 0x"));
        Serial.println(bme.sensorID(),16);
        Serial.print(F("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n"));
        Serial.print(F("   ID of 0x56-0x58 represents a BMP 280,\n"));
        Serial.print(F("        ID of 0x60 represents a BME 280.\n"));
        Serial.print(F("        ID of 0x61 represents a BME 680.\n"));
        delay(5000);
    }
    
    Serial.println(F("-- Default Test --"));
    delayTime = 1000;

    Serial.println();
}


void loop() { 
    printValues();
    delay(delayTime);
}


void printValues() {
  char buffer [64];
  
    Serial.print(F("Temperature = "));
    Serial.print(bme.readTemperature());
    Serial.println(F(" °C"));

    Serial.print(F("Pressure = "));

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(F(" hPa"));

    Serial.print(F("Approx. Altitude = "));
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(F(" m"));

    Serial.print(F("Humidity = "));
    Serial.print(bme.readHumidity());
    Serial.println(F(" %"));

    Serial.println();
}
