#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include "settings.h"

Adafruit_BME280 bme; // use I2C interface
Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();

void initBme280(TwoWire *i2cBus) {



  if (!bme.begin(BME_I2C_ADDR, i2cBus)) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    return;
  } else {
    Serial.println(F("Succesfully started BME sensor"));
  }
  
  bme_temp->printSensorDetails();
  bme_pressure->printSensorDetails();
  bme_humidity->printSensorDetails();
}

void getBme280Measurement(sensors_event_t *temp_event, sensors_event_t *pressure_event, sensors_event_t *humidity_event) {

    bme_temp->getEvent(temp_event);
    bme_pressure->getEvent(pressure_event);
    bme_humidity->getEvent(humidity_event);

    return;
}