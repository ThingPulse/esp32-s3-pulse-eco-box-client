/**
   BasicHTTPSClient.ino

    Created on: 14.10.2018

*/

#include <Arduino.h>

#include "network.h"
#include "pm-sensor.h"
#include "bme280.h"
#include "accelerometer.h"

struct sps30_measurement spsdata;
sensors_event_t temp_event, pressure_event, humidity_event;
accelerations_t accelerations;

TwoWire i2cBus = TwoWire(1); //I2C1 bus

void setup() {
  // For development only, to see startup messages
  delay(3000);
  Serial.begin(115200);
  SER.printf("Total heap: %d\n", ESP.getHeapSize());
  SER.printf("Free heap: %d\n", ESP.getFreeHeap());
  SER.printf("Total PSRAM: %d\n", ESP.getPsramSize());
  SER.printf("Free PSRAM: %d\n", ESP.getFreePsram());
  SER.println("Started");

  // The sensirion sensor has its own I2C bus
  Wire.begin(SPS_SDA, SPS_SCL);
  pmInit();

  // Initialize the 
  i2cBus.setPins(I2C_SDA, I2C_SCL);
  initBme280(&i2cBus);
  initQma7981(&i2cBus);

  // enable to send data
  // connectWifi();
  // setClock();  
}


void loop() {
  getPmMeasurement(&spsdata);
  Serial.printf("PM 0.5: %f, 1.0: %f, 2.5: %f\n", spsdata.nc_0p5, spsdata.nc_1p0 - spsdata.nc_0p5, spsdata.nc_2p5 - spsdata.nc_1p0);


  getBme280Measurement(&temp_event, &pressure_event, &humidity_event);
  Serial.printf("BME280 Temp: %f, Pressure: %f, Humidity: %f\n", temp_event.temperature, pressure_event.pressure, humidity_event.relative_humidity);

  getAccelerometerMeasurements(&accelerations);
  Serial.printf("Acc x: %d, y: %d, z: %d\n", accelerations.x, accelerations.y, accelerations.z);

  // enable to send data
  //sendData(spsdata.nc_2p5, spsdata.nc_10p0);
  Serial.println();
  Serial.println("Waiting 10s before the next round...");
  delay(10000);
}
