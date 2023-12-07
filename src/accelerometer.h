#include <Arduino.h>
#include "qma7981.h"
#include "settings.h"

QMA7981 Accel;

void initQma7981(TwoWire *twoWire) {
  Accel.initialize_default(twoWire);           // setup acceleromter with default settings
  Accel.set_full_scale_range(RANGE_4G); // set maximum range (+- 4G)
  Accel.set_bandwidth(MCLK_DIV_BY_975); // set bandwidth (samples per sec)
                                        // = CLK / DIV_BY = 50k / 975 = 50 samples / sec
}

void getAccelerometerMeasurements(accelerations_t *acc) {
  // This should probably be constantly sampled in a separate thread
  uint64_t startTime = millis();
  uint16_t maxX = 0, maxY = 0, maxZ = 0;
  Serial.printf("Sampling accelerometer for %dms\n", ACCEL_SAMPLING_MS); 
  while(true) {

    maxX = _max(maxX, abs(Accel.get_accel_x()));
    maxY = _max(maxY, abs(Accel.get_accel_y()));
    maxZ = _max(maxZ, abs(Accel.get_accel_z()));
    //Serial.printf("%d, %d, %d\n", abs(Accel.get_accel_x()), abs(Accel.get_accel_y()), abs(Accel.get_accel_z()));
    // Sample for ACCEL_SAMPLING_MS milliseconds
    if (millis() - startTime > ACCEL_SAMPLING_MS) {
      break;
    }
  }
  acc->x = maxX;
  acc->y = maxY;
  acc->z = maxZ;

  return;

}